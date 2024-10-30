// You only need to edit the varibales prefixed with user_

// The box inner length / depth in mm
user_inner_box_length = 54; // [1:300]
// The box inner height in mm
user_inner_box_height = 40 ; // [1:300]
// The box inner width in mm
user_inner_box_width = 38; // [1:300]
// The box wall width in mm
user_wall_width = 2.5; // [1:10]
// The minimum number of hooks
user_min_hook_count = 3; // [2:20]
// The box start offset in mm
user_box_start_offset = 10; // [0:100]

// You can stop editing after this line if you do not want to brick this script ;) 

if (version()[0] < 2019) {
  echo("WARNING: This script is only tested with 2019.01!");
}

assert(undef != user_inner_box_length, "Value \"user_inner_box_length\" must be specified!");
assert(user_inner_box_length >= 1, "The minimum value is 1mm!");
assert(user_inner_box_length <= 300, "The maximum value is 300mm!");

assert(undef != user_inner_box_height, "Value \"user_inner_box_height\" must be specified!");
assert(user_inner_box_height >= 1, "The minimum value is 1mm!");
assert(user_inner_box_height <= 300, "The maximum value is 300mm!");

assert(undef != user_inner_box_width, "Value \"user_inner_box_width\" must be specified!");
assert(user_inner_box_width >= 1, "The minimum value is 1mm!");
assert(user_inner_box_width <= 300, "The maximum value is 300mm!");

assert(undef != user_wall_width, "Value \"user_wall_width\" must be specified!");
assert(user_wall_width >= 1, "The minimum value is 1mm!");
assert(user_wall_width <= 10, "The maximum value is 10mm!");

assert(undef != user_min_hook_count, "Value \"user_min_hook_count\" must be specified!");
assert(user_min_hook_count >= 2);
assert(user_min_hook_count <= 20);

assert(undef != user_box_start_offset, "Value \"user_box_start_offset\" must be specified!");
assert(user_box_start_offset >= 0);
assert(user_box_start_offset <= 100);

caco_create_ikea_skadis_pistol_style_tool_holder(
  user_inner_box_length, 
  user_inner_box_height, 
  user_inner_box_width, 
  user_wall_width,
  (user_min_hook_count - 1) * 40,
  4,
  user_box_start_offset
);

/*
 * License: MIT License
 * 
 * Copyright (c) 2019 "Guido Krömer" <mail@cacodaemon.de>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
 */
module caco_create_rounded_corner_cube(size, radius = 1, resolution = 5, mode = "all_sides") { 
  half_radius = radius / 2;

  if (mode == "all_sides") {
    translate([half_radius, half_radius, half_radius]) 
    minkowski() { 
      resize(newsize = [radius, radius, radius]) 
      sphere(r = resolution);
      cube([size[0] - radius, size[1] - radius, size[2] - radius], false);
    }
  } else if (mode == "vertical_sides") {
    translate([half_radius, half_radius, 0]) 
    minkowski() { 
      resize(newsize = [radius, radius, radius]) 
      cylinder(r = resolution, h = resolution);
      cube([size[0] - radius, size[1] - radius, size[2] - radius], false);
    }
  } else if (mode == "horizontal_sides") {
    translate([half_radius, radius, half_radius]) 
    minkowski() { 
      resize(newsize = [radius, radius, radius]) 
      rotate([90,0,0]) 
      cylinder(r = resolution, h = resolution);
      cube([size[0] - radius, size[1] - radius, size[2] - radius], false);
    }
  } else {
    cube(size);
  }
}

module caco_create_hollow_rounded_corner_cube_vertical_sides(size, radius = 1, resolution = 5, wall_width = 1.5) {
  difference() {
    caco_create_rounded_corner_cube(size = size, radius = radius, resolution = resolution, mode = "vertical_sides");
    translate([wall_width, wall_width, -wall_width]) 
    cube([size[0] - wall_width * 2, size[1] - wall_width * 2, size[2]]);
  }
}

module caco_create_hook(side_lenght, length) {
  union() {
    cube([side_lenght, side_lenght, side_lenght]);
    caco_create_rounded_corner_cube([side_lenght, length, side_lenght], mode = "vertical_sides");
    translate([0, length - side_lenght, side_lenght - 1]) 
    caco_create_rounded_corner_cube([side_lenght, side_lenght, length]);
  }
}
   
module caco_create_hooks(width, hook_side_lenght, hook_length = 10) {
  union() {
    for(variable = [0 : 40 : width]) {
      translate([variable, 0, 0]) 
      caco_create_hook(side_lenght = hook_side_lenght, length = hook_length);
    }
  }
}

module caco_create_triangle(size) {
  rotate([0 ,0, -90]) 
  rotate([90, 0, 0]) 
  linear_extrude(height = size[0])
  polygon([[0, 0], [size[1], 0], [0, size[2]]]);
}

module caco_create_ikea_skadis_pistol_style_tool_holder(inner_box_length, inner_box_height, inner_box_width, wall_width = 1, static_slot_distance = 40, static_hook_side_lengt = 4, box_start_offset = 0) {
  inner_box_length = inner_box_length + box_start_offset;
  box_length = inner_box_length + wall_width * 2;
  box_height = inner_box_height + wall_width * 2;
  box_width = inner_box_width + wall_width * 2;
  box_width_back = max([static_slot_distance, box_width]);
  offset = ((box_width_back - (floor(box_width_back/static_slot_distance)*static_slot_distance)) / 2) - (static_hook_side_lengt/2);
  
  render() {
    translate([offset, 0, 0]) 
    caco_create_hooks(width = box_width_back, hook_side_lenght = static_hook_side_lengt);

    translate([offset, -wall_width, 0]) 
    caco_create_rounded_corner_cube([box_width_back - offset * 2, wall_width, box_height], radius = wall_width / 2, mode = "horizontal_sides");

    difference() {
      union() {
        translate([((box_width_back - box_width)/2)+box_width, 0, 0])
        caco_create_triangle([box_width, box_length, box_height]);

        translate([(box_width_back - box_width)/2, -box_length, 0]) 
        caco_create_rounded_corner_cube([box_width, box_length, wall_width * 2], mode = "vertical_sides");
      }

      translate([wall_width, wall_width, 0])
      translate([(box_width_back - box_width)/2, -box_length, 0])
      caco_create_rounded_corner_cube([inner_box_width, inner_box_length, box_height], mode = "vertical_sides");
    }

    if (box_start_offset > 0) {
        translate([(box_width_back - box_width)/2, -box_start_offset -wall_width, 0])
        caco_create_rounded_corner_cube([box_width, box_start_offset, wall_width], mode = "none");
    }
  }
}