#include "data/scripts/dc_target/config.h"

#import "data/scripts/dc_target/animation.c"
#import "data/scripts/dc_target/entity.c"
#import "data/scripts/dc_target/offset.c"

// Caskey, Damon V.
// 2018-12-01
//
// Find total distance from acting enity to
// target.
float dc_target_find_total_distance_to_target(void target)
{
	float result;
	void ent;

	ent = dc_target_get_entity();

	if (typeof(target) != openborconstant("VT_PTR"))
	{
		//target = dc_target_get_target();
		return 0.0;
	}

	// Start with 0, and add the difference between acting
	// entity and target for each axis.
	result = 0.0;
	result += dc_math_difference_float(getentityproperty(target, "x"), getentityproperty(ent, "x"));
	result += dc_math_difference_float(getentityproperty(target, "y"), getentityproperty(ent, "y"));
	result += dc_math_difference_float(getentityproperty(target, "z"), getentityproperty(ent, "z"));

	// Return final result.
	return result;
}

// Caskey, Damon V.
// 2018-11-30
//
// Return true if:
//
// A) Acting entity has acing animation.
// B) Target entity is within acting
// animation range.
int dc_target_check_target_in_range_x(void target)
{
	int target_pos;

	// Must have a target.
	if (typeof(target) != openborconstant("VT_PTR"))
	{
		//target = dc_target_get_target();
		return 0;
	}

	// Get position.
	target_pos = getentityproperty(target, "x");

	//  Run the range function using target's
	// position as target position.
	return dc_target_check_position_in_range_x(target_pos);
}

// Caskey, Damon V.
// 2018-11-29 (breakdown of orginal from 2017-03-18)
//
// Return true if target position is 
// within animation's X range.
int dc_target_check_position_in_range_x(float target_pos)
{
	// Use library offset if no target position provided.
	if (typeof(target_pos) == openborconstant("VT_EMPTY"))
	{
		// Get target position.
		target_pos = dc_target_get_offset_x();
	}

	return dc_target_check_range_in_range_x(target_pos, target_pos);
}

// Caskey, Damon V.
// 2018-12-04
//
// Return true if any range of min/max falls within
// range of acting animation for acting entity.
int dc_target_check_range_in_range_x(float min, float max)
{
	void ent;			// Acting entity.
	int range_min_ani;	// Minimum range, animation.
	int range_max_ani;	// Minimum range, animation.
	int range_min;		// Minimum range.
	int range_max;		// Maximum range.
	float ent_pos;		// Current entity position.
	int animation;		// Animation to use.
	int result;

	// Get action ent and position.
	ent = dc_target_get_entity();
	ent_pos = getentityproperty(ent, "x");

	// Get animation and verify entity has it.
	animation = dc_target_get_animation();

	if (!getentityproperty(ent, "animvalid", animation))
	{
		return 0;
	}
	
	// Get range settings.
	range_min_ani = getentityproperty(ent, "range", "xmin", animation);
	range_max_ani = getentityproperty(ent, "range", "xmax", animation);

	// Add animation range to entity X position
	// for final X range coordinates. Subtract and
	// swap min/max when facing left.
	if (getentityproperty(ent, "direction") == openborconstant("DIRECTION_RIGHT"))
	{
		range_min = ent_pos + range_min_ani;
		range_max = ent_pos + range_max_ani;
	}
	else
	{		
		range_min = ent_pos - range_max_ani;
		range_max = ent_pos - range_min_ani;
	}	
	
	// Return true if ranges overlap, false otherwise.
	result = (range_min <= max && min <= range_max);

	return result;
}

// Caskey, Damon V.
// 2018-11-30
//
// Return true if:
//
// A) Acting entity has acting animation.
// B) Target entity is within acting
// animation range.
int dc_target_check_target_in_range_y(void target)
{
	int target_pos;

	// Must have a target.
	if (typeof(target) != openborconstant("VT_PTR"))
	{
		//target = dc_target_get_target();
		return 0;
	}

	// Get positions.
	target_pos = getentityproperty(target, "y");

	//  Run the range function using target's
	// position as target position.
	return dc_target_check_position_in_range_y(target_pos);
}

