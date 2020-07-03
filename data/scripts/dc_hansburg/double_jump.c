
#include "data/scripts/dc_hansburg/config.h"

#import "data/scripts/dc_hansburg/command.c"
#import "data/scripts/dc_hansburg/entity.c"
#import "data/scripts/dc_hansburg/animation.c"

// Number of double jumps executed.
int dc_hansburg_get_double_jump_count()
{
	char id;
	int result;

	// Get id.
	id = dc_hansburg_get_instance() + DC_HANSBURG_MEMBER_DOUBLE_JUMP_COUNT;

	result = getlocalvar(id);

	if (typeof(result) != openborconstant("VT_INTEGER"))
	{
		result = DC_HANSBURG_DEFAULT_DOUBLE_JUMP_COUNT;
	}

	return result;
}

void dc_hansburg_set_double_jump_count(int value)
{
	char id;

	// Get id.
	id = dc_hansburg_get_instance() + DC_HANSBURG_MEMBER_DOUBLE_JUMP_COUNT;

	if (value == DC_HANSBURG_DEFAULT_DOUBLE_JUMP_COUNT)
	{
		value = NULL();
	}

	setlocalvar(id, value);
}

// Reset double jump count when jumping from screen edge.
int dc_hansburg_get_double_jump_count_reset()
{
	char id;
	int result;

	// Get id.
	id = dc_hansburg_get_instance() + DC_HANSBURG_MEMBER_DOUBLE_JUMP_COUNT_RESET;

	result = getlocalvar(id);

	if (typeof(result) != openborconstant("VT_INTEGER"))
	{
		result = DC_HANSBURG_DEFAULT_DOUBLE_JUMP_COUNT_RESET;
	}

	return result;
}

void dc_hansburg_set_double_jump_count_reset(int value)
{
	char id;

	// Get id.
	id = dc_hansburg_get_instance() + DC_HANSBURG_MEMBER_DOUBLE_JUMP_COUNT_RESET;

	if (value == DC_HANSBURG_DEFAULT_DOUBLE_JUMP_COUNT_RESET)
	{
		value = NULL();
	}

	setlocalvar(id, value);
}

// Maximum allowed double jumps.
int dc_hansburg_get_double_jump_max()
{
	char id;
	int result;

	// Get id.
	id = dc_hansburg_get_instance() + DC_HANSBURG_MEMBER_DOUBLE_JUMP_MAX;

	result = getlocalvar(id);

	if (typeof(result) != openborconstant("VT_INTEGER"))
	{
		result = DC_HANSBURG_DEFAULT_DOUBLE_JUMP_MAX;
	}

	return result;
}

void dc_hansburg_set_double_jump_max(int value)
{
	char id;

	// Get id.
	id = dc_hansburg_get_instance() + DC_HANSBURG_MEMBER_DOUBLE_JUMP_MAX;

	if (value == DC_HANSBURG_DEFAULT_DOUBLE_JUMP_MAX)
	{
		value = NULL();
	}

	setlocalvar(id, value);
}

// Caskey, Damon V.
// 2019-10-30
//
// Attempt to perform a double jump. The following 
// conditions must pass:
//
// -- Entity is airborne.
// -- Entity has not exceeded the maximum allowed 
// double jumps (resets when entity jumps from ground). 
int dc_hansburg_try_double_jump()
{
	log("\n\n");
	log("\n dc_hansburg_try_double_jump");


	void ent = dc_hansburg_get_entity();
	int cmd_direction;
	int result = DC_HANSBURG_NO_EXTRA_JUMP;
	int double_jump_count = 0;	

	log("\n dc_hansburg_try_double_jump, passed Y");

	// Check the double jump count. If it at or over 
	// the maximum, we can't double jump. Just exit.
		
	double_jump_count = dc_hansburg_get_double_jump_count();

	log("\n dc_hansburg_try_double_jump, dc_hansburg_get_double_jump_max(): " + dc_hansburg_get_double_jump_max());
	log("\n dc_hansburg_try_double_jump, double_jump_count: " + double_jump_count);

	if (double_jump_count >= dc_hansburg_get_double_jump_max())
	{
		return result;
	}		

	log("\n dc_hansburg_try_double_jump, passed count");

	// Check the player's direction command, and depending
	// on their input, we will send Forward, Neutral or
	// backward jump animations to dc_hansburg_try_jump_animation
	// function to apply a running or non-running version
	// of the double jump, assuming entity has either.
		
	cmd_direction = dc_hansburg_find_direction_command();

	switch (cmd_direction)
	{
		// No direction at all.
	default:
	case DC_HANSBURG_KEY_MOVE_HORIZONTAL_NEUTRAL:

		result = dc_hansburg_try_jump_animation(DC_HANSBURG_ANI_JUMP_DOUBLE_NEUTRAL, DC_HANSBURG_ANI_JUMP_DOUBLE_NEUTRAL_RUN);
		break;

		// Backward.
	case DC_HANSBURG_KEY_MOVE_HORIZONTAL_BACK:

		result = dc_hansburg_try_jump_animation(DC_HANSBURG_ANI_JUMP_DOUBLE_BACK, DC_HANSBURG_ANI_JUMP_DOUBLE_BACK_RUN);
		break;

		// Forward.
	case DC_HANSBURG_KEY_MOVE_HORIZONTAL_FORWARD:

		result = dc_hansburg_try_jump_animation(DC_HANSBURG_ANI_JUMP_DOUBLE_FORWARD, DC_HANSBURG_ANI_JUMP_DOUBLE_FORWARD_RUN);
		break;
	}

	// If we sucessfuly double jumped, then let's increment the
	// double jump counter.
	if (result != DC_HANSBURG_NO_EXTRA_JUMP)
	{			
		log("\n dc_hansburg_try_double_jump, double_jump_count: " + double_jump_count);
		double_jump_count = double_jump_count + 1;
		log("\n dc_hansburg_try_double_jump, double_jump_count: " + double_jump_count);
		dc_hansburg_set_double_jump_count(double_jump_count);
	}

	log("\n dc_hansburg_try_double_jump, all");
	log("\n dc_hansburg_try_double_jump, dc_hansburg_get_double_jump_count: " + dc_hansburg_get_double_jump_count());

	return result;
}



