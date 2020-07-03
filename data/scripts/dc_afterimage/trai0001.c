#include "data/scripts/dc_afterimage/config.h"

void trai0001()
{
    /*
    trai0001
    Utunnels
    Unknown Date (Converted to Hungarian Notation by Damon Vaughn Caskey 10262009)

    Parses artificial array (created by numerically sequenced global vars) and displays stored sprite
    depending on stored settings.
    */

	int     i;                  // Loop index.
	int     cd;                 // Expire time.
	void    sprite;             // Sprite pointer.
	float   pos_X;              // Sprite position.
	float   pos_Y;
	float   pos_Z;
	int     draw_flip_x;        // facing.
    void    draw_table;
    float   draw_scale_x;
    float   draw_scale_y;
    int     key_index;

    //  Existing draw methods.
    void    old_draw_table;
    int     old_draw_scale_x;
    int     old_draw_scale_y;
    int     old_draw_alpha;
	int     old_draw_flip_x;
    int     old_draw_enable;

    // Loop afterimage slots.
	for(i=1; i<=DC_AFTERIMAGE_GLOBAL_MAX; i++)
	{
        // Get afterimage sprite.
		sprite = getglobalvar(DC_AFTERIMAGE_KEY_BASE+i+DC_AFTERIMAGE_KEY_SPRITE);

		// Sprite found?
		if(sprite)
		{
		    // If there is no expired time or the time is
		    // 0, then we know this afterimage is expired.
		    // We'll clear out the globals for this index
		    // and exit the function.
			cd = getglobalvar(DC_AFTERIMAGE_KEY_BASE+i+DC_AFTERIMAGE_KEY_EXPIRE);

			if(!cd)
			{
			    for(key_index = 0; key_index < DC_AFTERIMAGE_KEY_THE_END; key_index++)
                {
                    // Clear the globals for this element.
                    setglobalvar(DC_AFTERIMAGE_KEY_BASE+i+key_index, NULL());
                }

                return;
			}

            // Let's get the current drawmethod settings
            // so we can reapply them when we're done.
            old_draw_enable     = getdrawmethod(NULL(), "enabled");
            old_draw_flip_x     = getdrawmethod(NULL(), "flipx");
            old_draw_scale_x    = getdrawmethod(NULL(), "scalex");
            old_draw_scale_y    = getdrawmethod(NULL(), "scaley");
            old_draw_table      = getdrawmethod(NULL(), "table");
            old_draw_alpha      = getdrawmethod(NULL(), "alpha");

            // Game not paused?
            if(openborvariant("game_paused")==0)
            {
                // Decrement expire time.
                setglobalvar(DC_AFTERIMAGE_KEY_BASE+i+DC_AFTERIMAGE_KEY_EXPIRE, cd-1);
            }

            // Get global sprite adjustment values.
            pos_X           = getglobalvar(DC_AFTERIMAGE_KEY_BASE+i+DC_AFTERIMAGE_KEY_POS_X);
            pos_Z           = getglobalvar(DC_AFTERIMAGE_KEY_BASE+i+DC_AFTERIMAGE_KEY_POS_Z);
            pos_Y           = getglobalvar(DC_AFTERIMAGE_KEY_BASE+i+DC_AFTERIMAGE_KEY_POS_Y);
            draw_flip_x     = getglobalvar(DC_AFTERIMAGE_KEY_BASE+i+DC_AFTERIMAGE_KEY_FLIP_X);
            draw_table      = getglobalvar(DC_AFTERIMAGE_KEY_BASE+i+DC_AFTERIMAGE_KEY_TABLE);
            draw_scale_x    = getglobalvar(DC_AFTERIMAGE_KEY_BASE+i+DC_AFTERIMAGE_KEY_SCALE_X);
            draw_scale_y    = getglobalvar(DC_AFTERIMAGE_KEY_BASE+i+DC_AFTERIMAGE_KEY_SCALE_Y);

            // Position adjustments.
            pos_X -= openborvariant("xpos");
            pos_Y = (pos_Z-pos_Y-openborvariant("ypos")) + DC_AFTERIMAGE_CORRECTION_Y;
            pos_Z -= i;

            // Set global drawmethods.
            changedrawmethod(NULL(), "enabled", 1);
            changedrawmethod(NULL(), "alpha", DC_AFTERIMAGE_BLEND);
            changedrawmethod(NULL(), "scalex", draw_scale_x);
            changedrawmethod(NULL(), "scaley", draw_scale_x);
            changedrawmethod(NULL(), "flipx", draw_flip_x);
            changedrawmethod(NULL(), "table", draw_table);

            // Draw the afterimage sprite.
            drawsprite(sprite, pos_X, pos_Y, pos_Z, 0);

            // Restore old drawmethods.
            changedrawmethod(NULL(), "enabled", old_draw_enable);
            changedrawmethod(NULL(), "flipx", old_draw_flip_x);
            changedrawmethod(NULL(), "scalex", old_draw_scale_x);
            changedrawmethod(NULL(), "scaley", old_draw_scale_y);
            changedrawmethod(NULL(), "flipx", old_draw_flip_x);
            changedrawmethod(NULL(), "table", old_draw_table);
            changedrawmethod(NULL(), "alpha", old_draw_alpha);

		}
	}
}
