// Caskey, Damon V.
// 2020-09-02 
//
// Simulate rain splatter on player, enemy, and
// npc entities by mapping sprites, locating the
// first non-transparent pixel top to bottom and
// drawing a dot with 1-2 pixel random shifting.
void dc_rain_splatter()
{

	void    ent = getlocalvar("self");  // Target entity pointer.

	int     ent_count = 0;				// Entity count.
	int		model_type = 0;
	int     i = 0;						// Loop counter.

	void sprite = NULL();

	int pixel_color_index = 0;
	int size_x = 0;
	int size_y = 0;
	int center_x = 0;
	int center_y = 0;

	float pos_x = 0.0;
	float pos_y = 0.0;
	float pos_z = 0.0;

	int scroll_x = 0; // Scroll and quake. 
	int scroll_y = 0;

	int pixel_row_top = 0;
	int pixel_row = 0;
	int pixel_column = 0;

	int column_offset = getlocalvar("dc_column_offset");
	int row_offset = 1;
	int elapsed_time = openborvariant("elapsed_time");
	int trigger_time = getlocalvar("dc_column_offset_time");

	int res_h = openborvariant("hresolution");
	int res_v = openborvariant("vresolution");

	int screen_pos_x = 0;
	int screen_pos_y = 0;

	int sprite_right = 0;
	int sprite_left = 0;

	int pos_d = 0;

	// Final dot draw locations.
	int dot_pos_x = 0;
	int dot_pos_y = 0;
	int dot_color = rgbcolor(150, 150, 150);

#define DC_RAIN_SPLATTER_DOT_ALPHA 0	

	// At each time increment, switch the shift
	// to change our dot pattern.

	if (elapsed_time > trigger_time || !trigger_time)
	{
		setlocalvar("dc_column_offset_time", elapsed_time + 20);

		if (column_offset)
		{
			row_offset = 1;
			column_offset = 0;
		}
		else
		{
			row_offset = 2;
			column_offset = 1;
		}

		setlocalvar("dc_column_offset", column_offset);
	}

	// Loop over each entity index.

	ent_count = openborvariant("count_entities");

	for (i = 0; i < ent_count; i++)
	{
		// Get entity pointer.
		ent = getentity(i);

		if (!ent)
		{
			continue;
		}

		model_type = getentityproperty(ent, "type");

		if (model_type == openborconstant("TYPE_ENEMY") || model_type == openborconstant("TYPE_PLAYER") || model_type == openborconstant("TYPE_NPC"))
		{
			pos_x = get_entity_property(ent, "position_x");
			pos_y = get_entity_property(ent, "position_y");
			pos_z = get_entity_property(ent, "position_z");

			// Apply scroll and quake effect to get our scrolling
			// position in the stage. Note that native engine code
			// takes into account the noquake model property.
			// 
			// screenx - ((entity->modeldata.noquake & NO_QUAKEN) ? 0 : gfx_x_offset);
			// 
			// At this time there's no way to get the noquake property
			// in script. If it really becomes an issue, we'll need 
			// to have an algorithm that uses location instead to 
			// determine if we apply the quake offset. For now, we'll 
			// assume we always do.

			scroll_x = openborvariant("xpos") - openborvariant("gfx_x_offset");
			scroll_y = openborvariant("ypos") - openborvariant("gfx_y_offset") - openborvariant("gfx_y_offset_adj");

			// If out of visible screen, exit this loop iteration.
			// There's no use wasting CPU power to calculate
			// or draw something we can't see.

			if (pos_x < scroll_x - 20 || pos_x > scroll_y + res_h + 20)
			{
				continue;
			}

			// Use the scrolling position and entitiy's absolute
			// position to get the position on screen.

			screen_pos_x = pos_x - scroll_x;
			screen_pos_y = pos_z - pos_y - scroll_y;

			// Get the sprite pointer. Then get its basic dimensions 
			// and offsets.

			sprite = getentityproperty(ent, "sprite");

			size_x = getgfxproperty(sprite, "width");
			size_y = getgfxproperty(sprite, "height");
			center_x = getgfxproperty(sprite, "centerx");
			center_y = getgfxproperty(sprite, "centery");

			// Sprites do not flip in memory, so we don't need
			// to worry about direction in our pixel testing, but 
			// we do need to account for it when drawing the rain
			// dots onto screen. Get the left and right column
			// as it will appear based on entity direction.

			pos_d = get_entity_property(ent, "position_direction");

			if (pos_d == openborconstant("DIRECTION_RIGHT"))
			{
				sprite_left = screen_pos_x - center_x;
				sprite_right = screen_pos_x + (size_x - center_x);
			}
			else
			{
				sprite_right = screen_pos_x + center_x;
				sprite_left = screen_pos_x - (size_x - center_x);
			}

			// Locate the top row of pixels.

			pixel_row_top = (size_y - (size_y - center_y));
			
			// Now let's map the sprite.
			//
			// Starting at top row and column offset, loop accross 
			// the sprite's pixels by increment. At each column 
			// increment, loop down every row and check the color
			// table index of pixel at that row/column position
			// until we find a non-transparent pixel or reach
			// bottom of the sprite.
			//
			// Starting from an alternating 0 or 1 column and
			// incrementing by 2 gives us the animated rain 
			// effect and also halves the number of column
			// loop iterations.

			for (pixel_column = column_offset; pixel_column < size_x; pixel_column += 2)
			{
				for (pixel_row = 0; pixel_row < size_y; pixel_row++)
				{
					// Alternates drops up and down. We put it
					// here in the row loop before verifying
					// pixels to be intentionally out of sync 
					// with column loop and found pixels. This
					// gives us a little bit of random effect.
					
					if (row_offset == 1)
					{
						row_offset = 2)
					}
					else
					{
						row_offset = 1;
					}

					// Check the pixel. If it is not transparent we have
					// found the top outline of visible pixels in the
					// sprite. Now we can draw our rain dot.

					pixel_color_index = getgfxproperty(sprite, "pixel", pixel_column, pixel_row);

					if (pixel_color_index)
					{
						// Now we calculate the on screen X position to
						// draw dot. If entity is facing right, we add
						// on screen location of sprite's left row to
						// column cursor position and we're done.
						//
						// If entity is facing left, we need to work in 
						// reverse. As noted above, this is because sprites
						// do not change direction in memory, only as the
						// are drawn to the screen.

						if (pos_d == openborconstant("DIRECTION_RIGHT"))
						{
							dot_pos_x = sprite_left + pixel_column;
						}
						else
						{
							dot_pos_x = (sprite_right - pixel_column) - 1;
						}

						// Now get Y position. Same process as X, but using
						// the row cursor and we don't have to worry about
						// direction. Include row offset we set above to
						// give the dot a random up/down movement.
						
						dot_pos_y = screen_pos_y - (center_y - pixel_row) - row_offset;

						drawdot(dot_pos_x, dot_pos_y, pos_z, dot_color, DC_RAIN_SPLATTER_DOT_ALPHA);

						break;
					}
				}
			}
		}
	}

	#undef DC_RAIN_SPLATTER_DOT_ALPHA
}


