#include "data/scripts/dc_afterimage/config.h"

void trai0002(void target)
{

    /*
    trai0002
    Utunnels
    Unknown Date (Converted to Hungarian Notation by Damon Vaughn Caskey 10262009)
    Sets current sprite, location, and draw settings into artifical array (see trai0001) to
    be displayed as a shadow trail.
    */

    int     i;
    int     draw_scale_x;
    int     draw_scale_y;
	void    old_sprite;
	void    sprite;
	void    draw_table;
	int     time_remaining;
	float   pos_x;
	float   pos_y;
	float   pos_z;
	int     direction;
	int     elapsed_time;

    elapsed_time = openborvariant("elapsed_time");

	log("\n elapsed_time: " + elapsed_time);
	log("\n elapsed_time / DC_AFTERIMAGE_DELAY: " + (elapsed_time / DC_AFTERIMAGE_DELAY));
	log("\n elapsed_time % DC_AFTERIMAGE_DELAY: " + (elapsed_time % DC_AFTERIMAGE_DELAY));


    // Modulo of elapsed time and trailer expire time 0?
	if(elapsed_time % DC_AFTERIMAGE_DELAY==0)
	{

		log("\n elapsed_time % DC_AFTERIMAGE_DELAY==0 verified");

        // Loop through trailer slots.
        for(i=1; i<=DC_AFTERIMAGE_GLOBAL_MAX; i++)
		{
            // Is this an empty slot? If so lets
            // populate our artificial array with
            // current sprite, drawmethods, and time.

			old_sprite = getglobalvar(DC_AFTERIMAGE_KEY_BASE+i+DC_AFTERIMAGE_KEY_SPRITE);

			if(!old_sprite)
			{
			    draw_scale_x    = getdrawmethod(target, "scalex");
			    draw_scale_y    = getdrawmethod(target, "scaley");
			    draw_table      = getdrawmethod(target, "table");
			    time_remaining  = DC_AFTERIMAGE_ENTITY_MAX * DC_AFTERIMAGE_LIFESPAN;
			    pos_x           = getentityproperty(target, "x");
                pos_z           = getentityproperty(target, "z");
                pos_y           = getentityproperty(target, "y");
                direction       = !getentityproperty(target, "direction");
                sprite          = getentityproperty(target, "sprite");

                setglobalvar(DC_AFTERIMAGE_KEY_BASE+i+DC_AFTERIMAGE_KEY_SCALE_X, draw_scale_x);
                setglobalvar(DC_AFTERIMAGE_KEY_BASE+i+DC_AFTERIMAGE_KEY_SCALE_X, draw_scale_y);
				setglobalvar(DC_AFTERIMAGE_KEY_BASE+i+DC_AFTERIMAGE_KEY_SPRITE, sprite);
                setglobalvar(DC_AFTERIMAGE_KEY_BASE+i+DC_AFTERIMAGE_KEY_TABLE, draw_table);
				setglobalvar(DC_AFTERIMAGE_KEY_BASE+i+DC_AFTERIMAGE_KEY_POS_X, pos_x);
				setglobalvar(DC_AFTERIMAGE_KEY_BASE+i+DC_AFTERIMAGE_KEY_POS_Z, pos_z);
				setglobalvar(DC_AFTERIMAGE_KEY_BASE+i+DC_AFTERIMAGE_KEY_POS_Y, pos_y);
				setglobalvar(DC_AFTERIMAGE_KEY_BASE+i+DC_AFTERIMAGE_KEY_FLIP_X, direction);
				setglobalvar(DC_AFTERIMAGE_KEY_BASE+i+DC_AFTERIMAGE_KEY_EXPIRE, time_remaining);

				break;
			}
		}
	}
}
