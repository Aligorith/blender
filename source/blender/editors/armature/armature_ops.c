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
 * The Original Code is Copyright (C) 2009 Blender Foundation.
 * All rights reserved.
 *
 * 
 * Contributor(s): Blender Foundation
 *
 * ***** END GPL LICENSE BLOCK *****
 */

/** \file blender/editors/armature/armature_ops.c
 *  \ingroup edarmature
 */

#include "RNA_access.h"

#include "WM_api.h"
#include "WM_types.h"

#include "ED_armature.h"
#include "ED_screen.h"
#include "ED_transform.h"

#include "armature_intern.h"

/* ************************** registration **********************************/

/* Both operators ARMATURE_OT_xxx and POSE_OT_xxx here */
void ED_operatortypes_armature(void)
{
	/* EDIT ARMATURE */
	WM_operatortype_append(ARMATURE_OT_bone_primitive_add);
	
	WM_operatortype_append(ARMATURE_OT_align);
	WM_operatortype_append(ARMATURE_OT_calculate_roll);
	WM_operatortype_append(ARMATURE_OT_switch_direction);
	WM_operatortype_append(ARMATURE_OT_subdivide);
	
	WM_operatortype_append(ARMATURE_OT_parent_set);
	WM_operatortype_append(ARMATURE_OT_parent_clear);
	
	WM_operatortype_append(ARMATURE_OT_select_all);
	WM_operatortype_append(ARMATURE_OT_select_mirror);
	WM_operatortype_append(ARMATURE_OT_select_more);
	WM_operatortype_append(ARMATURE_OT_select_less);
	WM_operatortype_append(ARMATURE_OT_select_hierarchy);
	WM_operatortype_append(ARMATURE_OT_select_linked);
	WM_operatortype_append(ARMATURE_OT_select_similar);
	WM_operatortype_append(ARMATURE_OT_shortest_path_pick);

	WM_operatortype_append(ARMATURE_OT_delete);
	WM_operatortype_append(ARMATURE_OT_dissolve);
	WM_operatortype_append(ARMATURE_OT_duplicate);
	WM_operatortype_append(ARMATURE_OT_symmetrize);
	WM_operatortype_append(ARMATURE_OT_extrude);
	WM_operatortype_append(ARMATURE_OT_hide);
	WM_operatortype_append(ARMATURE_OT_reveal);
	WM_operatortype_append(ARMATURE_OT_click_extrude);
	WM_operatortype_append(ARMATURE_OT_fill);
	WM_operatortype_append(ARMATURE_OT_merge);
	WM_operatortype_append(ARMATURE_OT_separate);
	WM_operatortype_append(ARMATURE_OT_split);
	
	WM_operatortype_append(ARMATURE_OT_autoside_names);
	WM_operatortype_append(ARMATURE_OT_flip_names);
	
	WM_operatortype_append(ARMATURE_OT_layers_show_all);
	WM_operatortype_append(ARMATURE_OT_armature_layers);
	WM_operatortype_append(ARMATURE_OT_bone_layers);

	/* SKETCH */
	WM_operatortype_append(SKETCH_OT_gesture);
	WM_operatortype_append(SKETCH_OT_delete);
	WM_operatortype_append(SKETCH_OT_draw_stroke);
	WM_operatortype_append(SKETCH_OT_draw_preview);
	WM_operatortype_append(SKETCH_OT_finish_stroke);
	WM_operatortype_append(SKETCH_OT_cancel_stroke);
	WM_operatortype_append(SKETCH_OT_convert);
	WM_operatortype_append(SKETCH_OT_select);

	/* POSE */
	WM_operatortype_append(POSE_OT_hide);
	WM_operatortype_append(POSE_OT_reveal);
	
	WM_operatortype_append(POSE_OT_armature_apply);
	WM_operatortype_append(POSE_OT_visual_transform_apply);
	
	WM_operatortype_append(POSE_OT_rot_clear);
	WM_operatortype_append(POSE_OT_loc_clear);
	WM_operatortype_append(POSE_OT_scale_clear);
	WM_operatortype_append(POSE_OT_transforms_clear);
	WM_operatortype_append(POSE_OT_user_transforms_clear);
	
	WM_operatortype_append(POSE_OT_copy);
	WM_operatortype_append(POSE_OT_paste);
	
	WM_operatortype_append(POSE_OT_select_all);

	WM_operatortype_append(POSE_OT_select_parent);
	WM_operatortype_append(POSE_OT_select_hierarchy);
	WM_operatortype_append(POSE_OT_select_linked);
	WM_operatortype_append(POSE_OT_select_constraint_target);
	WM_operatortype_append(POSE_OT_select_grouped);
	WM_operatortype_append(POSE_OT_select_mirror);
	
	WM_operatortype_append(POSE_OT_group_add);
	WM_operatortype_append(POSE_OT_group_remove);
	WM_operatortype_append(POSE_OT_group_move);
	WM_operatortype_append(POSE_OT_group_sort);
	WM_operatortype_append(POSE_OT_group_assign);
	WM_operatortype_append(POSE_OT_group_unassign);
	WM_operatortype_append(POSE_OT_group_select);
	WM_operatortype_append(POSE_OT_group_deselect);
	
	WM_operatortype_append(POSE_OT_paths_calculate);
	WM_operatortype_append(POSE_OT_paths_update);
	WM_operatortype_append(POSE_OT_paths_clear);
	
	WM_operatortype_append(POSE_OT_autoside_names);
	WM_operatortype_append(POSE_OT_flip_names);
	
	WM_operatortype_append(POSE_OT_rotation_mode_set);

	WM_operatortype_append(POSE_OT_quaternions_flip);
	
	WM_operatortype_append(POSE_OT_bone_layers);
	
	WM_operatortype_append(POSE_OT_propagate);
	
	/* POSELIB */
	WM_operatortype_append(POSELIB_OT_browse_interactive);
	WM_operatortype_append(POSELIB_OT_apply_pose);
	
	WM_operatortype_append(POSELIB_OT_pose_add);
	WM_operatortype_append(POSELIB_OT_pose_remove);
	WM_operatortype_append(POSELIB_OT_pose_rename);
	
	WM_operatortype_append(POSELIB_OT_new);
	WM_operatortype_append(POSELIB_OT_unlink);
	
	WM_operatortype_append(POSELIB_OT_action_sanitize);
	
	/* POSE SLIDING */
	WM_operatortype_append(POSE_OT_push);
	WM_operatortype_append(POSE_OT_relax);
	WM_operatortype_append(POSE_OT_breakdown);
	
	/* POSE SKETCHING */
	WM_operatortype_append(POSE_OT_sketch_direct);
	
	/* POSE SCULPTING */
	WM_operatortype_append(POSE_OT_brush_paint);
	WM_operatortype_append(POSE_OT_brush_set);
}

