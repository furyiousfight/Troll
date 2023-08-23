
/**
 * This is the behavior file for the tilting inverted pyramids in BitFS/LLL.
 * The object essentially just tilts and moves Mario with it.
 */

/**
 * Initialize the object's transform matrix with Y being up.
 */
#include "actors/DRExplosion/geo_header.h"
#include "actors/nether/geo_header.h"
#include "actors/psychiatristsit/geo_header.h"
#include "actors/psych_stand/geo_header.h"
#include "actors/psych_walk/geo_header.h"
#include "actors/zero/geo_header.h"
#include "actors/zero_walk/geo_header.h"
#include "actors/zero_sit/geo_header.h"
#include "actors/katana_a_button/geo_header.h"
#include "actors/psych_killrock/geo_header.h"
#include "actors/psych_getneedle/geo_header.h"
#include "actors/psych_walkneedle/geo_header.h"
#include "actors/psych_inject/geo_header.h"
#include "levels/bob/header.h"
#include "actors/frisk/geo_header.h"
Bool8 pressedSwitch[9];
extern Bool8 isPikmin;
f32 pikminScale;
s16 cachedMarioPosAndFaceAngle[3];
s16 cachedPikminPosAndFaceAngle[3];
extern u16 sophieCutsceneState;
extern u8 undertaleDialogState;
extern u8 undertaleTimer;
s16 NetherPos[2];
s16 friskPos[2];
Bool8 undertaleWarp;
u8 undertaleArea;
extern struct MarioState *gMarioState;
extern u8 therapyState;
extern Bool8 InPortal;
extern u8 DRExplosion[];

extern u8 frisk_front[];
extern u8 frisk_back[];
extern u8 frisk_side[];
extern u8 psych_sit[];
extern u8 psych_stand[];
extern u8 psych_walk[];
extern u8 fireplace[];
extern u8 zero_idle[];
extern u8 zero_walk[];
extern u8 zero_sit[];
extern u8 katana_a[];
extern u8 psych_killrock[];
extern u8 psych_getneedle[];
extern u8 psych_walkneedle[];
extern u8 psych_inject[];
u8 PsychSitFrame;
u8 PsychStandFrame;
u8 PsychWalkFrame;
u8 PsychKillRockFrame;
u8 PsychDeskFrame;
u8 PsychWalkSyringeFrame;
u8 PsychInjectFrame;
u8 PsychState;
Bool8 WalkToChair;
Bool8 WalkingLeft;
Bool8 WalkingRight;
u8 AFade;
Bool8 ZeroInjected;
Bool8 ZeroKilled;
Bool8 FreeMario = FALSE;
enum AButtonFadeStates{
    A_FADE_NONE,
    A_FADE_OPAQUE,
    A_FADE_IN,
    A_FADE_OUT
};

enum PsychStates{
    PSYCH_NONE,
    PSYCH_SIT,
    PSYCH_STAND,
    PSYCH_WALK,
    PSYCH_DESK,
    PSYCH_WALK_SYRINGE,
    PSYCH_INJECT,
    PSYCH_KILLROCK,
};

u8 FireplaceFrame;
u8 AFrame;
u8 LoopOffset;
u8 ZeroIdleFrame;
u8 ZeroWalkFrame;
u8 ZeroSitFrame;
Bool8 ZeroSitting;
Bool8 SitRange;

void bhv_platform_normals_init(void) {
    vec3f_set(&o->oTiltingPyramidNormalVec, 0.0f, 1.0f, 0.0f);
    mtxf_align_terrain_normal(o->transform, &o->oTiltingPyramidNormalVec, &o->oPosVec, 0);
}

/**
 * Main behavior for the tilting pyramids in LLL/BitFS. These platforms calculate rough normals from Mario's position,
 * then gradually tilt back moving Mario with them.
 */
