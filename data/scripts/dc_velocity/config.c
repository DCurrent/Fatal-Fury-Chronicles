#include "data/scripts/dc_velocity/config.h"

// Which instance is in use?
int dc_velocity_get_instance()
{
	void result = getlocalvar(DC_VELOCITY_MEMBER_INSTANCE);

	if (!result)
	{
		result = DC_VELOCITY_DEFAULT_INSTANCE;
	}

	return result;
}

void dc_velocity_set_instance(int value)
{
	setlocalvar(DC_VELOCITY_MEMBER_INSTANCE, value);
}