void ED_operatormacros_armature(void)
{
	wmOperatorType *ot;
	wmOperatorTypeMacro *otmacro;

	ot = WM_operatortype_append_macro("ARMATURE_OT_duplicate_move", "Duplicate",
	                                  "Make copies of the selected bones within the same armature and move them",
	                                  OPTYPE_UNDO | OPTYPE_REGISTER);
	WM_operatortype_macro_define(ot, "ARMATURE_OT_duplicate");
	otmacro = WM_operatortype_macro_define(ot, "TRANSFORM_OT_translate");
	RNA_enum_set(otmacro->ptr, "proportional", 0);

	ot = WM_operatortype_append_macro("ARMATURE_OT_extrude_move", "Extrude",
	                                  "Create new bones from the selected joints and move them",
	                                  OPTYPE_UNDO | OPTYPE_REGISTER);
	otmacro = WM_operatortype_macro_define(ot, "ARMATURE_OT_extrude");
	RNA_boolean_set(otmacro->ptr, "forked", false);
	otmacro = WM_operatortype_macro_define(ot, "TRANSFORM_OT_translate");
	RNA_enum_set(otmacro->ptr, "proportional", 0);

	/* XXX would it be nicer to just be able to have standard extrude_move, but set the forked property separate?
	 * that would require fixing a properties bug 19733 */
	ot = WM_operatortype_append_macro("ARMATURE_OT_extrude_forked", "Extrude Forked",
	                                  "Create new bones from the selected joints and move them",
	                                  OPTYPE_UNDO | OPTYPE_REGISTER);
	otmacro = WM_operatortype_macro_define(ot, "ARMATURE_OT_extrude");
	RNA_boolean_set(otmacro->ptr, "forked", true);
	otmacro = WM_operatortype_macro_define(ot, "TRANSFORM_OT_translate");
	RNA_enum_set(otmacro->ptr, "proportional", 0);
	
	
	/* Pose Sketching -------------------------------------------------------- */
	
	/* Pose Sketching operators for now must be paired with Grease Pencil ones
	 * (GPencil first) or else we wouldn't have anything to work with
	 */
	ot = WM_operatortype_append_macro("POSE_OT_sketch_direct_interactive", "Sketch Bone Chain Pose",
	                                  "Interactively sketch the pose for the selected bones",
	                                  OPTYPE_UNDO | OPTYPE_REGISTER);
	otmacro = WM_operatortype_macro_define(ot, "GPENCIL_OT_draw");
	//RNA_boolean_set(otmacro->ptr, "wait_for_input", false); /* XXX - this means it can't be used from toolbars, but allows for nicer workflow */
	otmacro = WM_operatortype_macro_define(ot, "POSE_OT_sketch_direct");
	
	/* Pose Sculpting -------------------------------------------------------- */
	/* Pose Sculpting convenience operators which set the brush type, then sculpts using that */
	
	/* ADJUST */
	ot = WM_operatortype_append_macro("POSE_OT_sculpt_adjust", "Sculpt Adjust Brush",
	                                  "Sculpt pose using 'Adjust' brush",
	                                  OPTYPE_UNDO | OPTYPE_REGISTER);
	otmacro = WM_operatortype_macro_define(ot, "POSE_OT_brush_set");
	RNA_int_set(otmacro->ptr, "brush_type", PSCULPT_BRUSH_ADJUST);
	otmacro = WM_operatortype_macro_define(ot, "POSE_OT_brush_paint");
	RNA_boolean_set(otmacro->ptr, "invert", false);
	
	ot = WM_operatortype_append_macro("POSE_OT_sculpt_rotate", "Sculpt Rotate Brush",
	                                  "Sculpt pose using 'Rotate' brush",
	                                  OPTYPE_UNDO | OPTYPE_REGISTER);
	otmacro = WM_operatortype_macro_define(ot, "POSE_OT_brush_set");
	RNA_int_set(otmacro->ptr, "brush_type", PSCULPT_BRUSH_ADJUST);
	otmacro = WM_operatortype_macro_define(ot, "POSE_OT_brush_paint");
	RNA_boolean_set(otmacro->ptr, "invert", true);
	
	
	/* GRAB */
	ot = WM_operatortype_append_macro("POSE_OT_sculpt_grab", "Sculpt Grab Brush",
	                                  "Sculpt pose using 'Grab' brush",
	                                  OPTYPE_UNDO | OPTYPE_REGISTER);
	otmacro = WM_operatortype_macro_define(ot, "POSE_OT_brush_set");
	RNA_int_set(otmacro->ptr, "brush_type", PSCULPT_BRUSH_GRAB);
	otmacro = WM_operatortype_macro_define(ot, "POSE_OT_brush_paint");
	RNA_boolean_set(otmacro->ptr, "invert", false);
	
	ot = WM_operatortype_append_macro("POSE_OT_sculpt_push", "Sculpt Push Brush",
	                                  "Sculpt pose using 'Push' brush",
	                                  OPTYPE_UNDO | OPTYPE_REGISTER);
	otmacro = WM_operatortype_macro_define(ot, "POSE_OT_brush_set");
	RNA_int_set(otmacro->ptr, "brush_type", PSCULPT_BRUSH_GRAB);
	otmacro = WM_operatortype_macro_define(ot, "POSE_OT_brush_paint");
	RNA_boolean_set(otmacro->ptr, "invert", true);
	
	/* RESET */
	ot = WM_operatortype_append_macro("POSE_OT_sculpt_reset", "Sculpt 'Reset to Rest Pose' Brush",
	                                  "Sculpt pose using 'Reset to RestPose' brush",
	                                  OPTYPE_UNDO | OPTYPE_REGISTER);
	otmacro = WM_operatortype_macro_define(ot, "POSE_OT_brush_set");
	RNA_int_set(otmacro->ptr, "brush_type", PSCULPT_BRUSH_RESET);
	otmacro = WM_operatortype_macro_define(ot, "POSE_OT_brush_paint");
	RNA_boolean_set(otmacro->ptr, "invert", false);
	
	ot = WM_operatortype_append_macro("POSE_OT_sculpt_restore", "Sculpt 'Restore Pose' Brush",
	                                  "Sculpt pose using 'Reset to Keyed' brush",
	                                  OPTYPE_UNDO | OPTYPE_REGISTER);
	otmacro = WM_operatortype_macro_define(ot, "POSE_OT_brush_set");
	RNA_int_set(otmacro->ptr, "brush_type", PSCULPT_BRUSH_RESET);
	otmacro = WM_operatortype_macro_define(ot, "POSE_OT_brush_paint");
	RNA_boolean_set(otmacro->ptr, "invert", true);
}

