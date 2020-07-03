#include "data/scripts/dc_target/config.h"

#import "data/scripts/dc_target/animation.c"
#import "data/scripts/dc_target/entity.c"
#import "data/scripts/dc_target/offset.c"
#import "data/scripts/dc_target/range.c"

// Caskey, Damon V
// 2018-12-01 (Retool of original 2017-03-xx)
//
// Find nearest obstacle in range of animation.
int dc_target_find_obstacle() 
{
	int     result;			// Final result.
	void	ent;			// Acting entity.
	int		animation;		// Acting animation.
	void    target;			// Target entity pointer.
	int     target_count;	// Target Entity count.
	int     i;				// Loop cursor.
	float	distance_last;	// Last nearest distance in loop.
	float	distance_new;	// Current distance in loop.

	// Get acting entity and animation.
	ent = dc_target_get_entity();
	animation = dc_target_get_animation();

	// If this entity doesn't have the animation at all,
	// then exit. There's nothing else to do.
	if (!getentityproperty(ent, "animvalid", animation))
	{
		return result;
	}

	// Get entity count.
	target_count = openborvariant("count_entities");

	// Loop over each entity index.
	for (i = 0; i < target_count; i++)
	{
		// Get entity pointer.
		target = getentity(i);

		// If the target is not an obstacle, then
		// we're already done with this iteration
		// of the loop.
		if (getentityproperty(target, "type") != openborconstant("TYPE_OBSTACLE"))
		{
			continue;
		}

		// If the target falls out of any range, 
		// it's not a valid target, so get out of 
		// this loop iteration.

		if (!dc_target_check_target_in_range_z(target))
		{
			continue;
		}

		if (!dc_target_check_target_in_range_x(target))
		{
			continue;
		}

		if (!dc_target_check_target_in_range_y(target))
		{
			continue;
		}

		// Now we get distance to the current target in loop iteration. 
		// Then we compare that to distance from previous iteration. If
		// the previous distance doesn't exist (this is first iteration)
		// or this iteration's distance is closer, then we record
		// distance for next iteration and the target as a result. When 
		// all targets are iterated, result will be the closest one.

		distance_new = dc_target_find_total_distance_to_target(target);

		if (distance_last || distance_new < distance_last)
		{
			distance_last = distance_new;
			result = target;
		}
	}

	// Return final result.
	return result;
}

// Caskey, Damon V.
// 2017-03-18
// 
// Get X position of screen edge if found within X range of
// animation.
int dc_target_find_edge_x()
{
	void ent;		// Acting entity.
	int result = 0;		// Final result.
	int scroll_x;	// Screen scroll position.
	int far_x;		// Location of far screen edge.
	int animation;	// Acting animation.

	// Acting entity.
	ent = dc_target_get_entity();

	// Acting animation
	animation = dc_target_get_animation();

	// Get current scroll position, far edge position
	// and entity x position.
	scroll_x = openborvariant("xpos");
	far_x = scroll_x + openborvariant("hResolution");

	// Is scroll X in range of near screen position? Then
	// we can scroll X. Just in case scroll X is in range
	// but still 0, we'll return 1 instead.

	// Run the check and set result accordingly.
	if (dc_target_check_position_in_range_x(scroll_x))
	{
		if (scroll_x)
		{
			result = scroll_x;
		}
		else
		{
			result = 1;
		}

		return result;
	}

	// Same as above, but this time for the far edge of screen.
	if (dc_target_check_position_in_range_x(far_x))
	{		
		result = far_x;
		return result;
	}

	// If we got this far, return the default (false).
	return result;
}

