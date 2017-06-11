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
        RTClock* clock;
        double command_update_rate;
        string mapping_filename;
        Json::Value json_mapping; 
        int* msg_map;
	    double min_msg;
  	    double max_msg;
        ros::Publisher publisher;

        void readMappingFile();
        void sendROS();

};

#endif // CONT_ROS_ADAPTER_H

