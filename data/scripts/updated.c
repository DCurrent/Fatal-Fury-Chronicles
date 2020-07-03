// Import functions.
#include "data/scripts/dc_afterimage/main.c"
#include "data/scripts/dc_kanga/main.c"
#include "data/scripts/dc_fidelity/main.c"

#define DC_UPDATED_KEY_SCREEN          "key_screen"
#define OG_SCREEN_SIZE_MAX_X			openborvariant("hresolution")
#define OG_SCREEN_SIZE_MAX_Y			openborvariant("vresolution")

#define WAIT_NAME_FONT		3
#define SELECT_NAME_FONT	4
#define FONT_Y				18	// Vertical size of font (unavailable as of 2019-02-22). Includes margin.
#define SELECT_Y_BASE		105
#define SPACE_CHAR			"_"
#define	MAX_DRAW_SIZE		256 * 10
#define MAX_DRAW_SIZE_TIME	100

#define OG_SCREEN_BASE_POS_X openborvariant("hresolution") / 2
#define OG_SCREEN_BASE_POS_Y openborvariant("vresolution") / 2

#define OG_SCREEN_SCALE_MAX_X 256
#define OG_SCREEN_SCALE_MAX_Y 256

void oncreate()
{
	log("\n");
	log("updated.c");
	log("\t");
	log("- oncreate().");
	log("\n");	
}

void ondestroy()
{
	log("\n");
	log("update.c");
	log("\t");
	log("- ondestroy().");
	log("\n");
}

void main() {

	void    ent = NULL();   // Target entity pointer.
	int     ent_count = 0;        // Entity count.
	int     i = 0;        // Loop counter.

	
	dc_draw_select_names();

	//screen_test();

	// Get entity count.
	ent_count = openborvariant("count_entities");

	// Loop over each entity index.
	for (i = 0; i < ent_count; i++)
	{
		// Get entity pointer.
		ent = getentity(i);

		// Execute tint effect on entity.
		dc_kanga_auto_tint(ent);
		
	}	

	// Time delay sounds.
	dc_fidelity_play_timed();

	// Draw after images
	trai0001();
}


void dc_kanga_position(void ent, int box, int box_y, int i)
{
	int animation = getentityproperty(ent, "animationid");
	int frame = getentityproperty(ent, "animpos");

	float x = get_entity_property(ent, "position_x");
	float y = get_entity_property(ent, "position_y");
	float z = get_entity_property(ent, "position_z");

	settextobj(box, 50, box_y, 0, -1, "ent: " + i + ", Ani: " + animation + "(" + frame + "), X: " + x + ", Y: " + y + ", Z: " + z, openborvariant("elapsed_time") + 200);
}

void dc_get_screen(int index, int size_x, int size_y)
{
	void screen;
	char screen_key;	
	char size_x_key;
	char size_y_key;
	
	screen_key = DC_UPDATED_KEY_SCREEN + index;	
	
	// Get current screen.
	screen = getlocalvar(screen_key);	

	// If no screen is set up,
	// initialize it here.
	if (!screen)
	{
		// Allocate screen and use it to populate
		// the screen variable, then populate
		// background variable.
		screen = allocscreen(size_x, size_y);
		setlocalvar(screen_key, screen);		
	}	

	return screen;
}