void bhv_tilting_inverted_pyramid_loop(void) {
#ifndef PLATFORM_DISPLACEMENT_2
    Vec3f posBeforeRotation, posAfterRotation;
    Vec3f marioPos, dist;
#endif
    Vec3f targetNormal;
    Mat4 *transform = &o->transform;
    s32 marioOnPlatform = (gMarioObject->platform == o);

    if (marioOnPlatform) {
#ifndef PLATFORM_DISPLACEMENT_2
        // Target the normal in Mario's direction
        vec3_diff(dist, gMarioStates[0].pos, &o->oPosVec);

        // Get Mario's position before the rotation
        vec3f_copy(marioPos, gMarioStates[0].pos);

        linear_mtxf_mul_vec3f(*transform, posBeforeRotation, dist);
        targetNormal[0] = dist[0];
        targetNormal[2] = dist[2];
#else // PLATFORM_DISPLACEMENT_2
        targetNormal[0] = gMarioStates[0].pos[0] - o->oPosX;
        targetNormal[2] = gMarioStates[0].pos[2] - o->oPosZ;
#endif
        targetNormal[1] = 500.0f;
        vec3f_normalize(targetNormal);
    } else {
        // Target normal is directly upwards when Mario is not on the platform.
        vec3f_set(targetNormal, 0.0f, 1.0f, 0.0f);
    }

    // Approach the normals by 0.01f towards the new goal, then create a transform matrix and orient the object. 
    // Outside of the other conditionals since it needs to tilt regardless of whether Mario is on.
    approach_f32_symmetric_bool(&o->oTiltingPyramidNormalX, targetNormal[0], 0.01f);
    approach_f32_symmetric_bool(&o->oTiltingPyramidNormalY, targetNormal[1], 0.01f);
    approach_f32_symmetric_bool(&o->oTiltingPyramidNormalZ, targetNormal[2], 0.01f);
    mtxf_align_terrain_normal(*transform, &o->oTiltingPyramidNormalVec, &o->oPosVec, 0x0);

#ifndef PLATFORM_DISPLACEMENT_2
    // If Mario is on the platform, adjust his position for the platform tilt.
    if (marioOnPlatform) {
        linear_mtxf_mul_vec3f(*transform, posAfterRotation, dist);
        marioPos[0] += posAfterRotation[0] - posBeforeRotation[0];
        marioPos[1] += posAfterRotation[1] - posBeforeRotation[1];
        marioPos[2] += posAfterRotation[2] - posBeforeRotation[2];
        vec3f_copy(gMarioStates[0].pos, marioPos);
    }
#endif

    o->header.gfx.throwMatrix = transform;
}

void bhv_drexplosion_loop(void){
    cur_obj_set_model(MODEL_DREXPLOSION);
    u8 *texture_location_in_ram = segmented_to_virtual(&DRExplosion_explosion_44x44_rgba16);


    dma_read(texture_location_in_ram,(o->oTimer*3872)+DRExplosion,(o->oTimer*3872)+DRExplosion+3872);



            if (o->oTimer > 16) {
        o->oTimer = 0;
        mark_obj_for_deletion(o);
        }
        }

void bhv_nether_portal_loop(void){
    //print_text_fmt_int(180, 20, "oAction: %d", o->oAction);
    static u16 SoundTimer;
    if (sophieCutsceneState < 6){
        if (o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND){
            if (SoundTimer == 15){
            play_sound(SOUND_OBJ_POUNDING_LOUD, gGlobalSoundSource);
            }
            if (SoundTimer > 0){
            SoundTimer--;
            }

        } else{
        SoundTimer = 15;
        }
    } else if (InPortal == FALSE){
        if (SoundTimer == 0){
            play_sound(SOUND_PEACH_POWER_OF_THE_STARS, gGlobalSoundSource);
            SoundTimer = (random_u16()/100);
        } else {
            SoundTimer--;
        }
    }

    o->oFloorHeight = 820;
    NetherPos[0] = o->oPosX;
    NetherPos[1] = o->oPosY;
    NetherPos[2] = o->oPosZ;
    cur_obj_move_standard(-78);
    if (gMarioState->floor->type == SURFACE_NETHER){
        InPortal = TRUE;
    } if (gMarioState->floor->type != SURFACE_NETHER){
        InPortal = FALSE;
    }
    extern u8 NetherPortal[];
    u8 *texture_location_in_ram = segmented_to_virtual(&nether_nether_portal_base_rgba32);
    dma_read(texture_location_in_ram,(o->oTimer*1024)+NetherPortal,(o->oTimer*1024)+NetherPortal+1024);
    
    if (o->oTimer > 30) {
        o->oTimer = 0;
        }
}


