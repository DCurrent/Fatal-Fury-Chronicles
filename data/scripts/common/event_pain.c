#include "data/scripts/dc_elmers/main.c"
#include "data/scripts/dc_damage/main.c"

void main()
{
	void ent = getlocalvar("self");
	void other = getlocalvar("other");

	dc_damage_set_entity(ent);
	dc_damage_set_other(other);

	dc_damage_pain_animation_by_height();
}