#include "data/scripts/dc_damage/config.h"

#include "data/scripts/dc_damage/instance.c"

// Projectile mode to apply.
int dc_damage_get_projectile()
{
	char id;
	int result;

	// Get id.
	id = dc_damage_get_instance() + DC_DAMAGE_MEMBER_PROJECTILE;

	result = getlocalvar(id);

	if (typeof(result) != openborconstant("VT_INTEGER"))
	{
		result = DC_DAMAGE_DEFAULT_PROJECTILE;
	}

	return result;
}

void dc_damage_set_projectile(int value)
{
	char id;

	// Get id.
	id = dc_damage_get_instance() + DC_DAMAGE_MEMBER_PROJECTILE;

	if (value == DC_DAMAGE_DEFAULT_PROJECTILE)
	{
		value = NULL();
	}

	setlocalvar(id, value);
}