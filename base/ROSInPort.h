#ifndef ROS_IN_PORT_H
#define ROS_IN_PORT_H

#include <music.hh>
#include <ros/ros.h>
#include "InPort.h"

#include "jsoncpp/json/json.h"

#define DEBUG_OUTPUT false 

const std::string DEFAULT_ROS_TOPIC = "/laserscan";
const double DEFAULT_SENSOR_UPDATE_RATE = 30;
const std::string DEFAULT_ROS_NODE_NAME = "ros_sensor_node";

class ROSInPort : public InPort
{

    public:
        void init(MUSIC::Setup* setup, char* port_name);

    private:

};

#endif // ROS_IN_PORT_H 


