#include "data/scripts/dc_initialize/main.c"

void oncreate()
{
	dc_initialize_alias_quick_add("Ray");
	dc_initialize_alias_quick_add("Aussie");
	dc_initialize_alias_quick_add("Baxter");
	dc_initialize_alias_quick_add("Bloundie");
	dc_initialize_alias_quick_add("Brush");
	dc_initialize_alias_quick_add("Bryl");
	dc_initialize_alias_quick_add("Dapper");
	dc_initialize_alias_quick_add("Dep");
	dc_initialize_alias_quick_add("Fop");
	dc_initialize_alias_quick_add("Gel");
	dc_initialize_alias_quick_add("Mesh");
	dc_initialize_alias_quick_add("Moouse");
	dc_initialize_alias_quick_add("Mug");
	dc_initialize_alias_quick_add("Silky");
	dc_initialize_alias_quick_add("Slick");
	dc_initialize_alias_quick_add("Spike");
	dc_initialize_alias_quick_add("Woody");
}

void main()
{
	dc_initialize_level_spawn();
}