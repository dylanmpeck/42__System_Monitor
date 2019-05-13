
#include "Configuration.hpp"
#include <iostream>
#include <vector>
#include "GraphicsDisplay.hpp"
#include "HostnameModule.hpp"
#include "DateTimeModule.hpp"
#include "CPUModule.hpp"
#include "UsernameModule.hpp"
#include "OSModule.hpp"
#include "RamModule.hpp"
#include "NetModule.hpp"
#include "CPUInfoModule.hpp"

int main()
{
	srand(time(0));
	
	std::vector<IMonitorModule *> modules;

#ifdef _HostnameModule
	modules.push_back(new HostnameModule());
#endif

#ifdef _UsernameModule 
	modules.push_back(new UsernameModule());
#endif

#ifdef _OSModule 
	modules.push_back(new OSModule());
#endif

#ifdef _DateTimeModule 
	modules.push_back(new DateTimeModule());
#endif

#ifdef _CPUModule 
	modules.push_back(new CPUModule());
#endif

#ifdef _RamModule 
	modules.push_back(new RamModule());
#endif

#ifdef _NetModule 
	modules.push_back(new NetModule());
#endif

#ifdef _CPUInfoModule 
	modules.push_back(new CPUInfoModule());
#endif
	GraphicsDisplay gd(modules);
	gd.render();

	for (unsigned long i = 0; i < modules.size(); i++)
		delete modules[i];
	return (0);
}