#ifndef DC_INSET

#define DC_INSET    1

#define KEY_SCREEN          "key_screen"
#define KEY_BACKGROUND      "key_background"
#define SCREEN_BACKGROUND   "data/misc/blank.png"

#endif // DC_INSET

void get_screen()
{
	void screen;
	int  x;
	int  y;
	int  background_sprite;

	x = openborvariant("hresolution");
	y = openborvariant("vresolution");

	// Get current screen.
	screen = getlocalvar(KEY_SCREEN);

	// If no screen is set up,
	// initialize it here.
	if (!screen)
	{
		// Load the background sprite for our screen.
		background_sprite = loadsprite(SCREEN_BACKGROUND);

		// Allocate screen and use it to populate
		// the screen variable, then populate
		// background variable.
		screen = allocscreen(x, 60);
		setlocalvar(KEY_SCREEN, screen);
		setlocalvar(KEY_BACKGROUND, background_sprite);
	}

	return screen;
}

// Caskey, Damon V.
// 2020-09-07
//
// Disable or enable a group of layers.
// -- first_index: Index of first layer in set.
// -- last_index: Index of last layer in set.
// -- Property: Property name.
// -- value: Value to apply.
void dc_layer_group_set_property(int index_first, int index_last, char property, int value)
{
	int index = 0;

	for (index = index_first; index <= index_last; index++)
	{		
		changelayerproperty("fglayer", index, property, value);		
	}
}