void bhv_frisk_loop(void){
enum FRISK_STATE{
    FRISK_NEUTRAL,
    FRISK_UP,
    FRISK_DOWN,
    FRISK_LEFT,
    FRISK_RIGHT,

};
static u8 friskState;
static u8 friskFrame;
static u8 friskSideFrame;
friskPos[0] = o->oPosX;
friskPos[1] = o->oPosY;
friskPos[2] = o->oPosZ;
//print_text_fmt_int(10,60, "undertaleArea %d", undertaleArea);
if (undertaleArea == 2){
    o->oPosX = 1469;
    o->oPosZ = -1000;
}
cur_obj_move_standard(-78);
cur_obj_update_floor_and_walls();
if (o->oFloorType == SURFACE_UNDERTALE_WARP_1){
    mark_obj_for_deletion(o);
}
    //
    
//print_text_fmt_int(180, 20, "oTimer: %d", o->oTimer);
    u8 *texture_location_in_ram = segmented_to_virtual(&frisk_friskdefault_rgba16);
    if (undertaleArea < 4 || (undertaleArea == 4 && undertaleDialogState == 4)){
    if (gPlayer1Controller->stickX > 0){
        if (friskState == FRISK_NEUTRAL){
            friskState = FRISK_RIGHT;
        } else if (friskState == FRISK_LEFT){
            friskState = FRISK_RIGHT;
        } else {
            friskState = FRISK_NEUTRAL;
        }
        


        if (friskState == FRISK_RIGHT){
            friskFrame = 0;
            //print_text(180, 20, "RIGHT");
            o->oFaceAngleRoll = DEGREES(180);
            o->oMoveAngleYaw = DEGREES(90);
            o->oFaceAngleYaw = DEGREES(0);
            o->oForwardVel = 10;
            dma_read(texture_location_in_ram,(friskSideFrame*1102)+frisk_side,(friskSideFrame*1102)+frisk_side+1102);
            if (o->oTimer > 10.0f){
                friskSideFrame++;
                o->oTimer = 0;
            } if (friskSideFrame > 1){
                friskSideFrame = 0;
            } 
        }
    } if (gPlayer1Controller->stickX < 0){

        if (friskState == FRISK_NEUTRAL){
            friskState = FRISK_LEFT;
        } else if (friskState == FRISK_RIGHT){
            friskState = FRISK_LEFT;
        } else {
            friskState = FRISK_NEUTRAL;
            }
        if (friskState == FRISK_LEFT){
            friskFrame = 0;
            //print_text(180, 20, "LEFT");
            o->oFaceAngleRoll = DEGREES(0);
            o->oMoveAngleYaw = DEGREES(270);
            o->oFaceAngleYaw = DEGREES(0);
            o->oForwardVel = 10.0f;
            dma_read(texture_location_in_ram,(friskSideFrame*1102)+frisk_side,(friskSideFrame*1102)+frisk_side+1102);
            if (o->oTimer > 10){
                friskSideFrame++;
                o->oTimer = 0;
            } if (friskSideFrame > 1){
                friskSideFrame = 0;
            } 
        }
    } if (gPlayer1Controller->stickY < 0){
        //print_text(180, 20, "DOWN");
        if (friskState == FRISK_NEUTRAL){
            friskState = FRISK_DOWN;
        } else if (friskState == FRISK_UP){
            friskState = FRISK_DOWN;
        } else {
            friskState = FRISK_NEUTRAL;
            }
        if (friskState == FRISK_DOWN){
            friskSideFrame = 0;
            o->oFaceAngleRoll = DEGREES(0);
            o->oMoveAngleYaw = DEGREES(0);
            o->oFaceAngleYaw = DEGREES(0);
            o->oForwardVel = 10.0f;
            dma_read(texture_location_in_ram,(friskFrame*1102)+frisk_front,(friskFrame*1102)+frisk_front+1102);
            if (o->oTimer > 10){
                friskFrame++;
                o->oTimer = 0;
            } if (friskFrame > 3){
                friskFrame = 0;
            }
        }

        
    } if (gPlayer1Controller->stickY > 0){
        //print_text(180, 20, "UP");
        if (friskState == FRISK_NEUTRAL){
            friskState = FRISK_UP;
        } else if (friskState == FRISK_DOWN){
            friskState = FRISK_UP;
        } else {
            friskState = FRISK_NEUTRAL;
            }
        if (friskState == FRISK_UP){
            friskSideFrame = 0;
            o->oFaceAngleRoll = DEGREES(0);
            o->oFaceAngleYaw = DEGREES(0);
            o->oMoveAngleYaw = DEGREES(180);
            o->oForwardVel = 10.0f;
            dma_read(texture_location_in_ram,(friskFrame*1102)+frisk_back,(friskFrame*1102)+frisk_back+1102);
            if (o->oTimer > 10){
                friskFrame++;
                o->oTimer = 0;
            } if (friskFrame > 3){
                friskFrame = 0;
            }
        }
        

    } if (gPlayer1Controller->stickX == 0 && gPlayer1Controller->stickY == 0){

        friskState = FRISK_NEUTRAL;
        dma_read(texture_location_in_ram,(friskFrame*1102)+frisk_front,(friskFrame*1102)+frisk_front+1102);
        friskFrame = 0;
        o->oFaceAngleRoll = DEGREES(0);
        o->oFaceAngleYaw = DEGREES(0);
        o->oMoveAngleYaw = DEGREES(0);
        o->oForwardVel = 0.0f;
    }
    } else {
        o->oForwardVel = 0.0f;
        dma_read(texture_location_in_ram,(friskFrame*1102)+frisk_back,(friskFrame*1102)+frisk_back+1102);
        friskFrame = 0;
    }




}

