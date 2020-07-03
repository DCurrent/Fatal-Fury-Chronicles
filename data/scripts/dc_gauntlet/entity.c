#include "data/scripts/dc_gauntlet/config.h"

#import "data/scripts/dc_gauntlet/instance.c"

// Base entity functions will act on.
// Base entity functions will act on.
// Get
void dc_gauntlet_get_entity()
{
	char id;
	void result;

	// Get id key.
	id = dc_gauntlet_get_instance() + DC_GAUNTLET_MEMBER_ENT;

	result = getlocalvar(id);

	if (typeof(result) != openborconstant("VT_PTR"))
	{
		result = DC_GAUNTLET_DEFAULT_ENT;
	}

	return result;
}

// Set
void dc_gauntlet_set_entity(void value)
{
	char id;

	// Get id key.
	id = dc_gauntlet_get_instance() + DC_GAUNTLET_MEMBER_ENT;

	// If the value is same as default, then use
	// make sure variable is deleted instead. We fall
	// back to default for empty vars, so may as
	// well save the memory.
	if (value == DC_GAUNTLET_DEFAULT_ENT)
	{
		value = NULL();
	}

	setlocalvar(id, value);
}
// Spawned entity (if any).
// Get
void dc_gauntlet_get_spawn()
{
	int instance;
	void result;

	// Get instance.
	instance = dc_gauntlet_get_instance();

	result = getlocalvar(instance + DC_GAUNTLET_MEMBER_SPAWN);

	if (typeof(result) != openborconstant("VT_PTR"))
	{
		result = DC_GAUNTLET_DEFAULT_TARGET;
	}

	return result;
}

// Set spawn. Most of the time this is populated automatically
// and you shouldn't be setting it directly.
void dc_gauntlet_set_spawn(void value)
{
	int instance;

	// Get instance.
	instance = dc_gauntlet_get_instance();

	setlocalvar(instance + DC_GAUNTLET_MEMBER_SPAWN, value);
}
