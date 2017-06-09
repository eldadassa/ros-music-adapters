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

    Adapter::init(argc, argv);

    // config needed for this specific adapter
    
}

void
ROSContAdapter::tick()
{
}

void
ROSContAdapter::asyncTick()
{
}

