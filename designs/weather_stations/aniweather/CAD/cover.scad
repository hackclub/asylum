include <common.scad>

SWITCH_HEIGHT = 11.3;
SWITCH_WIDTH = 6.4;

module screw() {
	translate([0, 0, -PCB_DEPTH / 2 + WALL_THICKNESS - 0.0001])

	cylinder(h=SUPPORT_DEPTH+99999, d=3, $fn=50);
}

module main() {
	cube([CASE_WIDTH, CASE_HEIGHT, WALL_THICKNESS], true);
}

module button() {
	cube([BUTTON_WIDTH, BUTTON_HEIGHT, 100], true);
}

difference() {
	main();

	translate([(PCB_WIDTH - 4) / 2 - SCREW_OFFSET, (PCB_HEIGHT - 4) / 2 - SCREW_OFFSET, 0]) screw();
	translate([(PCB_WIDTH - 4) / 2 - SCREW_OFFSET, -(PCB_HEIGHT - 4) / 2 + SCREW_OFFSET, 0]) screw();
	translate([-(PCB_WIDTH - 4) / 2 + SCREW_OFFSET, (PCB_HEIGHT - 4) / 2 - SCREW_OFFSET, 0]) screw();
	translate([-(PCB_WIDTH - 4) / 2 + SCREW_OFFSET, -(PCB_HEIGHT - 4) / 2 + SCREW_OFFSET, 0]) screw();

	cube([LCD_WIDTH, LCD_HEIGHT, 500], true);

	translate([19.3 + SWITCH_WIDTH / 2, 0.407, 0])
	cube([SWITCH_WIDTH, SWITCH_HEIGHT, 500], true);

	corners();

	translate([15.95 + 1.5/2, 32 + 1.5/2 - 0.01, 0])
	button();

	translate([-15.95 - 1.5/2, 32 + 1.5/2 - 0.01, 0])
	button();
}

