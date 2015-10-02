// ROS specific includes
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_ros/point_cloud.h>
// PCL specific includes
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/PCLPointCloud2.h>

ros::Publisher pub;

void msgs_cb(const std_msgs::String::ConstPtr& msg){
	sensor_msgs::PointCloud2 output;
	pcl::PointCloud<pcl::PointXYZI>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZI>());

	pcl::io::loadPCDFile(msg->data,*cloud);

	pcl::toROSMsg(*cloud, output);
	output.header.frame_id="base_link";
	output.header.stamp = ros::Time::now();

	pub.publish(output);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "viewer");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("filename", 1000, msgs_cb);
	pub = n.advertise<sensor_msgs::PointCloud2>("output",1);
	ros::spin();
	return 0;
}
