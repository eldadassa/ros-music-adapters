#ifndef ROS_IN_PORT_H
#define ROS_IN_PORT_H

#include <music.hh>
#include "InPort.h"

#include <ros/ros.h>

#define DEBUG_OUTPUT false 

const std::string DEFAULT_ROS_TOPIC = "/laserscan";
const double DEFAULT_SENSOR_UPDATE_RATE = 30;
const std::string DEFAULT_ROS_NODE_NAME = "ros_sensor_node";

class ROSInPort : public InPort
{

    public:
        ros::NodeHandle ros_node;

        void init(MUSIC::Setup* setup, char* port_name);
        void initROS(int argc, char** argv);
        
        template<class M, class T>
        void subscribe(std::string topic, void(T::*fp)(M));

    private:
        char* port_name;

};

#endif // ROS_IN_PORT_H 


