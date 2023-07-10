#include "src/game/envfx_snow.h"

const GeoLayout DRExplosion_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(LAYER_ALPHA, 0, 0, 0, DRExplosion_DRExplosion_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, DRExplosion_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
