# Fatal-Fury-Chronicles
An OpenBOR module based on the Fatal Fury Series.

This module was first conceived in late 2007, and has undergone dozens of redesigns. It is intended to tell the story of Fatal Fury One, and originally used assets from that game, but has since been upgraded to KOF Era resources.

To put it bluntly, the current iteration is mostly unplayable. It was the victim of feature creep and constant experimentation with various scripting concepts, and I often moved onto something else without cleaning up the mess. Enemies are VERY poorly grouped, some attacks have odd effects attached, most grapple moves are currently disabled, and some actions will get you stuck. 

It will take a large amount of work to even make a reasonable demo. I do have all my previous iterations and so there is a clean version somewhere, but it would take unpacking and trying dozens of archives to find it. That's why we have software controlled versioning like GitHub now. :) 

That said, there are many features present and working beautifully that have not yet been seen in other OpenBOR modules to this day, or if they have, are in very unrefined form. I don't even remember most of them, but here are a few...

## Sounds On Sound Beach

- Sound effects are fully randomized, with a highly sophisticated sound file auto detect and play system that needs (and will get) its own repository. Characters even trash talk each other in response to big hits and KOs (this is better seen in Golden Axe Hackjob).
- Sounds are played with true stereo - If you have a stereo system or headphones, you'll notice a hit toward the screen left will be heard on the left, in the middle is in the middle, and so on, with infinite graduation between.

## 3D Fighting

In homage to Fatal Fury's Line Shift system, a heavy emphasis is made on lateral combat. All fighters (even basic mooks) at minimum may perform the following:

- Dash in all directions, including lateral sidesteps.
- Immediately follow up lateral side steps with a side step attack, back dash, or side step in the opposite direction.
- Perform lunging or leaping attacks to attack opponents at a distance along the lateral plane.
- Execute one of two powerful blows that knock the victim in either direction along the lateral plane.

## Attack Based Reaction and Fatalities

### Proximity Block And HitStun

Attack reactions are based on where on the opponent an attack hits, not just type. For example, a normal attack that contacts the head area will result in a head snap (or high guard if blocked), whereas the same attack will cause the opponent to buckle over if it hits their body (or middle guard on block). The same attack should it hit low may cause loss of footing or sweep them off their feet.

### Fatalities 

Rather than being tied to a specific special command, KO animations are based on the type and angle of finishing attack. With the following available:

- Incineration (fire or electricity)
- Decapitated (Heavy head level attacks)
- Bisected (Heavy cutting attacks at mid level)
- Bleed out (Light cutting attacks at mid level)
- Thrown into foreground or background with real-time scaling and rotation (Heavy attacks with Z axis force).

Even common KOs result in a unique character animation and the victim remaining on the playfield greyed out in lieu of flashing away. Knocking defeated enemies into certain areas can result in stage based Kos – see stages below for details.

## Stage Visuals And Interactivity

### Visuals

Sound beach combines Multiple scrolling layers with animation, weather effects, lighting, and interactivity all in a single area.

- Working dock, building, and boat lights via palette cycle.
- Several layers of independently animated water by stacking panel type entities.
- Animated foreground objects (palm trees, dust).
- Floating boats and other objects have their own animation.
- Time based environmental changes. As time passes, the sunny day will gradually fade to dusk.

### Interactivity

- Boomboxes near the beginning and end of stage are "real". Pressing the action button near one will have your fighter reach down and tune in a new music track for the stage. Sound Beach has three choices to cycle through.
- Defeating an opponent by knocking them into the background will send them splashing into the water for a little swim. ;)
- Should an opponent hit one of the boats when being thrown to the water, they will bounce off and visibly damage the boat. Damage a boat enough and it will sink, leaving you a nice surprise in the process.
