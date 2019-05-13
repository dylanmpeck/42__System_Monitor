#ifndef GKRELLM_HPP
#define GKRELLM_HPP

// for username / hostname
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <unistd.h>
#include <mach/boolean.h>
#include <mach/host_info.h>
#include <mach/task_info.h>
#include <mach/vm_types.h>
#include <stdarg.h>
#include <sys/time.h>
#include <sys/sysctl.h>
#include <string>
#include <stdio.h>
#include <time.h>
#include <mach/mach_init.h>
#include <mach/mach_error.h>
#include <mach/mach_host.h>
#include <mach/vm_map.h>
#include <ctype.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <sys/types.h>
#include <net/route.h>
#include <net/if.h>
// for os info
#include <sys/utsname.h>

#include <net/if_types.h>
#include <fstream>

typedef struct {
	/*
	 * Sample sequence number, incremented for every sample.  The first
	 * sample has a sequence number of 1.
	 */
	uint32_t		seq;

	/* Number of processes. */
	uint32_t		nprocs;

	/* CPU loads. */
	host_cpu_load_info_data_t cpu;
	host_cpu_load_info_data_t b_cpu;
	host_cpu_load_info_data_t p_cpu;

	/* Load averages for 1, 5, and 15 minutes. */
	float			loadavg[3];

	/* Start time, previous sample time, and current sample time. */
	struct timeval		time;
	struct timeval		b_time;
	struct timeval		p_time;

	/* Total number of threads. */
	uint32_t		threads;

	/* VM page size. */
	vm_size_t		pagesize;

	/* Physical memory size. */
	uint64_t		memsize;

	/* VM statistics. */
	vm_statistics64_data_t	vm_stat;
	vm_statistics64_data_t	b_vm_stat;
	vm_statistics64_data_t	p_vm_stat;

	boolean_t		purgeable_is_valid;

	/* Swap usage */
	struct xsw_usage	xsu;
	boolean_t		xsu_is_valid;

	/* Total number of memory regions. */
	uint32_t		reg;

	/* Total shared, private, virtual sizes. */
	uint64_t		rshrd;
	uint64_t		rprvt;
	uint64_t		vsize;

	/* Total private resident memory used by frameworks. */
	uint64_t		fw_private;

	/* Total virtual memory used by frameworks. */
	uint64_t		fw_vsize;

	/* Number of frameworks. */
	uint32_t		fw_count;

	/* Code size of frameworks. */
	uint64_t		fw_code;

	/* Data size of frameworks. */
	uint64_t		fw_data;

	/* Linkedit size of frameworks. */
	uint64_t		fw_linkedit;

#define LIBTOP_STATE_MAX	7
#define LIBTOP_NSTATES		(LIBTOP_STATE_MAX + 1)
#define LIBTOP_STATE_MAXLEN	8
	int			state_breakdown[LIBTOP_NSTATES];

	/* Network statistics. */
	uint64_t		net_ipackets;
	uint64_t		b_net_ipackets;
	uint64_t		p_net_ipackets;

	uint64_t		net_opackets;
	uint64_t		b_net_opackets;
	uint64_t		p_net_opackets;

	uint64_t		net_ibytes;
	uint64_t		b_net_ibytes;
	uint64_t		p_net_ibytes;

	uint64_t		net_obytes;
	uint64_t		b_net_obytes;
	uint64_t		p_net_obytes;

	/* Disk statistics. */
	uint64_t		disk_rops;
	uint64_t		b_disk_rops;
	uint64_t		p_disk_rops;

	uint64_t		disk_wops;
	uint64_t		b_disk_wops;
	uint64_t		p_disk_wops;

	uint64_t		disk_rbytes;
	uint64_t		b_disk_rbytes;
	uint64_t		p_disk_rbytes;

	uint64_t		disk_wbytes;
	uint64_t		b_disk_wbytes;
	uint64_t		p_disk_wbytes;

	uint64_t		pages_stolen;
} libtop_tsamp_t;

typedef struct  s_os_module
{
        std::string sysname;
        std::string nodename;
        std::string release;
        std::string version;
        std::string machine;
}               t_os_module;


typedef struct  s_ram_module
{
                int     used;
                int     total;
}               t_ram_module;

typedef struct s_cpu_module
{
                double user;
                double sys;
                double idle;
}               t_cpu_module;

typedef struct s_network_module
{
    std::string network_mb_in; 
    std::string network_mb_out;
    std::string packets_mb_in; 
    std::string packets_mb_out;
}               t_network_module;

typedef struct s_cpuinfo_module
{
	std::string brand;
	std::string clock;
	int cores;
	int threads;
}				t_cpuinfo_module;

const unsigned HOST_NAME_MAX = 300;



std::string         get_time();
std::string         get_username();
std::string         get_hostname();
t_os_module         *print_os_info(void);
t_network_module    *network(void);
t_ram_module        *ram(void);
t_cpu_module        *cpu(void);
t_cpuinfo_module	*cpuinfo(void);
#endif