void bhv_undertale_warp(void){
    if(cur_obj_dist_to_nearest_object_with_behavior(bhvFrisk) <= 50.0f){
        undertaleWarp = TRUE;
        undertaleArea++;
        mark_obj_for_deletion(o);
    }
}

void bhv_building_loop(void){
    //o->oPosX = 1519
    //o->oPosZ = -1395
    if (undertaleDialogState == 3){
        if (o->oPosZ < -1395.0f){
        print_text(20,20, "building time");
        o->oPosZ+=40.0f;
        } else {
            o->oPosZ = -1395.0f;
            
            undertaleDialogState = 4;
            set_background_music(0, SEQUENCE_NONE, 0);
            play_sound(SOUND_PEACH_THANK_YOU_MARIO, gGlobalSoundSource);
        }
        
    }
}


void bhv_psychiatrist_init(void){
    PsychState = PSYCH_SIT;
}

void bhv_psychiatrist_loop(void){
    //print_text_fmt_int(20,20, "Psych PENIS %d", PsychState);
    //print_text_fmt_int(20,35, "Sitting %d", ZeroSitting);
    cur_obj_move_standard(-78);
    cur_obj_update_floor_and_walls();
    
    if (PsychState == PSYCH_SIT){
        o->oMoveAngleYaw = DEGREES(-90);
        o->oFaceAngleYaw = DEGREES(90);
        PsychState = PSYCH_SIT;
    cur_obj_set_model(MODEL_PSYCH_SIT);
    u8 *texture_location_in_ram = segmented_to_virtual(&psychiatristsit_spr_psych_glasses_0_rgba16);
    dma_read(texture_location_in_ram,(PsychSitFrame*1496)+psych_sit,(PsychSitFrame*1496)+psych_sit+1496);
    if (o->oTimer > 2 && LoopOffset == FALSE) {
        PsychSitFrame++;
        o->oTimer = 0;
        }
        if (PsychSitFrame > 11){
            PsychSitFrame = 0;
            LoopOffset = TRUE;
        }
        if (LoopOffset == TRUE && o->oTimer > 150){
            LoopOffset = FALSE;
            o->oTimer = 0;
        }
    } if (ZeroSitting == TRUE && therapyState == 2){
        therapyState = 3;
    } if (therapyState == 100 && PsychState == PSYCH_SIT || therapyState == 101 && PsychState == PSYCH_SIT){
        cur_obj_set_model(MODEL_PSYCH_STAND);
        u8 *texture_location_in_ram = segmented_to_virtual(&psych_stand_standupdefault_rgba16);
    dma_read(texture_location_in_ram,(PsychStandFrame*2480)+psych_stand,(PsychStandFrame*2480)+psych_stand+2480);
    if (o->oTimer > 2 && PsychStandFrame < 11) {
        PsychStandFrame++;
        o->oTimer = 0;
        }
        if (PsychStandFrame > 10){
            PsychState = PSYCH_WALK;
        }
    } else if (PsychState == PSYCH_WALK){
        if (therapyState == 101){
            if (o->oPosX > 450){
                o->oPosX = 280;
            }
        o->oMoveAngleYaw = DEGREES(-90);
        o->oFaceAngleYaw = DEGREES(90);
            if (o->oPosX > -300 && o->oPosX < 450){
            o->oForwardVel = 15.0f;
            } else {
                o->oForwardVel = 0.0f;
                PsychState = PSYCH_KILLROCK;
            }
        } else if (therapyState == 100){
            if (o->oPosX < 1500){
                o->oMoveAngleYaw = DEGREES(90);
                o->oFaceAngleYaw = DEGREES(-90);
                o->oForwardVel = 15.0f;
                } else {
                    o->oForwardVel = 0.0f;
                    PsychState = PSYCH_DESK;
                }
        }
        cur_obj_set_model(MODEL_PSYCH_WALK);
        u8 *texture_location_in_ram = segmented_to_virtual(&psych_walk_psychwalkdefault_rgba16);
    dma_read(texture_location_in_ram,(PsychWalkFrame*1722)+psych_walk,(PsychWalkFrame*1722)+psych_walk+1722);
    if (o->oTimer > 2) {
        PsychWalkFrame++;
        o->oTimer = 0;
        } 
        if (PsychWalkFrame > 7){
            PsychWalkFrame = 0;
        }
    } else if (PsychState == PSYCH_KILLROCK){
        o->oMoveAngleYaw = DEGREES(90);
        o->oFaceAngleYaw = DEGREES(-90);
        cur_obj_set_model(MODEL_PSYCH_KILLROCK);
        u8 *texture_location_in_ram = segmented_to_virtual(&psych_killrock_defaultrock_rgba16);
        dma_read(texture_location_in_ram,(PsychKillRockFrame*2464)+psych_killrock,(PsychKillRockFrame*2464)+psych_killrock+2464);
        if (o->oTimer > 2 && PsychKillRockFrame < 7) {
        PsychKillRockFrame++;
        o->oTimer = 0;
        if (PsychKillRockFrame == 6){
            FreeMario = TRUE;
            play_sound(SOUND_ACTION_BONK, gGlobalSoundSource);
        }
        } if (PsychKillRockFrame == 7){
            ZeroKilled = TRUE;
        }
    } else if (PsychState == PSYCH_DESK){
        o->oMoveAngleYaw = DEGREES(-90);
        o->oFaceAngleYaw = DEGREES(90);
        cur_obj_set_model(MODEL_PSYCH_GRABNEEDLE);
        u8 *texture_location_in_ram = segmented_to_virtual(&psych_getneedle_grabneedledefault_rgba16);
        dma_read(texture_location_in_ram,(PsychDeskFrame*2214)+psych_getneedle,(PsychDeskFrame*2214)+psych_getneedle+2214);
        if (o->oTimer > 2) {
        PsychDeskFrame++;
        o->oTimer = 0;
        } if (PsychDeskFrame > 19){
            PsychDeskFrame = 0;
            PsychState = PSYCH_WALK_SYRINGE;
        }
    } else if (PsychState == PSYCH_WALK_SYRINGE){
        if (o->oPosX > -100){
        o->oMoveAngleYaw = DEGREES(-90);
        o->oFaceAngleYaw = DEGREES(90);
        o->oForwardVel = 15.0f;
        } else {
            o->oForwardVel = 0.0f;
            PsychState = PSYCH_INJECT;
        }
        cur_obj_set_model(MODEL_PSYCH_WALKNEEDLE);
        u8 *texture_location_in_ram = segmented_to_virtual(&psych_walkneedle_walkneedledefault_rgba16);
        dma_read(texture_location_in_ram,(PsychWalkSyringeFrame*1640)+psych_walkneedle,(PsychWalkSyringeFrame*1640)+psych_walkneedle+1640);
        if (o->oTimer > 2) {
        PsychWalkSyringeFrame++;
        o->oTimer = 0;
        } if (PsychWalkSyringeFrame > 9){
            PsychWalkSyringeFrame = 0;
        }
    } else if (PsychState == PSYCH_INJECT){
        cur_obj_set_model(MODEL_PSYCH_INJECT);
        o->oMoveAngleYaw = DEGREES(90);
        o->oFaceAngleYaw = DEGREES(-90);
        u8 *texture_location_in_ram = segmented_to_virtual(&psych_inject_injectdefault_rgba16);
        dma_read(texture_location_in_ram,(PsychInjectFrame*2214)+psych_inject,(PsychInjectFrame*2214)+psych_inject+2214);
        if (o->oTimer > 2 && PsychInjectFrame < 19) {
        PsychInjectFrame++;
        o->oTimer = 0;
        } if (PsychInjectFrame == 19){
            ZeroInjected = TRUE;
        }
    }
}

