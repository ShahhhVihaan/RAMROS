#!/bin/bash

# Path to the script you want to source
script_path="/home/vihaan/Projects/urbot_ws/devel/setup.bash"

# Check if the script exists
if [ -f "$script_path" ]; then
  # Source the script
  source "$script_path"
else
  echo "Script not found: $script_path"
  exit 1
fi

# Run the roslaunch command
roslaunch ur_gazebo ur3_bringup.launch paused:=true &
# Wait for 5 seconds
sleep 2

# Open a new terminal window and execute the command
gnome-terminal -- bash -c "gz physics -g 0,0,0; gz world -p 0; gz physics -g 0,0,-9.81"
source "$script_path"
roslaunch ur3_moveit_config moveit_planning_execution.launch sim:=true &

# Open a new terminal window and execute the command
gnome-terminal -- bash -c "source $script_path; roslaunch ur3_moveit_config moveit_rviz.launch"