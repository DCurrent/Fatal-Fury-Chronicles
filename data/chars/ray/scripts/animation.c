/*
Animation script: 

Ray McDougal (AI)

*/

#include "data/scripts/dc_grapple/main.c" 
#include "data/scripts/dc_fidelity/main.c" 

// Very simple alternate attack. If first performing an attack
// and combo has at least one hit in it, then randomly perform
// an alternate. This is so we can give a bit of variety 
// to combo finishers for AI.
void dc_combo_alt(int animation)
{
    #define COMBOSTEP_MIN_DEFAULT 1
	#define CHANCE_DEFAULT 0.3

	void	ent;
	int		combostep;
	int		modulo;
	int		chance;
	int		combostep_min;

	ent			= getlocalvar("self");
	combostep	= getentityproperty(ent, "combostep");
	
	// Get user value. If there isn't one, fall back
	// to default.
	combostep_min = getlocalvar("dc_combo_alt_combostep_min");

	if (typeof(combostep_min) == openborconstant("VT_EMPTY"))
	{
		combostep_min = COMBOSTEP_MIN_DEFAULT;
	}

	// Get user value. If there isn't one, fall back
	// to default.
	chance = getlocalvar("dc_combo_alt_chance");

	if (typeof(chance) == openborconstant("VT_EMPTY"))
	{
		chance = CHANCE_DEFAULT;
	}

	// Take our chance percentage and make it whole.
	chance *= 100;

	// Get a modulo value from random number and our 
	// chance value. 
	modulo = rand() % chance;

	if (modulo > 0)
	{
		if (combostep > combostep_min)
		{
			changeentityproperty(ent, "animation", animation);
		}
	}

	#undef COMBOSTEP_MIN_DEFAULT
	#undef CHANCE_DEFAULT

}