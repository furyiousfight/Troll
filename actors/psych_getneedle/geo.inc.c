#include "src/game/envfx_snow.h"

const GeoLayout psych_getneedle_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, psych_getneedle_psych_getneedle_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, psych_getneedle_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
