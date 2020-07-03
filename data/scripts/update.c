void oncreate()
{
	log("\n");
	log("update.c");
	log("\t");
	log("- oncreate().");
	log("\n");

	int i;
	int maxplayers;
	void screen;

	maxplayers = openborvariant("maxplayers");
	
	for (i = 0; i < maxplayers; i++)
	{
		screen = allocscreen(openborvariant("hResolution"), openborvariant("vResolution"));

		setlocalvar("dc_player_screen_" + i, screen);
	}
	
	

	
}

void ondestroy()
{
	log("\n");
	log("update.c");
	log("\t");
	log("- ondestroy().");
	log("\n");

	int i;
	int maxplayers;
	void screen;

	maxplayers = openborvariant("maxplayers");

	// Destroy player sreens.
	for (i = 0; i < maxplayers; i++)
	{
		screen = getlocalvar("dc_player_screen_" + i);
	
		free(screen);
	}
}




void main()
{
	//trai0001();
	//trai0002();

	//setdrawmethod(NULL(), 1, 512, 512, 0, 0, 0, 1, -1, 0, 0, 0, 0);

	//changedrawmethod(NULL(), "scalex", 512);
	//changedrawmethod(NULL(), "scaley", 512);
	//changedrawmethod(NULL(), "enabled", 1);

	//dc_draw_select_names();
	
}

// Caskey, Damon V.
// 2019-02-22
//
// Draws names of characters during select screen.
void dc_draw_select_names()
{
	#define WAIT_NAME_FONT		3
	#define SELECT_NAME_FONT	4
	#define FONT_Y				18	// Vertical size of font (unavailable as of 2019-02-22). Includes margin.
	#define SELECT_Y_BASE		105
	#define SPACE_CHAR			"_"
	#define	MAX_DRAW_SIZE		256 * 10
	#define MAX_DRAW_SIZE_TIME	1000

	// Don't waste any more cycles if we aren't 
	// in select screen.
	if (!openborvariant("in_selectscreen"))
	{
		//return;
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

	elapsed_time = openborvariant("elapsed_time");

	maxplayers = openborvariant("maxplayers");

	// Divide up the screen into even sections for each player.
	section_size = openborvariant("hresolution") / maxplayers;
	section_half = section_size / 2;

	for (i = 0; i < maxplayers; i++)
	{
		// When did player select a character?
		select_time = getlocalvar("dc_draw_select_p" + i);

		if (getplayerproperty(i, "playkeys") && !select_time)
		{
			setlocalvar("dc_draw_select_p" + i, elapsed_time + MAX_DRAW_SIZE_TIME);
		}

		// Get player screen.
		screen = getlocalvar("dc_player_screen_" + i);
		clearscreen(screen);

		if (select_time > elapsed_time)
		{
			int scale_size;
			int base_time;
			int difference;

			base_time = select_time - MAX_DRAW_SIZE_TIME;

			float percentage = (((elapsed_time - base_time) * 100) / (select_time - base_time)) * 0.01;

			changedrawmethod(NULL(), "scalex", percentage * 256);
			changedrawmethod(NULL(), "scaley", percentage * 256);

			drawstring(200, 30 + (i * 10), 1, "s: " + select_time + ", e: " + elapsed_time + ", s-e: " + (select_time - elapsed_time) + " p: " + percentage);
		}
		else
		{
			changedrawmethod(NULL(), "reset", 1);
		}

		

		// Get to start of our section, and add half to find the center.
		x_base = (dc_player_multiplier(i) * section_size) + section_half;

		name_full = getplayerproperty(i, "name");
		name_last = strinfirst(name_full, SPACE_CHAR);

		// No last name?
		if (name_last == -1)
		{
			x_pos = dc_center_string_x(x_base, name_full, WAIT_NAME_FONT);
			y_pos = dc_center_string_y(SELECT_Y_BASE, name_full, FONT_Y);

			//drawstring(x_pos, y_pos, WAIT_NAME_FONT, name_full);
			drawstringtoscreen(screen, x_pos, y_pos, WAIT_NAME_FONT, name_full);
		}
		else
		{
			// Get a Y center based on two lines (first name, last name).
			y_pos = dc_center_string_y(SELECT_Y_BASE, name_last, FONT_Y * 2);

			// Get first name string and center x position.
			name_first = strleft(name_full, strlength(name_full) - strlength(name_last));
			x_pos = dc_center_string_x(x_base, name_first, WAIT_NAME_FONT);

			//drawstring(x_pos, y_pos, WAIT_NAME_FONT, name_first);
			drawstringtoscreen(screen, x_pos, y_pos, WAIT_NAME_FONT, name_first);

			// Remove sapce character from last name.
			name_last = strright(name_last, 1);

			x_pos = dc_center_string_x(x_base, name_last, WAIT_NAME_FONT);

			// Add vertical font space.
			y_pos += FONT_Y;

			//drawstring(x_pos, y_pos, WAIT_NAME_FONT, name_last);
			drawstringtoscreen(screen, x_pos, y_pos, WAIT_NAME_FONT, name_last);
		}

		// draw player screen.
		changedrawmethod(NULL(), "enabled", 1);
		changedrawmethod(NULL(), "scalex", 1.5);
		changedrawmethod(NULL(), "scaley", 1.5);
		changedrawmethod(screen, "alpha", 1);
		drawscreen(screen, 0, 0, openborvariant("PLAYER_MAX_Z") + 1000, 0);
		changedrawmethod(NULL(), "reset", 1);

		// Restore drawmethod.
		//changedrawmethod(NULL(), "scalex", 256);
		//changedrawmethod(NULL(), "scaley", 256);
	}

	#undef SELECT_NAME_FONT
	#undef SELECT_NAME_FONT_Y
	#undef SELECT_Y_BASE
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
	switch(player)
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

void zoom()
{
	void vscreen = openborvariant("vscreen");
	int maxz = openborvariant("PLAYER_MAX_Z") + 1000;
	int zoom_value = getglobalvar("zoomvalue");
	int zoom_x = getglobalvar("zoomx");
	int zoom_y = getglobalvar("zoomy");
	void ent = getglobalvar("zoomentity");
	int px = getentityproperty(ent, "x") + zoom_x - openborvariant("xpos");
	int py = getentityproperty(ent, "z") + zoom_y - openborvariant("ypos"); //- getentityproperty(ent,"a");
	void zoom_scr = getglobalvar("zoomscreen");
	if (!zoom_scr) {
		zoom_scr = allocscreen(openborvariant("hResolution"), openborvariant("vResolution"));
		setglobalvar("zoomscreen", zoom_scr);
	}
	clearscreen(zoom_scr);

	//draw what we need
	drawspriteq(zoom_scr, 0, openborconstant("MIN_INT"), maxz, 0, 0);
	//setup drawMethod
	changedrawmethod(NULL(), "reset", 1);
	changedrawmethod(NULL(), "enabled", 1);
	changedrawmethod(NULL(), "scalex", zoom_value);
	changedrawmethod(NULL(), "scaley", zoom_value);
	changedrawmethod(NULL(), "centerx", px);
	changedrawmethod(NULL(), "centery", py);
	//Draw the resized customized screen to main screen.
	drawscreen(zoom_scr, px, py, maxz + 1);
	changedrawmethod(NULL(), "enabled", 0);
	drawspriteq(vscreen, 0, maxz + 1, maxz + 1, 0, 0);
	drawspriteq(vscreen, 0, maxz + 2, openborconstant("MAX_INT"), 0, 0);
	clearspriteq();
}