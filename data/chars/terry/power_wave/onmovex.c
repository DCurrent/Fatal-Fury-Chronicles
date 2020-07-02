#include "data/scripts/dc_disney/main.c"
#include "data/scripts/dc_math/main.c"

void oncreate()
{
}

void main()
{
	dc_kill_on_base_change();
}

// Caskey, Damon V.
// 2019-03-19
//
// Die if base is modified.
void dc_kill_on_base_change()
{
	void ent;
	int pos_x;
	int pos_y;
	int pos_z;
	int pos_b;
	int last_b;
	int last_y;

	if (getlocalvar("skip"))
	{
		return;
	}

	ent = getlocalvar("self");

	// Get our position.
	pos_x = get_entity_property(ent, "position_x");
	pos_z = get_entity_property(ent, "position_z");
	pos_y = get_entity_property(ent, "position_y");
	pos_b = get_entity_property(ent, "position_base");

	// Get position values from previous cycle.
	last_b = getlocalvar("last_b");
	last_y = getlocalvar("last_y");

	// Populate "last" values if they are blank. This must be 
	// first run of the function.
	if (typeof(last_b) == openborconstant("VT_EMPTY"))
	{
		last_b = pos_b;
	}

	if (typeof(last_y) == openborconstant("VT_EMPTY"))
	{
		last_y = pos_y;
	}

	if (dc_math_difference_float(checkbase(pos_x, pos_z, pos_y), last_b) > 5)
	{
		// Let's play the hit something animation. Unfortunatly now that we
		// have detected the base change, well, the base has changed. So if
		// we only switch animations, we're is still sitting on top of a wall, 
		// in a pit, or whever else and will look pretty stupid. We need to 
		// move overselves back to the intended base and height.

		// Have to turn on no adjust base, or we won't be able to reposition
		// overselves back where we belong.

		// Using a legacy property here because when I wrote this, I hadn't yet coded 
		// the new style for model property access into the engine. :P
		changeentityproperty(ent, "no_adjust_base", 1);

		changeentityproperty(ent, "subject_to_gravity", 0);
		set_entity_property(ent, "position_base", last_b);

		
		set_entity_property(ent, "position_y", last_y);
		dc_disney_play_animation(openborconstant("ANI_FOLLOW1"));

		setlocalvar("skip", 1);

		return;
	}

	// Update "last" vars for next cycle.
	setlocalvar("last_b", pos_b);
	setlocalvar("last_y", pos_y);
}