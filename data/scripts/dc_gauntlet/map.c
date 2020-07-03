#include "data/scripts/dc_gauntlet/config.h"

#import "data/scripts/dc_gauntlet/instance.c"

int dc_gauntlet_get_map()
{
	int instance;
	int result;

	// Get instance.
	instance = dc_gauntlet_get_instance();

	result = getlocalvar(instance + DC_GAUNTLET_MEMBER_MAP);

	if (typeof(result) != openborconstant("VT_INTEGER"))
	{
		result = DC_GAUNTLET_DEFAULT_MAP;
	}

	return result;
}

int dc_gauntlet_set_map(int value)
{
	char id;

	// Get ID.
	id = dc_gauntlet_get_instance() + DC_GAUNTLET_MEMBER_MAP;

	// If value is default, make sure the variable
	// is deleted.
	if (value != DC_GAUNTLET_DEFAULT_MAP)
	{
		setlocalvar(id, value);
	}
	else
	{
		setlocalvar(id, NULL());
	}
}