// Caskey, Damon V.
// 2019-02-22
//
// Draws names of characters during select screen.
void dc_draw_select_names()
{
	// Don't waste any more cycles if we aren't 
	// in select screen.
	if (!openborvariant("in_selectscreen"))
	{
		return;
	}

	int i;
	int maxplayers;
	char name_full;
	char name_last;
	char name_first;

	int font;
	int x_base;
	int x_pos;
	int y_pos;
	int string_width;

	int section_size;
	int section_half;

	int elapsed_time;
	int select_time;

	void screen;

	int screen_scale_x;
	int screen_scale_y;

	int scale_add;

	int screen_width;
	int screen_height;


	elapsed_time = openborvariant("elapsed_time");
	maxplayers = openborvariant("maxplayers");

	// Divide up the screen into even sections for each player.
	section_size = openborvariant("hresolution") / maxplayers;
	section_half = section_size / 2;

	for (i = 0; i < maxplayers; i++)
	{		
		// Get to start of our section, and add half to find the center.
		x_base = (dc_player_multiplier(i) * section_size) + section_half;

		name_full = getplayerproperty(i, "name");
		name_last = strinfirst(name_full, SPACE_CHAR);

		// No last name?
		if (name_last == -1)
		{
			x_pos = dc_center_string_x(x_base, name_full, WAIT_NAME_FONT);
			y_pos = dc_center_string_y(SELECT_Y_BASE, name_full, FONT_Y);

			screen_width = strwidth(name_full, WAIT_NAME_FONT);
			screen_height = FONT_Y;			

			drawstring(x_pos, y_pos, WAIT_NAME_FONT, name_full);
			//drawstringtoscreen(screen, x_pos, y_pos, WAIT_NAME_FONT, name_full);			
		}
		else
		{			
			// Get a Y center based on two lines (first name, last name).
			y_pos = dc_center_string_y(SELECT_Y_BASE, name_last, FONT_Y * 2);

			// Get first name string and center x position.
			name_first = strleft(name_full, strlength(name_full) - strlength(name_last));
			x_pos = dc_center_string_x(x_base, name_first, WAIT_NAME_FONT);

			drawstring(x_pos, y_pos, WAIT_NAME_FONT, name_first);
			//drawstringtoscreen(screen, x_pos, y_pos, WAIT_NAME_FONT, name_first);

			// Remove sapce character from last name.
			name_last = strright(name_last, 1);

			x_pos = dc_center_string_x(x_base, name_last, WAIT_NAME_FONT);

			// Add vertical font space.
			y_pos += FONT_Y;

			drawstring(x_pos, y_pos, WAIT_NAME_FONT, name_last);
			//drawstringtoscreen(screen, x_pos, y_pos, WAIT_NAME_FONT, name_last);

			screen_width = strwidth(name_first, WAIT_NAME_FONT);
			screen_height = FONT_Y;
		}

		//string_width = 20;
		//log("\n str w(" + i +"): +" + screen_width);
		//screen = dc_get_screen(i, screen_width, screen_height);
		//dc_draw_text_screen(screen, screen_scale_x, screen_scale_y);
	}

#undef SELECT_NAME_FONT
#undef SELECT_NAME_FONT_Y
#undef SELECT_Y_BASE
}

void dc_draw_text_screen(void screen, int scale_x, int scale_y)
{
	int pos_x;
	int pos_y;
	int pos_z;

	float scale_x_percentage;
	float scale_y_percentage;

	int screen_center_x;
	int screen_center_y;

	// Find where center of scaled size falls.
	//scale_x_percentage = scale_x / (OG_SCREEN_SCALE_MAX_X + 0.0);
	//scale_y_percentage = scale_y / (OG_SCREEN_SCALE_MAX_Y + 0.0);	

	//screen_center_x = (scale_x_percentage * size_x) * 0.5;
	//screen_center_y = (scale_y_percentage * size_y) * 0.5;

	//screen_center_x = (1 * size_x) * 0.5;
	//screen_center_y = (1 * size_y) * 0.5;
			                                                             
	pos_x = OG_SCREEN_BASE_POS_X;
	pos_y = OG_SCREEN_BASE_POS_Y;
	pos_z = openborvariant("PLAYER_MAX_Z") + 1000;	

	// Set the drawmethods.
	//changedrawmethod(NULL(), "reset", 1);
	//changedrawmethod(NULL(), "centerx", screen_center_x);
	//changedrawmethod(NULL(), "centery", screen_center_y);
	//changedrawmethod(NULL(), "enabled", 1);
	//changedrawmethod(NULL(), "transbg", 1);
	//changedrawmethod(NULL(), "scalex", scale_x);
	//changedrawmethod(NULL(), "rotate", count);
	//changedrawmethod(NULL(), "scaley", scale_x);

	

	//Draw the resized customized screen to main screen.
	drawscreen(screen, pos_x, pos_y, pos_z);

	//changedrawmethod(NULL(), "enabled", 0);
}

// Caskey, Damon V.
// 2019-02-22
//
// Return position to horizontaly center a string.
int dc_center_string_x(int x_base, char string, int font)
{
	return x_base - (strwidth(string, font) / 2);
}

// Caskey, Damon V.
// 2019-02-22
//
// Return position to horizontaly center a string. At time of
// coding, font height is not available, so we have to use
// a known static font size.
int dc_center_string_y(int y_base, char string, int font_size)
{
	return y_base - (font_size / 2);
}

// Caskey, Damon V.
// 2019-02-22
//
// Dirty function to deal with first player being in 
// the middle when we want to use player number as a
// position multiplier.
int dc_player_multiplier(int player)
{
	switch (player)
	{
	case 0:

		return 1;
		break;

	case 1:

		return 0;
		break;

	default:

		return player;
		break;
	}
}

void clear()
{
	void scr = getindexedvar(0);
	if (scr) {
		free(scr);
		free(getscriptvar(1));
	}
}
