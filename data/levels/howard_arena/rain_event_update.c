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

void oncreate()
{
}

void ondestroy()
{
}

void main() 
{
	dc_rain_splatter();
}
