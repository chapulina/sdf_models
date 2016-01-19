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

