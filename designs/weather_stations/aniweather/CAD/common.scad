PCB_WIDTH = 55 + 4;
PCB_HEIGHT = 75 + 4;
PCB_DEPTH = 16 + 5;

WALL_THICKNESS = 5;

CASE_WIDTH = PCB_WIDTH + WALL_THICKNESS * 2;
CASE_HEIGHT = PCB_HEIGHT + WALL_THICKNESS * 2;

CASE_FRONT_DEPTH = PCB_DEPTH + WALL_THICKNESS;

SCREW_OFFSET = 4;

SUPPORT_DEPTH = 6;

USB_WIDTH = 13;
USB_DEPTH = 8;

LCD_WIDTH = 34.5;
LCD_HEIGHT = 58.0;

BUTTON_WIDTH = 7.5;
BUTTON_HEIGHT = 7.5;

module corner() {
	translate([0, 0, -50])
	difference() {
		cube([WALL_THICKNESS + 0.002, WALL_THICKNESS + 0.002, 100]);

		translate([0, 0, -500])
		cylinder(r=WALL_THICKNESS, h=1000);
	}
}

module corners() {
	translate([-CASE_WIDTH / 2 + WALL_THICKNESS, -CASE_HEIGHT / 2 + WALL_THICKNESS, 0])
	mirror([1, 1, 0])
	corner();

	translate([-CASE_WIDTH / 2 + WALL_THICKNESS, CASE_HEIGHT / 2 - WALL_THICKNESS, 0])
	mirror([1, 0, 0])
	corner();

	translate([CASE_WIDTH / 2 - WALL_THICKNESS, -CASE_HEIGHT / 2 + WALL_THICKNESS, 0])
	mirror([0, 1, 0])
	corner();

	translate([CASE_WIDTH / 2 - WALL_THICKNESS, CASE_HEIGHT / 2 - WALL_THICKNESS, 0])
	corner();
}

