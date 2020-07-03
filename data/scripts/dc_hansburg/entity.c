#include "data/scripts/dc_hansburg/config.h"


// Base entity functions will act on.
// Get
void dc_hansburg_get_entity()
{
	char id;
	void result;

	// Get id.
	id = dc_hansburg_get_instance() + DC_HANSBURG_MEMBER_ENT;

	result = getlocalvar(id);

	if (typeof(result) != openborconstant("VT_PTR"))
	{
		result = DC_HANSBURG_DEFAULT_ENT;
	}

	return result;
}

// Set
void dc_hansburg_set_entity(void value)
{
	char id;

	// Get id.
	id = dc_hansburg_get_instance() + DC_HANSBURG_MEMBER_ENT;

	if (value == DC_HANSBURG_DEFAULT_ENT)
	{
		value == NULL();
	}

	setlocalvar(id, value);
}