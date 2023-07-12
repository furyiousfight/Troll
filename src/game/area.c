#include <PR/ultratypes.h>

#include "config.h"
#include "area.h"
#include "sm64.h"
#include "gfx_dimensions.h"
#include "behavior_data.h"
#include "game_init.h"
#include "object_list_processor.h"
#include "engine/surface_load.h"
#include "ingame_menu.h"
#include "screen_transition.h"
#include "mario.h"
#include "mario_actions_cutscene.h"
#include "print.h"
#include "hud.h"
#include "audio/external.h"
#include "area.h"
#include "rendering_graph_node.h"
#include "level_update.h"
#include "engine/geo_layout.h"
#include "save_file.h"
#include "level_table.h"
#include "dialog_ids.h"
#include "puppyprint.h"
#include "debug_box.h"
#include "engine/colors.h"
#include "profiling.h"
#include "text_strings.h"
#include "actors/MinecraftLoad/header.h"
#include "actors/MinecraftPortal/header.h"
#include "seq_ids.h"
#include "src/game/fb_effects.h"
#include "actors/textbox_1/header.h"
#include "actors/desicionbox/header.h"
#include "actors/desicionboxrim/header.h"
u8 rtext_display[400];
u8 rtext_read[400];
u8 blank_text[400];
u8 *rtext_insert_pointer[3];
u8 rtext_read_index = 0;
u8 rtext_dialog_delay = 0;
u8 rtext_done = FALSE;
u8 rtext_choice = 0;
u8 rtext_choice_amount = 0;
u8 rtext_choice_index = 0;
u8 rtext_offset_buffer[4];
u16 rtext_current_read_dialog = 0;
    u8 selected = 0;
    u8 selectionCooldown;
    
    u8 textsteps = 1;
    u8 text_advance;
f32 rtext_opacity = 0.0f;
u8 TextAlpha;
u8 TherapyTextAlpha = 0;
u8 TextFadeTimer = 0;
Bool8 TextFadeOut;
extern s32 DoorTrollTimer;
extern u8 DoorTrollCounter;
Bool8 PrintTroll;
u8 PortalTimer;
u8 PortalTransTimer;
extern u8 NetherPortal[];
Bool8 MinecraftTrans;
Bool8 MinecraftWarp;
u32 MinecraftLoadingBar;
Bool8 InPortal;
u8 Therapy_State;
u16 Therapy_Timer;
u16 responseTimer;
u16 PsychTextTimer;
float TextBoxScale = 0.0f;
u8 finalChoice;
s32 dialog_id;


u16 choiceOneText[3];

u16 choiceOneTextAlpha;
u16 choiceTwoTextAlpha;
u16 choiceThreeTextAlpha;

u16 redResponseTextAlpha;
u16 redResponseAlpha;
u16 choiceOneAlpha;
u16 choiceOneAlpha2;
u16 choiceTwoAlpha;
u16 choiceTwoAlpha2;
u16 choiceThreeAlpha;
u16 choiceThreeAlpha2;
u16 choiceTwo[2];
u16 choiceThree[2];
u16 responseOffset[] = {20, 75, 160, 300, 0, 0, 0};
// 0 start pos, 1 text default pos, 2 default pos, 3 end pos, 4 custom pos box 1, 5 custom pos box 2-3, 6 text 1, 7 text 2


u8 ConfirmationColorsRed[2];
u8 ConfirmationColorsBlue1[2];
u8 ConfirmationColorsBlue2[2];
u8 ConfirmationColorsBlue3[2];

u16 textLength;

u8 responseState;
enum ResponseStates {
    RESPONSE_STATE_NONE,
    RESPONSE_STATE_RED_FADE_IN,
    RESPONSE_STATE_RED,
    RESPONSE_STATE_RED_FADE_OUT,
    RESPONSE_STATE_FADE_IN,
    RESPONSE_STATE_MAIN,
    RESPONSE_STATE_CONFIRM,
    RESPONSE_STATE_FADE_OUT,
    RESPONSE_STATE_SELECTED,
};

Bool8 endResponseEarly;
Bool8 endResponseRed;

u8 TextBoxState;
enum TextBoxStates {
    TEXTBOX_STATE_NONE,
    TEXTBOX_STATE_GROWING,
    TEXTBOX_STATE_FINISHED,
    TEXTBOX_STATE_SHRINKING,
};
extern Bool8 ZeroSitting;
u8 Door_Troll_1[] = { TEXT_DOOR_TROLL_1 };
u8 Door_Troll_2[] = { TEXT_DOOR_TROLL_2 };
u8 Door_Troll_3[] = { TEXT_DOOR_TROLL_3 };
u8 Door_Troll_4[] = { TEXT_DOOR_TROLL_4 };
u8 Door_Troll_5[] = { TEXT_DOOR_TROLL_5 };
u8 Door_Troll_6[] = { TEXT_DOOR_TROLL_6 };
u8 Door_Troll_7[] = { TEXT_DOOR_TROLL_7 };
u8 Door_Troll_8[] = { TEXT_DOOR_TROLL_8 };
u8 Door_Troll_9[] = { TEXT_DOOR_TROLL_9 };
u8 Door_Troll_10[] = { TEXT_DOOR_TROLL_10 };
u8 Door_Troll_11[] = { TEXT_DOOR_TROLL_11 };
u8 Door_Troll_12[] = { TEXT_DOOR_TROLL_12 };
u8 Door_Troll_13[] = { TEXT_DOOR_TROLL_13 };
u8 Door_Troll_14[] = { TEXT_DOOR_TROLL_14 };
u8 Door_Troll_15[] = { TEXT_DOOR_TROLL_15 };
u8 Door_Troll_16[] = { TEXT_DOOR_TROLL_16 };
u8 Door_Troll_17[] = { TEXT_DOOR_TROLL_17 };
u8 Door_Troll_18[] = { TEXT_DOOR_TROLL_18 };
u8 Door_Troll_19[] = { TEXT_DOOR_TROLL_19 };
u8 *Door_Troll_Array[] = {
&Door_Troll_1,
&Door_Troll_2,
&Door_Troll_3,
&Door_Troll_4,
&Door_Troll_5,
&Door_Troll_6,
&Door_Troll_7,
&Door_Troll_8,
&Door_Troll_9,
&Door_Troll_10,
&Door_Troll_11,
&Door_Troll_12,
&Door_Troll_13,
&Door_Troll_14,
&Door_Troll_15,
&Door_Troll_16,
&Door_Troll_17,
&Door_Troll_18,
&Door_Troll_19,
};

