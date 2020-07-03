#include "data/scripts/dc_gauntlet/config.h"

#import "data/scripts/dc_gauntlet/instance.c"

// Primary acting entity.
char dc_gauntlet_get_model_name()
{
	int instance;
	char result;

	// Get instance.
	instance = dc_gauntlet_get_instance();

	result = getlocalvar(instance + DC_GUANTLET_MEMBER_MODEL_NAME);

	if (typeof(result) != openborconstant("VT_STR"))
	{
		result = DC_GAUNTLET_DEFAULT_MODEL_NAME;
	}

	return result;
}

char dc_gauntlet_set_model_name(char value)
{
	int instance;

	// Get instance.
	instance = dc_gauntlet_get_instance();

	setlocalvar(instance + DC_GUANTLET_MEMBER_MODEL_NAME, value);
}