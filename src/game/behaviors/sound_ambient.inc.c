// sound_ambient.inc.c
extern Bool8 MinecraftTrans;
void bhv_ambient_sounds_init(void) {
    if (gCamera->mode == CAMERA_MODE_BEHIND_MARIO) {
        return;
    }
    if (MinecraftTrans == TRUE){
        mark_obj_for_deletion(o);
    }
    play_sound(SOUND_AIR_CASTLE_OUTDOORS_AMBIENT, gGlobalSoundSource);
}