u8 Text_Therapy_Response_1[] = { TEXT_THERAPY_RESPONSE_1 };
u8 Text_Therapy_Response_2[] = { TEXT_THERAPY_RESPONSE_2 };
u8 Text_Therapy_Response_3[] = { TEXT_THERAPY_RESPONSE_3 };
Bool8 moveon;
u8 TrollNum;


struct SpawnInfo gPlayerSpawnInfos[1];
struct GraphNode *gGraphNodePointers[MODEL_ID_COUNT];
struct Area gAreaData[AREA_COUNT];

struct WarpTransition gWarpTransition;

s16 gCurrCourseNum;
s16 gCurrActNum;
s16 gCurrAreaIndex;
s16 gSavedCourseNum;
s16 gMenuOptSelectIndex;
s16 gSaveOptSelectIndex;

struct SpawnInfo *gMarioSpawnInfo = &gPlayerSpawnInfos[0];
struct GraphNode **gLoadedGraphNodes = gGraphNodePointers;
struct Area *gAreas = gAreaData;
struct Area *gCurrentArea = NULL;
struct CreditsEntry *gCurrCreditsEntry = NULL;

Vp *gViewportOverride = NULL;
Vp *gViewportClip = NULL;
s16 gWarpTransDelay = 0;
RGBA16FILL gFBSetColor = 0;
RGBA16FILL gWarpTransFBSetColor = 0;
Color gWarpTransRed= 0;
Color gWarpTransGreen = 0;
Color gWarpTransBlue = 0;
s16 gCurrSaveFileNum = 1;
s16 gCurrLevelNum = LEVEL_MIN;

/*
 * The following two tables are used in get_mario_spawn_type() to determine spawn type
 * from warp behavior.
 * When looping through sWarpBhvSpawnTable, if the behavior function in the table matches
 * the spawn behavior executed, the index of that behavior is used with sSpawnTypeFromWarpBhv
*/

const BehaviorScript *sWarpBhvSpawnTable[] = {
    bhvDoorWarp,                bhvStar,                   bhvExitPodiumWarp,          bhvWarp,
    bhvWarpPipe,                bhvFadingWarp,             bhvInstantActiveWarp,       bhvAirborneWarp,
    bhvHardAirKnockBackWarp,    bhvSpinAirborneCircleWarp, bhvDeathWarp,               bhvSpinAirborneWarp,
    bhvFlyingWarp,              bhvSwimmingWarp,           bhvPaintingStarCollectWarp, bhvPaintingDeathWarp,
    bhvAirborneStarCollectWarp, bhvAirborneDeathWarp,      bhvLaunchStarCollectWarp,   bhvLaunchDeathWarp,
};

u8 sSpawnTypeFromWarpBhv[] = {
    MARIO_SPAWN_DOOR_WARP,             MARIO_SPAWN_IDLE,                 MARIO_SPAWN_PIPE,                  MARIO_SPAWN_PIPE,
    MARIO_SPAWN_PIPE,                  MARIO_SPAWN_TELEPORT,             MARIO_SPAWN_INSTANT_ACTIVE,        MARIO_SPAWN_AIRBORNE,
    MARIO_SPAWN_HARD_AIR_KNOCKBACK,    MARIO_SPAWN_SPIN_AIRBORNE_CIRCLE, MARIO_SPAWN_DEATH,                 MARIO_SPAWN_SPIN_AIRBORNE,
    MARIO_SPAWN_FLYING,                MARIO_SPAWN_SWIMMING,             MARIO_SPAWN_PAINTING_STAR_COLLECT, MARIO_SPAWN_PAINTING_DEATH,
    MARIO_SPAWN_AIRBORNE_STAR_COLLECT, MARIO_SPAWN_AIRBORNE_DEATH,       MARIO_SPAWN_LAUNCH_STAR_COLLECT,   MARIO_SPAWN_LAUNCH_DEATH,
};

Vp gViewport = { {
    { 640, 480, 511, 0 },
    { 640, 480, 511, 0 },
} };

#if MULTILANG
const char *gNoControllerMsg[] = {
    "NO CONTROLLER",
    "MANETTE DEBRANCHEE",
    "CONTROLLER FEHLT",
};
#endif

void override_viewport_and_clip(Vp *vpOverride, Vp *vpClip, Color red, Color green, Color blue) {
    RGBA16 color = ((red >> 3) << IDX_RGBA16_R) | ((green >> 3) << IDX_RGBA16_G) | ((blue >> 3) << IDX_RGBA16_B) | MSK_RGBA16_A;

    gFBSetColor = (color << 16) | color;
    gViewportOverride = vpOverride;
    gViewportClip = vpClip;
}

void set_warp_transition_rgb(Color red, Color green, Color blue) {
    RGBA16 warpTransitionRGBA16 = ((red >> 3) << IDX_RGBA16_R) | ((green >> 3) << IDX_RGBA16_G) | ((blue >> 3) << IDX_RGBA16_B) | MSK_RGBA16_A;

    gWarpTransFBSetColor = (warpTransitionRGBA16 << 16) | warpTransitionRGBA16;
    gWarpTransRed = red;
    gWarpTransGreen = green;
    gWarpTransBlue = blue;
}