int dc_target_check_position_in_range_y(float target_pos)
{
	// Use library offset if target pos argument not given.
	if (typeof(target_pos) != openborconstant("VT_DECIMAL"))
	{
		target_pos = dc_target_get_offset_y();
	}

	dc_target_check_range_in_range_y(target_pos, target_pos);
}

// Caskey, Damon V.
// 2018-11-29 (breakdown of orginal from 2017-03-18)
//
// Return true if any range of min/max falls within
// range of acting animation for acting entity.
int dc_target_check_range_in_range_y(float min, float max)
{
	void ent;			// Acting entity.
	float ent_pos;		// Entity position.	
	int range_min;		// Minimum range.
	int range_max;		// Maximum range.
	float pos_current;	// Current entity position.
	int animation;		// Animation to use.
	int result;

	// Get action ent and position.
	ent = dc_target_get_entity();
	ent_pos = getentityproperty(ent, "y");

	// Get animation and verify entity has it.
	animation = dc_target_get_animation();

	if (!getentityproperty(ent, "animvalid", animation))
	{
		return 0;
	}

	// Get ranges.
	range_min = getentityproperty(ent, "range", "amin", animation);
	range_max = getentityproperty(ent, "range", "amax", animation);

	// Add current position to range.
	range_min += ent_pos;
	range_max += ent_pos;
	
	// Return true if ranges overlap, false otherwise.
	result = (range_min <= max && min <= range_max);	
	
	return result;
}

// Caskey, Damon V.
// 2018-11-30
//
// Return true if:
//
// A) Acting entity has acing animation.
// B) Target entity is within acting
// animation range.
//
// Logic is more or less a copy of OpenBOR's own
// check_range_target_z() function.
int dc_target_check_target_in_range_z(void target)
{
	int target_pos;

	// Must have a target.
	if (typeof(target) != openborconstant("VT_PTR"))
	{
		//target = dc_target_get_target();
		return 0;
	}

	// Get positions.
	target_pos = getentityproperty(target, "z");

	//  Run the range function using target's
	// position as target position.
	return dc_target_check_position_in_range_z(target_pos);
}

// Caskey, Damon V.
// 2018-11-29 (breakdown of orginal from 2017-03-18)
//
// Return true if target position is 
// within animation's Z range.
int dc_target_check_position_in_range_z(float target_pos)
{
	// Use library offset if target pos argument not given.
	if (typeof(target_pos) != openborconstant("VT_DECIMAL"))
	{
		target_pos = dc_target_get_offset_y();
	}

	dc_target_check_range_in_range_z(target_pos, target_pos);
}

// Caskey, Damon V.
// 2018-11-29 (breakdown of orginal from 2017-03-18)
//
// Return true if any range of min/max falls within
// range of acting animation for acting entity.
int dc_target_check_range_in_range_z(float min, float max)
{
	void ent;			// Acting entity.
	float ent_pos;		// Entity position.
	int range_min;		// Minimum range.
	int range_max;		// Maximum range.
	float pos_current;	// Current entity position.
	int animation;		// Animation to use.

	// Get action ent and position.
	ent = dc_target_get_entity();
	ent_pos = getentityproperty(ent, "z");

	// Get animation and verify entity has it.
	animation = dc_target_get_animation();

	if (!getentityproperty(ent, "animvalid", animation))
	{
		return 0;
	}

	// Get ranges.
	range_min = getentityproperty(ent, "range", "zmin", animation);
	range_max = getentityproperty(ent, "range", "zmax", animation);

	// Add current position to range.
	range_min += ent_pos;
	range_max += ent_pos;

	// Return true if ranges overlap, false otherwise.
	return (range_min <= max && min <= range_max);
}



