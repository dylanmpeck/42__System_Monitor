<h2>ft_gkrellm(System Monitor)</h2>

A simple version of Gkrellm written over 2 days as part of the C++ piscine (42 school's introduction to C++).

This project was done in collaboration with Kura Peng.

<h3>Modules</h3>

* Hostname
* Username
* OS Info
* CPU Info
* DateTime
* CPU Usage
* Ram Usage
* Network

<h3>Features</h3>

* Text based GUI made with Ncurses
* Colored GUI with animated graph made with SDL2
* Select any subset of modules by editing the Configuration.hpp file

<h3>Compiling and Running</h3>

Run "make" to create an executable which will display a text-based gui on the terminal. Run "make gui" to create an executable which will display the SDL2 gui in a separate window. For both cases, run "./ft_gkrellm" to display the system monitor.

<strong>DISCLAIMER:</strong>

This project was done in a short time frame and was written to both compile and scale in size to the computers in the lab we were working in. In order to fix compiling issues, you'll need to brew install SDL2 and SDL2_ttf and replace the .dylib files in SDL2 with your own or properly fix the links.

<h3>Using the configuration file</h3>

Anything that is defined in Configuration.hpp will be created and drawn. To remove and add submodules, simply open up Configuration.hpp and comment out any submodule you don't want to be displayed.

<h3>Screenshots</h3>

![alt-text](https://github.com/dylanmpeck/42__System_Monitor/blob/master/screenshots/ncurses.png "Ncurses")
![alt-text](https://github.com/dylanmpeck/42__System_Monitor/blob/master/screenshots/fullgraph.png "SDL2")

<h3>TODO</h3>

* Make the SDL2 window size and height of the modules scale to the user's screen resolution
* Even out and format the text better (smaller text was distorting) 
