# RAMROS

## Simulation Setup

1. Create a workspace directory: `mkdir -p {workspace_name}/src`
2. Change directory to `/{workspace_name}/src`.
3. Clone the package into the `src` folder by cloning the repository `git clone https://github.com/ShahhhVihaan/RAMROS.git`.
4. Install dependencies by first changing the directory back to `../{workspace_name}` and then entering the following commands:
    ```
    rosdep update
    rosdep install --rosdistro $noetic --ignore-src--from-paths src
    ```
5. Build the workspace using the command `catkin_make` after the dependencies are installed in the same directory as before `../{workspace_name}`.


In every terminal use the `source` command to source the bash script: `source ../{workspace_name}/devel/setup.bash`

---

In your **first terminal**, after sourcing the bash script, open gazebo with a spawned model of the UR3, using the command
```
roslaunch ur_gazebo ur3_bringup.launch paused:=true
```
This will open a paused model, allowing us to ensure that the controllers are set up correctly without encountering any errors in the subsequent steps. Additionally, the model is elevated from the floor to prevent any potential collision issues.

---
In your **second terminal**, after sourcing the bash script, enter the following commands:
```
gz physics -g 0
```
```
gz world -p 0
```
```
gz physics -g -9.81
```
As soon as Gazebo's physics engine starts running, the joints of the robot are immediately subjected to the effects of gravity. If the controller_manager fails to load a controller quickly enough to regulate the joints, which is often the case, the robot will sink to the ground. To learn more about this issue, you can refer to this page on [GitHub](https://github.com/ros-industrial/universal_robot/issues/627).

After executing the aforementioned three instructions using the gz command-line tool, the UR3 and its associated controllers should load without any issues. You can proceed to set up the MoveIt! planning package in the same terminal by running the command:
```
roslaunch ur3_moveit_config moveit_planning_execution.launch sim:=true
```
The MoveIt package provides a comprehensive motion planning and manipulation framework for controlling robotic manipulators. It offers a range of functionalities such as motion planning, inverse kinematics, trajectory generation, collision checking, and control.

Once you see the message "You can start planning now!", it indicates that the MoveIt planning package has been successfully set up and is ready to be used. You can now proceed with your planning tasks in the simulation environment.

---

Running the following command will start up RViz, a 3D visualization tool used in ROS, with a pre-configured environment that includes the MoveIt! Motion Planning plugin. This plugin enables RViz to interact with the MoveIt planning package and visualize the robot's motion planning, including its configuration, trajectory, and collision checking. By launching RViz with this configuration, you can visualize the robot and its environment in the simulation and use RViz's tools to plan the robot's motion.

In your **third terminal**, after sourcing the bash script, for starting up RViz with a configuration including the MoveIt! Motion Planning plugin run:
```
roslaunch ur3_moveit_config moveit_rviz.launch
```
