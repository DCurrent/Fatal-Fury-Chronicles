#include "data/scripts/dc_fidelity/main.c"

void dc_common_didhit()
{
	int blocked;
	void ent;
	void target;

	int projectile;
	int drop_previous;
	int drop;
	int animation_id;
	int knockdown_count;
	int type;

	blocked = getlocalvar("blocked");

	if (blocked)
	{
	}
	else
	{
		ent = getlocalvar("self");
		projectile = getentityproperty(ent, "projectile");

		animation_id = get_entity_property(ent, "animation_id");

		target = getlocalvar("damagetaker");
		drop_previous = get_entity_property(target, "drop");

		// Let's check for a few conditions before we trash talk.
		// 
		// 1. Target isn't falling already. We don't want to overdo by talking on juggle hits.
		// 2. Projectile flag isn't active (i.e. the hit isn't because we weren't thrown into someone).
		// 3. We're not in a grappled animation.
		if (!projectile && animation_id != openborconstant("ANI_FOLLOW10"))
		{
			// Will we knock the target down? Todo: Account for target's knockdown defense.

			drop = getlocalvar("drop");
			knockdown_count = get_entity_property(target, "knockdown_count");

			if (drop > knockdown_count)
			{
				// Players trash talk 

				type = getentityproperty(ent, "type");

				if (type == openborconstant("TYPE_PLAYER"))
				{
					dc_fidelity_set_sound_chance(0.5);
					dc_fidelity_timed_play(DC_FIDELITY_TYPE_VOICE_BATTLE_TAUNT, 175);
					dc_fidelity_set_sound_chance(NULL());

				}
				else
				{
					dc_fidelity_timed_play(DC_FIDELITY_TYPE_VOICE_BATTLE_TAUNT, 175);
				}
			}
		}
	}
}