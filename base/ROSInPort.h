#ifndef ROS_IN_PORT_H
#define ROS_IN_PORT_H

#include <music.hh>
#include "InPort.h"

#include <ros/ros.h>

#define DEBUG_OUTPUT false 

class ROSInPort : public InPort
{

    public:
        ros::NodeHandle* ros_node;

        void init(MUSIC::Setup* setup, char* port_name);
        void initROS(int argc, char** argv, std::string port_name);
        

    private:

};

#endif // ROS_IN_PORT_H 


