#include "ROSContAdapter.h"

int
main(int argc, char** argv)
{

    ROSContAdapter* adapter = new ROSContAdapter();
    adapter->init(argc, argv);

    adapter->run(true);

    
    adapter->finalize();
}

ROSContAdapter::ROSContAdapter()
{
    port_in = new ROSInPort();
    port_out = new ContOutPort();

}

void ROSContAdapter::init(int argc, char** argv)
{
    std::cout << "ros cont adapter init" << std::endl;

    Adapter::init(argc, argv);

    // config needed for this specific adapter
    
    std::string _msg_type;
    setup->config("message_type", &_msg_type);
    setup->config("ros_topic", &ros_topic);
    setup->config("sensor_update_rate", &sensor_update_rate);
    setup->config("ros_node_name", &ros_node_name);

    static_cast<ROSInPort*>(port_in)->initROS(argc, argv, ros_node_name);

    if (_msg_type.compare("Laserscan") == 0){
        msg_type = Laserscan;
        sub = static_cast<ROSInPort*>(port_in)->ros_node->subscribe(ros_topic, 1000, &ROSContAdapter::laserscanCallback, this);
    }
    else if (_msg_type.compare("Twist") == 0){
        msg_type = Twist;
        sub = static_cast<ROSInPort*>(port_in)->ros_node->subscribe(ros_topic, 1000, &ROSContAdapter::twistCallback, this);
    }
    else if (_msg_type.compare("FloatArray") == 0){
        msg_type = Float64MultiArray;
        sub = static_cast<ROSInPort*>(port_in)->ros_node->subscribe(ros_topic, 1000, &ROSContAdapter::float64MultiArrayCallback, this);
    }
    else if (_msg_type.compare("Odom") == 0){
        msg_type = Odom;
        sub = static_cast<ROSInPort*>(port_in)->ros_node->subscribe(ros_topic, 1000, &ROSContAdapter::odomCallback, this);
    }
    else
    {
        std::cout << "ERROR: msg type unknown" << std::endl;
        finalize();
    }
    

    std::cout << "sensor " << sensor_update_rate << std::endl;
    clock = new RTClock( 1. / (sensor_update_rate * rtf) );
}

void
ROSContAdapter::tick()
{
}

void
ROSContAdapter::asyncTick()
{

    ros::spinOnce();
    clock->sleepNext();
}

void
ROSContAdapter::laserscanCallback(const sensor_msgs::LaserScanConstPtr& msg)
{
    for (unsigned int i = 0; i < msg->ranges.size(); ++i)
    {
      // scale data between -1 and 1
      // TODO: catch exception if ranges.size not width of port
      if (isinf(msg->ranges.at(i))){
	port_out->data[i] = 1.;
      }
      else{
	port_out->data[i] = ((msg->ranges.at(i) - msg->range_min) / (msg->range_max - msg->range_min) ) * 2 - 1;
      }
    }
}

void
ROSContAdapter::twistCallback(const geometry_msgs::Twist msg)
{

    port_out->data[0] = msg.linear.x;
    port_out->data[1] = msg.angular.z;
    for (int i = 0; i < 2; ++i) // Twist msg has 2 dimensions
    {
        // limit data between -1 and 1
        if (port_out->data[i] > 1)
            port_out->data[i] = 1;
        else if (port_out->data[i] < -1)
            port_out->data[i] = -1;

    }

}

void
ROSContAdapter::float64MultiArrayCallback(const std_msgs::Float64MultiArray msg)
{

    for (int i = 0; i < port_out->data_size; ++i)
    {
        port_out->data[i] = msg.data[i];
    }

}

void 
ROSContAdapter::odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
    
    port_out->data[0] = msg->pose.pose.position.x;
    if (port_out->data_size > 1)
    {
        port_out->data[1] = msg->pose.pose.position.y;
    }
    if (port_out->data_size > 2)
    {
        port_out->data[2] = msg->pose.pose.position.z;
    }


   }