void dc_draw_cloud_layer()
{	
#define DC_HA_CLOUD_SCREEN_POSITION_X 0
#define DC_HA_CLOUD_SCREEN_POSITION_Y 0
#define DC_HA_CLOUD_SCREEN_POSITION_Z -84

#define DC_HA_CLOUD_SPRITE_QUE_Z_MAX -85
#define DC_HA_CLOUD_SPRITE_QUE_Z_MIN openborconstant("MIN_INT")
#define DC_HA_CLOUD_SPRITE_QUE_NEWONLY 0
#define DC_HA_CLOUD_SPRITE_OFFSET_X 0
#define DC_HA_CLOUD_SPRITE_OFFSET_Y 0


	void scr = get_screen();

	// Clear the screen, then add our target sprites.

	clearscreen(scr);
	drawspriteq(scr, DC_HA_CLOUD_SPRITE_QUE_NEWONLY, DC_HA_CLOUD_SPRITE_QUE_Z_MIN, DC_HA_CLOUD_SPRITE_QUE_Z_MAX, DC_HA_CLOUD_SPRITE_OFFSET_X, DC_HA_CLOUD_SPRITE_OFFSET_Y);

	// Set global drawMethods.

	changedrawmethod(NULL(), "reset", 1);
	changedrawmethod(NULL(), "enabled", 1);
	changedrawmethod(NULL(), "watermode", 3);
	changedrawmethod(NULL(), "beginsize", 6);
	changedrawmethod(NULL(), "endsize", 0.01);
	changedrawmethod(NULL(), "perspective", 0);
	changedrawmethod(NULL(), "alpha", 0);

	// Draw the screen, then disable the drawmethod.

	drawscreen(scr, DC_HA_CLOUD_SCREEN_POSITION_X, DC_HA_CLOUD_SCREEN_POSITION_Y, DC_HA_CLOUD_SCREEN_POSITION_Z);
	
	changedrawmethod(NULL(), "enabled", 0);
}

// Ccaskey, Damon V.
// 2020-09-04
//
// Given a set of layers configured as frames, will
// simulate simple looping animation by disabling
// all but one layer from first_index to last_index 
// in series.
//
// -- first_index: Index of first layer in set. Treated as 
// the first frame and also added to localvars so there
// can be mutiple instances of function in use without
// interfere with each other.

// -- last_index: Index of last layer in set.
// -- delay: Animation delay. Identical to animation
// delay used by models.
void dc_layer_animation(int first_index, int last_index, int delay)
{
	int time_current = openborvariant("elapsed_time");
	int time_expire = getlocalvar("dc_layer_animation_delay_expire" + first_index);
	int layer_current = 0;
	int layer_index = 0;

	// Animation delay timing.
	//
	// If there is no time expired set yet or time
	// has expired, set the next expire time and
	// continue function. Otherwise we exit and wait.
	if (!time_expire || time_current >= time_expire)
	{
		time_expire = time_current + delay;
		setlocalvar("dc_layer_animation_delay_expire" + first_index, time_expire);
	}
	else
	{
		return;
	}

	// Get current layer. If this is first run of 
	// function, current layer variable will be 
	// empty, so initialize it with the first 
	// layer index.

	layer_current = getlocalvar("dc_layer_animation_last_layer" + first_index);

	if (!layer_current)
	{
		layer_current = first_index;
	}

	// Loop over layers. Enable the current index, and
	// disable all the others.
	
	for (layer_index = first_index; layer_index <= last_index; layer_index++)
	{
		if (layer_index == layer_current)
		{
			changelayerproperty("fglayer", layer_index, "enabled", 1);
		}
		else
		{
			changelayerproperty("fglayer", layer_index, "enabled", 0);
		}
	}
		
	// Increment to next layer index, or back to first 
	// index if we are at the last layer in series.
	// The record into a localvar for next cycle.

	if (layer_current >= last_index)
	{
		layer_current = first_index;
	}
	else
	{
		layer_current++;
	}

	setlocalvar("dc_layer_animation_last_layer" + first_index, layer_current);
}

void clear()
{
	void scr = getindexedvar(0);
	if (scr) {
		free(scr);
		free(getscriptvar(1));
	}
}

#include "data/scripts/dc_d20/main.c"

