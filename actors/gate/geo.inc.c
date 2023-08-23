#include "src/game/envfx_snow.h"

const GeoLayout gate_geo[] = {
	GEO_CULLING_RADIUS(25500),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, gate_Cube_001_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, gate_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
