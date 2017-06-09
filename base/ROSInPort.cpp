#include "ROSInPort.h"


void
ROSInPort::init(MUSIC::Setup* setup, char* port_name)
{
    ros::init(setup->argc, setup->argv, port_name);
    ros::start();

    ros::NodeHandle n;

}