void print_intro_text(void) {
#if MULTILANG
    s32 language = eu_get_language();
#endif
    if ((gGlobalTimer & 31) < 20) {
        if (gControllerBits == 0) {
#if MULTILANG
            print_text_centered(SCREEN_CENTER_X, 20, gNoControllerMsg[language]);
#else
            print_text_centered(SCREEN_CENTER_X, 20, "NO CONTROLLER");
#endif
        } else {
#ifdef VERSION_EU
            print_text(20, 20, "START");
#else
            print_text_centered(60, 38, "PRESS");
            print_text_centered(60, 20, "START");
#endif
        }
    }
}

u32 get_mario_spawn_type(struct Object *obj) {
    s32 i;
    const BehaviorScript *behavior = virtual_to_segmented(SEGMENT_BEHAVIOR_DATA, obj->behavior);

    for (i = 0; i < 20; i++) {
        if (sWarpBhvSpawnTable[i] == behavior) {
            return sSpawnTypeFromWarpBhv[i];
        }
    }
    return MARIO_SPAWN_NONE;
}

struct ObjectWarpNode *area_get_warp_node(u8 id) {
    struct ObjectWarpNode *node = NULL;

    for (node = gCurrentArea->warpNodes; node != NULL; node = node->next) {
        if (node->node.id == id) {
            break;
        }
    }
    return node;
}

struct ObjectWarpNode *area_get_warp_node_from_params(struct Object *obj) {
    return area_get_warp_node(GET_BPARAM2(obj->oBehParams));
}

void load_obj_warp_nodes(void) {
    struct ObjectWarpNode *warpNode;
    struct Object *children = (struct Object *) gObjParentGraphNode.children;

    do {
        struct Object *obj = children;

        if (obj->activeFlags != ACTIVE_FLAG_DEACTIVATED && get_mario_spawn_type(obj) != 0) {
            warpNode = area_get_warp_node_from_params(obj);
            if (warpNode != NULL) {
                warpNode->object = obj;
            }
        }
    } while ((children = (struct Object *) children->header.gfx.node.next)
             != (struct Object *) gObjParentGraphNode.children);
}

void clear_areas(void) {
    s32 i;

    gCurrentArea = NULL;
    gWarpTransition.isActive = FALSE;
    gWarpTransition.pauseRendering = FALSE;
    gMarioSpawnInfo->areaIndex = -1;

    for (i = 0; i < AREA_COUNT; i++) {
        gAreaData[i].index = i;
        gAreaData[i].flags = AREA_FLAG_UNLOAD;
        gAreaData[i].terrainType = TERRAIN_GRASS;
        gAreaData[i].graphNode = NULL;
        gAreaData[i].terrainData = NULL;
        gAreaData[i].surfaceRooms = NULL;
        gAreaData[i].macroObjects = NULL;
        gAreaData[i].warpNodes = NULL;
        gAreaData[i].paintingWarpNodes = NULL;
        gAreaData[i].instantWarps = NULL;
        gAreaData[i].objectSpawnInfos = NULL;
        gAreaData[i].camera = NULL;
        gAreaData[i].unused = NULL;
        gAreaData[i].whirlpools[0] = NULL;
        gAreaData[i].whirlpools[1] = NULL;
        gAreaData[i].dialog[0] = DIALOG_NONE;
        gAreaData[i].dialog[1] = DIALOG_NONE;
        gAreaData[i].musicParam = 0;
        gAreaData[i].musicParam2 = 0;
    }
}

void clear_area_graph_nodes(void) {
    s32 i;

    if (gCurrentArea != NULL) {
#ifndef DISABLE_GRAPH_NODE_TYPE_FUNCTIONAL
        geo_call_global_function_nodes(&gCurrentArea->graphNode->node, GEO_CONTEXT_AREA_UNLOAD);
#endif
        gCurrentArea = NULL;
        gWarpTransition.isActive = FALSE;
    }

    for (i = 0; i < AREA_COUNT; i++) {
        if (gAreaData[i].graphNode != NULL) {
#ifndef DISABLE_GRAPH_NODE_TYPE_FUNCTIONAL
            geo_call_global_function_nodes(&gAreaData[i].graphNode->node, GEO_CONTEXT_AREA_INIT);
#endif
            gAreaData[i].graphNode = NULL;
        }
    }
}

void load_area(s32 index) {
    if (gCurrentArea == NULL && gAreaData[index].graphNode != NULL) {
        gCurrentArea = &gAreaData[index];
        gCurrAreaIndex = gCurrentArea->index;

        if (gCurrentArea->terrainData != NULL) {
            load_area_terrain(index, gCurrentArea->terrainData, gCurrentArea->surfaceRooms,
                              gCurrentArea->macroObjects);
        }

        if (gCurrentArea->objectSpawnInfos != NULL) {
            spawn_objects_from_info(0, gCurrentArea->objectSpawnInfos);
        }

        load_obj_warp_nodes();
#ifndef DISABLE_GRAPH_NODE_TYPE_FUNCTIONAL
        geo_call_global_function_nodes(&gCurrentArea->graphNode->node, GEO_CONTEXT_AREA_LOAD);
#endif
    }
}

void unload_area(void) {
    if (gCurrentArea != NULL) {
        unload_objects_from_area(0, gCurrentArea->index);
#ifndef DISABLE_GRAPH_NODE_TYPE_FUNCTIONAL
        geo_call_global_function_nodes(&gCurrentArea->graphNode->node, GEO_CONTEXT_AREA_UNLOAD);
#endif

        gCurrentArea->flags = AREA_FLAG_UNLOAD;
        gCurrentArea = NULL;
        gWarpTransition.isActive = FALSE;
    }
}

void load_mario_area(void) {
    stop_sounds_in_continuous_banks();
    load_area(gMarioSpawnInfo->areaIndex);

    if (gCurrentArea->index == gMarioSpawnInfo->areaIndex) {
        gCurrentArea->flags |= AREA_FLAG_LOAD;
        spawn_objects_from_info(0, gMarioSpawnInfo);
    }

    if (gAreaSkyboxStart[gCurrAreaIndex - 1]) {
        load_segment_decompress(SEGMENT_SKYBOX, gAreaSkyboxStart[gCurrAreaIndex - 1], gAreaSkyboxEnd[gCurrAreaIndex - 1]);
    }
}

