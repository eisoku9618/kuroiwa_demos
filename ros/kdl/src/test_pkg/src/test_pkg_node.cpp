#include <ros/ros.h>
#include <kdl_parser/kdl_parser.hpp>

int main(int argc, char **argv) {
  ros::init(argc, argv, "test", ros::init_options::AnonymousName);
  const ros::NodeHandle nh;

  // get robot_description parameter
  std::string robot_description_text;
  if (!nh.getParam("/robot_description", robot_description_text)) {
    ROS_FATAL("could not find /robot_description");
    return -1;
  }

  // parse urdf by using kdl_parser
  KDL::Tree robot_tree;
  kdl_parser::treeFromString(robot_description_text, robot_tree);
  const std::map<std::string, KDL::TreeElement> robot_segment = robot_tree.getSegments();

  // access each data by using iterator
  for(std::map<std::string, KDL::TreeElement>::const_iterator itr = robot_segment.begin();
      itr != robot_segment.end(); ++itr) {
    // get link name from std::map
    const std::string link_name = itr->first;
    // get link parameters
    const KDL::RigidBodyInertia rigid_body_inertia = itr->second.segment.getInertia();
    // get Mass of link
    const double mass = rigid_body_inertia.getMass();
    // get Center of Gravity parameters
    const KDL::Vector cog_point = rigid_body_inertia.getCOG();
    // get Center of Gravity position
    const double cog_point_x = cog_point.x();
    const double cog_point_y = cog_point.y();
    const double cog_point_z = cog_point.z();
    ROS_INFO_STREAM(link_name << " " << cog_point_x << " " << cog_point_y << " " << cog_point_z);
  }
}