void bhv_fireplace_loop(void){
    u8 *texture_location_in_ram = segmented_to_virtual(&bob_dl_fireplacedefault_rgba16);
    dma_read(texture_location_in_ram,(FireplaceFrame*1972)+fireplace,(FireplaceFrame*1972)+fireplace+1972);
        if (o->oTimer > 2) {
        FireplaceFrame++;
        o->oTimer = 0;
        } if (FireplaceFrame > 6){
            FireplaceFrame = 0;
        }
}

void bhv_zero_loop(void){
    cur_obj_move_standard(-78);
    cur_obj_update_floor_and_walls();

    
if (gPlayer1Controller->stickX != 0 && ZeroSitting == FALSE && WalkToChair == FALSE){
    o->oForwardVel = 15.0f;
    cur_obj_set_model(MODEL_ZERO_WALK);
    u8 *texture_location_in_ram = segmented_to_virtual(&zero_walk_spr_casualwalk_0_rgba16);
    dma_read(texture_location_in_ram,(ZeroWalkFrame*2448)+zero_walk,(ZeroWalkFrame*2448)+zero_walk+2448);
        if (o->oTimer > 2) {
        ZeroWalkFrame++;
        o->oTimer = 0;
        } if (ZeroWalkFrame > 7){
            ZeroWalkFrame = 0;
        }   if (gPlayer1Controller->stickX > 0){
                o->oMoveAngleYaw =DEGREES(90);

        } if (gPlayer1Controller->stickX < 0){
                o->oMoveAngleYaw =DEGREES(-90);

        }
} else if (ZeroSitting == FALSE && WalkToChair == FALSE){
    cur_obj_set_model(MODEL_ZERO);
    o->oForwardVel = 0.0f;
    u8 *texture_location_in_ram2 = segmented_to_virtual(&zero_casualdefault_rgba16);
    dma_read(texture_location_in_ram2,(ZeroIdleFrame*2240)+zero_idle,(ZeroIdleFrame*2240)+zero_idle+2240);
        if (o->oTimer > 2) {
        ZeroIdleFrame++;
        o->oTimer = 0;
        } if (ZeroIdleFrame > 10){
            ZeroIdleFrame = 0;
        }
} else if (ZeroSitting == TRUE){
        cur_obj_set_model(MODEL_ZERO_SIT);
        approach_f32_symmetric_bool(&o->oPosX, -297.0f, 15.0f);
        o->oMoveAngleYaw =DEGREES(90);
        o->oPosX = -297.0f;
        o->oForwardVel = 0.0f;

    u8 *texture_location_in_ram3 = segmented_to_virtual(&zero_sit_sitdowndefault_rgba16);
    dma_read(texture_location_in_ram3,(ZeroSitFrame*2304)+zero_sit,(ZeroSitFrame*2304)+zero_sit+2304);
        if (o->oTimer > 2 && ZeroSitFrame < 11) {
        ZeroSitFrame++;
        o->oTimer = 0;
        }
}
if (ZeroSitting == FALSE && WalkToChair == FALSE){
    if (o->oPosX > -1097.0f && o->oPosX < 403.0f){
        if (o->oPosX > -387.0f && o->oPosX < -207.0f){

            if (gPlayer1Controller->buttonPressed & A_BUTTON){
                ZeroSitting = TRUE;
            }
        } else if (gPlayer1Controller->buttonPressed & A_BUTTON){
        WalkToChair = TRUE;
        }

        SitRange = TRUE;
        
    

    } else {

        SitRange = FALSE;
    }
}
if (WalkToChair == TRUE){
    cur_obj_set_model(MODEL_ZERO_WALK);
    u8 *texture_location_in_ram = segmented_to_virtual(&zero_walk_spr_casualwalk_0_rgba16);
    dma_read(texture_location_in_ram,(ZeroWalkFrame*2448)+zero_walk,(ZeroWalkFrame*2448)+zero_walk+2448);
        if (o->oTimer > 2) {
        ZeroWalkFrame++;
        o->oTimer = 0;
        } if (ZeroWalkFrame > 7){
            ZeroWalkFrame = 0;
        }
    if (o->oPosX > -297.0f && WalkingLeft == FALSE){
        WalkingLeft = TRUE;
        o->oMoveAngleYaw =DEGREES(-90);
        o->oForwardVel = 15.0f;
    }
        if (o->oPosX <= -287.0f && WalkingLeft == TRUE){
        ZeroSitting = TRUE;
            WalkToChair = FALSE;
            WalkingLeft = FALSE;
        }
    
    
    if (o->oPosX < -297.0f && WalkingRight == FALSE){
        WalkingRight = TRUE;
        o->oMoveAngleYaw =DEGREES(90);
        o->oForwardVel = 15.0f;
    }
        if (o->oPosX >= -407.0f && WalkingRight == TRUE){
            ZeroSitting = TRUE;
            WalkToChair = FALSE;
            WalkingRight = FALSE;
        }
    
}
}
void bhv_a_press_init(void){
    o->oOpacity = 0;
}
void bhv_a_press_loop(void){
    if (therapyState == 2){
        if (o->oPosY > 898){
            approach_f32_symmetric_bool(&o->oPosY, 898.0f, 50.0f);
        }
    }
    if (SitRange == TRUE && WalkToChair == FALSE && ZeroSitting == FALSE){
        cur_obj_set_model(MODEL_KATANA_A);
        u8 *texture_location_in_ram = segmented_to_virtual(&katana_a_button_spr_xbox_a_0_rgba16);
        dma_read(texture_location_in_ram,(AFrame*448)+katana_a,(AFrame*448)+katana_a+448);
        if (o->oTimer > 10) {
        AFrame++;
        o->oTimer = 0;
        } if (AFrame > 1){
            AFrame = 0;
        } if (o->oOpacity < 225){
            o->oOpacity += 30;
            AFade = A_FADE_IN;
        } else if (o->oOpacity >= 225){
            o->oOpacity = 255;
            AFade = A_FADE_OPAQUE;
        }
    } else{
        if (o->oOpacity > 30){
            o->oOpacity -= 30;
            AFade = A_FADE_OUT;
        } else if (o->oOpacity <= 30){
            o->oOpacity = 0;
            AFade = A_FADE_NONE;
            AFrame = 0;
        }
    }
}

