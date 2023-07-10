// sound_birds.inc.c
extern Bool8 MinecraftTrans;
void bhv_birds_sound_loop(void) {
    if (gCamera->mode == CAMERA_MODE_BEHIND_MARIO) {
        return;
    }
    if (MinecraftTrans == TRUE){
        mark_obj_for_deletion(o);
    }

    switch (o->oBehParams2ndByte) {
        case 0:
            cur_obj_play_sound_1(SOUND_OBJ2_BIRD_CHIRP1);
            break;

        case 1:
            cur_obj_play_sound_1(SOUND_GENERAL2_BIRD_CHIRP2);
            break;

        case 2:
            cur_obj_play_sound_1(SOUND_OBJ_BIRD_CHIRP3);
            break;
    }
}
