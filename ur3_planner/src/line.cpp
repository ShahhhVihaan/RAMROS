#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>
#include <tf/tf.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "basic");
  ros::NodeHandle node_handle;
  ros::AsyncSpinner spinner(1);
  spinner.start();

  moveit::planning_interface::MoveGroupInterface group("manipulator");

  int count = 1;
  geometry_msgs::Pose pose_goal;

  while (ros::ok())
  {
    // Odd iteration configuration
    if (count % 2 == 1)
    {
      pose_goal.orientation.w = 0.0;
      pose_goal.position.x = 0.4;
      pose_goal.position.y = 0.15;
      pose_goal.position.z = 0.2;
      group.setPoseTarget(pose_goal);
      group.move();
      ros::Duration(2).sleep();
    }
    // Even iteration configuration
    else
    {
      pose_goal.orientation.w = 0.0;
      pose_goal.position.x = 0.2;
      pose_goal.position.y = 0.15;
      pose_goal.position.z = 0.2;
      group.setPoseTarget(pose_goal);
      group.move();
      ros::Duration(2).sleep();
    }

    count++;
  }

  ros::shutdown();
  return 0;
}
