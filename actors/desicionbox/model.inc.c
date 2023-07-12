Gfx desicionbox_texbox_outline_ia8_aligner[] = {gsSPEndDisplayList()};
u8 desicionbox_texbox_outline_ia8[] = {
	0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xf0, 0xf0, 0xf0, 
	0xff, 0xff, 0xf0, 0xf0, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 
	0xf0, 
};

Vtx desicionbox_desicionbox_mesh_vtx_0[8] = {
	{{ {88, 9, 0}, 0, {75, 85}, {0, 0, 127, 255} }},
	{{ {91, -7, 0}, 0, {75, 85}, {0, 0, 127, 255} }},
	{{ {91, 7, 0}, 0, {75, 85}, {0, 0, 127, 255} }},
	{{ {88, -9, 0}, 0, {75, 85}, {0, 0, 127, 255} }},
	{{ {-88, -9, 0}, 0, {75, 85}, {0, 0, 127, 255} }},
	{{ {-88, 9, 0}, 0, {75, 85}, {0, 0, 127, 255} }},
	{{ {-91, 7, 0}, 0, {75, 85}, {0, 0, 127, 255} }},
	{{ {-91, -7, 0}, 0, {75, 85}, {0, 0, 127, 255} }},
};

Gfx desicionbox_desicionbox_mesh_tri_0[] = {
	gsSPVertex(desicionbox_desicionbox_mesh_vtx_0 + 0, 8, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(4, 3, 0, 0),
	gsSP1Triangle(4, 0, 5, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSPEndDisplayList(),
};

Gfx mat_desicionbox_f3dlite_material_014_layer1[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT),
	gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 5, desicionbox_texbox_outline_ia8),
	gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 1, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTile(7, 0, 0, 16, 16),
	gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 1, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 3, 0, G_TX_CLAMP | G_TX_NOMIRROR, 3, 0),
	gsDPSetTileSize(0, 0, 0, 16, 16),
	gsSPEndDisplayList(),
};

Gfx mat_revert_desicionbox_f3dlite_material_014_layer1[] = {
	gsDPPipeSync(),
	gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
	gsSPEndDisplayList(),
};

Gfx desicionbox_desicionbox_mesh[] = {
	gsSPDisplayList(mat_desicionbox_f3dlite_material_014_layer1),
	gsSPDisplayList(desicionbox_desicionbox_mesh_tri_0),
	gsSPDisplayList(mat_revert_desicionbox_f3dlite_material_014_layer1),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

