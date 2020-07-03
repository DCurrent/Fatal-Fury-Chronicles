#include "data/scripts/dc_disney/main.c"
#include "data/scripts/dc_elmers/main.c"

void oncreate()
{
	log("\n");
	log("keyall.c");
	log("\t");
	log("- oncreate().");
	log("\n");
}

void ondestroy()
{
	log("\n");
	log("keyall.c");
	log("\t");
	log("- oncreate().");
	log("\n");
}

#define ANIMATION_AIR_BLOCK openborconstant("ANI_FOLLOW80")
#define ANIMATION_AIR_BACK_ATTACK openborconstant("ANI_FOLLOW81")
#define ANIMATION_ALTERNATE_JUMPATTACK2 openborconstant("ANI_FOLLOW89")
#define ANIMATION_DOWN_ATTACK openborconstant("ANI_FOLLOW82")

void main(){
    
	int     player_index;		// Player index.
	void    ent;				// Player entity.
		
	player_index = getlocalvar("player");

	// Populate the variables.
	ent = getplayerproperty(player_index, "entity");
	
	// Don't error out if we aren't in a level with entities.
	if (!ent)
	{
		return;
	}	

	// Set base entity for animation control library.
	dc_disney_set_entity(ent);

	// Run different action attempts based on basic entity state.
	if (get_entity_property(ent, "idle_state"))
    {
		// Backward dash (2x Special)
		if (dc_command_back_dash(player_index))
		{
			return;
		}

		// Hitting downed enemies.
		if (dc_try_down_attack(player_index))
		{
			return;
		}
	}
	else if (get_entity_property(ent, "block_state"))
	{
		// Backward dash (2x Special)
		if (dc_command_back_dash(player_index))
		{
			return;
		}
	}
    else if (get_entity_property(ent, "jump_state"))
    {
		// Air block.
		if (dc_command_airblock(player_index))
		{
			return;
		}
           
		// Alternate drop attack (Attack + down, not moving).
		if (dc_command_air_alternate_drop_attack(player_index))
		{
			return;
		}
    }
    else if (get_entity_property(ent, "attack_state"))
    {	
    }
	else if (get_entity_property(ent, "link"))
	{
		dc_try_grapple_side_switch();
	}

	
}

// Caskey, Damon V.
// 2018-11-03
//
// Return true if entity is in last from of a side dodge.
int dc_check_sidestep_complete(void ent)
{
	int animation;
	int frame;
	float velocity_z;

	// Must be playing at least one of the side
	// dodge animations.
	animation = getentityproperty(ent, "animationid");

	if (animation == openborconstant("ANI_ATTACKDOWN")	||	
		animation == openborconstant("ANI_ATTACKUP"))
	{
		// Nothing, just continue.
	}
	else
	{
		return 0;
	}

	// Not on the first frame.
	frame = getentityproperty(ent, "animpos");

	if (!frame)
	{
		return 0;
	}

	// Not moving along Z axis.
	velocity_z = getentityproperty(ent, "zdir");

	if (velocity_z)
	{
		return 0;
	}

	// Got this far - we can return true.
	return 1;
}

// Caskey, Damon V.
// 2018-11-01
//
// Perform backward dash if possible. Return true on success.
int dc_command_back_dash(int player_index)
{
	void ent;		// Base entity.
	int key_press;	// Key pressed.
	int key_hold;	// Key(s) hold.
	int time_current;
	int time_set;

	// Get base entity.
	ent = getplayerproperty(player_index, "entity");
	
	// Key press.
	key_press = getplayerproperty(player_index, "newkeys");
	   
	if (!(key_press & openborconstant("FLAG_SPECIAL")))
	{
		return 0;
	}
	
	// Get time.
	time_set = getlocalvar(player_index + "_sp");

	//  Get current time.
	time_current = openborvariant("elapsed_time");

	//  Set tracking var for next cycle.
	setlocalvar(player_index + "_sp", time_current + 50);
	
	// Fail on first cycle.
	if (!time_set)
	{
		return;
	}
	
	// Last attempt has to be within time of current
	// attempt.
	if (time_current > time_set)
	{
		return;
	}
	
	// If we got this far then we can backward dash.
	dc_disney_perform_attack(openborconstant("ANI_FREESPECIAL"));

	// Stop moving in case we were walking.
	changeentityproperty(ent, "velocity", 0, 0, 0);

	// Clear attack flag from key press.
	key_press -= openborconstant("FLAG_SPECIAL");
	changeplayerproperty(player_index, "newkeys", key_press);

	// Return true.
	return 1;
}

