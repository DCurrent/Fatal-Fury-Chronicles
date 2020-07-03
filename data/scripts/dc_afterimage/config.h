
#ifndef TRAIL_DEF

#define TRAIL_DEF 1

#define DC_AFTERIMAGE_BLEND 6

#define DC_AFTERIMAGE_GLOBAL_MAX    20  // Maximum number of afterimages on screen.
#define DC_AFTERIMAGE_ENTITY_MAX    5   // Maximum number of afterimages per entity.
#define DC_AFTERIMAGE_DELAY         20  // Delay between creation of each afterimage.
#define DC_AFTERIMAGE_LIFESPAN      25  // Time each afterimage is on screen.

#define DC_AFTERIMAGE_CORRECTION_Y	-4	// Applied to Y positon of shadow trail as a fix for math descrpencies.


#define DC_AFTERIMAGE_KEY_BASE      "dc_afi"
#define DC_AFTERIMAGE_KEY_EXPIRE    0
#define DC_AFTERIMAGE_KEY_FLIP_X    1
#define DC_AFTERIMAGE_KEY_POS_X     2
#define DC_AFTERIMAGE_KEY_POS_Y     3
#define DC_AFTERIMAGE_KEY_POS_Z     4
#define DC_AFTERIMAGE_KEY_SCALE_X   5
#define DC_AFTERIMAGE_KEY_SCALE_Y   6
#define DC_AFTERIMAGE_KEY_SPRITE    7
#define DC_AFTERIMAGE_KEY_TABLE     8
#define DC_AFTERIMAGE_KEY_THE_END   9  // Always last key.

#endif // TRAIL_DEF
