/*
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * Contributor(s): Blender Foundation
 *
 * ***** END GPL LICENSE BLOCK *****
 *
 */

/** \file blender/blenloader/intern/versioning_defaults.c
 *  \ingroup blenloader
 */

#include "BLI_utildefines.h"
#include "BLI_listbase.h"
#include "BLI_math.h"

#include "DNA_brush_types.h"
#include "DNA_freestyle_types.h"
#include "DNA_linestyle_types.h"
#include "DNA_scene_types.h"
#include "DNA_screen_types.h"
#include "DNA_space_types.h"
#include "DNA_userdef_types.h"
#include "DNA_mesh_types.h"
#include "DNA_material_types.h"
#include "DNA_object_types.h"

#include "BKE_brush.h"
#include "BKE_library.h"
#include "BKE_main.h"

#include "BLO_readfile.h"


/**
 * Override values in in-memory startup.blend, avoids resaving for small changes.
 */
void BLO_update_defaults_userpref_blend(void)
{
	/* defaults from T37518 */

	U.uiflag |= USER_ZBUF_CURSOR;
	U.uiflag |= USER_QUIT_PROMPT;
	U.uiflag |= USER_CONTINUOUS_MOUSE;

	U.versions = 1;
	U.savetime = 2;

	/* default from T47064 */
	U.audiorate = 48000;
}

/**
 * Update defaults in startup.blend, without having to save and embed the file.
 * This function can be emptied each time the startup.blend is updated. */
