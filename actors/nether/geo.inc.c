#include "src/game/envfx_snow.h"

const GeoLayout nether_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, nether_Nether_Portal_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, nether_Nether_Portal_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_ALPHA, nether_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, nether_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