void bhv_sophie_init(void) {
o->oGravity = 0.0f;
    o->oFriction = 0.8f;
    o->oBuoyancy = 1.3f;
    o->oInteractionSubtype = INT_SUBTYPE_NPC;
}
void bhv_sophie_loop(void) {
    cur_obj_move_standard(-78);
    //print_text_fmt_int(180, 180, "sophieCutsceneState: %d", sophieCutsceneState);
if (gCurrLevelNum == LEVEL_CASTLE_GROUNDS){
if (o->oInteractStatus & INT_STATUS_INTERACTED) {
    sophieCutsceneState = 1;

    if (set_mario_npc_dialog(MARIO_DIALOG_LOOK_FRONT) == MARIO_DIALOG_STATUS_SPEAK) {
        o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;


                if (cutscene_object_with_dialog(CUTSCENE_DIALOG, o, o->oBehParams2ndByte)
                    != BOBOMB_BUDDY_BP_STYPE_GENERIC) {
                    set_mario_npc_dialog(MARIO_DIALOG_STOP);
                    o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
                    o->oInteractStatus = INT_STATUS_NONE;
                    o->oInteractionSubtype = 0;
                }


    }
        } if (sophieCutsceneState == 4){
            cur_obj_rotate_yaw_toward(DEGREES(0), 0x600);
                if (o->oFaceAngleYaw == DEGREES(0)){
                    sophieCutsceneState = 5;
                }

        } if (sophieCutsceneState == 5){
            if (o->oPosZ < 900){
            o->oForwardVel = 10.0f;
            o->oVelY = 4.0f;
            } else {
                o->oForwardVel = 0.0f;
                o->oVelY = 0.0f;
                sophieCutsceneState = 6;
            }
        } if (sophieCutsceneState == 6){
            mark_obj_for_deletion(o);
            set_mario_action(gMarioState, ACT_IDLE, 0);
            sophieCutsceneState = 7;
            play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
        }
    } else {
        if (o->oInteractStatus & INT_STATUS_INTERACTED) {

    if (set_mario_npc_dialog(MARIO_DIALOG_LOOK_FRONT) == MARIO_DIALOG_STATUS_SPEAK) {
        o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;


                if (cutscene_object_with_dialog(CUTSCENE_DIALOG, o, o->oBehParams2ndByte)
                    != BOBOMB_BUDDY_BP_STYPE_GENERIC) {
                    set_mario_npc_dialog(MARIO_DIALOG_STOP);
                    o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
                    o->oInteractStatus = INT_STATUS_NONE;
                    o->oInteractionSubtype = 0;
                }


    }
        }
    }
}
/*
void hallway_loop(void){
    static s32 hallwayVerts;
    Vtx *hallwayVerts = segmented_to_virtual(&MinecraftLoad_LoadingScreen_mesh_vtx_2);
}
*/
struct ObjectHitbox sPikminHitbox = {
    /* interactType:      */ INTERACT_NONE,
    /* downOffset:        */   0,
    /* damageOrCoinValue: */   0,
    /* health:            */   1,
    /* numLootCoins:      */   0,
    /* radius:            */ 37,
    /* height:            */ 160,
    /* hurtboxRadius:     */ 37,
    /* hurtboxHeight:     */ 0,
    };

