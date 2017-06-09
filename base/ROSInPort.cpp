#include "ROSInPort.h"


void
ROSInPort::init(MUSIC::Setup* setup, char* port_name)
{
    //TODO pass real argv, argc??
    int argc = 1;
    char *argv = new char[0];
    ros::init(argc, &argv, port_name);
    ros::start();

    ros::NodeHandle n;

}