void dc_lightining_flash()
{
	#define DC_LF_FLASH_WAIT_MIN 0			// Minimum time between lightning occurence.
	#define DC_LF_FLASH_WAIT_MAX 4000			// Maximum time between lightning occurence.
	#define DC_LF_POSITION_X 0
	#define DC_LF_POSITION_Y 0
	#define DC_LF_POSITION_Z 1000
	#define DC_LF_FLASH_BLEND 1

	#define DC_LF_FLASH_COLOR_WHITE		rgbcolor(255, 255, 255)
	#define DC_LF_FLASH_COLOR_YELLOW	rgbcolor(255, 255, 153)
	#define DC_LF_FLASH_COLOR_BLUE		rgbcolor(153, 204, 204)

	#define DC_LF_FRAME_0_DELAY 40
	#define DC_LF_FRAME_1_DELAY DC_LF_FRAME_0_DELAY + 64
	#define DC_LF_FRAME_2_DELAY DC_LF_FRAME_1_DELAY + 24

	int elapsed_time = openborvariant("elapsed_time");
	int time_point = getlocalvar("dc_lf_time");
	int time_differential = 0;
	int box_size_x = 0;
	int box_size_y = 0;
	int box_color = 0;
	
	// If time temp is empty, initialize it to current 
	// elapsed time. Then get difference between time 
	// point vs. current elapsed time.

	if (typeof(time_point) != openborconstant("VT_INTEGER"))
	{
		time_point = elapsed_time;
		setlocalvar("dc_lf_time", time_point);
	}

	time_differential = elapsed_time - time_point;

	// If the time difference is negative, we are in the
	// interval between animations. Exit and do nothing.

	if (time_differential < 0)
	{
		return;
	}

	// Now take action based on time. We're actually just
	// choosing colors for the drawbox function. By cycling
	// through certain color sets, we get an initial flash,
	// then a strobing effect, and finally a lingering light
	// that closely approximates a lightning strike.

	if (time_differential < DC_LF_FRAME_0_DELAY)
	{
		// Play thunder sound if we aren't already.

		int playid = getlocalvar("dc_lf_playid");
		int sample_id = loadsample("data/sounds/custom/thunder_0.wav");

		if (typeof(playid) == openborconstant("VT_INTEGER"))
		{
			if (querychannel(playid) == -1)
			{
				playsample(sample_id, 0, 120, 120, 100, 0);
				playid = openborvariant("sample_play_id");

				setlocalvar("dc_lf_playid", playid);
			}
		}
		else
		{
			playsample(sample_id, 0, 120, 120, 100, 0);
			playid = openborvariant("sample_play_id");

			setlocalvar("dc_lf_playid", playid);
		}

		box_color = DC_LF_FLASH_COLOR_WHITE;
	}
	else if (time_differential >= DC_LF_FRAME_0_DELAY && time_differential < DC_LF_FRAME_1_DELAY)
	{
		// Randomly switch between blue and yellow.

		dc_d20_set_range_min(0);
		dc_d20_set_range_max(1);

		if (dc_d20_random_int())
		{
			box_color = DC_LF_FLASH_COLOR_BLUE;
		}
		else
		{
			box_color = DC_LF_FLASH_COLOR_YELLOW;
		}
	}
	else if (time_differential >= DC_LF_FRAME_1_DELAY && time_differential < DC_LF_FRAME_2_DELAY)
	{
		box_color = DC_LF_FLASH_COLOR_BLUE;
	}
	else
	{
		// Animation is finished. 
		// 
		// If elapsed time is divisible by 100, then
		// reset time point to empty. This gives us a 
		// slight chance of immediately looping back 
		// and instantly doing another lightning strike. 
		// We also delete the play ID that prevents thunder
		// overlap so a second thunder sound can play.
		// Just like real storms occasionally producing 
		// a crescendo of lightning.
		// 
		// Otherwise set the time point to be a randomized
		// period ahead of current elapsed time. This will 
		// cause time differential to be negative until current
		// elapsed time catches up, giving us an interval
		// between lightning strikes.

		//if (elapsed_time % 100 == 0)
		//{
		//	time_point = NULL();
		//}
		//else
		//{
			dc_d20_set_range_min(DC_LF_FLASH_WAIT_MIN);
			dc_d20_set_range_max(DC_LF_FLASH_WAIT_MAX);

			time_point = elapsed_time + dc_d20_random_int();
		//}		

		setlocalvar("dc_lf_time", time_point);
		setlocalvar("dc_lf_playid", -1);

		box_color = DC_LF_FLASH_COLOR_BLUE;
	}

	// Draw the box to create lightning effect.

	box_size_x = openborvariant("hresolution");
	box_size_y = openborvariant("vresolution");

	drawbox(DC_LF_POSITION_X, DC_LF_POSITION_Y, box_size_x, box_size_y, DC_LF_POSITION_Z, box_color, DC_LF_FLASH_BLEND);

	return;

	#undef DC_LF_FLASH_WAIT_MIN
	#undef DC_LF_FLASH_WAIT_MAX
	#undef DC_LF_POSITION_X
	#undef DC_LF_POSITION_Y
	#undef DC_LF_POSITION_Z
	#undef DC_LF_FLASH_BLEND

	#undef THUNDER_DIFFERENTIAL

	#undef DC_LF_FLASH_COLOR_WHITE
	#undef DC_LF_FLASH_COLOR_YELLOW
	#undef DC_LF_FLASH_COLOR_BLUE

	#undef DC_LF_FRAME_0_DELAY
	#undef DC_LF_FRAME_1_DELAY
	#undef DC_LF_FRAME_2_DELAY
}

