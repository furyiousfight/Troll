// sound_waterfall.inc.c
extern Bool8 MinecraftTrans;

void bhv_waterfall_sound_loop(void) {
    cur_obj_play_sound_1(SOUND_ENV_WATERFALL2);
    if (MinecraftTrans == TRUE){
        mark_obj_for_deletion(o);
    }
}
