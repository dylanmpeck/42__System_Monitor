
#include "gkrellm.hpp"

static boolean_t        ignore_PPP;
static libtop_tsamp_t   tsamp;

std::string     get_time()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}

std::string     get_username()
{
    struct passwd *p = getpwuid(getuid());  
    
    if (!p)
    {
        std::cerr << "Error when getting username\n";
        ::exit(EXIT_FAILURE);
    }
    return  p->pw_name;
}

std::string     get_hostname()
{
    char hostname[HOST_NAME_MAX+1];

    bzero(hostname, sizeof(hostname));
    if (gethostname(hostname, sizeof(hostname)) == -1)
    {
        std::cerr << "Error when getting hostname \n";
        ::exit(EXIT_FAILURE);
    }
    return hostname;
}

t_os_module *print_os_info()
{
    struct utsname info;
    static t_os_module tom;
    if (uname(&info) == -1)
    {
        std::cerr << "Error when getting system info\n";
          ::exit(EXIT_FAILURE);
    }
    tom.sysname = info.sysname;
    tom.nodename = info.nodename;
    tom.release = info.release;
    tom.version = info.version;
    tom.machine = info.machine;

    /*std::cout << "====== OS info ======" << std::endl;
    std::cout << "System name: " << info.sysname << std::endl;
    std::cout << "Network name: " << info.nodename << std::endl;
    std::cout << "release info: " << info.release << std::endl;
    std::cout << "version info: " << info.version << std::endl;
    std::cout << "Hardware identifier: " << info.machine << std::endl;*/
    return &tom;
} 

static void libtop_p_networks_sample(void)
{
	short network_layer;
	short link_layer;
 	int     mib[6];
     	char *buf = NULL, *lim, *next;
	size_t len;
	struct if_msghdr *ifm;

	tsamp.p_net_ipackets = tsamp.net_ipackets;
	tsamp.p_net_opackets = tsamp.net_opackets;
	tsamp.p_net_ibytes = tsamp.net_ibytes;
	tsamp.p_net_obytes = tsamp.net_obytes;

	tsamp.net_ipackets = 0;
	tsamp.net_opackets = 0;
	tsamp.net_ibytes = 0;
	tsamp.net_obytes = 0;

	mib[0]	= CTL_NET;			// networking subsystem
	mib[1]	= PF_ROUTE;			// type of information
	mib[2]	= 0;				// protocol (IPPROTO_xxx)
	mib[3]	= 0;				// address family
	mib[4]	= NET_RT_IFLIST2;	// operation
	mib[5]	= 0;
	if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0) return;
	if ((buf = reinterpret_cast<char *>(malloc(len))) == NULL) {
		printf("malloc failed\n");
		exit(1);
	}
	if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
		if (buf) free(buf);
		return;
	}

	lim = buf + len;
	for (next = buf; next < lim; ) {
		network_layer = link_layer = 0;
	        ifm = (struct if_msghdr *)next;
		next += ifm->ifm_msglen;

	        if (ifm->ifm_type == RTM_IFINFO2) {
			struct if_msghdr2 	*if2m = (struct if_msghdr2 *)ifm;

			if(if2m->ifm_data.ifi_type==IFT_ETHER)  /* If we've seen any ethernet traffic, */
				ignore_PPP=TRUE; 		/* ignore any PPP traffic (PPPoE or VPN) */


			if(/*We want to count them all in top.*/ 1 
				|| ((if2m->ifm_data.ifi_type!=IFT_LOOP)   /* do not count loopback traffic */
			   && !(ignore_PPP && if2m->ifm_data.ifi_type==IFT_PPP))) { /* or VPN/PPPoE */
				tsamp.net_opackets += if2m->ifm_data.ifi_opackets;
				tsamp.net_ipackets += if2m->ifm_data.ifi_ipackets;
				tsamp.net_obytes   += if2m->ifm_data.ifi_obytes;
				tsamp.net_ibytes   += if2m->ifm_data.ifi_ibytes;
			}
		} 
	}

	if (tsamp.seq == 1) {
		tsamp.b_net_ipackets = tsamp.net_ipackets;
		tsamp.p_net_ipackets = tsamp.net_ipackets;

		tsamp.b_net_opackets = tsamp.net_opackets;
		tsamp.p_net_opackets = tsamp.net_opackets;

		tsamp.b_net_ibytes = tsamp.net_ibytes;
		tsamp.p_net_ibytes = tsamp.net_ibytes;

		tsamp.b_net_obytes = tsamp.net_obytes;
		tsamp.p_net_obytes = tsamp.net_obytes;
	}

	free(buf);
}