void BLO_update_defaults_startup_blend(Main *bmain)
{
	Scene *scene;
	SceneRenderLayer *srl;
	FreestyleLineStyle *linestyle;
	Mesh *me;
	Material *mat;

	for (scene = bmain->scene.first; scene; scene = scene->id.next) {
		scene->r.im_format.planes = R_IMF_PLANES_RGBA;
		scene->r.im_format.compress = 15;

		for (srl = scene->r.layers.first; srl; srl = srl->next) {
			srl->freestyleConfig.sphere_radius = 0.1f;
			srl->pass_alpha_threshold = 0.5f;
		}

		if (scene->toolsettings) {
			ToolSettings *ts = scene->toolsettings;

			if (ts->sculpt) {
				Sculpt *sculpt = ts->sculpt;
				sculpt->paint.symmetry_flags |= PAINT_SYMM_X;
				sculpt->flags |= SCULPT_DYNTOPO_COLLAPSE;
				sculpt->detail_size = 12;
			}
			
			if (ts->gp_sculpt.brush[0].size == 0) {
				GP_BrushEdit_Settings *gset = &ts->gp_sculpt;
				GP_EditBrush_Data *brush;
				
				brush = &gset->brush[GP_EDITBRUSH_TYPE_SMOOTH];
				brush->size = 25;
				brush->strength = 0.3f;
				brush->flag = GP_EDITBRUSH_FLAG_USE_FALLOFF | GP_EDITBRUSH_FLAG_SMOOTH_PRESSURE;
				
				brush = &gset->brush[GP_EDITBRUSH_TYPE_THICKNESS];
				brush->size = 25;
				brush->strength = 0.5f;
				brush->flag = GP_EDITBRUSH_FLAG_USE_FALLOFF;
				
				brush = &gset->brush[GP_EDITBRUSH_TYPE_GRAB];
				brush->size = 50;
				brush->strength = 0.3f;
				brush->flag = GP_EDITBRUSH_FLAG_USE_FALLOFF;
				
				brush = &gset->brush[GP_EDITBRUSH_TYPE_PUSH];
				brush->size = 25;
				brush->strength = 0.3f;
				brush->flag = GP_EDITBRUSH_FLAG_USE_FALLOFF;
				
				brush = &gset->brush[GP_EDITBRUSH_TYPE_TWIST];
				brush->size = 50;
				brush->strength = 0.3f; // XXX?
				brush->flag = GP_EDITBRUSH_FLAG_USE_FALLOFF;
				
				brush = &gset->brush[GP_EDITBRUSH_TYPE_PINCH];
				brush->size = 50;
				brush->strength = 0.5f; // XXX?
				brush->flag = GP_EDITBRUSH_FLAG_USE_FALLOFF;
				
				brush = &gset->brush[GP_EDITBRUSH_TYPE_RANDOMIZE];
				brush->size = 25;
				brush->strength = 0.5f;
				brush->flag = GP_EDITBRUSH_FLAG_USE_FALLOFF;
			}
			
			ts->gpencil_v3d_align = GP_PROJECT_VIEWSPACE;
			ts->gpencil_v2d_align = GP_PROJECT_VIEWSPACE;
			ts->gpencil_seq_align = GP_PROJECT_VIEWSPACE;
			ts->gpencil_ima_align = GP_PROJECT_VIEWSPACE;
		}

		scene->gm.lodflag |= SCE_LOD_USE_HYST;
		scene->gm.scehysteresis = 10;

		scene->r.ffcodecdata.audio_mixrate = 48000;
	}

	for (linestyle = bmain->linestyle.first; linestyle; linestyle = linestyle->id.next) {
		linestyle->flag = LS_SAME_OBJECT | LS_NO_SORTING | LS_TEXTURE;
		linestyle->sort_key = LS_SORT_KEY_DISTANCE_FROM_CAMERA;
		linestyle->integration_type = LS_INTEGRATION_MEAN;
		linestyle->texstep = 1.0;
		linestyle->chain_count = 10;
	}

	{
		bScreen *screen;

		for (screen = bmain->screen.first; screen; screen = screen->id.next) {
			ScrArea *area;
			for (area = screen->areabase.first; area; area = area->next) {
				SpaceLink *space_link;
				ARegion *ar;

				for (space_link = area->spacedata.first; space_link; space_link = space_link->next) {
					if (space_link->spacetype == SPACE_CLIP) {
						SpaceClip *space_clip = (SpaceClip *) space_link;
						space_clip->flag &= ~SC_MANUAL_CALIBRATION;
					}
				}

				for (ar = area->regionbase.first; ar; ar = ar->next) {
					/* Remove all stored panels, we want to use defaults (order, open/closed) as defined by UI code here! */
					BLI_freelistN(&ar->panels);

					/* simple fix for 3d view properties scrollbar being not set to top */
					if (ar->regiontype == RGN_TYPE_UI) {
						float offset = ar->v2d.tot.ymax - ar->v2d.cur.ymax;
						ar->v2d.cur.ymax += offset;
						ar->v2d.cur.ymin += offset;
					}
				}
			}
		}
	}

	for (me = bmain->mesh.first; me; me = me->id.next) {
		me->smoothresh = DEG2RADF(180.0f);
		me->flag &= ~ME_TWOSIDED;
	}

	for (mat = bmain->mat.first; mat; mat = mat->id.next) {
		mat->line_col[0] = mat->line_col[1] = mat->line_col[2] = 0.0f;
		mat->line_col[3] = 1.0f;
	}

	{
		Brush *br;

		br = (Brush *)BKE_libblock_find_name_ex(bmain, ID_BR, "Fill");
		if (!br) {
			br = BKE_brush_add(bmain, "Fill", OB_MODE_TEXTURE_PAINT);
			br->imagepaint_tool = PAINT_TOOL_FILL;
			br->ob_mode = OB_MODE_TEXTURE_PAINT;
		}

		br = (Brush *)BKE_libblock_find_name_ex(bmain, ID_BR, "Mask");
		if (br) {
			br->imagepaint_tool = PAINT_TOOL_MASK;
			br->ob_mode |= OB_MODE_TEXTURE_PAINT;
		}

		/* remove polish brush (flatten/contrast does the same) */
		br = (Brush *)BKE_libblock_find_name_ex(bmain, ID_BR, "Polish");
		if (br) {
			BKE_libblock_free(bmain, br);
		}

		/* remove brush brush (huh?) from some modes (draw brushes do the same) */
		br = (Brush *)BKE_libblock_find_name_ex(bmain, ID_BR, "Brush");
		if (br) {
			BKE_libblock_free(bmain, br);
		}

		/* remove draw brush from texpaint (draw brushes do the same) */
		br = (Brush *)BKE_libblock_find_name_ex(bmain, ID_BR, "Draw");
		if (br) {
			br->ob_mode &= ~OB_MODE_TEXTURE_PAINT;
		}

		/* rename twist brush to rotate brush to match rotate tool */
		br = (Brush *)BKE_libblock_find_name_ex(bmain, ID_BR, "Twist");
		if (br) {
			BKE_libblock_rename(bmain, &br->id, "Rotate");
		}
	}
	
	
	/* Pose Sculpt... */
	{
		Scene *scene;
		
		/* init defaults for pose sculpt settings 
		 * ! Keep in sync with blenkernel/scene.c - BKE_scene_init()
		 */
		for (scene = bmain->scene.first; scene; scene = scene->id.next) {
			PSculptSettings *pset = &scene->toolsettings->psculpt;
			
			if (pset->brush[0].size == 0) {
				int i;
				
				for (i = 0; i < PSCULPT_TOT_BRUSH; i++) {
					pset->brush[i].strength = 0.5f;
					pset->brush[i].size = 50;
					pset->brush[i].rate = 0.01f;
					pset->brush[i].flag = PSCULPT_BRUSH_FLAG_USE_PRESSURE | PSCULPT_BRUSH_FLAG_USE_FALLOFF;
					
					pset->brush[i].bulge = 1.0f;
					pset->brush[i].bulge_min = 1.0f;
					pset->brush[i].bulge_max = 1.0f;
				}
				pset->brush[PSCULPT_BRUSH_SMOOTH].strength = 0.25f;
				pset->brush[PSCULPT_BRUSH_GRAB].strength = 1.0f;
				pset->brush[PSCULPT_BRUSH_CURL].strength = 0.25f;
				pset->brush[PSCULPT_BRUSH_TWIST].strength = 0.25f;
				//pset->brush[PSCULPT_BRUSH_RESET].strength = 1.0f;
				pset->brush[PSCULPT_BRUSH_CURL].xzMode = PSCULPT_BRUSH_DO_X;
				pset->brush[PSCULPT_BRUSH_GRAB].flag |= PSCULPT_BRUSH_FLAG_GRAB_INITIAL;
				pset->brush[PSCULPT_BRUSH_STRETCH].flag |= PSCULPT_BRUSH_FLAG_VOL_PRESERVE;
			}
		}
	}

}

