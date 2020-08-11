#include "data/scripts/dc_elmers/main.c"
#include "data/scripts/dc_fidelity/main.c"	// Used by common_didhit.

#import "data/scripts/common/common_didhit.c"

void main()
{
	void taker = getlocalvar("damagetaker");
	void ent = getlocalvar("self");
	int blocked = getlocalvar("blocked");

	int animation_id = get_entity_property(ent, "animation_id");
	
	// If this is rising tackle and they didn't block 
	// it, use the dc elmers adjustment function to 
	// draw taker in.
	if (animation_id == openborconstant("ANI_FREESPECIAL6") && !blocked)
	{
		dc_elmers_set_entity(taker);

		dc_elmers_set_offset_x(20);
		dc_elmers_set_offset_y(0);

		dc_elmers_set_position_adjust_quantity_x(5);
		dc_elmers_set_position_adjust_quantity_y(5);

		dc_elmers_adjust_distance_to_x();
		dc_elmers_adjust_distance_to_y();
	}

	// Run global didhit routines.
	dc_common_didhit();	
}