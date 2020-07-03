#include "data/scripts/dc_kanga/main.c"
#include "data/scripts/dc_fidelity/main.c"

void main() {

	void ent;
	float pos_z;
	int aggression;	
	int spawn_type;
	int mp;

	ent = getlocalvar("self");
	pos_z = getentityproperty(ent, "z");

	// Make sure autokill is on.
	changeentityproperty(ent, "autokill", 1);

	// Water fatality for sound beach. This needs to be moved
	// elsewhere.
	if (pos_z < openborvariant("PLAYER_MIN_Z") - 3)  
	{
		// stereo_sound_command_here(SNDWAT1);
		changeentityproperty(ent, "setlayer", -9);
		changeentityproperty(ent, "map", 1);
		//changeentityproperty(ent, "animation", openborconstant("ANI_FOLLOW1"));
	}
	else if (pos_z > openborvariant("PLAYER_MAX_Z"))   
	{
		killentity(ent);
	}


	spawn_type = get_entity_property(ent, "spawn_type");

	if (spawn_type == openborconstant("SPAWN_TYPE_DUST_LAND") || spawn_type == openborconstant("SPAWN_TYPE_DUST_JUMP"))
	{
		changedrawmethod(ent, "enabled", 1);
		changedrawmethod(ent, "alpha", 1);
		
		mp = getentityproperty(ent, "maxmp");

		if (mp <= 0)
		{
			mp = 128;
		}
		
		changedrawmethod(ent, "scalex", mp);
		changedrawmethod(ent, "scaley", mp);

		//dc_kanga_z_position_autoscale(ent);
	}

	// By default OpenBOR spawns dust effects in front of
	// parent, but we want them behind.
	if (getentityproperty(ent, "throwdamage") != 1)
	{
		set_entity_property(ent, "position_z", pos_z - 1);
	}
	

	// Play sound.
	dc_fidelity_quick_play(DC_FIDELITY_TYPE_SOUND_SPAWN);
}