#include "data/scripts/dc_hansburg/config.h"


// Tosstime to apple when placed into a boundary (wall/obstacle/screen edge) jump start.

// Get
int dc_hansburg_get_boundary_jump_start_hover()
{
	char id;
	void result;

	// Get id.
	id = dc_hansburg_get_instance() + DC_HANSBURG_MEMBER_BOUNDARY_JUMP_START_HOVER;

	result = getlocalvar(id);

	if (typeof(result) != openborconstant("VT_PTR"))
	{
		result = DC_HANSBURG_DEFAULT_BOUNDARY_JUMP_START_HOVER;
	}

	return result;
}

// Set
void dc_hansburg_boundary_jump_start_hover(void value)
{
	char id;

	// Get id.
	id = dc_hansburg_get_instance() + DC_HANSBURG_MEMBER_BOUNDARY_JUMP_START_HOVER;

	if (value == DC_HANSBURG_DEFAULT_BOUNDARY_JUMP_START_HOVER)
	{
		value == NULL();
	}

	setlocalvar(id, value);
}