void bhv_pikmin_loop(void){
    if (isPikmin == TRUE){
        mark_obj_for_deletion(o);
    }
    sPikminHitbox.radius = 37 * pikminScale;
    sPikminHitbox.height = 160 * pikminScale;
    obj_set_hitbox(o, &sPikminHitbox);
    cur_obj_scale(pikminScale);
    cur_obj_move_standard(-78);
    cur_obj_update_floor_and_walls();
    if (isPikmin == FALSE){
        cachedPikminPosAndFaceAngle[0] = o->oPosX;
        cachedPikminPosAndFaceAngle[1] = o->oPosY;
        cachedPikminPosAndFaceAngle[2] = o->oPosZ;
        cachedPikminPosAndFaceAngle[3] = o->oFaceAngleYaw;
    }
    static u8 pikminState;
    enum pikmin_states{
        PIKMIN_IDLE,
        PIKMIN_IDLE_FOLLOW,
        PIKMIN_FOLLOW,
        PIKMIN_BEGIN_THROW,
        PIKMIN_THROW,
        PIKMIN_DESCEND,
    };
    
    switch (pikminState){
        case PIKMIN_IDLE:
            o->oForwardVel = 0;
            cur_obj_init_animation(0);
            if (o->oDistanceToMario < 300.0f) {
                pikminState = PIKMIN_IDLE_FOLLOW;
            }
            break;
        case PIKMIN_IDLE_FOLLOW:
            if (gMarioState->action == ACT_PUNCHING || gMarioState->action == ACT_MOVE_PUNCHING){
                pikminState = PIKMIN_BEGIN_THROW;
            }
            cur_obj_init_animation(0);
            o->oForwardVel = 0.0f;
            if (o->oDistanceToMario >= 150.0f) {
                pikminState = PIKMIN_FOLLOW;
            }
            break;
        case PIKMIN_FOLLOW:
            if (gMarioState->action == ACT_PUNCHING || gMarioState->action == ACT_MOVE_PUNCHING){
                pikminState = PIKMIN_BEGIN_THROW;
            }
            cur_obj_init_animation_with_accel_and_sound(2, 3.0f);
            cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x600);
            if (o->oDistanceToMario >= 150.0f && o->oDistanceToMario < 1000.0f) {
                cur_obj_set_vel_from_mario_vel(10,1);
            } else if (o->oDistanceToMario >= 1000.0f){
                pikminState = PIKMIN_IDLE;
            } else {
                o->oForwardVel-=3.0f;
                if (o->oForwardVel <= 0){
                o->oForwardVel = 0;
                pikminState = PIKMIN_IDLE_FOLLOW;
                }
            } if (o->oMoveFlags & OBJ_MOVE_HIT_WALL){
                o->oForwardVel = 0;
                pikminState = PIKMIN_IDLE;
            }
            break;
        case PIKMIN_BEGIN_THROW:
            cur_obj_init_animation(1);
            o->oFaceAngleYaw = gMarioState->faceAngle[1];
            o->oMoveAngleYaw = gMarioState->faceAngle[1];
            o->oPosX = gMarioState->pos[0];
            o->oPosY = gMarioState->pos[1];
            o->oPosZ = gMarioState->pos[2];
            o->oTimer = 0;
            pikminState = PIKMIN_THROW;
            break;
        case PIKMIN_THROW:
            o->oForwardVel = 30.0f;
            
                o->oVelY = 55.0f;
                if (o->oTimer > 15){
                    pikminState = PIKMIN_DESCEND;
                }

            
            break;
        case PIKMIN_DESCEND:

            if (o->oVelY > -40.0f){
            o->oVelY-=4.0f;
            } else if (o->oVelY <= -40.0f){
                o->oVelY = -40.0f;
            }
            if (o->oFloorHeight == o->oPosY){
                pikminState = PIKMIN_IDLE;
            }
            break;
    }
}

