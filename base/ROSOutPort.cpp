#include "ROSOutPort.h"


void
ROSOutPort::init(MUSIC::Setup* setup, char* port_name)
{
}

void
ROSOutPort::initROS(int argc, char** argv, std::string port_name)
{
    ros::init(argc, argv, port_name);
    ros::start();
    ros_node = new ros::NodeHandle();
}


