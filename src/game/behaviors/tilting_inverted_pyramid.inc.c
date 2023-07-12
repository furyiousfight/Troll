
/**
 * This is the behavior file for the tilting inverted pyramids in BitFS/LLL.
 * The object essentially just tilts and moves Mario with it.
 */

/**
 * Initialize the object's transform matrix with Y being up.
 */
#include "actors/DRExplosion/geo_header.h"
#include "actors/nether/geo_header.h"
#include "actors/FriskBack/geo_header.h"
#include "actors/FriskFront/geo_header.h"
#include "actors/FriskLeft/geo_header.h"
#include "actors/FriskRight/geo_header.h"
#include "actors/psychiatristsit/geo_header.h"
#include "actors/psych_stand/geo_header.h"
#include "actors/psych_walk/geo_header.h"
#include "actors/fireplace/geo_header.h"
#include "actors/zero/geo_header.h"
#include "actors/zero_walk/geo_header.h"
#include "actors/zero_sit/geo_header.h"
#include "actors/katana_a_button/geo_header.h"
extern struct MarioState *gMarioState;
extern u8 Therapy_State;
extern Bool8 InPortal;
extern u8 DRExplosion[];
extern u8 NetherPortal[];
extern u8 frisk_up[];
extern u8 frisk_down[];
extern u8 frisk_left[];
extern u8 frisk_right[];
extern u8 psych_sit[];
extern u8 psych_stand[];
extern u8 psych_walk[];
extern u8 fireplace[];
extern u8 zero_idle[];
extern u8 zero_walk[];
extern u8 zero_sit[];
extern u8 katana_a[];
u8 PsychSitFrame;
u8 PsychStandFrame;
u8 PsychWalkFrame;
u8 PsychDeskFrame;
u8 PsychWalkSyringeFrame;
u8 PsychInjectFrame;
u8 PsychState;
Bool8 WalkToChair;
Bool8 WalkingLeft;
Bool8 WalkingRight;
u8 AFade;
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
    PSYCH_INJECT
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
    if (gMarioState->floor->type == SURFACE_NETHER){
        InPortal = TRUE;
    } if (gMarioState->floor->type != SURFACE_NETHER){
        InPortal = FALSE;
    }
    u8 *texture_location_in_ram = segmented_to_virtual(&nether_nether_portal_base_rgba32);
    dma_read(texture_location_in_ram,(o->oTimer*1024)+NetherPortal,(o->oTimer*1024)+NetherPortal+1024);
    if (o->oTimer > 30) {
        o->oTimer = 0;
        }
}

/*
void bhv_frisk_loop(loop){
enum FRISK_STATE{
    FRISK_NEUTRAL,
    FRISK_UP,
    FRISK_DOWN,
    FRISK_LEFT,
    FRISK_RIGHT,

}
    if (gPlayer1Controller->stickX > 0){
        cur_obj_set_model(MODEL_FRISK_RIGHT);
    } if (gPlayer1Controller->stickX < 0){
        cur_obj_set_model(MODEL_FRISK_LEFT);
    } if (gPlayer1Controller->stickY > 0){
        cur_obj_set_model(MODEL_FRISK_BACK);
    } if (gPlayer1Controller->stickY < 0){
        cur_obj_set_model(MODEL_FRISK_FRONT);
    } if (gPlayer1Controller->stickX == 0 && gPlayer1Controller->stickY == 0){
        cur_obj_set_model(MODEL_FRISK_FRONT);
    }

    u8 *texture_location_in_ram = segmented_to_virtual(&FriskBack_friskupdefault_rgba16);
    dma_read(texture_location_in_ram,(o->oTimer*1024)+FriskBack,(o->oTimer*1024)+NetherPortal+1024);
    if (o->oTimer > 30) {
        o->oTimer = 0;
        }

}

*/
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
    } if (ZeroSitting == TRUE && Therapy_State == 2){
        Therapy_State = 3;
    } if (Therapy_State == 100){
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
        o->oMoveAngleYaw = DEGREES(90);
        o->oFaceAngleYaw = DEGREES(-90);
        o->oForwardVel = 15.0f;
        cur_obj_set_model(MODEL_PSYCH_WALK);
        u8 *texture_location_in_ram = segmented_to_virtual(&psych_walk_psychwalkdefault_rgba16);
    dma_read(texture_location_in_ram,(PsychWalkFrame*1722)+psych_walk,(PsychWalkFrame*1722)+psych_walk+1722);
    if (o->oTimer > 2) {
        PsychWalkFrame++;
        o->oTimer = 0;
        } 
        if (PsychWalkFrame > 9){
            PsychWalkFrame = 0;
        }
    }
}

void bhv_fireplace_loop(void){
    u8 *texture_location_in_ram = segmented_to_virtual(&fireplace_fireplacedefault_rgba16);
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
    if (Therapy_State == 2){
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

void bhv_textbox_loop(void){

}