#include "src/game/envfx_snow.h"

const GeoLayout katana_a_button_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE_DECAL, katana_a_button_katana_a_button_mesh_layer_2),
		GEO_DISPLAY_LIST(LAYER_OPAQUE_DECAL, katana_a_button_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
