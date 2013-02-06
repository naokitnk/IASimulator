IASimulator
===========

*Insured Access Simulator*

This software is developed for the ongoing research on Insured Access.  
All functionalities are not necessarily implemented, nor are the codes thoroughly tested.  
Take full responsibility for your use of the software. 


Installation
------------

IASimulator is written in C++ and uses some functionalities of [Boost C++ Libraries][boost].  
Thus, you need to install [Boost C++ Libraries][boost] before building IASimulator.
[boost]: http://www.boost.org

To build IASimulator:

    $ ./configure
    $ make
    # make install

`SimulationTestbed` is the binary you use to run the simulator.


Usage
-----

To run the simulator:

    $ SimulationTestbed sim_type param_filename out_filename [count]

There are three simulation types specified by the `sim_type` parameter.

* *One-Round Simulation*: Multiple runs of one-round simulation. Specify `0` for the `sim_type` parameter. You need to specify the number of runs for the `count` parameter.
* *Discrete Event Simulation (Single)*: Single run of discrete event simulation. Specify `1` for the `sim_type` parameter.
* *Discrete Event Simulation (Multiple)*: Multiple runs of discrete event simulation. Specify `2` for the `sim_type` parameter.  You need to specify the number of runs for the `count` parameter.

`parameters_sample.xml` is provided as an example of the parameter file specified by the `param_filename` parameter.


References
----------

* Naoki Tanaka, Marianne Winslett, Adam J. Lee, David K. Y. Yau, Feng Bao: "Insured Access: An Approach to Ad-hoc Information Sharing for Virtual Organizations", Proceedings of the third ACM Conference on Data and Application Security and Privacy (CODASPY), San Antonio, TX, USA, February 2013.


License
-------

Copyright (c) 2013, Naoki Tanaka  
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
