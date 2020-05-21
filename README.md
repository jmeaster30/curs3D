# curs3D
A 3d render engine written in ncurses.

My goal with this project is to make a rendering engine that runs in a terminal.

Currently (May 2020) we can render lines and triangle in color with color blending however the blending on filled triangles doesn't work quite right. I figured if when rendering the horizontal lines in the triangle rasterizing algorithm if we blended the colors along the individual lines it would work but its a little more complicated.

Honestly, this already runs better than I thought it would so if I can just get a 3d cube spinning I feel like this project will be done.
