#include "data/scripts/dc_velocity/config.h"

#import "data/scripts/dc_velocity/config.c"

// Base entity functions will act on.
void dc_velocity_get_entity()
{
	int instance;
	void result;

	result = getlocalvar(instance + DC_VELOCITY_MEMBER_ENT);

	if (typeof(result) != openborconstant("VT_PTR"))
	{
		result = DC_VELOCITY_DEFAULT_ENT;
	}

	return result;
}

void dc_velocity_set_entity(void value)
{
	int instance;

	setlocalvar(instance + DC_VELOCITY_MEMBER_ENT, value);
}

// Apply an inverted X when entity faces left?
int dc_velocity_get_invert_x()
{
	int instance;
	int result;

	result = getlocalvar(instance + DC_VELOCITY_MEMBER_INVERT_X);

	if (typeof(result) != openborconstant("VT_INTEGER"))
	{
		result = DC_VELOCITY_DEFAULT_INVERT_X;
	}

	return result;
}

int dc_velocity_set_invert_x(int value)
{
	int instance;

	setlocalvar(instance + DC_VELOCITY_MEMBER_INVERT_X, value);
}

// Velocity setting, X axis.
float dc_velocity_get_velocity_x()
{
	int instance;
	float result; 
	
	result = getlocalvar(instance + DC_VELOCITY_MEMBER_VELOCITY_X);

	if (typeof(result) == openborconstant("VT_EMPTY"))
	{
		result = DC_VELOCITY_DEFAULT_VELOCITY_X;
	}

	return result;
}

void dc_velocity_set_velocity_x(float value)
{
	int instance;

	setlocalvar(instance + DC_VELOCITY_MEMBER_VELOCITY_X, value);
}

// Velocity setting, Y axis.
float dc_velocity_get_velocity_y()
{
	int instance;
	float result;

	result = getlocalvar(instance + DC_VELOCITY_MEMBER_VELOCITY_Y);

	if (typeof(result) == openborconstant("VT_EMPTY"))
	{
		result = DC_VELOCITY_DEFAULT_VELOCITY_X;
	}

	return result;
}

void dc_velocity_set_velocity_y(float value)
{
	int instance;

	setlocalvar(instance + DC_VELOCITY_MEMBER_VELOCITY_Y, value);
}

// Velocity setting, Z axis.
float dc_velocity_get_velocity_z()
{
	int instance;
	float result;

	result = getlocalvar(instance + DC_VELOCITY_MEMBER_VELOCITY_Z);

	if (typeof(result) == openborconstant("VT_EMPTY"))
	{
		result = DC_VELOCITY_DEFAULT_VELOCITY_Z;
	}

	return result;
}

void dc_velocity_set_velocity_z(float value)
{
	int instance;

	setlocalvar(instance + DC_VELOCITY_MEMBER_VELOCITY_Z, value);
}

// Caskey, Damon V.
// 2018-11-12
//
// Output inverted X velocity if facing left
// and X invert is on.
float dc_velocity_check_invert_x()
{
	float result;
	void ent;
	int direction;
	
	result = dc_velocity_get_velocity_x();

	ent = dc_velocity_get_entity();
	direction = getentityproperty(ent, "direction");

	// Facing left? Then check for invert setting
	// and if found invert the X value.
	if (direction == openborconstant("DIRECTION_LEFT"))
	{
		if (dc_velocity_get_invert_x() == DC_VELOCITY_INVERT_X_AUTO)
		{
			result = -result;
		}
	}

	return result;
}

// Caskey, Damon V.
// 2018-11-12
//
// Apply velocity settings to entity's X axis.
void dc_velocity_apply_velocity_x()
{
	void ent;
	float vel_x;
	float vel_y;
	float vel_z;

	ent = dc_velocity_get_entity();

	// Get final velocity values.
	vel_x = dc_velocity_check_invert_x();
	vel_y = getentityproperty(ent, "tossv");
	vel_z = getentityproperty(ent, "zdir");	

	// Apply velocity.
	set_entity_property(ent, "velocity_x", vel_x);
	set_entity_property(ent, "velocity_y", vel_y);
	set_entity_property(ent, "velocity_z", vel_z);
}

// Caskey, Damon V.
// 2018-11-12
//
// Apply velocity settings to entity's Y axis.
void dc_velocity_apply_velocity_y()
{
	void ent;
	float vel_x;
	float vel_y;
	float vel_z;

	ent = dc_velocity_get_entity();

	// Get final velocity values.
	vel_x = getentityproperty(ent, "xdir");
	vel_y = dc_velocity_get_velocity_y();
	vel_z = getentityproperty(ent, "zdir");

	// Apply velocity.
	changeentityproperty(ent, "velocity", vel_x, vel_z, vel_y);
}

// Caskey, Damon V.
// 2018-11-12
//
// Apply velocity settings to entity's Z axis.
void dc_velocity_apply_velocity_z()
{
	void ent;
	float vel_x;
	float vel_y;
	float vel_z;

	ent = dc_velocity_get_entity();

	// Get final velocity values.
	vel_x = getentityproperty(ent, "xdir");
	vel_y = getentityproperty(ent, "tossv");
	vel_z = dc_velocity_get_velocity_z();

	// Apply velocity.
	changeentityproperty(ent, "velocity", vel_x, vel_z, vel_y);
}

// Caskey, Damon V.
//
// Apply velocity settings to entity.
void dc_velocity_apply_velocity() 
{
	void ent;
	float vel_x;
	float vel_y;
	float vel_z;

	ent = dc_velocity_get_entity();

	// Get final velocity values.
	vel_x = dc_velocity_check_invert_x();
	vel_y = dc_velocity_get_velocity_y();
	vel_z = dc_velocity_get_velocity_z();

	// Apply velocity.
	changeentityproperty(ent, "velocity", vel_x, vel_z, vel_y);
}