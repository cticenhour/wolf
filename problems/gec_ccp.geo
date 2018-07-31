/*
*  GEC RF Reference Cell, Capacitively-Coupled
*  Dimensions taken from:
*  D. P. Lymberopolous and D. J. Economou, "Fluid simulations of radio frequency
*  glow discharges: Two-dimensional argon discharge including metastables,"
*  Appl. Phys. Lett. 63 (18), 1993
*/

gap = 0.0254; // meters
electrode_height = 0.0381;
electrode_radius = 0.0508;
insulator_width = 0.0015;
wall_width = 0.0015;
chamber_radius = 0.1016;
chamber_height = 0.1016;

// Center of grounded electrode
Point(1) = {0, electrode_height + gap, 0};

// Outer edge of grounded electrode
Point(2) = {electrode_radius, electrode_height + gap, 0};

// Outer edge of top insulator
Point(3) = {electrode_radius + insulator_width, electrode_height + gap, 0};

// Outer edge of wall, beside grounded electrode
Point(4) = {electrode_radius + insulator_width + wall_width, electrode_height + gap, 0};

// Center of powered electrode
Point(5) = {0, electrode_height, 0};

// Outer edge of powered electrode
Point(6) = {electrode_radius, electrode_height, 0};

// Outer edge of bottom insulator
Point(7) = {electrode_radius + insulator_width, electrode_height, 0};

// Outer edge of wall, beside powered electrode
Point(8) = {electrode_radius + insulator_width + wall_width, electrode_height, 0};

// Open chamber, bottom left
Point(9) = {electrode_radius + insulator_width + wall_width, 0, 0};

// Open chamber, bottom right
Point(10) = {chamber_radius, 0, 0};

// Open chamber, top left
Point(11) = {electrode_radius + insulator_width + wall_width, chamber_height, 0};

// Open chamber, top right
Point(12) = {chamber_radius, chamber_height, 0};

// Grounded electrode surface
Line(1) = {1, 2};

// Top insulator surface
Line(2) = {2, 3};

// Top wall surface beside grounded electrode
Line(3) = {3, 4};

// Top left open chamber wall
Line(4) = {4, 11};

// Top wall of open chamber
Line(5) = {11, 12};

// Outer wall
Line(6) = {12, 10};

// Bottom wall of open chamber
Line(7) = {10, 9};

// Bottom left open chamber wall
Line(8) = {9, 8};

// Bottom wall surface beside powered electrode
Line(9) = {8, 7};

// Bottom insulator surface
Line(10) = {7, 6};

// Powered electrode surface
Line(11) = {6, 5};

// Axis of symmetry
Line(12) = {5, 1};

// Wall 1
Line Loop(13) = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
Plane Surface(14) = {13};

// Plasma Domain
Physical Surface("plasma") = {14};

// Bottom electrode
Physical Line("bottom") = {11};

// Top electrode
Physical Line("top") = {1};

// Physical chamber wall
Physical Line("walls") = {3, 4, 5, 6, 7, 8, 9};

// Physical insulator
Physical Line("insulator") = {2, 10};

// Physical axis of symmetry
Physical Line("axis") = {12};
