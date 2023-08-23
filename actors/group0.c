#include <ultra64.h>
#include "sm64.h"
#include "surface_terrains.h"
#include "geo_commands.h"

#include "make_const_nonconst.h"

// Note: This bin does not use bin IDs, unlike the other segmented bins.
#include "mario/model.inc.c"

#include "bubble/model.inc.c"

#include "walk_smoke/model.inc.c"

#include "burn_smoke/model.inc.c"

#include "small_water_splash/model.inc.c"

#include "water_wave/model.inc.c"

#include "sparkle/model.inc.c"

#include "water_splash/model.inc.c"

#include "white_particle_small/model.inc.c"

#include "sparkle_animation/model.inc.c"

#ifdef S2DEX_TEXT_ENGINE
#include "src/s2d_engine/config.h"
#include FONT_C_FILE
#endif

#include "DRExplosion/model.inc.c"
#include "nether/model.inc.c"
#include "nether/collision.inc.c"

#include "psychiatristsit/model.inc.c"
#include "zero/model.inc.c"
#include "zero_walk/model.inc.c"
#include "zero_sit/model.inc.c"
#include "psych_stand/model.inc.c"
#include "psych_walk/model.inc.c"
#include "katana_a_button/model.inc.c"
#include "psych_killrock/model.inc.c"
#include "sophie/model.inc.c"
#include "sophie/anims/data.inc.c"
#include "sophie/anims/table.inc.c"
#include "psych_getneedle/model.inc.c"
#include "psych_walkneedle/model.inc.c"
#include "psych_inject/model.inc.c"
#include "frisk/model.inc.c"
#include "building_ext/model.inc.c"
#include "hallway/model.inc.c"
#include "hallway/collision.inc.c"
#include "pikmin/model.inc.c"
#include "pikmin/anims/data.inc.c"
#include "pikmin/anims/table.inc.c"
#include "fake_mario/model.inc.c"
#include "bulborb/model.inc.c"
#include "gate/model.inc.c"
#include "gate/collision.inc.c"