#ifndef CONT_ROS_ADAPTER_H
#define CONT_ROS_ADAPTER_H

#include <iostream>
#include <math.h>

#include <music.hh>
#include <mpi.h>

#include "Adapter.h"
#include "ContInPort.h"
#include "ROSOutPort.h"

#include <ros/ros.h>
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Float64MultiArray.h"
#include "nav_msgs/Odometry.h"

#include <json/json.h>
#include <fstream>
#include "sys/time.h"

enum msg_types {Float64MultiArray, Twist};

const msg_types DEFAULT_MESSAGE_TYPE = Float64MultiArray;
const std::string DEFAULT_ROS_TOPIC = "/cmd_vel";
const double DEFAULT_COMMAND_UPDATE_RATE = 20.;
const std::string DEFAULT_ROS_NODE_NAME = "cmd_out";
const std::string DEFAULT_MAPPING_FILENAME = "mapping.json";

class ContROSAdapter : public Adapter
{
    public:
        ContROSAdapter();
        void init(int argc, char** argv);
        void tick();
        void asyncTick();

    private:
        msg_types msg_type;
        std::string ros_topic;
        std::string ros_node_name;
        RTClock* clock;
        double command_update_rate;
        string mapping_filename;
        Json::Value json_mapping; 
        double* msg_map[6];
        double null;
	    double min_msg;
  	    double max_msg;
        ros::Publisher publisher;


        void readMappingFile();
        void sendROS();

};

#endif // CONT_ROS_ADAPTER_H

