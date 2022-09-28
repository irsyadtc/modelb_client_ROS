#include <ros/ros.h>
#include <tf2_ros/static_transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <cstdio>
#include <tf2/LinearMath/Quaternion.h>


std::string child_frame;
std::string parent_frame;
double pos_x,pos_y,pos_z;
double roll,pitch,yaw;
int main(int argc, char **argv)
{
  ros::init(argc,argv, "my_static_tf2_broadcaster");
  ros::NodeHandle node;
  
  node.getParam("child_frame", child_frame);
  node.getParam("parent_frame", parent_frame);
  //node.param<std::string>("chlid_frame", child_frame, "marker_3");
  //node.param<std::string>("parent_frame", parent_frame, "map");
  node.param<double>("pos_x", pos_x, 5);
  node.param<double>("pos_y", pos_y, 3);
  node.param<double>("pos_z", pos_z, 0);
  node.param<double>("roll", roll, 0);
  node.param<double>("pitch", pitch, 0);
  node.param<double>("yaw", yaw, 0);
  
  static tf2_ros::StaticTransformBroadcaster static_broadcaster;
  geometry_msgs::TransformStamped static_transformStamped;

  static_transformStamped.header.stamp = ros::Time::now();
  static_transformStamped.header.frame_id = parent_frame;
  static_transformStamped.child_frame_id = child_frame;
  static_transformStamped.transform.translation.x = pos_x;
  static_transformStamped.transform.translation.y = pos_y;
  static_transformStamped.transform.translation.z = pos_z;
  tf2::Quaternion quat;
  quat.setRPY(roll, pitch, yaw);
  static_transformStamped.transform.rotation.x = quat.x();
  static_transformStamped.transform.rotation.y = quat.y();
  static_transformStamped.transform.rotation.z = quat.z();
  static_transformStamped.transform.rotation.w = quat.w();
  static_broadcaster.sendTransform(static_transformStamped);
  ROS_INFO("Spinning until killed publishing %s to %s", child_frame.c_str(),parent_frame.c_str());
  ros::spin();
  return 0;
};
