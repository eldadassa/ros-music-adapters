#ifndef ROS_CONT_ADAPTER_H
#define ROS_CONT_ADAPTER_H

#include <iostream>
#include <map>
#include <math.h>

#include <music.hh>
#include <mpi.h>

#include "Adapter.h"
#include "ROSInPort.h"
#include "ContOutPort.h"

#include <ros/ros.h>
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Float64MultiArray.h"
#include "nav_msgs/Odometry.h"

#include "sys/time.h"

enum msg_types {Laserscan, Twist, Float64MultiArray, Odom}; 

class ROSContAdapter : public Adapter
{
    public:
        ROSContAdapter();
        void init(int argc, char** argv);
        void tick();
        void asyncTick();

    private:
        msg_types msg_type;
        std::string ros_topic;
        RTClock* clock;
        double sensor_update_rate;

        void laserscanCallback(const sensor_msgs::LaserScanConstPtr& msg);
        void twistCallback(const geometry_msgs::Twist msg);
        void float64MultiArrayCallback(const std_msgs::Float64MultiArray msg);
        void odomCallback(const nav_msgs::Odometry::ConstPtr& msg);


};

#endif // ROS_CONT_ADAPTER_H