void unload_mario_area(void) {
    if ((gCurrentArea != NULL) && (gCurrentArea->flags & AREA_FLAG_LOAD)) {
        unload_objects_from_area(0, gMarioSpawnInfo->activeAreaIndex);

        gCurrentArea->flags &= ~AREA_FLAG_LOAD;
        if (gCurrentArea->flags == AREA_FLAG_UNLOAD) {
            unload_area();
        }
    }
}

void change_area(s32 index) {
    s32 areaFlags = gCurrentArea->flags;

    if (gCurrAreaIndex != index) {
        unload_area();
        load_area(index);

        gCurrentArea->flags = areaFlags;
        gMarioObject->oActiveParticleFlags = ACTIVE_PARTICLE_NONE;
    }

    if (areaFlags & AREA_FLAG_LOAD) {
        gMarioObject->header.gfx.areaIndex = index, gMarioSpawnInfo->areaIndex = index;
    }
}

void area_update_objects(void) {
    gAreaUpdateCounter++;
    update_objects(0);
}

/*
 * Sets up the information needed to play a warp transition, including the
 * transition type, time in frames, and the RGB color that will fill the screen.
 */
void play_transition(s16 transType, s16 time, Color red, Color green, Color blue) {
#ifndef L3DEX2_ALONE
    gWarpTransition.isActive = TRUE;
    gWarpTransition.type = transType;
    gWarpTransition.time = time;
    gWarpTransition.pauseRendering = FALSE;

    // The lowest bit of transType determines if the transition is fading in or out.
    if (transType & WARP_TRANSITION_FADE_INTO) {
        set_warp_transition_rgb(red, green, blue);
    } else {
        red = gWarpTransRed, green = gWarpTransGreen, blue = gWarpTransBlue;
    }

    if (transType < WARP_TRANSITION_TYPE_STAR) { // if transition is WARP_TRANSITION_TYPE_COLOR
        gWarpTransition.data.red = red;
        gWarpTransition.data.green = green;
        gWarpTransition.data.blue = blue;
    } else { // if transition is textured
        gWarpTransition.data.red = red;
        gWarpTransition.data.green = green;
        gWarpTransition.data.blue = blue;

        // Both the start and end textured transition are always located in the middle of the screen.
        // If you really wanted to, you could place the start at one corner and the end at
        // the opposite corner. This will make the transition image look like it is moving
        // across the screen.
        gWarpTransition.data.startTexX = SCREEN_CENTER_X;
        gWarpTransition.data.startTexY = SCREEN_CENTER_Y;
        gWarpTransition.data.endTexX = SCREEN_CENTER_X;
        gWarpTransition.data.endTexY = SCREEN_CENTER_Y;

        gWarpTransition.data.texTimer = 0;

        if (transType & WARP_TRANSITION_FADE_INTO) { // Is the image fading in?
            gWarpTransition.data.startTexRadius = GFX_DIMENSIONS_FULL_RADIUS;
            if (transType >= WARP_TRANSITION_FADES_INTO_LARGE) {
                gWarpTransition.data.endTexRadius = 16;
            } else {
                gWarpTransition.data.endTexRadius = 0;
            }
        } else { // The image is fading out. (Reverses start & end circles)
            if (transType >= WARP_TRANSITION_FADES_FROM_LARGE) {
                gWarpTransition.data.startTexRadius = 16;
            } else {
                gWarpTransition.data.startTexRadius = 0;
            }
            gWarpTransition.data.endTexRadius = GFX_DIMENSIONS_FULL_RADIUS;
        }
    }
#endif
}

/*
 * Sets up the information needed to play a warp transition, including the
 * transition type, time in frames, and the RGB color that will fill the screen.
 * The transition will play only after a number of frames specified by 'delay'
 */
void play_transition_after_delay(s16 transType, s16 time, u8 red, u8 green, u8 blue, s16 delay) {
    gWarpTransDelay = delay; // Number of frames to delay playing the transition.
    play_transition(transType, time, red, green, blue);
}