void ED_keymap_armature(wmKeyConfig *keyconf)
{
	wmKeyMap *keymap;
	wmKeyMapItem *kmi;
	
	/* Armature ------------------------ */
	keymap = WM_keymap_find(keyconf, "Armature", 0, 0);
	keymap->poll = ED_operator_editarmature;
	
	/* Armature -> Etch-A-Ton ------------------------ */
	WM_keymap_add_item(keymap, "SKETCH_OT_delete", XKEY, KM_PRESS, 0, 0);
	WM_keymap_add_item(keymap, "SKETCH_OT_delete", DELKEY, KM_PRESS, 0, 0);
	WM_keymap_add_item(keymap, "SKETCH_OT_finish_stroke", RIGHTMOUSE, KM_PRESS, 0, 0);
	WM_keymap_add_item(keymap, "SKETCH_OT_cancel_stroke", ESCKEY, KM_PRESS, 0, 0);
	/* Already part of view3d select */
	//WM_keymap_add_item(keymap, "SKETCH_OT_select", SELECTMOUSE, KM_PRESS, 0, 0);

	/* sketch poll checks mode */
	WM_keymap_add_item(keymap, "SKETCH_OT_gesture", LEFTMOUSE, KM_PRESS, KM_SHIFT, 0);
	WM_keymap_add_item(keymap, "SKETCH_OT_draw_stroke", LEFTMOUSE, KM_PRESS, 0, 0);
	kmi = WM_keymap_add_item(keymap, "SKETCH_OT_draw_stroke", LEFTMOUSE, KM_PRESS, KM_CTRL, 0);
	RNA_boolean_set(kmi->ptr, "snap", true);
	WM_keymap_add_item(keymap, "SKETCH_OT_draw_preview", MOUSEMOVE, KM_ANY, 0, 0);
	kmi = WM_keymap_add_item(keymap, "SKETCH_OT_draw_preview", MOUSEMOVE, KM_ANY, KM_CTRL, 0);
	RNA_boolean_set(kmi->ptr, "snap", true);

	/* only set in editmode armature, by space_view3d listener */
	kmi = WM_keymap_add_item(keymap, "ARMATURE_OT_hide", HKEY, KM_PRESS, 0, 0);
	RNA_boolean_set(kmi->ptr, "unselected", false);
	kmi = WM_keymap_add_item(keymap, "ARMATURE_OT_hide", HKEY, KM_PRESS, KM_SHIFT, 0);
	RNA_boolean_set(kmi->ptr, "unselected", true);

	WM_keymap_add_item(keymap, "ARMATURE_OT_reveal", HKEY, KM_PRESS, KM_ALT, 0);
	WM_keymap_add_item(keymap, "ARMATURE_OT_align", AKEY, KM_PRESS, KM_CTRL | KM_ALT, 0);
	WM_keymap_add_item(keymap, "ARMATURE_OT_calculate_roll", NKEY, KM_PRESS, KM_CTRL, 0);
	
	WM_keymap_add_item(keymap, "ARMATURE_OT_switch_direction", FKEY, KM_PRESS, KM_ALT, 0);
	
	WM_keymap_add_item(keymap, "ARMATURE_OT_bone_primitive_add", AKEY, KM_PRESS, KM_SHIFT, 0);
	
	WM_keymap_add_item(keymap, "ARMATURE_OT_parent_set", PKEY, KM_PRESS, KM_CTRL, 0);
	WM_keymap_add_item(keymap, "ARMATURE_OT_parent_clear", PKEY, KM_PRESS, KM_ALT, 0);
	
	kmi = WM_keymap_add_item(keymap, "ARMATURE_OT_select_all", AKEY, KM_PRESS, 0, 0);
	RNA_enum_set(kmi->ptr, "action", SEL_TOGGLE);
	kmi = WM_keymap_add_item(keymap, "ARMATURE_OT_select_all", IKEY, KM_PRESS, KM_CTRL, 0);
	RNA_enum_set(kmi->ptr, "action", SEL_INVERT);

	kmi = WM_keymap_add_item(keymap, "ARMATURE_OT_select_mirror", MKEY, KM_PRESS, KM_CTRL | KM_SHIFT, 0);
	RNA_boolean_set(kmi->ptr, "extend", false);
	
	kmi = WM_keymap_add_item(keymap, "ARMATURE_OT_select_hierarchy", LEFTBRACKETKEY, KM_PRESS, 0, 0);
	RNA_enum_set(kmi->ptr, "direction", BONE_SELECT_PARENT);
	RNA_boolean_set(kmi->ptr, "extend", false);
	kmi = WM_keymap_add_item(keymap, "ARMATURE_OT_select_hierarchy", LEFTBRACKETKEY, KM_PRESS, KM_SHIFT, 0);
	RNA_enum_set(kmi->ptr, "direction", BONE_SELECT_PARENT);
	RNA_boolean_set(kmi->ptr, "extend", true);
	
	kmi = WM_keymap_add_item(keymap, "ARMATURE_OT_select_hierarchy", RIGHTBRACKETKEY, KM_PRESS, 0, 0);
	RNA_enum_set(kmi->ptr, "direction", BONE_SELECT_CHILD);
	RNA_boolean_set(kmi->ptr, "extend", false);
	kmi = WM_keymap_add_item(keymap, "ARMATURE_OT_select_hierarchy", RIGHTBRACKETKEY, KM_PRESS, KM_SHIFT, 0);
	RNA_enum_set(kmi->ptr, "direction", BONE_SELECT_CHILD);
	RNA_boolean_set(kmi->ptr, "extend", true);

	WM_keymap_add_item(keymap, "ARMATURE_OT_select_more", PADPLUSKEY, KM_PRESS, KM_CTRL, 0);
	WM_keymap_add_item(keymap, "ARMATURE_OT_select_less", PADMINUS, KM_PRESS, KM_CTRL, 0);

	WM_keymap_add_item(keymap, "ARMATURE_OT_select_similar", GKEY, KM_PRESS, KM_SHIFT, 0);

	WM_keymap_add_item(keymap, "ARMATURE_OT_select_linked", LKEY, KM_PRESS, 0, 0);

	WM_keymap_add_item(keymap, "ARMATURE_OT_shortest_path_pick", SELECTMOUSE, KM_PRESS, KM_CTRL, 0);
	
	WM_keymap_add_menu(keymap, "VIEW3D_MT_edit_armature_delete", XKEY, KM_PRESS, 0, 0);
	WM_keymap_add_menu(keymap, "VIEW3D_MT_edit_armature_delete", DELKEY, KM_PRESS, 0, 0);
	WM_keymap_add_item(keymap, "ARMATURE_OT_dissolve", XKEY, KM_PRESS, KM_CTRL, 0);
	WM_keymap_add_item(keymap, "ARMATURE_OT_duplicate_move", DKEY, KM_PRESS, KM_SHIFT, 0);
	WM_keymap_add_item(keymap, "ARMATURE_OT_extrude_move", EKEY, KM_PRESS, 0, 0);
	WM_keymap_add_item(keymap, "ARMATURE_OT_extrude_forked", EKEY, KM_PRESS, KM_SHIFT, 0);
	WM_keymap_add_item(keymap, "ARMATURE_OT_click_extrude", ACTIONMOUSE, KM_CLICK, KM_CTRL, 0);
	WM_keymap_add_item(keymap, "ARMATURE_OT_fill", FKEY, KM_PRESS, 0, 0);
	WM_keymap_add_item(keymap, "ARMATURE_OT_merge", MKEY, KM_PRESS, KM_ALT, 0);
	WM_keymap_add_item(keymap, "ARMATURE_OT_split", YKEY, KM_PRESS, 0, 0);
	
	WM_keymap_add_item(keymap, "ARMATURE_OT_separate", PKEY, KM_PRESS, 0, 0);
	
	/* set flags */
	WM_keymap_add_menu(keymap, "VIEW3D_MT_bone_options_toggle", WKEY, KM_PRESS, KM_SHIFT, 0);
	WM_keymap_add_menu(keymap, "VIEW3D_MT_bone_options_enable", WKEY, KM_PRESS, KM_CTRL | KM_SHIFT, 0);
	WM_keymap_add_menu(keymap, "VIEW3D_MT_bone_options_disable", WKEY, KM_PRESS, KM_ALT, 0);
	
	/* armature/bone layers */
	WM_keymap_add_item(keymap, "ARMATURE_OT_layers_show_all", ACCENTGRAVEKEY, KM_PRESS, KM_CTRL, 0);
	WM_keymap_add_item(keymap, "ARMATURE_OT_armature_layers", MKEY, KM_PRESS, KM_SHIFT, 0);
	WM_keymap_add_item(keymap, "ARMATURE_OT_bone_layers", MKEY, KM_PRESS, 0, 0);
	
	/* special transforms: */
	/*  1) envelope/b-bone size */
	kmi = WM_keymap_add_item(keymap, "TRANSFORM_OT_transform", SKEY, KM_PRESS, KM_CTRL | KM_ALT, 0);
	RNA_enum_set(kmi->ptr, "mode", TFM_BONESIZE);
	/*  2) envelope radius */
	kmi = WM_keymap_add_item(keymap, "TRANSFORM_OT_transform", SKEY, KM_PRESS, KM_ALT, 0);
	RNA_enum_set(kmi->ptr, "mode", TFM_BONE_ENVELOPE);
	/*  3) set roll */
	kmi = WM_keymap_add_item(keymap, "TRANSFORM_OT_transform", RKEY, KM_PRESS, KM_CTRL, 0);
	RNA_enum_set(kmi->ptr, "mode", TFM_BONE_ROLL);
		
	/* menus */
	WM_keymap_add_menu(keymap, "VIEW3D_MT_armature_specials", WKEY, KM_PRESS, 0, 0);

	/* Pose ------------------------ */
	/* only set in posemode, by space_view3d listener */
	keymap = WM_keymap_find(keyconf, "Pose", 0, 0);
	keymap->poll = ED_operator_posemode;
	
	/* set parent and add object are object-based operators, but we make them
	 * available here because it's useful to do in pose mode too */
	WM_keymap_add_item(keymap, "OBJECT_OT_parent_set", PKEY, KM_PRESS, KM_CTRL, 0);
	WM_keymap_add_menu(keymap, "INFO_MT_add", AKEY, KM_PRESS, KM_SHIFT, 0);
	
	kmi = WM_keymap_add_item(keymap, "POSE_OT_hide", HKEY, KM_PRESS, 0, 0);
	RNA_boolean_set(kmi->ptr, "unselected", false);
	kmi = WM_keymap_add_item(keymap, "POSE_OT_hide", HKEY, KM_PRESS, KM_SHIFT, 0);
	RNA_boolean_set(kmi->ptr, "unselected", true);

	WM_keymap_add_item(keymap, "POSE_OT_reveal", HKEY, KM_PRESS, KM_ALT, 0);
	
	WM_keymap_add_menu(keymap, "VIEW3D_MT_pose_apply", AKEY, KM_PRESS, KM_CTRL, 0);
	
	/* TODO: clear pose */
	WM_keymap_add_item(keymap, "POSE_OT_rot_clear", RKEY, KM_PRESS, KM_ALT, 0);
	WM_keymap_add_item(keymap, "POSE_OT_loc_clear", GKEY, KM_PRESS, KM_ALT, 0);
	WM_keymap_add_item(keymap, "POSE_OT_scale_clear", SKEY, KM_PRESS, KM_ALT, 0);
	
	WM_keymap_add_item(keymap, "POSE_OT_quaternions_flip", FKEY, KM_PRESS, KM_ALT, 0);
	
	WM_keymap_add_item(keymap, "POSE_OT_rotation_mode_set", RKEY, KM_PRESS, KM_CTRL, 0);
	
	WM_keymap_add_item(keymap, "POSE_OT_copy", CKEY, KM_PRESS, KM_CTRL, 0);
	kmi = WM_keymap_add_item(keymap, "POSE_OT_paste", VKEY, KM_PRESS, KM_CTRL, 0);
	RNA_boolean_set(kmi->ptr, "flipped", false);
	kmi = WM_keymap_add_item(keymap, "POSE_OT_paste", VKEY, KM_PRESS, KM_CTRL | KM_SHIFT, 0);
	RNA_boolean_set(kmi->ptr, "flipped", true);
	
#ifdef __APPLE__
	WM_keymap_add_item(keymap, "POSE_OT_copy", CKEY, KM_PRESS, KM_OSKEY, 0);
	kmi = WM_keymap_add_item(keymap, "POSE_OT_paste", VKEY, KM_PRESS, KM_OSKEY, 0);
	RNA_boolean_set(kmi->ptr, "flipped", false);
	kmi = WM_keymap_add_item(keymap, "POSE_OT_paste", VKEY, KM_PRESS, KM_OSKEY | KM_SHIFT, 0);
	RNA_boolean_set(kmi->ptr, "flipped", true);
#endif

	kmi = WM_keymap_add_item(keymap, "POSE_OT_select_all", AKEY, KM_PRESS, 0, 0);
	RNA_enum_set(kmi->ptr, "action", SEL_TOGGLE);
	kmi = WM_keymap_add_item(keymap, "POSE_OT_select_all", IKEY, KM_PRESS, KM_CTRL, 0);
	RNA_enum_set(kmi->ptr, "action", SEL_INVERT);

	WM_keymap_add_item(keymap, "POSE_OT_select_parent", PKEY, KM_PRESS, KM_SHIFT, 0);

	kmi = WM_keymap_add_item(keymap, "POSE_OT_select_hierarchy", LEFTBRACKETKEY, KM_PRESS, 0, 0);
	RNA_enum_set(kmi->ptr, "direction", BONE_SELECT_PARENT);
	RNA_boolean_set(kmi->ptr, "extend", false);
	kmi = WM_keymap_add_item(keymap, "POSE_OT_select_hierarchy", LEFTBRACKETKEY, KM_PRESS, KM_SHIFT, 0);
	RNA_enum_set(kmi->ptr, "direction", BONE_SELECT_PARENT);
	RNA_boolean_set(kmi->ptr, "extend", true);
	
	kmi = WM_keymap_add_item(keymap, "POSE_OT_select_hierarchy", RIGHTBRACKETKEY, KM_PRESS, 0, 0);
	RNA_enum_set(kmi->ptr, "direction", BONE_SELECT_CHILD);
	RNA_boolean_set(kmi->ptr, "extend", false);
	kmi = WM_keymap_add_item(keymap, "POSE_OT_select_hierarchy", RIGHTBRACKETKEY, KM_PRESS, KM_SHIFT, 0);
	RNA_enum_set(kmi->ptr, "direction", BONE_SELECT_CHILD);
	RNA_boolean_set(kmi->ptr, "extend", true);

	WM_keymap_add_item(keymap, "POSE_OT_select_linked", LKEY, KM_PRESS, 0, 0);
	WM_keymap_add_item(keymap, "POSE_OT_select_grouped", GKEY, KM_PRESS, KM_SHIFT, 0);
	WM_keymap_add_item(keymap, "POSE_OT_select_mirror", FKEY, KM_PRESS, KM_SHIFT | KM_CTRL, 0);
	
	WM_keymap_add_item(keymap, "POSE_OT_constraint_add_with_targets", CKEY, KM_PRESS, KM_CTRL | KM_SHIFT, 0);
	WM_keymap_add_item(keymap, "POSE_OT_constraints_clear", CKEY, KM_PRESS, KM_CTRL | KM_ALT, 0);
	WM_keymap_add_item(keymap, "POSE_OT_ik_add", IKEY, KM_PRESS, /*KM_CTRL|*/ KM_SHIFT, 0);
	WM_keymap_add_item(keymap, "POSE_OT_ik_clear", IKEY, KM_PRESS, KM_CTRL | KM_ALT, 0);
	
	WM_keymap_add_menu(keymap, "VIEW3D_MT_pose_group", GKEY, KM_PRESS, KM_CTRL, 0);
	
	/* set flags */
	WM_keymap_add_menu(keymap, "VIEW3D_MT_bone_options_toggle", WKEY, KM_PRESS, KM_SHIFT, 0);
	WM_keymap_add_menu(keymap, "VIEW3D_MT_bone_options_enable", WKEY, KM_PRESS, KM_CTRL | KM_SHIFT, 0);
	WM_keymap_add_menu(keymap, "VIEW3D_MT_bone_options_disable", WKEY, KM_PRESS, KM_ALT, 0);

	/* armature/bone layers */
	WM_keymap_add_item(keymap, "ARMATURE_OT_layers_show_all", ACCENTGRAVEKEY, KM_PRESS, KM_CTRL, 0);
	WM_keymap_add_item(keymap, "ARMATURE_OT_armature_layers", MKEY, KM_PRESS, KM_SHIFT, 0);
	WM_keymap_add_item(keymap, "POSE_OT_bone_layers", MKEY, KM_PRESS, 0, 0);
	
	/* special transforms: */
	/*  1) envelope/b-bone size */
	kmi = WM_keymap_add_item(keymap, "TRANSFORM_OT_transform", SKEY, KM_PRESS, KM_CTRL | KM_ALT, 0);
	RNA_enum_set(kmi->ptr, "mode", TFM_BONESIZE);
	
	/* keyframes management */
	WM_keymap_verify_item(keymap, "ANIM_OT_keyframe_insert_menu", IKEY, KM_PRESS, 0, 0);
	WM_keymap_verify_item(keymap, "ANIM_OT_keyframe_delete_v3d", IKEY, KM_PRESS, KM_ALT, 0);
	WM_keymap_verify_item(keymap, "ANIM_OT_keying_set_active_set", IKEY, KM_PRESS, KM_CTRL | KM_SHIFT | KM_ALT, 0);
	
	/* Pose -> PoseLib ------------- */
	/* only set in posemode, by space_view3d listener */
	WM_keymap_add_item(keymap, "POSELIB_OT_browse_interactive", LKEY, KM_PRESS, KM_CTRL, 0);
	
	WM_keymap_add_item(keymap, "POSELIB_OT_pose_add", LKEY, KM_PRESS, KM_SHIFT, 0);
	WM_keymap_add_item(keymap, "POSELIB_OT_pose_remove", LKEY, KM_PRESS, KM_ALT, 0);
	WM_keymap_add_item(keymap, "POSELIB_OT_pose_rename", LKEY, KM_PRESS, KM_CTRL | KM_SHIFT, 0);
	
	/* Pose -> Pose Sliding ------------- */
	/* only set in posemode, by space_view3d listener */
	WM_keymap_add_item(keymap, "POSE_OT_push", EKEY, KM_PRESS, KM_CTRL, 0);
	WM_keymap_add_item(keymap, "POSE_OT_relax", EKEY, KM_PRESS, KM_ALT, 0);
	WM_keymap_add_item(keymap, "POSE_OT_breakdown", EKEY, KM_PRESS, KM_SHIFT, 0);
	
	/* Menus */
	WM_keymap_add_menu(keymap, "VIEW3D_MT_pose_specials", WKEY, KM_PRESS, 0, 0);
	WM_keymap_add_menu(keymap, "VIEW3D_MT_pose_propagate", PKEY, KM_PRESS, KM_ALT, 0);
	
	/* Pose -> Pose Sketching/Sculpting ------------- */
	/* only set in posemode, by space_view3d listener */
	// XXX: pehrpas the "direct" hotkeys should only be available when in sculpt mode (to replace the default movement keys), but nothing else?
	
	/* Sketch - Direct Chain */
	WM_keymap_add_item(keymap, "POSE_OT_sketch_direct_interactive", EKEY, KM_PRESS, 0, 0);
	
	/* Sculpting - Apply effects... */
	// XXX: it would be nice if this was used exclusively for the draw/adjust brush...
	kmi = WM_keymap_add_item(keymap, "POSE_OT_brush_paint", LEFTMOUSE, KM_PRESS,        0, QKEY);
	RNA_boolean_set(kmi->ptr, "invert", false);
	
	kmi = WM_keymap_add_item(keymap, "POSE_OT_brush_paint", LEFTMOUSE, KM_PRESS, KM_SHIFT, QKEY);
	RNA_boolean_set(kmi->ptr, "invert", true);
	
	/* Sculpting - Reset */
	/* Used for clearing transforms, so 'x' to "scrub" seems like a good match... */
	kmi = WM_keymap_add_item(keymap, "POSE_OT_sculpt_reset", LEFTMOUSE, KM_PRESS,          0, XKEY);
	kmi = WM_keymap_add_item(keymap, "POSE_OT_sculpt_restore", LEFTMOUSE, KM_PRESS, KM_SHIFT, XKEY);
	
	/* Sculpting - Grab */
	// XXX: mappping here still needs work
	WM_keymap_add_item(keymap, "POSE_OT_sculpt_grab", LEFTMOUSE, KM_PRESS,        0, YKEY);
	WM_keymap_add_item(keymap, "POSE_OT_sculpt_push", LEFTMOUSE, KM_PRESS, KM_SHIFT, YKEY);
	
	/* Sculpting - Adjust */
	// XXX: mappping here still needs work
	WM_keymap_add_item(keymap, "POSE_OT_sculpt_adjust", LEFTMOUSE, KM_PRESS, 0,        VKEY);
	WM_keymap_add_item(keymap, "POSE_OT_sculpt_rotate", LEFTMOUSE, KM_PRESS, KM_SHIFT, VKEY);
	
	/* Adjust brush size/strength */
	kmi = WM_keymap_add_item(keymap, "WM_OT_radial_control", FKEY, KM_PRESS, 0, 0);
	RNA_string_set(kmi->ptr, "data_path_primary", "tool_settings.pose_sculpt.brush.size");
	
	kmi = WM_keymap_add_item(keymap, "WM_OT_radial_control", FKEY, KM_PRESS, KM_SHIFT, 0);
	RNA_string_set(kmi->ptr, "data_path_primary", "tool_settings.pose_sculpt.brush.strength");
}

