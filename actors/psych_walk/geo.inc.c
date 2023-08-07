#include "src/game/envfx_snow.h"

const GeoLayout psych_walk_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, psych_walk_psych_walk_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, psych_walk_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
