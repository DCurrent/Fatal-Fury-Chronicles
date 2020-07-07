#include "data/scripts/dc_damage/config.h"

#include "data/scripts/dc_damage/instance.c"

// Force (amount of hitpoint damage) to apply.
int dc_damage_get_damage_force()
{
	int instance;
	int result;

	// Get instance.
	instance = dc_damage_get_instance();

	result = getlocalvar(instance + DC_DAMAGE_MEMBER_FORCE);

	if (typeof(result) != openborconstant("VT_INTEGER"))
	{
		result = DC_DAMAGE_DEFAULT_FORCE;
	}

	return result;
}

void dc_damage_set_damage_force(int value)
{
	int instance;

	// Get instance.
	instance = dc_damage_get_instance();

	setlocalvar(instance + DC_DAMAGE_MEMBER_FORCE, value);
}