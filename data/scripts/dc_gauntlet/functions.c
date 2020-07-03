#include "data/scripts/dc_gauntlet/config.h"

#import "data/scripts/dc_gauntlet/instance.c"
#import "data/scripts/dc_gauntlet/autokill.c"
#import "data/scripts/dc_gauntlet/entity.c"

void dc_gauntlet_set_spawn_entry(char property, void value)
{
	setspawnentry(property, value);
}

void dc_gauntlet_clear_spawn_entry()
{
	clearspawnentry();
}

void dc_gauntlet_spawn()
{
	return spawn();
}



