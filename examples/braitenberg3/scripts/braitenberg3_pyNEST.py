#!/usr/bin/python

import nest
import numpy as np
import sys
from datetime import datetime
from mpi4py import MPI

comm = MPI.COMM_WORLD

to_ms = lambda t: t * 1000.


nest.ResetKernel()
nest.set_verbosity("M_FATAL")
nest.SetKernelStatus({'resolution': 1.0})
#nest.SetKernelStatus({'print_time': True})

NUM_ENC_NEURONS = 2 

proxy_in = nest.Create('music_event_in_proxy', NUM_ENC_NEURONS)
nest.SetStatus(proxy_in, [{'port_name': 'in', 'music_channel': c} for c in range(NUM_ENC_NEURONS)])
nest.SetAcceptableLatency('in', 1.0)

proxy_out = nest.Create('music_event_out_proxy')
nest.SetStatus(proxy_out, {'port_name': 'out'})

parrot = nest.Create("parrot_neuron", NUM_ENC_NEURONS)

nest.Connect(proxy_in, parrot, 'one_to_one')
for i in range(NUM_ENC_NEURONS):
    nest.Connect([parrot[i]], proxy_out, 'all_to_all', {'music_channel': i})

comm.Barrier()
start = datetime.now()

nest.Simulate(1000000)

end = datetime.now()
dt = end - start
run_time = dt.seconds + dt.microseconds / 1000000.

print 
print
print "RUN TIME:", run_time
print 
print

