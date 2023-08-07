#include "src/game/envfx_snow.h"

const GeoLayout building_ext_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, building_ext_building_ext_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, building_ext_building_ext_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, building_ext_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, building_ext_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
