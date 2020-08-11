#include "data/scripts/dc_elmers/main.c"

void main()
{
	void taker = getlocalvar("damagetaker");

	

	//dc_elmers_quick_spot(taker);

	dc_elmers_set_entity(taker);

	dc_elmers_set_offset_x(20);
	dc_elmers_set_offset_y(0);

	dc_elmers_set_position_adjust_quantity_x(5);
	dc_elmers_set_position_adjust_quantity_y(5);

	dc_elmers_adjust_distance_to_x();
	dc_elmers_adjust_distance_to_y();
}