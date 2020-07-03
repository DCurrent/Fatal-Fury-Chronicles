#include "data/scripts/dc_hansburg/config.h"

#import "data/scripts/dc_hansburg/boundary_jump_start_hover.c"
#import "data/scripts/dc_hansburg/double_jump.c"
#import "data/scripts/dc_hansburg/entity.c"
#import "data/scripts/dc_hansburg/animation.c"

// Caskey, Damon V.
// Revamped 2019-10-28
//
// Places entity at a target position and sets facing to
// look away (from position). Use when setting up a wall
// or screen edge jump.
int dc_hansburg_try_wall_jump()
{
	void	ent;
	int		pos_direction;				// Position entity is set to.
	float   position_x = 0.0;		// Entity position, X axis.
	int		wall_x;
	int		running;
	int		animation;					// Animation to act on.

	// Get acting entity.
	ent = dc_hansburg_get_entity();

	// Let's determine which animation we will use.
	// If we don't have the selected animation, then 
	// we exit.

	animation = dc_hansburg_find_animation_from_run_state(DC_HANSBURG_ANI_JUMP_WALL_START, DC_HANSBURG_ANI_JUMP_WALL_START_RUN);

	if (!getentityproperty(ent, "animvalid", animation))
	{
		return DC_HANSBURG_NO_EXTRA_JUMP;
	}

	// Now we look for a screen edge within the acting 
	// animation's range. If we don't find a an edge in
	// range then we exit.
	
	dc_target_set_instance(dc_hansburg_get_instance_dependency());
	dc_target_set_entity(dc_hansburg_get_entity());
	
	dc_target_set_animation(animation);
	wall_x = dc_target_find_wall_x();

	if (wall_x == DC_TARGET_NO_WALL_FOUND)
	{
		return DC_HANSBURG_NO_EXTRA_JUMP;
	}

	// Face away from the wall location. 

	position_x = get_entity_property(ent, "position_x");

	if (position_x < wall_x)
	{
		pos_direction = openborconstant("DIRECTION_LEFT");
		position_x = wall_x;
	}
	else
	{
		pos_direction = openborconstant("DIRECTION_RIGHT");
		position_x = wall_x;
	}

	set_entity_property(ent, "position_direction", pos_direction);
	set_entity_property(ent, "position_x", position_x);

	// Stop all movement.
	set_entity_property(ent, "velocity_x", 0);
	set_entity_property(ent, "velocity_y", 0);
	set_entity_property(ent, "velocity_z", 0);

	// Set the edge jump start animation.
	performattack(ent, animation);

	// Hover in midair so we don't slide
	// down the edge while in startup pose
	// for edge jump.
	set_entity_property(ent, "toss_time", openborvariant("elapsed_time") + dc_hansburg_get_boundary_jump_start_hover());

	// If reset flag is set, reset the double jump counter.
	if (dc_hansburg_get_double_jump_count_reset() & DC_HANSBURG_DOUBLE_JUMP_COUNT_RESET_WALL)
	{
		dc_hansburg_set_double_jump_count(NULL());
	}

	// If we made it here, we have successfully
	// started an edge jump. Return animation.
	return animation;
}

// Caskey, Damon V.
// 2019-11-03
//
// Complete the wall jump. Run this on last frame of the 
// start up animation.
void dc_hansburg_do_wall_jump_finish()
{
	dc_hansburg_try_jump_animation(DC_HANSBURG_ANI_JUMP_WALL, DC_HANSBURG_ANI_JUMP_WALL_RUN);
}