#include "data/scripts/dc_damage/config.h"

#import "data/scripts/dc_damage/instance.c"

// Base entity functions will act on.
void dc_damage_get_entity()
{
	int instance;
	void result;

	// Get instance.
	instance = dc_damage_get_instance();

	result = getlocalvar(instance + DC_DAMAGE_MEMBER_ENT);

	if (typeof(result) != openborconstant("VT_PTR"))
	{
		result = DC_DAMAGE_DEFAULT_ENT;
	}

	return result;
}

void dc_damage_set_entity(void value)
{
	int instance;

	// Get instance.
	instance = dc_damage_get_instance();

	setlocalvar(instance + DC_DAMAGE_MEMBER_ENT, value);
}

// Entity given credit for damage.
void dc_damage_get_other()
{
	int instance;
	void result;

	// Get instance.
	instance = dc_damage_get_instance();

	result = getlocalvar(instance + DC_DAMAGE_MEMBER_OTHER);

	if (typeof(result) != openborconstant("VT_PTR"))
	{
		result = DC_DAMAGE_DEFAULT_OTHER;
	}

	return result;
}

void dc_damage_set_other(void value)
{
	int instance;

	// Get instance.
	instance = dc_damage_get_instance();

	setlocalvar(instance + DC_DAMAGE_MEMBER_OTHER, value);
}