// Caskey, Damon V.
// 2018-11-03
//
// Turn player entity around if player holds opposite direction key
// to entity's facing.
void dc_command_direction_switch(int player_index)
{
	void ent;			// Base entity
	int direction;		// Entity direction.
	int opposite_key;	// Player key command vs. entity direction.

	// If player isn't holding opposite key, then we don't 
	// care about anything else.
	opposite_key = dc_check_key_back(player_index);
	
	if (!opposite_key)
	{
		return;
	}

	// We got this far, so let's turn the entity around.

	// Get base entity and direction.
	ent			= getplayerproperty(player_index, "entity");
	direction	= getentityproperty(ent, "direction");

	// Update direction variable as nessesaary.
	if (direction == openborconstant("DIRECTION_LEFT"))
	{
		direction = openborconstant("DIRECTION_RIGHT");
	}
	else if (direction == openborconstant("DIRECTION_RIGHT"))
	{
		direction = openborconstant("DIRECTION_LEFT");
	}

	// Apply updated direction to entity.
	changeentityproperty(ent, "direction", direction);
}

// Caskey, Damon V.
// 2018-11-03
//
// Return true if current directional key is "back" in relation to entity direction.
int dc_check_key_back(int player_index)
{

	void ent;		// Base entity
	int key_hold;	// Key(s) hold.
	int direction;	// Current facing.

	// Get base entity.
	ent = getplayerproperty(player_index, "entity");

	// Get key hold and direction.
	key_hold	= getplayerproperty(player_index, "keys");
	direction	= getentityproperty(ent, "direction");

	// Direction and key opposing? Then we return true.
	if (direction == openborconstant("DIRECTION_LEFT"))
	{
		if (key_hold &  openborconstant("FLAG_MOVERIGHT"))
		{
			return 1;
		}
	}
	else if (direction == openborconstant("DIRECTION_RIGHT"))
	{
		if (key_hold &  openborconstant("FLAG_MOVELEFT"))
		{
			return 1;
		}
	}
	
	// No checks passed, return false.
	return 0;
}

// Caskey, Damon  V.
// 2018-11-03
//
// Perform airblock on command if possible. Return true on success.
int dc_command_airblock(int player_index)
{
	void ent;
	int key_press;
	int attacking;
	//int jumping;

	// Get base entity.
	ent = getplayerproperty(player_index, "entity");

	// Verify key press.
	key_press = getplayerproperty(player_index, "newkeys");

	if (!(key_press & openborconstant("FLAG_SPECIAL")))
	{
		return 0;
	}

	// Must be jumping.
	//jumping = getentityproperty(ent, "aiflag", "jumping");

	//if (!jumping)
	//{
	//	return 0;
	//}

	// Can't be attacking.
	attacking = getentityproperty(ent, "aiflag", "attacking");

	if (attacking)
	{
		return 0;
	}

	// Must have an air block.
	if (!getentityproperty(ent, "animvalid", ANIMATION_AIR_BLOCK))
	{
		return 0;
	}

	// Set the animation.
	dc_disney_play_animation(ANIMATION_AIR_BLOCK);

	// Clear key flag from key press.
	key_press -= openborconstant("FLAG_SPECIAL");
	changeplayerproperty(player_index, "newkeys", key_press);

	// Return true.
	return 1;

}

