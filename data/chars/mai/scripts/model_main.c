#include "data/chars/galford/scripts/model_config.h"

// Galford loses his sword under certain conditions.
void try_weapon_drop(void ent)
{
	int  force_drop;                      // Incomming knockdown force.
	int  force_damage;                    // Incoming damage.
	int  health = getentityproperty(ent, "health");       //Current HP.
	float pos_y;
	float pos_base;

	void weapon_item;
	char weapon_name;

	// Have a weapon?
	weapon_item = get_entity_property(ent, "weapon_item");

	if (!weapon_item)
	{
		return 0;
	}

	// Is weapon the one we are looking for? Weapon number
	// would be omre optimal, but for whatever reason it
	// seems to return bad data. 
	//weapon_name = get_entity_property(ent, "name");
	
	//if (weapon_name != GALFORD_SWORD)
		
	//	return 0;
	//}

	// Now let's look at conditions.
	force_drop = getlocalvar("drop");

	if (force_drop < GALFOD_DROP_THRESHOLD)
	{
		return 0;
	}


	force_damage = getlocalvar("damage");

	pos_y = get_entity_property(ent, "position_y");
	pos_base = get_entity_property(ent, "position_base");

	// If the damage is less than our threshold AND we're
	// on the ground, then return false.
	if (force_damage < GALFORD_DAMAGE_THRESHOLD && dc_math_difference_float(pos_y, pos_base) <= 0.1)
	{
		return 0;
	}

	log("\n\n do_weapon_drop: " + weapon_item);

	// Lose and drop the weapon.
	do_weapon_drop(ent, weapon_item);

	return 1;
}

// Caskey, Damon V.
// 2019-10-04
//
// Host entity reverts to default model and weapon is dropped 
// as an item pickup. This is more or less a copy of OpenBOR's
// native dropweapon() function so we can replicate its
// functionality manually. If counter falls below a given
// threshold, the weapon breaks instead.
void do_weapon_drop(void ent, void weapon_ent)
{	
	float pos_x;
	float pos_y;
	float pos_z;
	float pos_base;
	float pos_direction;
	float height;
	int dropcount;
	
	// We're going to use our own position for the weapon.
	pos_x = get_entity_property(ent, "position_x");
	pos_y = get_entity_property(ent, "position_y");
	pos_z = get_entity_property(ent, "position_z");
	pos_base = get_entity_property(ent, "position_base");
	pos_direction = get_entity_property(ent, "position_direction");

	set_entity_property(weapon_ent, "position_x", pos_x);
	set_entity_property(weapon_ent, "position_y", pos_y);
	set_entity_property(weapon_ent, "position_z", pos_z);
	set_entity_property(weapon_ent, "position_base", pos_base);
	set_entity_property(weapon_ent, "position_direction", pos_direction);

	//log("\n\n position: " + pos_x + ", " + ", " + pos_y + ", " + )

	// If the flag is 2 or below, we subtract the flag's
	// value from weapon counter.
	//if (flag < 2)
	//{
	//	self->weapent->modeldata.counter -= flag;
	//}
	
	
	// Get current drop count, and start at 0 if we don't have one.
	dropcount = getlocalvar(GALFORD_WEAPON_DROP_COUNT_KEY);

	if (!dropcount)
	{
		dropcount = 0;
	}

	// Increment counter and save.
	dropcount++;
	setlocalvar(GALFORD_WEAPON_DROP_COUNT_KEY, dropcount);

	// Set animation control to weapon entity.
	dc_disney_set_entity(weapon_ent);

	// If we have dropped weapon too many times, use follow2 
	// animation to put weapon out of play. Otherwise just
	// use follow1 (weapon falls to ground as item).
	if (dropcount >= GALFORD_WEAPON_MAX_DROP)
	{
		dc_disney_play_animation(openborconstant("ANI_FOLLOW2"));
		setlocalvar(GALFORD_WEAPON_DROP_COUNT_KEY, NULL());
	}
	else
	{
		dc_disney_play_animation(openborconstant("ANI_FOLLOW1"));
	}
		

	// If the weapon's counter is depleted, then weapon is lost for good.
	// If it is an "animal", then we apply the animal running away logic.
	// Otherwise the weapon blinks out.
	//if (!self->weapent->modeldata.counter)
	//{
	//	if (!self->modeldata.animal)
	//	{
	//		self->weapent->blink = 1;
	//		self->weapent->takeaction = common_lie;
	//	}
	//	else
	//	{
	//		self->weapent->modeldata.type = TYPE_NONE;
	//		self->weapent->think = runanimal;
	//	}
	//}
	//self->weapent->nextthink = _time + 1;
		
	// Clear our tracking variable that keeps the weapon entity pointer.
	set_entity_property(ent, "weapon_item", NULL());

	changeentityproperty(ent, "weapon", GALFORD_WEAPON_UNARMED);

}


// Mimics spawning with a weapon pick up. 
void weapon_spawn()
{
	void ent = getlocalvar("self");
	void spawn = dc_gauntlet_quick_spawn("Justice_Sword");
	int animation;

	// Item spawns at our position, but hidden on Z axis.
	set_entity_property(spawn, "position_x", get_entity_property(ent, "position_x"));
	set_entity_property(spawn, "position_y", get_entity_property(ent, "position_y"));
	set_entity_property(spawn, "position_z", openborconstant("ITEM_HIDE_POSITION_Z"));

	// Make sure engine knowns this is a weapon type spawn.
	set_entity_property(spawn, "spawn_type", openborconstant("SPAWN_TYPE_WEAPON"));

	// Now we "pick up" the item. Our weapon changes and the item
	// pointer is stored in our weapon item property, just like
	// the engine's native pickup. 
	set_entity_property(ent, "weapon_item", spawn);
	changeentityproperty(ent, "weapon", 1);

	
}