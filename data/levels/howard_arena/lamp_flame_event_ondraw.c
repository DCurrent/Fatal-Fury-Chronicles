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

	if (get_entity_property(ent, "animation_id") != openborconstant("ANI_IDLE"))
	{
		return;
	}

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

	int offset_x = 0; // Scroll and quake. 
	int offset_y = 0;

	int pixel_row_top = 0;
	int pixel_row = 0;
	int pixel_column = 0;

	int column_offset = getlocalvar("dc_column_offset");
	int row_offset = 1;
	int elapsed_time = openborvariant("elapsed_time");
	int trigger_time = getlocalvar("dc_column_offset_time");

	int res_h = openborvariant("hresolution");
	int res_v = openborvariant("vresolution");

	int screen_draw_x = 0;
	int screen_draw_y = 0;

	int sprite_right = 0;
	int sprite_left = 0;

	int pos_d = 0;

	// Final dot draw locations.
	int dot_pos_x = 0;
	int dot_pos_y = 0;
	int dot_pos_z = 0;
	int dot_color = rgbcolor(150, 150, 150);
	int dot_alpha = 0;

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

			// Apply scroll and quake effect to get our basic
			// offset. Note that native engine code takes into 
			// account the noquake model property.
			// 
			// screenx - ((entity->modeldata.noquake & NO_QUAKEN) ? 0 : gfx_x_offset);
			// 
			// At this time there's no way to get the noquake property
			// in script. If it really becomes an issue, we'll need 
			// to have an algorithm that uses location instead to 
			// determine if we apply the quake offset. For now, we'll 
			// assume we always do.

			offset_x = openborvariant("xpos") - openborvariant("gfx_x_offset");
			offset_y = openborvariant("ypos") - openborvariant("gfx_y_offset") - openborvariant("gfx_y_offset_adj");

			// If out of sight, don't waste the CPU power to calculate
			// or draw anything.
			if (pos_x < offset_x - 20 || pos_x > offset_x + res_h + 20)
			{
				continue;
			}

			sprite = getentityproperty(ent, "sprite");

			size_x = getgfxproperty(sprite, "width");
			size_y = getgfxproperty(sprite, "height");
			center_x = getgfxproperty(sprite, "centerx");
			center_y = getgfxproperty(sprite, "centery");

			pixel_row_top = (size_y - (size_y - center_y));
			pixel_row = 0; //pixel_row_top;
			pixel_column = 0;

			screen_draw_x = pos_x - offset_x;
			screen_draw_y = pos_z - pos_y - offset_y;

			pos_d = get_entity_property(ent, "position_direction");

			if (pos_d == openborconstant("DIRECTION_RIGHT"))
			{
				sprite_left = screen_draw_x - center_x;
				sprite_right = screen_draw_x + (size_x - center_x);
			}
			else
			{
				sprite_right = screen_draw_x + center_x;
				sprite_left = screen_draw_x - (size_x - center_x);
			}

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

					pixel_color_index = getgfxproperty(sprite, "pixel", pixel_column, pixel_row);

					if (pixel_color_index)
					{
						// Sprite properties are not directional, but on 
						// screen objects are, so we need to reverse the
						// X coordinates before we use them to draw.
						if (pos_d == openborconstant("DIRECTION_RIGHT"))
						{
							dot_pos_x = sprite_left + pixel_column;
						}
						else
						{
							dot_pos_x = (sprite_right - pixel_column) - 1;
						}

						dot_pos_y = screen_draw_y - (center_y - pixel_row) - row_offset;
						dot_pos_z = pos_z;

						drawdot(dot_pos_x, dot_pos_y, dot_pos_z, dot_color, dot_alpha);

						break;
					}
				}
			}
		}
	}
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

#define WATERFALL_INDEX_FIRST 8
#define WATERFALL_INDEX_LAST 11
#define WATERFALL_DELAY 20

#define LAMPS_INDEX_FIRST 14
#define LAMPS_INDEX_LAST 17
#define LAMPS_DELAY 20

#define RAIN_INDEX_FIRST 18
#define RAIN_INDEX_LAST 21
#define RAIN_DELAY 8

#define STORM_START_TIME 11662 // 5831

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

void oncreate()
{
	// Disable all rain layers.
	//dc_layer_group_set_property(RAIN_INDEX_FIRST, RAIN_INDEX_LAST, "enabled", 0);
}

void ondestroy()
{
}

