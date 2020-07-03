#include "data/scripts/dc_hansburg/config.h"

#import "data/scripts/dc_hansburg/double_jump.c"
#import "data/scripts/dc_hansburg/edge_jump.c"
#import "data/scripts/dc_hansburg/wall_jump.c"
#import "data/scripts/dc_hansburg/entity.c"
#import "data/scripts/dc_hansburg/limits.c"

// Caskey, Damon V.
// 2019-10-30
//
// Verify basic eligibility requirements before we allow 
// a secondary jump. Returns 1 (true) if the jump is 
// allowed, 0 (false) if not.
int dc_hansburg_check_extra_jump_elgible()
{
	void ent = dc_hansburg_get_entity();
	float pos_y;
	int pos_base;

	// If we aren't in the air, then we are starting a
	// normal jump. Along with returning false, we also 
	// need to clear the double jump count.
	
	pos_y = get_entity_property(ent, "position_y");
	pos_base = get_entity_property(ent, "position_base");

	if (pos_y - pos_base <= DC_HANSBURG_IN_AIR)
	{
		// If reset flag is set, reset the double jump counter.
		if (dc_hansburg_get_double_jump_count_reset() & DC_HANSBURG_DOUBLE_JUMP_COUNT_RESET_BASE)
		{
			dc_hansburg_set_double_jump_count(NULL());
		}

		return 0;
	}

	// We have to be in the assigned jump animation.

	if (get_entity_property(ent, "animation_id") != get_entity_property(ent, "jump_animation_id"))
	{
		return 0;
	}

	// Secondary jumping temporarily disabled?

	if (dc_hansburg_disable_check())
	{
		return 0;
	}

	// Above current Y position limit?

	if(pos_y > dc_hansburg_get_max_y())
	{
		return 0;
	}	

	// All checks passed, so return true.
	return 1;
}

// Caskey, Damon V.
// 2019-11-01 (Retooled from dc_hansburg_execute ~2018-03)
// 
// Main auxiliary jump function. Checks entity for Wall, edge, obstacle,
// and double jumping animations, evaluates usability based on
// "entity_status" and environment, and executes as necessary. Returns
// the animation set, or DC_HANSBURG_NO_EXTRA_JUMP if none.
int dc_hansburg_try_extra_jump(){

	log("\n\n\n dc_hansburg_try_extra_jump -----------------------------------------------");

    void    ent;					// Entity controlled by player index.
	int		player_index;			// Player index controlling entity.
	int     key_press       = 0;    // Key press triggering event.
	int		result;

	// Get acting entity.	
	ent = dc_hansburg_get_entity();

	// Verify the trigger event is a Jump key press. This is 
	// very important - key events run when any key is pressed,
	// released, and on every update while held. In other words, 
	// the vast majority of the time this will be a key event we 
	// don't care about. So to avoid wasting CPU time we want to 
	// get out quickly as possible as we can unless key event 
	// is the one we are looking for.
	
	player_index = get_entity_property(ent, "player_index");
    key_press    = getplayerproperty(player_index, "newkeys");	
	
	if (!(key_press & openborconstant("FLAG_JUMP")))
	{
		return DC_HANSBURG_NO_EXTRA_JUMP;
	}

	// Now let's see if the entity exists in play.
	if (!get_entity_property(ent, "exists"))
	{
		return DC_HANSBURG_NO_EXTRA_JUMP;
	}

	// Verify we are elgible for a secondary jump.
	if (!dc_hansburg_check_extra_jump_elgible())
	{
		return DC_HANSBURG_NO_EXTRA_JUMP;
	}	    	    
				

	// Try an obstacle jump, and exit if successful.

	// Try a wall jump, and exit if successful.
	result = dc_hansburg_try_wall_jump();

	if (result != DC_HANSBURG_NO_EXTRA_JUMP)
	{
		return result;
	}

	// Try a screen edge jump, and exit if successful.

	result = dc_hansburg_try_edge_jump();

	if (result != DC_HANSBURG_NO_EXTRA_JUMP)
	{
		return result;
	}

	// Try a double jump. This is our last extra jump
	// attempt, so just return the result directly.

	return dc_hansburg_try_double_jump();
}