void render_game(void) {
    if (gCurrentArea != NULL && !gWarpTransition.pauseRendering) {
        if (gCurrentArea->graphNode) {
            geo_process_root(gCurrentArea->graphNode, gViewportOverride, gViewportClip, gFBSetColor);
        }

        gSPViewport(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(&gViewport));

        gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, gBorderHeight, SCREEN_WIDTH,
                      SCREEN_HEIGHT - gBorderHeight);
        render_hud();
        if (gCurrLevelNum ==LEVEL_BOB){
                print_text_fmt_int(20, 20, "Therapy State: %d", Therapy_State);
            switch (Therapy_State){
                case 0:
                    therapy_timer_increment_to_state(30,1);
                    break;
                case 1:
                    render_psych_text_box(Therapy_State, DIALOG_001, &textbox_1_textbox_1_003_mesh, 95, 101, 20);
                    break;
                case 2:
                    break;
                case 3:
                    therapy_timer_increment_to_state(30,4);
                    break;
                case 4:
                    render_psych_text_box(Therapy_State, DIALOG_002, &textbox_1_textbox_1_003_mesh, 95, 101, 100);
                    respondable_dialog(60);
                    break;
            }
        }






        

if (InPortal == TRUE && MinecraftTrans == FALSE){
    if (PortalTransTimer < 255) {
        PortalTransTimer+=3;
    } if (PortalTransTimer >= 255) {
        MinecraftTrans = TRUE;
        PortalTransTimer = 0;
        set_background_music(0, SEQ_STREAMED_MUTATION, 0);
    }
    PortalTimer++;

        create_dl_ortho_matrix();
create_dl_translation_matrix(G_MTX_PUSH, 0, 0, 0);
gDPSetRenderMode(gDisplayListHead++,G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, PortalTransTimer);
gSPDisplayList(gDisplayListHead++, &MinecraftPortal_PortalTrans_mesh);

gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

        u8 *texture_location_in_ram3 = segmented_to_virtual(&MinecraftPortal_nether_portal_base_rgba32);
    dma_read(texture_location_in_ram3,(PortalTimer*1024)+NetherPortal,(PortalTimer*1024)+NetherPortal+1024);
    if (PortalTimer > 30) {
        PortalTimer = 0;
        }

} else {
    PortalTransTimer = 0;
    PortalTimer = 0;
}
if (MinecraftTrans == TRUE){
    set_mario_action(gMarioState, ACT_UNINITIALIZED, 0);
    create_dl_ortho_matrix();
create_dl_translation_matrix(G_MTX_PUSH, 0, 0, 0);
gDPSetRenderMode(gDisplayListHead++,G_RM_TEX_EDGE, G_RM_TEX_EDGE2);

gSPDisplayList(gDisplayListHead++, &MinecraftLoad_LoadingScreen_mesh);
u8 end = 217;
u16 MinecraftLoadingBarTimer;
u16 Rand;

if (MinecraftLoadingBarTimer == 0){
    MinecraftLoadingBarTimer = (random_u16() / 6000);
} if (MinecraftLoadingBarTimer > 0){
    MinecraftLoadingBarTimer--;
    Rand = (random_u16() / 8000);
}
gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
Vtx *MinecraftLoadingBar = segmented_to_virtual(&MinecraftLoad_LoadingScreen_mesh_vtx_2);
    if (MinecraftLoadingBar[0,0].v.ob[0] < 217 && MinecraftLoadingBarTimer == 0){
    MinecraftLoadingBar[0,0].v.ob[0]+=Rand;
    MinecraftLoadingBar[0,1].v.ob[0]+=Rand;
    MinecraftLoadingBar[0,6].v.ob[0]+=Rand;
    MinecraftLoadingBar[0,7].v.ob[0]+=Rand;
    }
    if (MinecraftLoadingBar[0,0].v.ob[0] >= 217){
    MinecraftLoadingBar[0,0].v.ob[0]=217;
    MinecraftLoadingBar[0,1].v.ob[0]=217;
    MinecraftLoadingBar[0,6].v.ob[0]=217;
    MinecraftLoadingBar[0,7].v.ob[0]=217;
    MinecraftWarp = TRUE;
    MinecraftTrans = FALSE;
    PortalTransTimer = 0;
    play_transition(WARP_TRANSITION_FADE_FROM_COLOR, 32767, 0, 0, 0);
    set_mario_action(gMarioState, ACT_IDLE, 0);
    }
} else {
    Vtx *MinecraftLoadingBar = segmented_to_virtual(&MinecraftLoad_LoadingScreen_mesh_vtx_2);
    MinecraftLoadingBar[0,0].v.ob[0]=105;
    MinecraftLoadingBar[0,1].v.ob[0]=105;
    MinecraftLoadingBar[0,6].v.ob[0]=105;
    MinecraftLoadingBar[0,7].v.ob[0]=105;
}

        //print_text_fmt_int(20, 200, "TrollNum %d", TrollNum);
        //print_text_fmt_int(20, 180, "DoorTrollTimer %d", DoorTrollTimer);
        if (DoorTrollCounter >= 1 && DoorTrollCounter <= 4){
            TrollNum = DoorTrollCounter - 1;
            PrintTroll = TRUE;
        } else if (DoorTrollCounter >= 6 && DoorTrollCounter <= 19){
            TrollNum = DoorTrollCounter - 2;
            PrintTroll = TRUE;
        } else if (DoorTrollCounter >= 25 ){
            TrollNum = 18;
            PrintTroll = TRUE;
        } else {
            PrintTroll = FALSE;
        }
        if (PrintTroll == TRUE){
            gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
            gDPSetEnvColor(gDisplayListHead++, 0x36, 0x45, 0x4F, TextAlpha);
            print_generic_string(6,39,Door_Troll_Array[TrollNum]);
            gDPSetEnvColor(gDisplayListHead++, 0xA6, 0xD9, 0xF1, TextAlpha);
            print_generic_string(5,40,Door_Troll_Array[TrollNum]);
        }
        if (DoorTrollTimer <= 3){
            TextAlpha = 255;
        }
        if (DoorTrollTimer >= 600 && TextAlpha >= 10){
                    TextAlpha -= 10;
                    } else if (TextAlpha < 10){
                        TextAlpha = 0;
                    }

        gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        render_text_labels();
        do_cutscene_handler();
        print_displaying_credits_entry();
        gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, gBorderHeight, SCREEN_WIDTH,
                      SCREEN_HEIGHT - gBorderHeight);
        gMenuOptSelectIndex = render_menus_and_dialogs();

        if (gMenuOptSelectIndex != 0) {
            gSaveOptSelectIndex = gMenuOptSelectIndex;
        }

        if (gViewportClip != NULL) {
            make_viewport_clip_rect(gViewportClip);
        } else
            gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, gBorderHeight, SCREEN_WIDTH,
                          SCREEN_HEIGHT - gBorderHeight);

        if (gWarpTransition.isActive) {
            if (gWarpTransDelay == 0) {
                gWarpTransition.isActive = !render_screen_transition(0, gWarpTransition.type, gWarpTransition.time,
                                                                     &gWarpTransition.data);
                if (!gWarpTransition.isActive) {
                    if (gWarpTransition.type & WARP_TRANSITION_FADE_INTO) {
                        gWarpTransition.pauseRendering = TRUE;
                    } else {
                        set_warp_transition_rgb(0, 0, 0);
                    }
                }
            } else {
                gWarpTransDelay--;
            }
        }
    } else {
        render_text_labels();
        if (gViewportClip != NULL) {
            clear_viewport(gViewportClip, gWarpTransFBSetColor);
        } else {
            clear_framebuffer(gWarpTransFBSetColor);
        }
    }

    gViewportOverride = NULL;
    gViewportClip     = NULL;
    
    profiler_update(PROFILER_TIME_GFX);
    profiler_print_times();
