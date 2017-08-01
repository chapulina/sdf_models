# Run

1. Compile the plugins

    cd plugins
    mkdir build
    cd build
    cmake ..
    make
    export GAZEBO_PLUGIN_PATH=`pwd`:$GAZEBO_PLUGIN_PATH

2. Open the world

    cd ../..
    gazebo puzzle.world

# TODO

* Display joint angle on GUI

* Force fix other center joints when applying torque to one of them (e.g. fix DRLFB when pressing U)

* Hotkeys for applying force to strategic links like with the apply force dialog.

