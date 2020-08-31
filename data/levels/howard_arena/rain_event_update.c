void oncreate()
{
}

void ondestroy()
{
}

void main() {

	void    ent = getlocalvar("self");  // Target entity pointer.
	int     ent_count = 0;				// Entity count.
	int     i = 0;						// Loop counter.

	if (get_entity_property(ent, "animation_id") != openborconstant("ANI_IDLE"))
	{
		return;
	}

	// Get entity count.
	ent_count = openborvariant("count_entities");

	// Loop over each entity index.
	for (i = 0; i < ent_count; i++)
	{
		// Get entity pointer.
		ent = getentity(i);

		if (!ent)
		{
			continue;
		}

		int type = getentityproperty(ent, "type");

		if (type == openborconstant("TYPE_ENEMY") || type == openborconstant("TYPE_PLAYER") || type == openborconstant("TYPE_NPC"))
		{
			void sprite = getentityproperty(ent, "sprite");

			//settextobj(1, 40, 20, 1, openborconstant("FRONTPANEL_Z"), "sprite: " + sprite);

			int pixel_color_index = 0;
			int size_x = getgfxproperty(sprite, "width");
			int size_y = getgfxproperty(sprite, "height");
			int center_x = getgfxproperty(sprite, "centerx");
			int center_y = getgfxproperty(sprite, "centery");

			float pos_x = get_entity_property(ent, "position_x");
			float pos_y = get_entity_property(ent, "position_y");
			float pos_z = get_entity_property(ent, "position_z");

			int offset_x = 0; // Scroll and quake. 
			int offset_y = 0;

			int pixel_row_top = (size_y - (size_y - center_y));
			int pixel_row = 0; //pixel_row_top;
			int pixel_column = 0;

			int column_offset = getlocalvar("dc_column_offset");
			int row_offset = 1;
			int elapsed_time = openborvariant("elapsed_time");
			int trigger_time = getlocalvar("dc_column_offset_time");

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

			int screen_draw_x = 0;
			int screen_draw_y = 0;

			screen_draw_x = pos_x - offset_x;
			screen_draw_y = pos_z - pos_y - offset_y;

			int sprite_right = 0;
			int sprite_left = 0;

			int pos_d;

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

			//log("\n\n ---- \n\n");

			//settextobj(2, 40, 30, 1, openborconstant("FRONTPANEL_Z"), "Pixel: " + pixel_color_index);
			//settextobj(3, 40, 50, 1, openborconstant("FRONTPANEL_Z"), "size (X: " + size_x + ", Y: " + size_y + ")");

			for (pixel_column = column_offset; pixel_column < size_x; pixel_column += 2)
			{
				// log("\n C: " + pixel_column);

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

					// log("\n\t R: " + pixel_row);

					pixel_color_index = getgfxproperty(sprite, "pixel", pixel_column, pixel_row);
					// log(", Index: " + pixel_color_index);

					if (pixel_color_index)
					{						
						// log(", TRUE");
						
						if (pos_d == openborconstant("DIRECTION_RIGHT"))
						{
							drawdot(sprite_left + pixel_column, screen_draw_y - (center_y - pixel_row) - row_offset, pos_z + 1, rgbcolor(150, 150, 150), 0);
						}
						else
						{
							drawdot((sprite_right - pixel_column)-1, screen_draw_y - (center_y - pixel_row) - row_offset, pos_z + 1, rgbcolor(150, 150, 150), 0);
						}
						
						break;
					}
				}				
			}
		}		
	}	
}
