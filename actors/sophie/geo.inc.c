#include "src/game/envfx_snow.h"

const GeoLayout sophie_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_ALPHA, 0, 21, 8, sophie_root_mesh_layer_4),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, sophie_Chest_skinned_mesh_layer_1),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 28, 0, sophie_Chest_mesh_layer_1),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 27, 0, sophie_Head_mesh_layer_1),
				GEO_OPEN_NODE(),
					GEO_DISPLAY_LIST(LAYER_OPAQUE, sophie_Left_Ear_1_skinned_mesh_layer_1),
					GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 17, 26, -3, 0, 0, -65),
					GEO_OPEN_NODE(),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, sophie_Left_Ear_1_mesh_layer_1),
						GEO_OPEN_NODE(),
							GEO_DISPLAY_LIST(LAYER_OPAQUE, sophie_Left_Ear_2_skinned_mesh_layer_1),
							GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 23, 0, 0, 0, -5),
							GEO_OPEN_NODE(),
								GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, sophie_Left_Ear_2_mesh_layer_1),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
					GEO_DISPLAY_LIST(LAYER_OPAQUE, sophie_Right_Ear_1_skinned_mesh_layer_1),
					GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, -17, 26, -3, 0, 0, 65),
					GEO_OPEN_NODE(),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, sophie_Right_Ear_1_mesh_layer_1),
						GEO_OPEN_NODE(),
							GEO_DISPLAY_LIST(LAYER_OPAQUE, sophie_Right_Ear_2_skinned_mesh_layer_1),
							GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 23, 0, 0, 0, 5),
							GEO_OPEN_NODE(),
								GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, sophie_Right_Ear_2_mesh_layer_1),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, sophie_Left_Arm_1_skinned_mesh_layer_1),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 14, 21, -5, 0, 0, -90),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, sophie_Left_Arm_1_mesh_layer_1),
					GEO_OPEN_NODE(),
						GEO_DISPLAY_LIST(LAYER_OPAQUE, sophie_Left_Arm_2_skinned_mesh_layer_1),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 19, 0, sophie_Left_Arm_2_mesh_layer_1),
						GEO_OPEN_NODE(),
							GEO_DISPLAY_LIST(LAYER_OPAQUE, sophie_Left_Hand_skinned_mesh_layer_1),
							GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 21, 0, sophie_Left_Hand_mesh_layer_1),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, -7, -3, -14, 2, 6, -108),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, sophie_Left_Bottom_Wing_1_mesh_layer_4),
					GEO_OPEN_NODE(),
						GEO_DISPLAY_LIST(LAYER_ALPHA, sophie_Left_Bottom_Wing_2_skinned_mesh_layer_4),
						GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 38, 0, -13, 1, -2),
						GEO_OPEN_NODE(),
							GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, sophie_Left_Bottom_Wing_2_mesh_layer_4),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, -8, 15, -14, -2, 6, -74),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, sophie_Left_Top_Wing_1_mesh_layer_4),
					GEO_OPEN_NODE(),
						GEO_DISPLAY_LIST(LAYER_ALPHA, sophie_Left_Top_Wing_2_skinned_mesh_layer_4),
						GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 37, 0, -14, 0, 0),
						GEO_OPEN_NODE(),
							GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, sophie_Left_Top_Wing_2_mesh_layer_4),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, sophie_Right_Arm_1_skinned_mesh_layer_1),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, -14, 21, -5, 0, 0, 90),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, sophie_Right_Arm_1_mesh_layer_1),
					GEO_OPEN_NODE(),
						GEO_DISPLAY_LIST(LAYER_OPAQUE, sophie_Right_Arm_2_skinned_mesh_layer_1),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 19, 0, sophie_Right_Arm_2_mesh_layer_1),
						GEO_OPEN_NODE(),
							GEO_DISPLAY_LIST(LAYER_OPAQUE, sophie_Right_Hand_skinned_mesh_layer_1),
							GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 21, 0, sophie_Right_Hand_mesh_layer_1),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 7, -3, -14, 2, -6, 108),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, sophie_Right_Bottom_Wing_1_mesh_layer_4),
					GEO_OPEN_NODE(),
						GEO_DISPLAY_LIST(LAYER_ALPHA, sophie_Right_Bottom_Wing_2_skinned_mesh_layer_4),
						GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 38, 0, -13, -1, 2),
						GEO_OPEN_NODE(),
							GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, sophie_Right_Bottom_Wing_2_mesh_layer_4),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 8, 15, -14, -2, -6, 74),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, sophie_Right_Top_Wing_1_mesh_layer_4),
					GEO_OPEN_NODE(),
						GEO_DISPLAY_LIST(LAYER_ALPHA, sophie_Right_Top_Wing_2_skinned_mesh_layer_4),
						GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 37, 0, -14, 0, 0),
						GEO_OPEN_NODE(),
							GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, sophie_Right_Top_Wing_2_mesh_layer_4),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 9, 4, 0, 0, -90, -180),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
				GEO_OPEN_NODE(),
					GEO_DISPLAY_LIST(LAYER_OPAQUE, sophie_Left_Leg_2_skinned_mesh_layer_1),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 19, 0, sophie_Left_Leg_2_mesh_layer_1),
					GEO_OPEN_NODE(),
						GEO_DISPLAY_LIST(LAYER_OPAQUE, sophie_Left_Foot_skinned_mesh_layer_1),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 19, 0, sophie_Left_Foot_mesh_layer_1),
						GEO_OPEN_NODE(),
							GEO_DISPLAY_LIST(LAYER_ALPHA, sophie_Left_Foot_mesh_layer_4),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, -9, 4, 0, 0, 90, 180),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
				GEO_OPEN_NODE(),
					GEO_DISPLAY_LIST(LAYER_OPAQUE, sophie_Right_Leg_2_skinned_mesh_layer_1),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 19, 0, sophie_Right_Leg_2_mesh_layer_1),
					GEO_OPEN_NODE(),
						GEO_DISPLAY_LIST(LAYER_OPAQUE, sophie_Right_Foot_skinned_mesh_layer_1),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 19, 0, sophie_Right_Foot_mesh_layer_1),
						GEO_OPEN_NODE(),
							GEO_DISPLAY_LIST(LAYER_ALPHA, sophie_Right_Foot_mesh_layer_4),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
			GEO_SHADOW(1, 191, 65),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, sophie_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, sophie_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