// Control stage effects for Howard Arena.
void dc_howard_arena_control()
{
#define WATERFALL_INDEX_FIRST 8
#define WATERFALL_INDEX_LAST 11
#define WATERFALL_DELAY 20

#define LAMP_FLAME_DELAY 20

#define LAMP_FLAME_BACKGROUND_INDEX_FIRST 14
#define LAMP_FLAME_BACKGROUND_INDEX_LAST 17

#define LAMP_FLAME_BACKGROUND_FLIPPED_INDEX_FIRST 18
#define LAMP_FLAME_BACKGROUND_FLIPPED_INDEX_LAST 21

#define LAMP_FLAME_FOREGROUND_INDEX_FIRST 22
#define LAMP_FLAME_FOREGROUND_INDEX_LAST 25

#define RAIN_INDEX_FIRST 26
#define RAIN_INDEX_LAST 29
#define RAIN_DELAY 12

#define LAMP_RAIN_INDEX_FIRST 30
#define LAMP_RAIN_INDEX_LAST 31
#define LAMP_RAIN_DELAY 20



#define STORM_START_TIME 400 //11662 // 5831	

	int elapsed_time = openborvariant("elapsed_time");

	// Perspective cloud screen draw.
	dc_draw_cloud_layer();

	// Background lamp frames.
	dc_layer_animation(LAMP_FLAME_BACKGROUND_INDEX_FIRST, LAMP_FLAME_BACKGROUND_INDEX_LAST, LAMP_FLAME_DELAY);
	dc_layer_animation(LAMP_FLAME_BACKGROUND_FLIPPED_INDEX_FIRST, LAMP_FLAME_BACKGROUND_FLIPPED_INDEX_LAST, LAMP_FLAME_DELAY);

	// Waterfall and foreground lamp flames.
	dc_layer_animation(WATERFALL_INDEX_FIRST, WATERFALL_INDEX_LAST, WATERFALL_DELAY);
	dc_layer_animation(LAMP_FLAME_FOREGROUND_INDEX_FIRST, LAMP_FLAME_FOREGROUND_INDEX_LAST, LAMP_FLAME_DELAY);

	// If it's time for the storm, apply the animations
	// and effects we need. Otherwise make sure the 
	// storm effect layers are disabled.

	if (elapsed_time >= STORM_START_TIME)
	{
		// Rain effect animation and rain splatter on foreground lamps.
		dc_layer_animation(LAMP_RAIN_INDEX_FIRST, LAMP_RAIN_INDEX_LAST, LAMP_RAIN_DELAY);	// Rain
		dc_layer_animation(RAIN_INDEX_FIRST, RAIN_INDEX_LAST, RAIN_DELAY);	// Rain

		// Randomized lightning flash effect.		
		dc_lightining_flash();

		// Rain splatter on active entities (players, enemies, etc.)
		dc_rain_splatter();
	}
	else
	{
		dc_layer_group_set_property(LAMP_RAIN_INDEX_FIRST, LAMP_RAIN_INDEX_LAST, "enabled", 0);
		dc_layer_group_set_property(RAIN_INDEX_FIRST, RAIN_INDEX_LAST, "enabled", 0);
	}

#undef WATERFALL_INDEX_FIRST
#undef WATERFALL_INDEX_LAST
#undef WATERFALL_DELAY

#undef LAMP_FLAME_DELAY

#undef LAMP_FLAME_BACKGROUND_INDEX_FIRST
#undef LAMP_FLAME_BACKGROUND_INDEX_LAST

#undef LAMP_FLAME_BACKGROUND_FLIPPED_INDEX_FIRST
#undef LAMP_FLAME_BACKGROUND_FLIPPED_INDEX_LAST

#undef LAMP_FLAME_FOREGROUND_INDEX_FIRST
#undef LAMP_FLAME_FOREGROUND_INDEX_LAST

#undef RAIN_INDEX_FIRST
#undef RAIN_INDEX_LAST
#undef RAIN_DELAY

#undef STORM_START_TIME
}

void oncreate()
{
	// Disable all rain layers.
	//dc_layer_group_set_property(RAIN_INDEX_FIRST, RAIN_INDEX_LAST, "enabled", 0);
}

void ondestroy()
{
}

void main() 
{
	// Perspective cloud screen draw.
	dc_draw_cloud_layer();
	dc_howard_arena_control();
}