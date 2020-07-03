#include "data/scripts/dc_gauntlet/config.h"

#import "data/scripts/dc_gauntlet/instance.c"
#import "data/scripts/dc_gauntlet/functions.c"
#import "data/scripts/dc_gauntlet/autokill.c"
#import "data/scripts/dc_gauntlet/entity.c"

// Caskey, Damon V.
// 2019-04-23
//
// Just a one step way to run spawn functions when we
// all we need is a quick spawn.
void dc_gauntlet_quick_spawn(char model_name)
{
	void spawn;

	// Clear the spawn entry, spawn in new entity, and clear again.
	dc_gauntlet_clear_spawn_entry();

	dc_gauntlet_set_spawn_entry("name", model_name);

	spawn = dc_gauntlet_spawn();

	dc_gauntlet_clear_spawn_entry();

	// Now apply properties that are not part of spawn system.
	set_entity_property(spawn, "autokill", dc_gauntlet_get_autokill());
	
	return spawn;
}

// Caskey, Damon V.
// 2019-04-23
//
// Just a one step way to run spawn functions when we
// all we need is a quick spawn.
void dc_gauntlet_quick_flash(char model_name)
{
	void spawn;

	// Clear the spawn entry, spawn in new entity, and clear again.
	dc_gauntlet_clear_spawn_entry();

	dc_gauntlet_set_spawn_entry("name", model_name);

	spawn = dc_gauntlet_spawn();

	dc_gauntlet_clear_spawn_entry();

	// Now apply default properties for a flash.
	set_entity_property(spawn, "autokill", openborconstant("AUTOKILL_ANIMATION_COMPLETE"));
	set_entity_property(spawn, "spawn_type", openborconstant("SPAWN_TYPE_FLASH"));

	return spawn;
}