// Based on model by death_metal
// https://www.thingiverse.com/thing:201745

// Modified by chapulina
// https://www.thingiverse.com/chapulina

module wheel(dia=30, tyre=7.5, width=15) {
	union() {
		translate([0,-width/2,0]) {
			rotate([-90,0,0]) {
/*
				// rim
				difference() {
					cylinder(h=width, r1=dia, r2=dia);
					translate([0,0,-0.5])
					cylinder(h=width + 1, r1=dia - tyre, r2=dia - tyre);
				}
*/

                rotate_extrude(convexity = 10, $fn = 32)
                translate([dia*0.9, width*0.5, 0])
                circle(r = width*0.2, $fn = 12);


				// hub
				cylinder(h=width, r1=dia/6, r2=dia/6);

				// wheelnut
				translate([0,0,-width/2])
				cylinder(h=width * 2, r1=dia/10, r2=dia/9);
			}

			// spokes
			translate([0,width/2,0])
			spokes(length=dia - 1, count=10, dia=width*0.1);
		}
	}
}

module spokes(length=30, count=10, dia=2.5) {
	angle = 360 / count;
	for (i = [0 : count]) {
		rotate([angle * i,0,90])
		cylinder(h=length, r1=dia/4, r2=dia);
	}
}

module frame(length, dia=5) {
	// crossbar
	translate([0, 0, length * 0.5])
	rotate([0,90,0])
	cylinder(h=length * 0.5, r1=dia, r2=dia);

	// downtube
	cylinder(h=length * 0.6, r1=dia*1.5, r2=dia*1.5);

	// back bottom
	translate([1 - length/2, 1-dia , 0])
	rotate([0,90,-5])
	cylinder(length * 0.5, r1=dia/2, r2=dia);
	translate([1 - length/2, dia , 0])
	rotate([0,90,5])
	cylinder(length * 0.5, r1=dia/2, r2=dia);

	// back top
	translate([1 - length/2, 1-dia , 0])
	rotate([0,45,-2.5])
	cylinder(length * 0.7, r1=dia/2, r2=dia);
	translate([1 - length/2, dia , 0])
	rotate([0,45,2.5])
	cylinder(length * 0.7, r1=dia/2, r2=dia);

	// bottom support
	rotate([0,45,0])
	cylinder(h=length * 0.7, r1=dia, r2=dia);

	// seat
	translate([0,0,length*0.7])
	seat(length * 0.3, dia = length * 0.04);
}

module front(length, dia, has_wheel = true) {

    // handlebars
	translate([length * 0.5, (length * 0.75)/2, length * 0.8])
	handlebars(length * 0.75, dia= length * 0.04);

    // steering
	translate([length * 0.5,0,length * 0.3])
	cylinder(h=length * 0.3, r1=dia*1.5, r2=dia*1.5);

	// forks
	translate([length * 0.5 ,dia * 1.2,-length*0.05])
	cylinder(h=length * 0.4, r1=dia/2, r2=dia);
	translate([length * 0.5,-dia * 1.2,-length*0.05])
	cylinder(h=length * 0.4, r1=dia/2, r2=dia);

    if (has_wheel) {
        translate([length * 0.5, 0, -length * 0.05])
        wheel(dia = length * 0.3, tyre = length * 0.075, width = length * 0.15);
    }
}

module crank(length, width) {

	rotate([90,0,0]) {
		cylinder(h=width/5, r1=length, r2=length);
		translate([0,0,-width])
		cylinder(h=width, r1=length/2, r2=length/2);
	}

	// crank arms
	translate([length * 1.75/2,width,0])
	cube([length * 1.75, length/4, length/2], center=true);

	translate([-(length * 1.75/2),-(width/5),0])
	cube([length * 1.75, length/4, length/2], center=true);
}

module seat(length, dia=2.5) {
	rotate([0,90,0])
	difference() {
		translate([0,0,-length/2])
		cylinder(h=length, r1=length/2, r2=length/3);

		translate([length/2 -0.5, 0,0])
		cube(length + 1, center=true);
	}
	translate([0,0,1-length/2 ])
	cylinder(h=length/2, r1=dia, r2=dia);
}


module handlebars(length, dia=2.5) {
	// shaft
	translate([0,-length/2,-length/3])
	cylinder(h=length/3, r1=dia, r2=dia);

	// bar
	rotate([90,0,0])
	cylinder(h=length, r1=dia, r2=dia);

	// ends
	translate([dia/2 - 1.5,-dia,0])
	rotate([0,-90,0])
	cylinder(h=length*0.3, r1=dia,r2=dia/2);

	translate([dia/2 - 1.5,-length + dia,0])
	rotate([0,-90,0])
	cylinder(h=length*0.3, r1=dia,r2=dia/2);
}

union() {
    l = 200;
    d = l/20;

    // frame
	frame(length=l, dia=d);

    // crank
	translate([0, -l * 0.1, 0])
	crank(l * 0.15, l * 0.25);

    // front
    rotate([0,-20,0])
    translate([l * 0.2, 0, -l * 0.2])
    front(l, d, true);

    // back wheel
	translate([-l * 0.5, 0, 0])
	wheel(dia = l * 0.3, tyre = l * 0.075, width = l * 0.15);
}
