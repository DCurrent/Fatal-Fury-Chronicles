#include "data/scripts/dc_hansburg/config.h"
#import "data/scripts/dc_hansburg/entity.c"

// Caskey, Damon V.
// 2019-11-03
//
// Select from running or non-running animations. If the
// animations are identical or running animation is not
// available, default to walking animation. Does NOT
// verify the animations are available.
int dc_hansburg_find_animation_from_run_state(int animation_default, int animation_run)
{
	void ent = dc_hansburg_get_entity();
	int running = get_entity_property(ent, "run_state");
	int result = animation_default;

	if (running)
	{
		if (animation_default == animation_run)
		{
			result = animation_default;
		}
		else
		{
			result = animation_run;
		}
	}

	return result;

}

// Caskey, Damon V.
// 2019-10-30
//
// Attempt to set jump animation based on running state
// and availability.
//
// -- Switch to edge jump animation. Returns 
// DC_HANSBURG_NO_EXTRA_JUMP if entity does not 
// have requested jump animation.
// -- Set jumping flag.
// -- Turn off tosstime that we applied when 
// starting the jump.
int dc_hansburg_try_jump_animation(int animation_base, int animation_running)
{
	void ent = dc_hansburg_get_entity();
	int running = get_entity_property(ent, "run_state");
	int animation;

	// Reset toss time.
	set_entity_property(ent, "toss_time", 0);	

	// If we are running and have version of the secondary jump, then let's
	// switch to and return it.
	if (running && getentityproperty(ent, "animvalid", animation_running))
	{
		// Switch to the animation.
		performattack(ent, animation_running, 1);

		// Set AI action so this is treated like a normal jump.
		changeentityproperty(ent, "takeaction", "common_jump");
		
		set_entity_property(ent, "jump_animation_id", animation_running);
		
		return animation_running;
	}

	// Do we have the normal secondary jump? 
	if (getentityproperty(ent, "animvalid", animation_base))
	{
		// Switch to the animation.
		performattack(ent, animation_base, 1);

		// Set AI action so this is treated like a normal jump.
		changeentityproperty(ent, "takeaction", "common_jump");

		set_entity_property(ent, "jump_animation_id", animation_base);

		return animation_base;
	}

	return DC_HANSBURG_NO_EXTRA_JUMP;
}