// Caskey, Damon V.
// 2019-11-03
//
// Get X position of screen edge if found within X range of
// animation.
float dc_target_find_wall_x()
{
	void ent;						// Acting entity.
	int wall_count;					// Number of walls in level.
	int wall_cursor;				// Wall we are currently evaluating.

	int wall_height;				// Wall height.

	float pos_x;					// Entity position, X axis.
	float pos_y;					// Entity position, Y axis.
	float pos_z;					// Entity position, Z axis.

	int wall_pos_x;					// Wall position, X axis.
	int wall_pos_z;					// Wall position, Z axis.
	int wall_depth;					// Wall size, Z axis.
	int wall_lower_left;			// Wall lower left corner.
	int wall_lower_right;			// Wall lower right corner.
	int wall_upper_left;			// Wall upper left corner.
	int wall_upper_right;			// Wall upper right corner.

	float wall_coef_left;			// Wall coefficiant, left side.
	float wall_coef_right;			// Wall coefficiant, right side.

	float wall_point_left;			// Final left X extent of wall along a Z axis point.
	float wall_point_right;			// Final right X extent of wall along a Z axis point.

	float distance_to_point_left;	// How far we are from a wall's left point.
	float distance_to_point_right;	// How far we are from a wall's right point.

	float result = DC_TARGET_NO_WALL_FOUND;

	ent = dc_target_get_entity();
	
	// To find out if a wall is in range, We'll loop over each wall in the level 
	// and if any range checks fail we move on to the next wall. We run the checks
	// that are simple and most likely to fail first to keep things optimal as possible. 
	// 
	// We don't care about which wall or if there is more than one in range, so
	// once we find one, we exit the loop immediately.
	//
	// This technique is very similar to the way OpenBOR’s native code looks for walls. 
	// At first glance it map appear backwards and un-optimal to loop through all the 
	// walls, and it might seem like a good idea to run checkwall() on points within a 
	// range. Don’t fall for that trap! Due to additive vs cubic math, and a few other
	// caveats, looping the walls is FAR more efficiant. Contact me if you'd like a
	// full explanation. :)

	wall_count = openborvariant("numwalls");

	for (wall_cursor = 0; wall_cursor < wall_count; wall_cursor++)
	{
		// If wall height is not within our vertical (Y axis) range, exit.

		wall_height = getlevelproperty("wall", wall_cursor, "height");
		
		if (!dc_target_check_range_in_range_y(0, wall_height))
		{
			continue;
		}

		// If wall depth is not within our lateral (depth/Z axis) range, exit.
		
		wall_pos_z = getlevelproperty("wall", wall_cursor, "z");
		wall_depth = getlevelproperty("wall", wall_cursor, "depth");

		if (!dc_target_check_range_in_range_z(wall_pos_z - wall_depth, wall_pos_z))
		{
			continue;
		}

		// If wall width is not within our X range, exit. This gets a bit more
		// complex than the Y or Z axis since walls may have angled sides. We'll 
		// need to find a coefficiant for the left and right side based on our 
		// Z position in relation to the wall. This is the same basic formula used 
		// by the engine's native wall check. 
		//
		// Once we have the coefficiants, we'll create a final point by 
		// combining them with the wall's X position and corner offsets. These
		// points are the exact X axis extent of the wall's sides at our 
		// entity's Z position. We can then send those on to the X range 
		// function to see if either side falls within animation's X range.

		pos_z = get_entity_property(ent, "position_z");

		wall_pos_x = getlevelproperty("wall", wall_cursor, "x");
		wall_lower_left = getlevelproperty("wall", wall_cursor, "lowerleft");
		wall_upper_left = getlevelproperty("wall", wall_cursor, "upperleft");
		wall_lower_right = getlevelproperty("wall", wall_cursor, "lowerright");
		wall_upper_right = getlevelproperty("wall", wall_cursor, "upperright");

		wall_coef_left = (wall_pos_z - pos_z) * ((wall_upper_left - wall_lower_left) / wall_depth);
		wall_coef_right = (wall_pos_z - pos_z) * ((wall_upper_right - wall_lower_right) / wall_depth);

		wall_point_left = wall_pos_x + wall_lower_left + wall_coef_left;
		wall_point_right = wall_pos_x + wall_lower_right + wall_coef_right;		

		// If the wall is not in range, go to next loop. If the wall IS in range
		// break out of loop and set result DC_TARGET_WALL_FOUND.
		if (!dc_target_check_range_in_range_x(wall_point_left, wall_point_right))
		{
			continue;
		}
		else
		{
			result = DC_TARGET_WALL_FOUND;
			break;
		}
	}	

	// If result == DC_TARGET_WALL_FOUND, then loop found a wall within animation range. 
	// Now we need to decide which side to send as a result. Get the entity location, 
	// compare its distance to both wall points and send the closer one as a result.
	if (result == DC_TARGET_WALL_FOUND)
	{
		pos_x = get_entity_property(ent, "position_x");

		distance_to_point_left = dc_math_difference_float(pos_x, wall_point_left);
		distance_to_point_right = dc_math_difference_float(pos_x, wall_point_right);		

		// Use closer side. In the unlikely event we are exactly the same
		// distance to both sides, default to left.
		if (distance_to_point_left <= distance_to_point_right)
		{
			result = wall_point_left;
		}
		else
		{
			result = wall_point_right;
		}
	}	

	return result;

}