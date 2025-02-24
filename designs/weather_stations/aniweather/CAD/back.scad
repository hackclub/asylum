include <common.scad>

module PCB_Hole() {
	cube([PCB_WIDTH, PCB_HEIGHT, PCB_DEPTH], true);
}

module screw() {
	translate([0, 0, -PCB_DEPTH / 2 + WALL_THICKNESS - 0.0001])

	difference() {
		cylinder(h=SUPPORT_DEPTH, d=7, $fn=50);
		cylinder(h=SUPPORT_DEPTH+2, d=3, $fn=50);
	}
}

module case() {
	difference() {
		cube([CASE_WIDTH, CASE_HEIGHT, CASE_FRONT_DEPTH], true);

		translate([0, 0, WALL_THICKNESS + 0.0001]) PCB_Hole();

		// Wemos
		translate([CASE_WIDTH / 2, 2 - USB_WIDTH/2, USB_DEPTH/2])
		cube([30, USB_WIDTH + 5, USB_DEPTH], true);

		// Battery
		translate([-CASE_WIDTH / 2, 7.5 + USB_WIDTH/2, USB_DEPTH/2])
		cube([30, USB_WIDTH + 5, USB_DEPTH], true);

		// Saber!
		mirror([1,0,0])
		resize(newsize=[CASE_WIDTH - 0.4, CASE_HEIGHT - 0.4, 0])
		translate([-0.2, -0.2, -CASE_FRONT_DEPTH/2 + 0.5 - 0.04])
		linear_extrude(height=1, center=true, convexity = 15)
		import(file="saber.svg", center=true, $fn=400);
	}
}

union() {
translate([(PCB_WIDTH - 4) / 2 - SCREW_OFFSET, (PCB_HEIGHT - 4) / 2 - SCREW_OFFSET, 0]) screw();
translate([(PCB_WIDTH - 4) / 2 - SCREW_OFFSET, -(PCB_HEIGHT - 4) / 2 + SCREW_OFFSET, 0]) screw();
translate([-(PCB_WIDTH - 4) / 2 + SCREW_OFFSET, (PCB_HEIGHT - 4) / 2 - SCREW_OFFSET, 0]) screw();
translate([-(PCB_WIDTH - 4) / 2 + SCREW_OFFSET, -(PCB_HEIGHT - 4) / 2 + SCREW_OFFSET, 0]) screw();

difference() {
	case();

	corners();
}
}

