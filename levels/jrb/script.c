#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/level_update.h"

#include "levels/scripts.h"

#include "actors/common1.h"

/* Fast64 begin persistent block [includes] */
/* Fast64 end persistent block [includes] */

#include "make_const_nonconst.h"
#include "levels/jrb/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_jrb_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _jrb_segment_7SegmentRomStart, _jrb_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x0B, _effect_yay0SegmentRomStart, _effect_yay0SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _water_yay0SegmentRomStart, _water_yay0SegmentRomEnd), 
	LOAD_YAY0(0x0A, _clouds_skybox_yay0SegmentRomStart, _clouds_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group4_yay0SegmentRomStart, _group4_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group3_geoSegmentRomStart, _group3_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group13_yay0SegmentRomStart, _group13_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group13_geoSegmentRomStart, _group13_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	LOAD_MIO0(0x7, _jrb_segment_7SegmentRomStart, _jrb_segment_7SegmentRomEnd), 
	LOAD_MIO0(0xa, _water_skybox_mio0SegmentRomStart, _water_skybox_mio0SegmentRomEnd), 
	LOAD_MIO0(0x5, _group3_mio0SegmentRomStart, _group3_mio0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_4), 
	JUMP_LINK(script_func_global_14), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_SHIP_LEFT_HALF_PART, jrb_geo_000978), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_SHIP_BACK_LEFT_PART, jrb_geo_0009B0), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_SHIP_RIGHT_HALF_PART, jrb_geo_0009E8), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_SHIP_BACK_RIGHT_PART, jrb_geo_000A00), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_SUNKEN_SHIP, jrb_geo_000990), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_SUNKEN_SHIP_BACK, jrb_geo_0009C8), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_ROCK, jrb_geo_000930), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_SLIDING_BOX, jrb_geo_000960), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_FALLING_PILLAR, jrb_geo_000900), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_FALLING_PILLAR_BASE, jrb_geo_000918), 
	LOAD_MODEL_FROM_GEO(MODEL_JRB_FLOATING_PLATFORM, jrb_geo_000948), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, jrb_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_ENDING, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_ENDING, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_PIKMIN, -755, -249, 1721, 0, 0, 0, 0x00000000, bhvPikmin),
		OBJECT(MODEL_SOPHIE, -87, -249, 3133, 0, 0, 0, (159 << 16), bhvSophie),
		OBJECT(MODEL_BULBORB, 143, -249, -3969, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, -82, -249, -4841, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, -504, -249, -4337, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, -989, -249, -3972, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, -1293, -249, -4810, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, -1645, -249, -4147, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_GATE, -170, 529, -868, 0, 0, 0, (3 << 16), bhvGate),
		OBJECT(MODEL_PURPLE_SWITCH, -1866, -248, -1529, 0, 0, 0, (3 << 16), bhvFloorSwitchHardcodedModel),
		OBJECT(MODEL_GATE, -1651, 529, -5240, 0, 0, 0, (1 << 16), bhvGate),
		OBJECT(MODEL_PURPLE_SWITCH, 556, -248, -6509, 0, 0, 0, (1 << 16), bhvFloorSwitchHardcodedModel),
		OBJECT(MODEL_GATE, 220, 552, -7366, 0, 0, 0, (2 << 16), bhvGate),
		OBJECT(MODEL_PURPLE_SWITCH, -1683, 1440, -7098, 0, 0, 0, (2 << 16), bhvFloorSwitchHardcodedModel),
		OBJECT(MODEL_BULBORB, 486, -249, -7082, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, -267, -249, -6899, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_WOODEN_SIGNPOST, -755, -249, 2761, 0, 0, 0, (38 << 24) | (38 << 16), bhvMessagePanel),
		OBJECT(MODEL_BULBORB, 2128, -249, -9040, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, 1375, -249, -8857, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, 1712, -249, -9046, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, 1932, -249, -8872, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, 2398, -249, -8853, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, 2426, -249, -8676, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, 2814, -249, -8536, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, 2643, -249, -8331, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, 2783, -249, -8021, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, 2534, -249, -7822, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, 2606, -249, -7645, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, 2184, -249, -7453, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, 2389, -249, -7356, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, 1764, -249, -7390, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, 1441, -249, -7328, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, 1454, -249, -7561, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, 1575, -249, -8822, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, 1907, -249, -9161, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, 1317, -249, -8449, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_BULBORB, 1305, -249, -7996, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_KING_BOBOMB, 1951, -249, -8189, 0, 0, 0, 0x00000000, bhvKingBobomb),
		OBJECT(MODEL_NONE, -748, -249, 3250, 0, 180, 0, 0x000A0000, bhvSpinAirborneWarp),
		MARIO_POS(0x01, 180, -748, -249, 3250),
		TERRAIN(jrb_area_1_collision),
		MACRO_OBJECTS(jrb_area_1_macro_objs),
		STOP_MUSIC(0),
		SHOW_DIALOG(0x00, DIALOG_100),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 180, -748, -249, 3250),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
