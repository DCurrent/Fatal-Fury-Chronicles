#include "data/scripts/dc_hansburg/config.h"

#import "data/scripts/dc_hansburg/entity.c"

int dc_hansburg_get_axis_control()
{
	char id;
	int result;

	id = dc_hansburg_get_instance() + DC_HANSBURG_MEMBER_AXIS_CONTROL;

	result = getlocalvar(id);

	if (typeof(result) != openborconstant("VT_INTEGER"))
	{
		result = DC_HANSBURG_DEFAULT_AXIS_CONTROL;
	}

	return result;
}

void dc_hansburg_set_axis_control(float value)
{
	char id;

	// Get id.
	id = dc_hansburg_get_instance() + DC_HANSBURG_MEMBER_AXIS_CONTROL;

	if (value == DC_HANSBURG_DEFAULT_AXIS_CONTROL)
	{
		value = NULL();
	}

	// Set value.
	setlocalvar(id, value);
}

float dc_hansburg_get_mario_min_y()
{
	char id;
	int result;

	id = dc_hansburg_get_instance() + DC_HANSBURG_MEMBER_MARIO_MIN_Y;

	result = getlocalvar(id);

	if (typeof(result) != openborconstant("VT_INTEGER"))
	{
		result = DC_HANSBURG_DEFAULT_MARIO_MIN_Y;
	}

	return result;
}

float dc_hansburg_set_mario_min_y(float value)
{
	int id;

	// Get id.
	id = dc_hansburg_get_instance() + DC_HANSBURG_MEMBER_MARIO_MIN_Y;

	if (value == DC_HANSBURG_DEFAULT_MARIO_MIN_Y)
	{
		value = NULL();
	}

	// Set value.
	setlocalvar(id, value);
}

float dc_hansburg_get_mario_y_stop()
{
	char id;
	int result;

	id = dc_hansburg_get_instance() + DC_HANSBURG_MEMBER_MARIO_Y_STOP;

	result = getlocalvar(id);

	if (typeof(result) != openborconstant("VT_INTEGER"))
	{
		result = DC_HANSBURG_DEFAULT_MARIO_Y_STOP;
	}

	return result;
}

float dc_hansburg_set_mario_y_stop(int value)
{
	int id;

	// Get id.
	id = dc_hansburg_get_instance() + DC_HANSBURG_MEMBER_MARIO_Y_STOP;

	if (value == DC_HANSBURG_DEFAULT_MARIO_Y_STOP)
	{
		value = NULL();
	}

	// Set value.
	setlocalvar(id, value);
}

// Caskey, Damon V.
//
// 2019-04-16
// Return true if in a jumping animation.
int dc_hansburg_verify_jump()
{
	void ent;
	int	animation_id;

	ent = dc_hansburg_get_entity();

	animation_id = get_entity_property(ent, "animation");

	if (animation_id == openborconstant("ANI_JUMP")
		|| animation_id == openborconstant("ANI_FORWARDJUMP")
		|| animation_id == openborconstant("ANI_RUNJUMP")
		|| animation_id == DC_HANSBURG_ANI_JUMP_DOUBLE_NEUTRAL
		|| animation_id == DC_HANSBURG_ANI_JUMP_DOUBLE_BACK
		|| animation_id == DC_HANSBURG_ANI_JUMP_DOUBLE_FORWARD
		|| animation_id == DC_HANSBURG_ANI_JUMP_EDGE
		|| animation_id == DC_HANSBURG_ANI_JUMP_OBJECT
		|| animation_id == DC_HANSBURG_ANI_JUMP_WALL)
	{
		return 1;
	}

	return 0;
}

// Caskey, Damon V.
// 2019-04-16
//
// Rework of the old jump0005 portion that controls Y
// velocity. Creates a mario brothers style jump effect
// where player controls jump height by how long they
// hold down the jump key.
int dc_hansburg_axis_control_mario()
{
	void ent;
	int	animation_id;
	float velocity_y;
	int index;
	int pos_base;
	int pos_y;

	if (dc_hansburg_get_axis_control() & DC_HANSBURG_AXIS_CONTROL_VELOCITY_Y_MARIO)
	{
	}
	else
	{
		return 0;
	}

	ent = dc_hansburg_get_entity();
	index = get_entity_property(ent, "player_index");

	// If player is holding jump, exit.
	if (playerkeys(0, 0, "jump"))
	{
		return 0;
	}

	// Must be at minimum Y position.
	pos_y = get_entity_property(ent, "position_y");
	pos_base = get_entity_property(ent, "position_base");

	if (pos_y - pos_base < dc_hansburg_get_mario_min_y())
	{
		return 0;
	}

	// Let's get the current velocity.
	velocity_y = get_entity_property(ent, "velocity_y");

	// If we're already falling, exit.
	if (velocity_y < 0)
	{
		return 0;
	}

	// Made it here, so let's stop the jump. We don't just set
	// a Y velocity of 0 though, or it will look like the entity
	// smacked into a glass ceiling. Instead we apply a % of the
	// current velocity. This stops the jump with a smooth arc.
	velocity_y *= dc_hansburg_get_mario_y_stop();

	set_entity_property(ent, "velocity_y", velocity_y);

	// Return true.
	return 1;
}
