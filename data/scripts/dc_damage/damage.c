#include "data/scripts/dc_damage/config.h"
#import "data/scripts/dc_damage/config.c"
#import "data/scripts/dc_damage/instance.c"
#import "data/scripts/dc_damage/direction.c"
#import "data/scripts/dc_damage/lethality.c"
#import "data/scripts/dc_damage/damage_force.c"
#import "data/scripts/dc_damage/damage_land.c"
#import "data/scripts/dc_damage/damage_type.c"
#import "data/scripts/dc_damage/direction.c"
#import "data/scripts/dc_damage/drop.c"
#import "data/scripts/dc_damage/entity.c"
#import "data/scripts/dc_damage/instance.c"
#import "data/scripts/dc_damage/projectile.c"
#import "data/scripts/dc_damage/toss.c"
#import "data/scripts/dc_damage/velocity.c"

// Caskey, Damon V.
// 2018-11-13
//
// Apply damage to entity.
void dc_damage_apply_damage()
{
	void ent;
	void other;

	int force;
	int drop;
	int type;
	int fall;
	int dol_force;
	int projectile;


	// Entities.
	ent = dc_damage_get_entity();
	other = dc_damage_get_other();

	// Unset target's death status so it can receive damage effect even if already killed. This won't
	// adversely affect anything, because assuming hitpoints are at or below 0 after damage applies
	// the engine will immediately reset dead flag.
	set_entity_property(ent, "dead", 0);                                      

	// Attack attributes.	
	drop = dc_damage_get_drop_force();
	type = dc_damage_get_attack_type();

	if (dc_damage_get_lethality() == DC_DAMAGE_LETHALITY_NON_LETHAL)
	{
		force = dc_damage_find_non_lethal_force();
	}
	else
	{
		force = dc_damage_get_damage_force();
	}

	// Apply damage.
	damageentity(ent, other, force, drop, type);	

	// Damge on land / projectile properties.
	dol_force = dc_damage_get_damage_on_landing_force();
	projectile = dc_damage_get_projectile();
		
	changeentityproperty(ent, "damage_on_landing", dol_force);

	set_entity_property(ent, "blast_state", projectile);

	// If damage knocked target down, openBOR
	// has already applied its default velocity,
	// which we can't control with damageentity()
	// function. So we'll re-toss the entity with
	// our own here.
	fall = getentityproperty(ent, "aiflag", "falling");

	if (fall)
	{
		dc_damage_apply_toss();
	}

	// Adjust direction as needed.
	dc_damage_apply_direction_adjust();
	
}

// Caskey, Damon V.
// 2019-10-16
// 
// If opponent is KO's, toss them away a bit. This is
// mainly for grapple holds and other situations where
// we might damage opponent without letting it go into
// pain oor fall. But if the damage KO's target, it will
// just appear on the floor dead when released. Run this
// function at time of release so the death doesn't look
// stupid. :)
void dc_damage_ko_release()
{
	void ent;
	void other;

	// Entities.
	ent = dc_damage_get_entity();
	other = dc_damage_get_other();

	// Reset this instance to clear memory and avoid future conflicts.
	dc_damage_reset_instance();

	// KO/Dead?
	//if (get_entity_property(ent, "dead"))
	//{
		dc_damage_set_drop_force(DC_DAMAGE_DROP_FORCE_MAX);

		// Give it a toss.
		dc_damage_apply_damage();

		dc_damage_set_drop_force(NULL());

		return 1;
	//}

	return 0;
}

// Caskey, Damon V.
// 2019-10-17
// 
// Get and return the amount of damage entity will actually take 
// after the engine's interal calculations are complete (offense,
// defense, etc.).
int dc_damage_get_final_force()
{
	void ent;
	void other;
	int force;
	int result;
	int drop;
	int type;

	// Entities.
	ent = dc_damage_get_entity();
	other = dc_damage_get_other();

	// Damage and type.
	force = dc_damage_get_damage_force();
	type = dc_damage_get_attack_type();
	drop = dc_damage_get_drop_force();

	// Send entites and attack arguments to the
	// calculate function and get result.
	result = getcomputeddamage(ent, other, force, drop, type);

	return result;
}

// Caskey, Damon V.
// 2019-10-17
//
// Return true if final damage will kill entity.
int dc_damage_check_ko()
{
	void ent;
	int health;
	int final_force;

	ent = dc_damage_get_entity();

	health = get_entity_property(ent, "hp");
	final_force = dc_damage_get_final_force();

	// Final force will reduce health to 0?
	if (final_force >= health)
	{
		return 1;
	}

	return 0;
}

// Caskey, Damon V.
// 2019-10-17
//
// Returns nearest non-lethal amount force.
int dc_damage_find_non_lethal_force()
{
	int force_old;
	int force_result;


	force_old = dc_damage_get_damage_force();

	force_result = force_old;

	// Keep decrementing force member until
	// it's no longer enough to cause lethal damage.
	while (dc_damage_check_ko())
	{
		force_result--;

		dc_damage_set_damage_force(force_result);
	}

	// Restore member to its orginal value.
	dc_damage_set_damage_force(force_old);

	// Return non-lethal force amount.
	return force_result;
}