// Caskey, Damon  V.
// 2018-11-03
//
// Perform air alternate drop attack (hold down + attack, when
// not moving along X axis) on command if possible. 
// Return true on c.
int dc_command_air_alternate_drop_attack(int player_index)
{
	void ent;
	int key_press;
	int key_hold;
	int attacking;
	float velocity_x;
	
	// Get base entity.
	ent = getplayerproperty(player_index, "entity");

	// Verify key press.
	key_press = getplayerproperty(player_index, "newkeys");

	if (!(key_press & openborconstant("FLAG_ATTACK")))
	{
		return 0;
	}

	// Verify key hold.
	key_hold = getplayerproperty(player_index, "keys");

	if (!(key_hold & openborconstant("FLAG_MOVEDOWN")))
	{
		return 0;
	}

	// Can't be attacking.
	attacking = getentityproperty(ent, "aiflag", "attacking");

	if (attacking)
	{
		return 0;
	}

	// Can't be moving along X axis.
	velocity_x = getentityproperty(ent, "xdir");

	if (velocity_x)
	{
		return 0;
	}

	// Must have the animation.
	if (!getentityproperty(ent, "animvalid", ANIMATION_ALTERNATE_JUMPATTACK2))
	{
		return 0;
	}

	// Set the animation.
	dc_disney_play_animation(ANIMATION_ALTERNATE_JUMPATTACK2);

	// Clear key flag from key press.
	key_press -= openborconstant("FLAG_ATTACK");
	changeplayerproperty(player_index, "newkeys", key_press);

	// Return true.
	return 1;

}

// Caskey, Damon V.
// 2018-11-01
//
// Verify conditions for down attack and execute if possible.
int dc_try_down_attack(int player_index)
{
	void ent;		// Base entity.
	int key_press;	// Key pressed.
	int key_hold;	// Key(s) hold.
	void target;	// Target entity.
	int idle;


	// Get base entity.
	ent = getplayerproperty(player_index, "entity");

	// Key press must be attack 1.
	key_press = getplayerproperty(player_index, "newkeys");
		
	if (!(key_press & openborconstant("FLAG_ATTACK")))
	{
		return 0;
	}

	// Key hold must be Down.
	key_hold = getplayerproperty(player_index, "keys");

	if (!(key_hold & openborconstant("FLAG_MOVEDOWN")))
	{
		return 0;
	}

	// Must have a down attack.
	if (!getentityproperty(ent, "animvalid", ANIMATION_DOWN_ATTACK))
	{
		return 0;
	}

	// Must have a target within range of Down attack.
	// Any target in range of down attack?
	target = findtarget(ent, ANIMATION_DOWN_ATTACK);

	if (!target)
	{
		return 0;
	}

	// Target cannot be animating. This is how we
	// know it has completed a fall.
	if (getentityproperty(target, "aiflag", "animating"))
	{
		return 0;
	}

	// Target cannot be dead.
	if (getentityproperty(target, "dead"))
	{
		return 0;
	}

	// If we got this far then we can set a down attack.
	dc_disney_perform_attack(ANIMATION_DOWN_ATTACK);

	// Stop moving in case we were walking.
	changeentityproperty(ent, "velocity", 0, 0, 0); 

	// Clear attack flag from key press.
	key_press -= openborconstant("FLAG_ATTACK");
	changeplayerproperty(player_index, "newkeys", key_press);

	// Return true.
	return 1;
}

// Caskey, Damon V.
// 2018-11-01
//
// Verify conditions for switching sides and do it if possible.
int dc_try_grapple_side_switch(int player_index)
{
	int key_press;	// Key pressed.	

	// Key press validation.
	key_press = getplayerproperty(player_index, "playkeys");

	if (!(key_press & openborconstant("FLAG_JUMP")))
	{
		return 0;
	}	

	// Run the action function.
	dc_elmers_set_target(getplayerproperty(player_index, "entity"));
	dc_elmers_side_switch();
	
	// Clear flag from key press.
	key_press -= openborconstant("FLAG_JUMP");
	changeplayerproperty(player_index, "playkeys", 0);

	// Return true.
	return 1;
}