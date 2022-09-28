#include <ros/ros.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/Pose.h>

std::string turtle_frame;
std::string reference_frame;
double pos_x,pos_y,theta_;
bool direction = true;
  
void broadcast(){
  ros::NodeHandle node;
  

  
  node.param<std::string>("turtle_frame", turtle_frame, "camera_head");
  node.param<std::string>("reference_frame", reference_frame, "marker_3");
  node.param<double>("pos_x", pos_x, 0);
  node.param<double>("pos_y", pos_y, 0);
  node.param<double>("theta_", theta_, 0);
  
  static tf2_ros::TransformBroadcaster br;
  geometry_msgs::TransformStamped transformStamped;
  
  ROS_INFO("turtle_frame: %s", turtle_frame.c_str());
	ROS_INFO("reference_frame: %s", reference_frame.c_str());
  ros::Rate rate(10.0);
  
  while(ros::ok())
  {
  	if(direction)
  	{
  		ROS_INFO("positive");
  		pos_x = pos_x + 0.01;
  		if(pos_x > 20)
  		{
  			ROS_INFO("switch_negative");
  			direction = false;
  			}
  	}
  	else
  	{
  		ROS_INFO("negative");
  		pos_x = pos_x - 0.01;
  		if(pos_x <= 0.0)
  		{
  			ROS_INFO("switch_positive");
  			direction = true;
  			}
  	}
  	
  	transformStamped.header.stamp = ros::Time::now();
  	transformStamped.header.frame_id = reference_frame;
  	transformStamped.child_frame_id = turtle_frame;
  	transformStamped.transform.translation.x = pos_x;
  	transformStamped.transform.translation.y = pos_y;
  	transformStamped.transform.translation.z = 0.0;
  	tf2::Quaternion q;
  	q.setRPY(0, 0, theta_);
  	transformStamped.transform.rotation.x = q.x();
  	transformStamped.transform.rotation.y = q.y();
  	transformStamped.transform.rotation.z = q.z();
  	transformStamped.transform.rotation.w = q.w();

		
  	br.sendTransform(transformStamped);
  
  	rate.sleep();
  	//ros::spin();
  }
}

int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf2_broadcaster");
	/*
  ros::NodeHandle private_node("~");
  if (! private_node.hasParam("turtle"))
  {
    if (argc != 2){ROS_ERROR("need turtle name as argument"); return -1;};
    turtle_frame = argv[1];
  }
  else
  {
    private_node.getParam("turtle", turtle_frame);
  }
  */
    

  
  //ros::Subscriber sub = node.subscribe(turtle_frame+"/pose", 10, &poseCallback);

	broadcast();
  
  return 0;
};
