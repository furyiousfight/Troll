const Collision gate_collision[] = {
	COL_INIT(),
	COL_VERTEX_INIT(12),
	COL_VERTEX(-647, 0, -51),
	COL_VERTEX(-647, 0, 51),
	COL_VERTEX(647, 0, 51),
	COL_VERTEX(647, 0, -51),
	COL_VERTEX(647, -812, 51),
	COL_VERTEX(-647, -812, 51),
	COL_VERTEX(-647, -812, -51),
	COL_VERTEX(647, -812, -51),
	COL_VERTEX(647, 1262, 51),
	COL_VERTEX(-647, 1262, 51),
	COL_VERTEX(-647, 1262, -51),
	COL_VERTEX(647, 1262, -51),
	COL_TRI_INIT(SURFACE_DEFAULT, 10),
	COL_TRI(0, 1, 2),
	COL_TRI(0, 2, 3),
	COL_TRI(4, 2, 1),
	COL_TRI(4, 1, 5),
	COL_TRI(6, 0, 3),
	COL_TRI(6, 3, 7),
	COL_TRI(1, 2, 8),
	COL_TRI(1, 8, 9),
	COL_TRI(3, 0, 10),
	COL_TRI(3, 10, 11),
	COL_TRI_STOP(),
	COL_END()
};