#if PUPPYPRINT_DEBUG
    puppyprint_render_profiler();
#endif
}

void read_dialog(s32 dialog_id) {
    u16 char_in_array;
    u16 iwrite;

    u8 **dialogTable = segmented_to_virtual(seg2_dialog_table);
    struct DialogEntry *sdialog = segmented_to_virtual(dialogTable[dialog_id]);
    u8 *sstr = segmented_to_virtual(sdialog->str);

    rtext_current_read_dialog = dialog_id;

    char_in_array = 0;
    iwrite = 0;
    while(sstr[char_in_array] != DIALOG_CHAR_TERMINATOR) {
        
            rtext_read[iwrite] = sstr[char_in_array];
            iwrite++;
            
        char_in_array++;
    }
    

    rtext_read[iwrite] = DIALOG_CHAR_TERMINATOR;
    rtext_read_index = 0;
}

void type_on_text(textx, texty){
 if (TextBoxState == TEXTBOX_STATE_FINISHED){
        for (text_advance=0;text_advance<textsteps;text_advance++) {
            if (rtext_read[rtext_read_index] != DIALOG_CHAR_TERMINATOR) {
                if (rtext_dialog_delay == 0) {
                    rtext_display[rtext_read_index] = rtext_read[rtext_read_index];
                    rtext_display[rtext_read_index+1] = DIALOG_CHAR_TERMINATOR;
                    TherapyTextAlpha = 255;

                    if (rtext_read[rtext_read_index] != DIALOG_CHAR_SPACE) {

                            play_sound(SOUND_MENU_THANK_YOU_PLAYING_MY_GAME,gGlobalSoundSource);
                        rtext_dialog_delay = 2;
                    }
                    if (rtext_read[rtext_read_index] == DIALOG_CHAR_COMMA) {
                        rtext_dialog_delay = 4;
                    }
                    if (rtext_read[rtext_read_index] == 0x3F) {
                        rtext_dialog_delay = 6;
                    }
                    if (rtext_read[rtext_read_index] == 0xF2) {
                        rtext_dialog_delay = 6;
                    }

                    rtext_read_index ++;
                } else {
                    rtext_dialog_delay --;
                }
            } else {
                //done reading
                rtext_done = TRUE;
                
                
                
                
            }
    }
 } else { 
    
 }
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, TherapyTextAlpha);
        print_generic_string(textx,texty, rtext_display);//rtext_pressa
        
}


