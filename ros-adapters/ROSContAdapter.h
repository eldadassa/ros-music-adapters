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

#include "sys/time.h"

class ROSContAdapter : public Adapter
{
    public:
        ROSContAdapter();
        void init(int argc, char** argv);
        void tick();
        void asyncTick();

    private:

};

#endif // ROS_CONT_ADAPTER_H