void old_main()
{	

	void scr = get_screen();

	int max_z = openborvariant("PLAYER_MAX_Z");
	int min_z = openborconstant("MIN_INT");

	
	//if(openborvariant("game_paused"))return;
	
	clearscreen(scr);
	drawspriteq(scr, 0, min_z, -85, 0, 0);

	//Set drawMethod
	changedrawmethod(NULL(), "reset", 1);
	changedrawmethod(NULL(), "enabled", 1);
	//changedrawmethod(NULL(),"scalex",43);
	//changedrawmethod(NULL(),"scaley",52);
	changedrawmethod(NULL(), "watermode", 3);
	changedrawmethod(NULL(), "beginsize", 6);
	changedrawmethod(NULL(), "endsize", 0.01);
	//changedrawmethod(NULL(), "scalex", 54);
	//changedrawmethod(NULL(), "scaley", 54);
	changedrawmethod(NULL(), "perspective", 0);
	changedrawmethod(NULL(), "alpha", 0);

	//Draw the resized customized screen to main screen.
	float x = openborvariant("xpos") + 35;
	float y = 83;

	x = 0; //getentityproperty(self, "x") - x;
	y = 0; // getentityproperty(self, "y") + getentityproperty(self, "base") - 22;

	drawscreen(scr, x, -y, -84);
	
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
#define FLASH_WAIT_MIN 0			// Minimum time between lightning occurence.
#define FLASH_WAIT_MAX 4000			// Maximum time between lightning occurence.
#define POSITION_X 0
#define POSITION_Y 0
#define POSITION_Z 1000
#define FLASH_BLEND 1

#define THUNDER_DIFFERENTIAL 10		// Play thunder sound when differential is this value.

#define FLASH_COLOR_WHITE	rgbcolor(255, 255, 255)
#define FLASH_COLOR_YELLOW	rgbcolor(255, 255, 153)
#define FLASH_COLOR_BLUE	rgbcolor(153, 204, 204)

#define FRAME_0_DELAY 40
#define FRAME_1_DELAY FRAME_0_DELAY + 64
#define FRAME_2_DELAY FRAME_1_DELAY + 24

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

	if (time_differential < FRAME_0_DELAY)
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

		box_color = FLASH_COLOR_WHITE;
	}
	else if (time_differential >= FRAME_0_DELAY && time_differential < FRAME_1_DELAY)
	{
		// Randomly switch between blue and yellow.

		dc_d20_set_range_min(0);
		dc_d20_set_range_max(1);

		if (dc_d20_random_int())
		{
			box_color = FLASH_COLOR_BLUE;
		}
		else
		{
			box_color = FLASH_COLOR_YELLOW;
		}
	}
	else if (time_differential >= FRAME_1_DELAY && time_differential < FRAME_2_DELAY)
	{
		box_color = FLASH_COLOR_BLUE;
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
		// a crecendo of lightning.
		// 
		// Otherwise set the time point to be a randomized
		// period ahead of current elapsed time. This will 
		// cause time differential to be negative until current
		// elapsed time catches up, giving us an interval
		// between lightning strikes.

		if (elapsed_time % 100 == 0)
		{
			time_point = NULL();
		}
		else
		{
			dc_d20_set_range_min(FLASH_WAIT_MIN);
			dc_d20_set_range_max(FLASH_WAIT_MAX);

			time_point = elapsed_time + dc_d20_random_int();
		}		

		setlocalvar("dc_lf_time", time_point);
		setlocalvar("dc_lf_playid", NULL());

		box_color = FLASH_COLOR_BLUE;
	}

	// Draw the box to create lightning effect.

	box_size_x = openborvariant("hresolution");
	box_size_y = openborvariant("vresolution");

	drawbox(POSITION_X, POSITION_Y, box_size_x, box_size_y, POSITION_Z, box_color, FLASH_BLEND);

	return;
}

void main() 
{
	int elapsed_time = openborvariant("elapsed_time");

	old_main();

	dc_layer_animation(WATERFALL_INDEX_FIRST, WATERFALL_INDEX_LAST, WATERFALL_DELAY);	// Watefall
	dc_layer_animation(LAMPS_INDEX_FIRST, LAMPS_INDEX_LAST, LAMPS_DELAY);	// Lamps (foreground)

	if (elapsed_time >= STORM_START_TIME)
	{
		dc_layer_animation(RAIN_INDEX_FIRST, RAIN_INDEX_LAST, RAIN_DELAY);	// Rain
		dc_lightining_flash();
		dc_rain_splatter();
	}	
	else
	{
		dc_layer_group_set_property(RAIN_INDEX_FIRST, RAIN_INDEX_LAST, "enabled", 0);
	}		
}

#undef WATERFALL_INDEX_FIRST
#undef WATERFALL_INDEX_LAST
#undef WATERFALL_DELAY

#undef LAMPS_INDEX_FIRST
#undef LAMPS_INDEX_LAST
#undef LAMPS_DELAY

#undef RAIN_INDEX_FIRST
#undef RAIN_INDEX_LAST
#undef RAIN_DELAY

#undef STORM_START_TIME