void bhv_fake_mario(void){
    cachedMarioPosAndFaceAngle[0] = o->oPosX;
    cachedMarioPosAndFaceAngle[1] = o->oPosY;
    cachedMarioPosAndFaceAngle[2] = o->oPosZ;
    cachedMarioPosAndFaceAngle[3] = o->oFaceAngleYaw;
    cur_obj_init_animation(0);
    if (isPikmin == FALSE){
        mark_obj_for_deletion(o);
    }
}

/*
cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x600);
o->oPosY = gMarioState->floorHeight;
        if (o->oDistanceToMario > 300.0f) {
            cur_obj_set_vel_from_mario_vel(10,1);
            cur_obj_init_animation(2);
                } else {
        o->oForwardVel -=3;
        if (o->oForwardVel <= 0){
            o->oForwardVel = 0;
            cur_obj_init_animation(1);
        }
    

    }
    */

void bhv_blow_up_col(void){
u8 switchNum = GET_BPARAM2(o->oBehParams);
if (pressedSwitch[switchNum] == TRUE){
    spawn_object(o, MODEL_DREXPLOSION, bhvDRExplosion);
    play_sound(SOUND_GENERAL_BOWSER_BOMB_EXPLOSION, o->header.gfx.cameraToObject);
    mark_obj_for_deletion(o);
}
}