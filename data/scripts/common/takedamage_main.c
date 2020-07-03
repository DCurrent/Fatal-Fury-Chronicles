#include "data/scripts/common/takedamage_config.h"
#include "data/scripts/dc_elmers/main.c"
#include "data/scripts/dc_gauntlet/main.c"
#include "data/scripts/dc_fidelity/main.c"

// Caskey, Damon V.
// 2019-10-02
// 
// Compute results of damage taking (knocked down, burned, KO'd, etc) and 
// combine into a single integer we can use bitwise logic on elsewhere. We 
// might have several sets of behavior like sound effects, fatalities, weapon 
// loss or whatever else divided accross mutiple functions, and each one
// will need to check the results of taking damage to work. 
//
// By compressing the results into a single integer value here, those individual 
// functions can use very simple bitwise logic to find the conditions they need
// and we avoid repeating the same checks over and over.
void common_take_damage_result(void ent)
{
	int animation_id;
	int animation_frame;
	int landframe;
	int drop;
	int attack_type;
	float hp;
	float hp_max;
	float hp_ratio;
	int result = 0;

	// HP result. We get max and current HP, find the percentage
	// of current vs. high, and then set flag based on
	// preset thresholds.
	hp = 0.0 + get_entity_property(ent, "hp");
	hp_max = 0.0 + getentityproperty(ent, "maxhealth");

	hp_ratio = hp / hp_max;

	if (hp_ratio <= 0)
	{
		result += DC_DAMAGE_TAKEDAMAGE_HP_KO;
	}
	else if (hp_ratio <= DC_DAMAGE_HP_LOW)
	{
		result += DC_DAMAGE_TAKEDAMAGE_HP_LOW;
	}
	else if (hp_ratio < DC_DAMAGE_HP_MAX)
	{
		result += DC_DAMAGE_TAKEDAMAGE_HP_HIGH;
	}
	else
	{
		result += DC_DAMAGE_TAKEDAMAGE_HP_MAX;
	}



	// Is this landing damage?
	animation_frame = get_entity_property(ent, "animation_frame");
	landframe = getentityproperty(ent, "landframe", animation_id);

	if (animation_frame == landframe)
	{
		result += DC_DAMAGE_TAKEDAMAGE_LANDING;
	}


	// Knockdown hit?
	drop = get_entity_property(ent, "drop");

	if (drop)
	{
		result += DC_DAMAGE_TAKEDAMAGE_KNOCKDOWN_INITIAL;
	}


	// Burn/shock hit?
	animation_id = get_entity_property(ent, "animation_id");
	attack_type = getlocalvar("attacktype");

	if (attack_type == openborconstant("ATK_BURN"))
	{
		// Was already burning?
		if (animation_id == openborconstant("ANI_BURN") || animation_id == openborconstant("ANI_BURNPAIN"))
		{
			result += DC_DAMAGE_TAKEDAMAGE_BURN_ADDITION;
		}
		else
		{
			result += DC_DAMAGE_TAKEDAMAGE_BURN_INITIAL;
		}
	}
	else if (attack_type == openborconstant("ATK_SHOCK"))
	{
		// Was already shocked?
		if (animation_id == openborconstant("ANI_SHOCK") || animation_id == openborconstant("ANI_SHOCKPAIN"))
		{
			result += DC_DAMAGE_TAKEDAMAGE_SHOCK_ADDITION;
		}
		else
		{
			result += DC_DAMAGE_TAKEDAMAGE_SHOCK_INITIAL;
		}
	}

	// Return final result.
	return result;
}

//  Spawn visual effect entity for certain attack types.
void common_spawn_damage_effect(int damage_result)
{
	if (damage_result & DC_DAMAGE_TAKEDAMAGE_BURN_INITIAL)
	{
		//dc_elmers_quick_particle_free(dc_gauntlet_quick_spawn("body_burn"));
	}
	else if (damage_result & DC_DAMAGE_TAKEDAMAGE_SHOCK_INITIAL)
	{
	}
}

// Caskey, Damon V.
// 2019-10-03 (moved out of takedamage main)
//
// Play sound effect based on results of taking damage.
void common_take_damage_sound(int damage_result)
{
	if (damage_result & DC_DAMAGE_TAKEDAMAGE_HP_KO)
	{
		dc_fidelity_quick_play(DC_FIDELITY_TYPE_VOICE_KO);

		return;
	}

	// Damage from falling? Otherwise it's a normal hit.
	if (damage_result & DC_DAMAGE_TAKEDAMAGE_LANDING)
	{
		if (damage_result & DC_DAMAGE_TAKEDAMAGE_HP_LOW)
		{
			// Play HP low voice.
			dc_fidelity_quick_play(DC_FIDELITY_TYPE_VOICE_NEAR_KO);
		}
		else
		{
			// Standard pain voice.
			dc_fidelity_quick_play(DC_FIDELITY_TYPE_VOICE_PAIN);
		}
	}
	else
	{
		// Knockdown hit?
		if (damage_result & DC_DAMAGE_TAKEDAMAGE_KNOCKDOWN_INITIAL)
		{
			// We want to know if this is a burn or shock hit, in which
			// case we also want to know if we're not already in the burn
			// or shock animaiton. In those cases, we play the burn or shock
			// voice.
			//
			// Otherwise this is a standard knockdown, so we'll react accordingly.

			if (damage_result & DC_DAMAGE_TAKEDAMAGE_BURN_INITIAL)
			{
				dc_fidelity_quick_play(DC_FIDELITY_TYPE_VOICE_PAIN_BURN);
			}
			else if (damage_result & DC_DAMAGE_TAKEDAMAGE_SHOCK_INITIAL)
			{
				dc_fidelity_quick_play(DC_FIDELITY_TYPE_VOICE_PAIN_SHOCK);
			}
			else
			{
				// This is a normal knockdown, or a burn/shock but we're already 
				// in the burn/shock animation (we don't want to do the dramatic 
				// burn/shock scream over and over). Are our hitpoints low? Decide
				// if we'll play a normal pain grunt or the low health voice
				// accordingly.

				if (damage_result & DC_DAMAGE_TAKEDAMAGE_HP_LOW)
				{
					// Play HP low voice.
					dc_fidelity_quick_play(DC_FIDELITY_TYPE_VOICE_NEAR_KO);
				}
				else
				{
					// Standard pain falling voice.
					dc_fidelity_quick_play(DC_FIDELITY_TYPE_VOICE_PAIN_FALL);
				}
			}
		}
		else
		{
			// Non knockdown hit.
			dc_fidelity_quick_play(DC_FIDELITY_TYPE_VOICE_PAIN);
		}
	}
}
