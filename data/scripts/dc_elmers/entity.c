#include "data/scripts/dc_elmers/config.h"

#import "data/scripts/dc_elmers/instance.c"


// Base entity functions will act on.
// Get
void dc_elmers_member_get_entity()
{
	char id;
	void result;

	// Get id.
	id = dc_elmers_member_get_instance() + DC_ELMERS_MEMBER_ENT;

	result = getlocalvar(id);

	if (typeof(result) != openborconstant("VT_PTR"))
	{
		result = DC_ELMERS_DEFAULT_ENT;
	}

	return result;
}

// Set
void dc_elmers_member_set_entity(void value)
{
	char id;

	// Get id.
	id = dc_elmers_member_get_instance() + DC_ELMERS_MEMBER_ENT;

	if (value == DC_ELMERS_DEFAULT_ENT)
	{
		value = NULL();
	}

	setlocalvar(id, value);
}

// Target entity (if any).
// Get
void dc_elmers_member_get_target()
{
	char id;
	void result;

	// Get id.
	id = dc_elmers_member_get_instance() + DC_ELMERS_MEMBER_TARGET;

	result = getlocalvar(id);

	if (typeof(result) != openborconstant("VT_PTR"))
	{
		result = DC_ELMERS_DEFAULT_TARGET;
	}

	return result;
}

// Set
void dc_elmers_member_set_target(void value)
{
	char id;

	// Get id.
	id = dc_elmers_member_get_instance() + DC_ELMERS_MEMBER_TARGET;

	if (value == DC_ELMERS_DEFAULT_TARGET)
	{
		value = NULL();
	}

	setlocalvar(id, value);
}

// Caskey, Damon V.
// 2019-06-15
//
// Swap target and entity members.
void dc_elmers_swap_entities()
{
	void ent;
	void target;

	target = dc_elmers_member_get_target();
	ent = dc_elmers_member_get_entity();

	dc_elmers_member_set_entity(target);
	dc_elmers_member_set_target(ent);
}
