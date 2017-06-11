#include "ROSOutPort.h"


void
ROSOutPort::init(MUSIC::Setup* setup, char* port_name)
{

    this->port_name = port_name;

}

void
ROSOutPort::initROS(int argc, char** argv)
{
    ros::init(argc, argv, port_name);
    ros::start();
}


