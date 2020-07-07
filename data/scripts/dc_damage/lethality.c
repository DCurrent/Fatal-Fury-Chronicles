#include "data/scripts/dc_damage/config.h"

#import "data/scripts/dc_damage/config.c"
#import "data/scripts/dc_damage/instance.c"

// Direction adjustment.
int dc_damage_get_lethality()
{
	int instance;
	int result;

	result = getlocalvar(instance + DC_DAMAGE_MEMBER_LETHALITY);

	if (typeof(result) != openborconstant("VT_INTEGER"))
	{
		result = DC_DAMAGE_DEFAULT_LETHALITY;
	}

	return result;
}

void dc_damage_set_lethality(int value)
{
	int instance;

	setlocalvar(instance + DC_DAMAGE_MEMBER_LETHALITY, value);
}