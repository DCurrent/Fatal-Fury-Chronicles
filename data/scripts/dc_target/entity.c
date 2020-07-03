#include "data/scripts/dc_target/config.h"

#import "data/scripts/dc_target/instance.c"

// Acting entity.
void dc_target_get_entity()
{
	void result;
	char id;

	// Concatenate instance with var key
	// to get a finished variable id.
	id = dc_target_get_instance() + DC_TARGET_MEMBER_ENT;

	// Get current value.
	result = getlocalvar(id);

	// If the value is blank or wrong type,
	// use default instead.
	if (typeof(result) != openborconstant("VT_PTR"))
	{
		result = DC_TARGET_DEFAULT_ENT;
	}

	// Return value.
	return result;
}

void dc_target_set_entity(void value)
{
	char id;
	void result;

	// Concatenate instance with var key
	// to get a finished variable id.
	id = dc_target_get_instance() + DC_TARGET_MEMBER_ENT;

	// If the value we intend to set is
	// same as default, then just make sure
	// the variable is deleted instead. No
	// reason to waste memory on default values.
	if (value == DC_TARGET_DEFAULT_ENT)
	{
		value = NULL();
	}

	// Apply value to a local var with
	// our concatenated id.
	setlocalvar(id, value);
}