#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2/LinearMath/Quaternion.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf2_add_frame");
  ros::NodeHandle node;

  tf2_ros::TransformBroadcaster tfb;
  geometry_msgs::TransformStamped transformStamped;
	std::string turtle_frame;
	std::string reference_frame;
	
  node.param<std::string>("turtle_frame", turtle_frame, "camera_head");
  node.param<std::string>("reference_frame", reference_frame, "marker_3");
  transformStamped.header.frame_id = reference_frame;
  transformStamped.child_frame_id = turtle_frame;
  //transformStamped.transform.translation.x = 0.0;
  

  ros::Rate rate(10.0);
  while (node.ok()){
    transformStamped.header.stamp = ros::Time::now();
    
    transformStamped.transform.translation.x = 2.0*sin(ros::Time::now().toSec());
    transformStamped.transform.translation.y = 2.0;
  	transformStamped.transform.translation.z = 0.0;
  	tf2::Quaternion q;
    q.setRPY(0, 0, 0);
  	transformStamped.transform.rotation.x = q.x();
  	transformStamped.transform.rotation.y = q.y();
  	transformStamped.transform.rotation.z = q.z();
  	transformStamped.transform.rotation.w = q.w();
  	
    tfb.sendTransform(transformStamped);
    rate.sleep();
    printf("sending\n");
  }

};
