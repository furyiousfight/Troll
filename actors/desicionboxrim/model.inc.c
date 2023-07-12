Gfx desicionboxrim_texbox_outline_ia8_aligner[] = {gsSPEndDisplayList()};
u8 desicionboxrim_texbox_outline_ia8[] = {
	0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xf0, 0xf0, 0xf0, 
	0xff, 0xff, 0xf0, 0xf0, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 
	0xf0, 
};

Vtx desicionboxrim_desicionboxrim_mesh_vtx_0[30] = {
	{{ {-89, -9, 1}, 0, {45, 160}, {0, 0, 127, 255} }},
	{{ {89, -9, 1}, 0, {45, 160}, {0, 0, 127, 255} }},
	{{ {89, -7, 1}, 0, {45, 0}, {0, 0, 127, 255} }},
	{{ {-89, -7, 1}, 0, {45, 0}, {0, 0, 127, 255} }},
	{{ {-89, 7, 1}, 0, {45, 0}, {0, 0, 127, 255} }},
	{{ {89, 7, 1}, 0, {45, 0}, {0, 0, 127, 255} }},
	{{ {89, 9, 1}, 0, {45, 160}, {0, 0, 127, 255} }},
	{{ {-89, 9, 1}, 0, {45, 160}, {0, 0, 127, 255} }},
	{{ {89, -7, 1}, 0, {45, 0}, {0, 0, 127, 255} }},
	{{ {91, -7, 1}, 0, {45, 160}, {0, 0, 127, 255} }},
	{{ {91, 7, 1}, 0, {45, 160}, {0, 0, 127, 255} }},
	{{ {-89, -7, 1}, 0, {45, 0}, {0, 0, 127, 255} }},
	{{ {-91, 7, 1}, 0, {45, 160}, {0, 0, 127, 255} }},
	{{ {-91, -7, 1}, 0, {45, 160}, {0, 0, 127, 255} }},
	{{ {-89, -9, 1}, 0, {0, 160}, {0, 0, 127, 255} }},
	{{ {-89, -7, 1}, 0, {160, 160}, {0, 0, 127, 255} }},
	{{ {-91, -7, 1}, 0, {160, 0}, {0, 0, 127, 255} }},
	{{ {-91, -9, 1}, 0, {0, 0}, {0, 0, 127, 255} }},
	{{ {-91, 7, 1}, 0, {0, 160}, {0, 0, 127, 255} }},
	{{ {-89, 7, 1}, 0, {160, 160}, {0, 0, 127, 255} }},
	{{ {-89, 9, 1}, 0, {160, 0}, {0, 0, 127, 255} }},
	{{ {-91, 9, 1}, 0, {0, 0}, {0, 0, 127, 255} }},
	{{ {89, 9, 1}, 0, {0, 160}, {0, 0, 127, 255} }},
	{{ {89, 7, 1}, 0, {160, 160}, {0, 0, 127, 255} }},
	{{ {91, 7, 1}, 0, {160, 0}, {0, 0, 127, 255} }},
	{{ {91, 9, 1}, 0, {0, 0}, {0, 0, 127, 255} }},
	{{ {91, -7, 1}, 0, {0, 160}, {0, 0, 127, 255} }},
	{{ {89, -7, 1}, 0, {160, 160}, {0, 0, 127, 255} }},
	{{ {89, -9, 1}, 0, {160, 0}, {0, 0, 127, 255} }},
	{{ {91, -9, 1}, 0, {0, 0}, {0, 0, 127, 255} }},
};

Gfx desicionboxrim_desicionboxrim_mesh_tri_0[] = {
	gsSPVertex(desicionboxrim_desicionboxrim_mesh_vtx_0 + 0, 14, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(5, 8, 9, 0),
	gsSP1Triangle(5, 9, 10, 0),
	gsSP1Triangle(11, 4, 12, 0),
	gsSP1Triangle(11, 12, 13, 0),
	gsSPVertex(desicionboxrim_desicionboxrim_mesh_vtx_0 + 14, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPEndDisplayList(),
};

Gfx mat_desicionboxrim_f3dlite_material_013_layer1[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, 0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, 0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsDPSetTextureFilter(G_TF_POINT),
	gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 5, desicionboxrim_texbox_outline_ia8),
	gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 1, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTile(7, 0, 0, 16, 16),
	gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 1, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 3, 0, G_TX_CLAMP | G_TX_NOMIRROR, 3, 0),
	gsDPSetTileSize(0, 0, 0, 16, 16),
	gsSPEndDisplayList(),
};

Gfx mat_revert_desicionboxrim_f3dlite_material_013_layer1[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsDPSetTextureFilter(G_TF_BILERP),
	gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
	gsSPEndDisplayList(),
};

Gfx desicionboxrim_desicionboxrim_mesh[] = {
	gsSPDisplayList(mat_desicionboxrim_f3dlite_material_013_layer1),
	gsSPDisplayList(desicionboxrim_desicionboxrim_mesh_tri_0),
	gsSPDisplayList(mat_revert_desicionboxrim_f3dlite_material_013_layer1),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