t_ram_module *ram(void)
{
    int                     mib[2];
    int64_t                 physical_memory;
    size_t                  length = sizeof(int64_t);
    vm_size_t               page_size;
    mach_port_t             mach_port;
    mach_msg_type_number_t  count;
    vm_statistics64_data_t  vm_stats;
    static t_ram_module     trm;

    mib[0] = CTL_HW;
    mib[1] = HW_MEMSIZE;
    sysctl(mib, 2, &physical_memory, &length, NULL, 0);
    mach_port = mach_host_self();
    count = sizeof(vm_stats) / sizeof(natural_t);
    if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
        KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
                                        (host_info64_t)&vm_stats, &count))
    {
        long long used_memory = ((int64_t)vm_stats.active_count +
                                 (int64_t)vm_stats.inactive_count +
                                 (int64_t)vm_stats.wire_count) *  (int64_t)page_size;
        trm.used = static_cast<int>(used_memory / 1073741824);
    }
    trm.total = static_cast<int>(physical_memory / 1073741824);

    //std::cout << "Ram used: " << trm.used << "G" << std::endl;
    //std::cout << "total RAM: " << trm.total << "G" << std::endl;
    return &trm;
}

t_cpu_module *cpu(void)
{
    FILE * fpIn = popen("/usr/bin/top | head -4 | tail -1", "r");
    static t_cpu_module tcm;

    if (fpIn)
    {
        char buf[512];
        while(fgets(buf, sizeof(buf), fpIn) != NULL)
        {
            std::string str(buf);
            std::stringstream user;
            user << str.substr(11, 6);
            std::stringstream sys ;
            sys  <<  str.substr(str.find("user") + 6, 6);
            std::stringstream idle;
            idle << str.substr(str.find("sys") + 5, 5);

            if (idle.str().find("%") == std::string::npos)
            {
                idle.clear();
                idle << (idle.str() + "%");
            }
            user >> tcm.user;
            sys >> tcm.sys;
            idle >> tcm.idle;

            //std::cout << tcm.user << std::endl;
            //std::cout << tcm.sys  << std::endl;
            //std::cout << tcm.idle << std::endl;
            pclose(fpIn);
            return &tcm;
        }
    }
    return NULL;
}

t_network_module    *network(void)
{
    libtop_p_networks_sample();
    static t_network_module tnm;
    
    std::stringstream network_mb_in; 
    std::stringstream network_mb_out;
    std::stringstream packets_mb_in; 
    std::stringstream packets_mb_out;

    network_mb_in << (tsamp.net_ibytes / 1000000) << " mb"; 
    network_mb_out << (tsamp.net_obytes / 1000000) << " mb";
    packets_mb_in << tsamp.net_ipackets << " packets";
    packets_mb_out << tsamp.net_opackets << " packets";

    tnm.network_mb_in  = network_mb_in.str();
    tnm.network_mb_out = network_mb_out.str();
    tnm.packets_mb_in  = packets_mb_in.str();
    tnm.packets_mb_out = packets_mb_out.str();

    //std::cout << tnm.network_mb_in  << std::endl;
    //std::cout << tnm.network_mb_out << std::endl;
    //std::cout << tnm.packets_mb_in  << std::endl;
    //std::cout << tnm.packets_mb_out << std::endl;
    return &tnm;
}

t_cpuinfo_module    *cpuinfo(void)
{
    char buffer[256];
    buffer[255] = '\0';
    int cores;
    int threads;
    size_t size = 255;
    sysctlbyname("machdep.cpu.brand_string", &buffer, &size, NULL, 0);
    sysctlbyname("machdep.cpu.core_count", &cores, &size, NULL, 0);
    sysctlbyname("machdep.cpu.thread_count", &threads, &size, NULL, 0);
    static t_cpuinfo_module tcim;
    int i = 0;
    for (; i < 255 && buffer[i]; i++)
    {
        if (buffer[i] == '@')
        {
            tcim.brand.pop_back();
            break;
        }
        tcim.brand.push_back(buffer[i]);
    }
    i += 2;
    for (; i < 255 && buffer[i]; i++)
        tcim.clock.push_back(buffer[i]);
    tcim.cores = cores;
    tcim.threads = threads;
    return (&tcim);
}