void render_psych_text_box(state, dialog_id, DisplayList, textx, texty, postdialogframes){
            textLength = postdialogframes;
            Bool8 init_dialog = FALSE;
            //print_text_fmt_int(10, 15, "Therapy Timer: %d", Therapy_Timer);
            //print_text_fmt_int(10, 30, "TextFadeTimer: %d", TextFadeTimer);
            //print_text_fmt_int(10, 30, "TherapyTextAlpha: %d", TherapyTextAlpha);
            //print_text_fmt_int(10, 45, "TextBoxState: %d", TextBoxState);
            if (TextBoxState == TEXTBOX_STATE_NONE){
                TextFadeTimer = 0;
                TextBoxState = TEXTBOX_STATE_GROWING;
            } if (TextBoxState == TEXTBOX_STATE_GROWING){
                if (TextBoxScale < 1.0f) {
                TextBoxScale+=0.15f;
                } if (TextBoxScale >= 1.0f) {
                    TextBoxState = TEXTBOX_STATE_FINISHED;

                    init_dialog = TRUE;
                    TextBoxScale = 1.0f;
                }
                create_dl_translation_matrix(G_MTX_PUSH, 185, 118, 0);
                create_dl_scale_matrix(G_MTX_PUSH, 1.0f, TextBoxScale, 1.0f);
                gDPSetRenderMode(gDisplayListHead++,G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
                gSPDisplayList(gDisplayListHead++, DisplayList);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW); 

                
            } if (TextBoxState == TEXTBOX_STATE_FINISHED){
                create_dl_translation_matrix(G_MTX_PUSH, 185, 118, 0);
                gDPSetRenderMode(gDisplayListHead++,G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
                gSPDisplayList(gDisplayListHead++, DisplayList);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                if (init_dialog == TRUE){
                read_dialog(dialog_id);
                init_dialog = FALSE;
                }
                type_on_text(textx,texty);
                if ((rtext_read[rtext_read_index] == DIALOG_CHAR_TERMINATOR)){
                    TextFadeTimer++;

                
                    if (responseState == RESPONSE_STATE_NONE){
                    if (TherapyTextAlpha > 25){
                    TherapyTextAlpha-=25;
                    } else if (TherapyTextAlpha <= 25){
                        TherapyTextAlpha = 0;
                        TextBoxState = TEXTBOX_STATE_SHRINKING;
                        TextBoxScale = 1.0f;
                    }
                    }
                }
                }
                 if (TextBoxState == TEXTBOX_STATE_SHRINKING){
                    if (TextBoxScale > 0.0f){
                    TextBoxScale-=0.15f;
                 } else if (TextBoxScale <= 0.0f){
                    TextBoxState = TEXTBOX_STATE_NONE;
                    Therapy_State = state + 1;
                    TextBoxScale = 0.0f;

                    }
                    
                    create_dl_translation_matrix(G_MTX_PUSH, 185, 118, 0);
                create_dl_scale_matrix(G_MTX_PUSH, 1.0f, TextBoxScale, 1.0f);
                gDPSetRenderMode(gDisplayListHead++,G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
                gSPDisplayList(gDisplayListHead++, DisplayList);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW); 
                }
            }

void therapy_timer_increment_to_state(frames_spent, intended_state){
    Therapy_Timer++;
    if (Therapy_Timer > frames_spent){
        Therapy_Timer = 0;
        Therapy_State = intended_state;
    }
}

void respondable_dialog(redWindow, ansRedStateReturn, ans1StateReturn, ans2StateReturn, ans3StateReturn){

    print_text_fmt_int(10, 15, "responseState: %d", responseState);
    if (selectionCooldown > 0){
        selectionCooldown--;
    } if (responseState == RESPONSE_STATE_NONE && TextBoxState == TEXTBOX_STATE_FINISHED){
        finalChoice = 0;
        choiceOneAlpha = 0;
        choiceOneAlpha2 = 0;
        choiceOneTextAlpha = 0;
        choiceOneText[0] = 0x97;
        choiceOneText[1] = 0x02;
        choiceOneText[2] = 0x02;
        if (redWindow > 0){
        responseState = RESPONSE_STATE_RED_FADE_IN;
        } else {
        responseState = RESPONSE_STATE_FADE_IN;
        }

    } if (responseState == RESPONSE_STATE_RED_FADE_IN){

        if (responseOffset[4] < responseOffset[2]){
            responseOffset[4]+=10;
        } if (responseOffset[4] >= responseOffset[2]){
            responseOffset[4] = responseOffset[2];
        }
        if (redResponseTextAlpha < 255) {
            redResponseTextAlpha+=13;
            redResponseAlpha+=13;
        } if (redResponseTextAlpha >= 255) {
            redResponseTextAlpha = 255;
            redResponseAlpha = 255;
            responseState = RESPONSE_STATE_RED;
        }
        print_text_fmt_int(20,195, "choiceOneAlpha2: %d", choiceOneAlpha2);
        print_text_fmt_int(20,180, "choiceOneAlpha: %d", choiceOneAlpha);
        print_text_fmt_int(20,165, "ResponseOffset4: %d", responseOffset[4]);

    }
    if (responseState == RESPONSE_STATE_RED){
        if (gPlayer1Controller->buttonPressed & A_BUTTON){
            finalChoice = 0;
        endResponseRed = TRUE;
        }
        responseTimer++;
        print_text_fmt_int(20,195, "responseTimer: %d", responseTimer);
        if (responseTimer >= redWindow && endResponseRed == FALSE){
            responseState = RESPONSE_STATE_RED_FADE_OUT;
            responseTimer = 0;
        } else if (endResponseRed == TRUE){
            responseState = RESPONSE_STATE_SELECTED;
            responseTimer = 0;
        }
    } if (responseState == RESPONSE_STATE_RED_FADE_OUT){

            responseOffset[4]+=10;

        if (redResponseTextAlpha > 25) {
            redResponseTextAlpha-=25;
            redResponseAlpha-=25;
        } if (redResponseTextAlpha <= 25) {
            redResponseTextAlpha = 0;
            redResponseAlpha = 0;
            responseState = RESPONSE_STATE_FADE_IN;
            choiceOneAlpha = 0;
            choiceOneAlpha2 = 0;
            choiceTwoAlpha = 0;
            choiceTwoAlpha2 = 0;
            choiceThreeAlpha = 0;
            choiceThreeAlpha2 = 0;
            responseOffset[4]=0;
            
        }
    } if (responseState == RESPONSE_STATE_FADE_IN){
        print_text_fmt_int(0,195, "choiceOneAlpha: %d", choiceOneAlpha);
        print_text_fmt_int(0,180, "choiceOneAlpha2: %d", choiceOneAlpha2);
        print_text_fmt_int(0,165, "choiceTwoAlpha: %d", choiceTwoAlpha);
        print_text_fmt_int(0,150, "choiceTwoAlpha2: %d", choiceTwoAlpha2);
        print_text_fmt_int(0,135, "choiceThreeAlpha: %d", choiceThreeAlpha);
        print_text_fmt_int(0,120, "choiceThreeAlpha2: %d", choiceThreeAlpha2);

        if (responseOffset[4] < responseOffset[2]){
            responseOffset[4]+=10;
            responseOffset[5]+=10;
            responseOffset[6]+=10;
        } if (responseOffset[4] >= responseOffset[2]){
            responseOffset[4] = responseOffset[2];
            responseOffset[5] = responseOffset[2];
            responseOffset[6] = responseOffset[2];
        }
        if (choiceOneAlpha < 255) {
            choiceOneAlpha+=13;
            choiceOneAlpha2+=13;
            choiceTwoAlpha2+=13;
            choiceThreeAlpha2+=13;
        } if (choiceOneAlpha2 >= 255) {
            choiceOneAlpha = 255;
            choiceOneAlpha2 = 255;
            choiceTwoAlpha2 = 255;
            choiceThreeAlpha2 = 255;
            responseState = RESPONSE_STATE_MAIN;
            selected = 0;
        }


    }
    if (responseState == RESPONSE_STATE_MAIN){
        responseTimer++;
        if (responseTimer >= textLength || endResponseEarly == TRUE){
            responseState = RESPONSE_STATE_CONFIRM;
            finalChoice = selected;
            responseTimer = 0;
        } 

        if (selected < 2){
            if (gPlayer1Controller->stickY < 0 && selectionCooldown == 0){
                selected++;
                selectionCooldown = 6;
            } 
            } if (selected > 0){
                if (gPlayer1Controller->stickY > 0 && selectionCooldown == 0){
                selected--;
                selectionCooldown = 10;
            }//0DA099 blue
        } //970202 red
     if (gPlayer1Controller->buttonPressed & A_BUTTON){
        play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
        endResponseEarly = TRUE;
    }
    if (selected == 0){
        choiceOneAlpha = 255;
    } else {
        if (choiceOneAlpha >= 25) {
            choiceOneAlpha-=25;
        } if (choiceOneAlpha < 25) {
            choiceOneAlpha = 0;
        }
    } if (selected == 1){
        choiceTwoAlpha = 255;
    } else {
        if (choiceTwoAlpha >= 25) {
            choiceTwoAlpha-=25;
        } if (choiceTwoAlpha < 25) {
            choiceTwoAlpha = 0;
        }
    } if (selected == 2){
        choiceThreeAlpha = 255;
    } else {
        if (choiceThreeAlpha >= 25) {
            choiceThreeAlpha-=25;
        } if (choiceThreeAlpha < 25) {
            choiceThreeAlpha = 0;
        }
    }
    } if (responseState == RESPONSE_STATE_CONFIRM){
            responseTimer++;
            if (selected == 0){
                responseOffset[5]+=10;
                responseOffset[6]+=10;
                if (choiceTwoAlpha2 >= 25) {
                    choiceTwoAlpha-=25;
                    choiceThreeAlpha-=25;
                    choiceTwoAlpha2-=25;
                    choiceThreeAlpha2-=25;
                } 
                if (choiceTwoAlpha2 < 25) {
                    choiceTwoAlpha = 0;
                    choiceThreeAlpha = 0;
                    choiceTwoAlpha2 = 0;
                    choiceThreeAlpha2 = 0;
            }
            } if (selected == 1){
                responseOffset[4]+=10;
                responseOffset[6]+=10;

                if (choiceOneAlpha2 >= 25) {
                    choiceOneAlpha-=25;
                    choiceThreeAlpha-=25;
                    choiceOneAlpha2-=25;
                    choiceThreeAlpha2-=25;
                } 
                if (choiceOneAlpha2 < 25) {
                    choiceOneAlpha = 0;
                    choiceThreeAlpha = 0;
                    choiceOneAlpha2 = 0;
                    choiceThreeAlpha2 = 0;
            }
            }
            if (responseTimer >= 30){
                responseState = RESPONSE_STATE_SELECTED;
                responseTimer = 0;
            }
        } if (responseState == RESPONSE_STATE_SELECTED){
            if (redResponseTextAlpha >= 25) {
                redResponseTextAlpha-=25;
                redResponseAlpha-=25;
            } if (redResponseTextAlpha < 25) {
                redResponseTextAlpha = 0;
                redResponseAlpha = 0;
            }
            if (choiceOneAlpha2 >= 25) {
                choiceOneAlpha2-=25;
                choiceOneAlpha-=25;
            } if (choiceOneAlpha2 < 25) {
                choiceOneAlpha2 = 0;
                choiceOneAlpha = 0;
            }
            if (choiceTwoAlpha2 >= 25) {
                choiceTwoAlpha2-=25;
                choiceTwoAlpha-=25;
            } if (choiceTwoAlpha2 < 25) {
                choiceTwoAlpha2 = 0;
                choiceTwoAlpha = 0;
            }
            if (choiceThreeAlpha2 >= 25) {
                choiceThreeAlpha2-=25;
                choiceThreeAlpha-=25;
            } if (choiceThreeAlpha2 < 25) {
                choiceThreeAlpha2 = 0;
                choiceThreeAlpha = 0;
            }
            if (choiceThreeAlpha2 == 0 && choiceTwoAlpha2 == 0 && choiceOneAlpha2 == 0 || redResponseTextAlpha == 0){
                responseState = RESPONSE_STATE_NONE;
                if (finalChoice == 0){
                Therapy_State = ans1StateReturn;
                } else if (finalChoice == 1){
                Therapy_State = ans2StateReturn;
                } else if (finalChoice == 2){
                Therapy_State = ans3StateReturn;
                }
            }
            
        } 
    
                //red response 
                
                create_dl_translation_matrix(G_MTX_PUSH, responseOffset[4], 55, 0);
                gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, redResponseTextAlpha);
                gSPDisplayList(gDisplayListHead++, &desicionbox_desicionbox_mesh);
                gDPSetEnvColor(gDisplayListHead++, 0x97, 0x02, 0x02, redResponseAlpha);
                gSPDisplayList(gDisplayListHead++, &desicionboxrim_desicionboxrim_mesh);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                
                gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
                gDPSetEnvColor(gDisplayListHead++, 0x97, 0x02, 0x02, redResponseTextAlpha);
                print_generic_string(responseOffset[4]-75,47, Text_Therapy_Response_1);//rtext_pressa    
                
                      
                //option 1
                create_dl_translation_matrix(G_MTX_PUSH, responseOffset[4], 55, 0);
                gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, choiceOneAlpha2);
                gSPDisplayList(gDisplayListHead++, &desicionbox_desicionbox_mesh);
                gDPSetEnvColor(gDisplayListHead++, 0x0D, 0xA0, 0x99, choiceOneAlpha);
                gSPDisplayList(gDisplayListHead++, &desicionboxrim_desicionboxrim_mesh);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                
                gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, choiceOneAlpha2);
                print_generic_string(responseOffset[4]-85,47, Text_Therapy_Response_1);//rtext_pressa
                //option 2
                create_dl_translation_matrix(G_MTX_PUSH, responseOffset[5], 35, 0);
                gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, choiceTwoAlpha2);
                gSPDisplayList(gDisplayListHead++, &desicionbox_desicionbox_mesh);
                gDPSetEnvColor(gDisplayListHead++, 0x0D, 0xA0, 0x99, choiceTwoAlpha);
                gSPDisplayList(gDisplayListHead++, &desicionboxrim_desicionboxrim_mesh);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

                gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, choiceTwoAlpha2);
                print_generic_string(responseOffset[5]-85,27, Text_Therapy_Response_2);//rtext_pressa
                //option 3
                create_dl_translation_matrix(G_MTX_PUSH, responseOffset[6], 15, 0);
                gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, choiceThreeAlpha2);
                gSPDisplayList(gDisplayListHead++, &desicionbox_desicionbox_mesh);
                gDPSetEnvColor(gDisplayListHead++, 0x0D, 0xA0, 0x99, choiceThreeAlpha);
                gSPDisplayList(gDisplayListHead++, &desicionboxrim_desicionboxrim_mesh);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

                gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, choiceThreeAlpha2);
                print_generic_string(responseOffset[6]-85,7, Text_Therapy_Response_3);//rtext_pressa
                
}