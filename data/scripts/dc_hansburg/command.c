#include "data/scripts/dc_hansburg/config.h"

#import "data/scripts/dc_hansburg/entity.c"

// Caskey, Damon V.
// 2018-11-28 (rewrite - original 2016)
//
// Find out if player is holding "forward" or "back" key 
// command in relation to entity direction.
int dc_hansburg_find_direction_command()
{
	int result;
	void ent;
	int direction;
	int player_index;
	int key_hold;

	// Default to neutral.
	result = DC_HANSBURG_KEY_MOVE_HORIZONTAL_NEUTRAL;

	// Action entity.
	ent = dc_hansburg_get_entity();

	// Get the key "entity_status".
	player_index = getentityproperty(ent, "playerindex");
	key_hold = getplayerproperty(player_index, "keys");

	// Get direction.
	direction = get_entity_property(ent, "position_direction");

	// If player is holding left or right, check
	// entity direction. If the two match, then
	// we can consider the player key "forward".
	// If key and direction oppose, player is 
	// holding back.
	if (key_hold & openborconstant("FLAG_MOVELEFT"))
	{
		if (direction == openborconstant("DIRECTION_LEFT"))
		{			
			result = DC_HANSBURG_KEY_MOVE_HORIZONTAL_FORWARD;
		}
		else if(direction == openborconstant("DIRECTION_RIGHT"))
		{
			result = DC_HANSBURG_KEY_MOVE_HORIZONTAL_BACK;
		}		
	}
	else if (key_hold & openborconstant("FLAG_MOVERIGHT"))
	{
		if (direction == openborconstant("DIRECTION_LEFT"))
		{
			result = DC_HANSBURG_KEY_MOVE_HORIZONTAL_BACK;
		}
		else if (direction == openborconstant("DIRECTION_RIGHT"))
		{
			result = DC_HANSBURG_KEY_MOVE_HORIZONTAL_FORWARD;
		}
	}

	// Now return our results.
	return result;
}

