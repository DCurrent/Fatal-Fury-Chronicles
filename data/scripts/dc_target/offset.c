#include "data/scripts/dc_target/config.h"

#import "data/scripts/dc_target/instance.c"

// Base offset.
int dc_target_get_offset_base()
{
	int result;
	char id;

	// Concatenate instance with var key
	// to get a finished variable id.
	id = dc_target_get_instance() + DC_TARGET_MEMBER_OFFSET_BASE;

	// Get current value.
	result = getlocalvar(id);

	// If the value is blank or wrong type,
	// use default instead.
	if (typeof(result) != openborconstant("VT_INTEGER"))
	{
		result = DC_TARGET_DEFAULT_OFFSET_BASE;
	}

	// Return value.
	return result;
}

void dc_target_set_offset_base(int value)
{
	char id;

	// Concatenate instance with var key
	// to get a finished variable id.
	id = dc_target_get_instance() + DC_TARGET_MEMBER_OFFSET_BASE;

	// If the value we intend to set is
	// same as default, then just make sure
	// the variable is deleted instead. No
	// reason to waste memory on default values.
	if (value == DC_TARGET_DEFAULT_OFFSET_BASE)
	{
		value = NULL();
	}

	// Apply value to a local var with
	// our concatenated id.
	setlocalvar(id, value);
}

// X axis offset.
int dc_target_get_offset_x()
{
	int result;
	char id;

	// Concatenate instance with var key
	// to get a finished variable id.
	id = dc_target_get_instance() + DC_TARGET_MEMBER_OFFSET_X;

	// Get current value.
	result = getlocalvar(id);

	// If the value is blank or wrong type,
	// use default instead.
	if (typeof(result) != openborconstant("VT_INTEGER"))
	{
		result = DC_TARGET_DEFAULT_OFFSET_X;
	}

	// Return value.
	return result;
}

void dc_target_set_offset_x(int value)
{
	char id;

	// Concatenate instance with var key
	// to get a finished variable id.
	id = dc_target_get_instance() + DC_TARGET_MEMBER_OFFSET_X;

	// If the value we intend to set is
	// same as default, then just make sure
	// the variable is deleted instead. No
	// reason to waste memory on default values.
	if (value == DC_TARGET_DEFAULT_OFFSET_X)
	{
		value = NULL();
	}	
	
	// Apply value to a local var with
	// our concatenated id.
	setlocalvar(id, value);	
}

// Y axis offset.
int dc_target_get_offset_y()
{
	int result;
	char id;

	// Concatenate instance with var key
	// to get a finished variable id.
	id = dc_target_get_instance() + DC_TARGET_MEMBER_OFFSET_Y;

	// Get current value.
	result = getlocalvar(id);

	// If the value is blank or wrong type,
	// use default instead.
	if (typeof(result) != openborconstant("VT_INTEGER"))
	{
		result = DC_TARGET_DEFAULT_OFFSET_Y;
	}

	// Return value.
	return result;
}

void dc_target_set_offset_y(int value)
{
	char id;

	// Concatenate instance with var key
	// to get a finished variable id.
	id = dc_target_get_instance() + DC_TARGET_MEMBER_OFFSET_Y;

	// If the value we intend to set is
	// same as default, then just make sure
	// the variable is deleted instead. No
	// reason to waste memory on default values.
	if (value == DC_TARGET_DEFAULT_OFFSET_Y)
	{
		value = NULL();
	}

	// Apply value to a local var with
	// our concatenated id.
	setlocalvar(id, value);
}

// Z axis offset.
int dc_target_get_offset_z()
{
	int result;
	char id;

	// Concatenate instance with var key
	// to get a finished variable id.
	id = dc_target_get_instance() + DC_TARGET_MEMBER_OFFSET_Z;

	// Get current value.
	result = getlocalvar(id);

	// If the value is blank or wrong type,
	// use default instead.
	if (typeof(result) != openborconstant("VT_INTEGER"))
	{
		result = DC_TARGET_DEFAULT_OFFSET_Z;
	}

	// Return value.
	return result;
}

void dc_target_set_offset_z(int value)
{
	char id;

	// Concatenate instance with var key
	// to get a finished variable id.
	id = dc_target_get_instance() + DC_TARGET_MEMBER_OFFSET_Z;

	// If the value we intend to set is
	// same as default, then just make sure
	// the variable is deleted instead. No
	// reason to waste memory on default values.
	if (value == DC_TARGET_DEFAULT_OFFSET_Z)
	{
		value = NULL();
	}

	// Apply value to a local var with
	// our concatenated id.
	setlocalvar(id, value);
}