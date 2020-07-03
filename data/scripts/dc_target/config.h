#ifndef DC_TARGET_CONFIG
#define DC_TARGET_CONFIG 1

// Dependencies
#include "data/scripts/dc_math/main.c"

// Name of library. Used mainly as a base for variable IDs. Must
// be unique vs all other libraries. Try to keep it short.
#define DC_TARGET_BASE_ID		"dctarg"

// Result flags.
#define DC_TARGET_NO_WALL_FOUND			-10000
#define DC_TARGET_WALL_FOUND			1

// Defaults
#define DC_TARGET_DEFAULT_INSTANCE		0
#define DC_TARGET_DEFAULT_ANIMATION		openborconstant("ANI_IDLE")
#define DC_TARGET_DEFAULT_ENT			getlocalvar("self")
#define DC_TARGET_DEFAULT_OFFSET_BASE	0
#define DC_TARGET_DEFAULT_OFFSET_X		0
#define DC_TARGET_DEFAULT_OFFSET_Y		0
#define DC_TARGET_DEFAULT_OFFSET_Z		0

// Variable keys.
#define DC_TARGET_MEMBER_INSTANCE		DC_TARGET_BASE_ID + 0
#define DC_TARGET_MEMBER_ANIMATION		DC_TARGET_BASE_ID + 1
#define DC_TARGET_MEMBER_ENT			DC_TARGET_BASE_ID + 2
#define DC_TARGET_MEMBER_OFFSET_BASE	DC_TARGET_BASE_ID + 3
#define DC_TARGET_MEMBER_OFFSET_X		DC_TARGET_BASE_ID + 4
#define DC_TARGET_MEMBER_OFFSET_Y		DC_TARGET_BASE_ID + 5
#define DC_TARGET_MEMBER_OFFSET_Z		DC_TARGET_BASE_ID + 6
#define DC_TARGET_MEMBER_THE_END		6			// Should always last, with a value one higher than previous key ID.

#endif // !DC_TARGET_CONFIG
