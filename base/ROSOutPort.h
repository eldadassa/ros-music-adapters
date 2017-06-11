#ifndef ROS_OUT_PORT_H
#define ROS_OUT_PORT_H

#include <music.hh>
#include "OutPort.h"

#include <ros/ros.h>

#define DEBUG_OUTPUT false 


class ROSOutPort : public OutPort
{

    public:
        ros::NodeHandle* ros_node;

        void init(MUSIC::Setup* setup, char* port_name);
        void initROS(int argc, char** argv, std::string port_name);
        

    private:

};

#endif // ROS_OUT_PORT_H 


