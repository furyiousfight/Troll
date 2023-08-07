Lights1 background_f3dlite_material_lights = gdSPDefLights1(
	0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x28, 0x28, 0x28);

Vtx background_background_mesh_vtx_0[4] = {
	{{ {0, 0, 0}, 0, {-16, 9200}, {0, 0, 127, 162} }},
	{{ {321, 0, 0}, 0, {12272, 9200}, {0, 0, 127, 162} }},
	{{ {321, 240, 0}, 0, {12272, -16}, {0, 0, 127, 162} }},
	{{ {0, 240, 0}, 0, {-16, -16}, {0, 0, 127, 162} }},
};

Gfx background_background_mesh_tri_0[] = {
	gsSPVertex(background_background_mesh_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_background_f3dlite_material[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(background_f3dlite_material_lights),
	gsSPEndDisplayList(),
};

Gfx background_background_mesh[] = {
	gsSPDisplayList(mat_background_f3dlite_material),
	gsSPDisplayList(background_background_mesh_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

