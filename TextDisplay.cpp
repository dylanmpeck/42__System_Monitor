/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextDisplay.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 23:32:27 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/12 20:16:28 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TextDisplay.hpp"
#include <iostream>

TextDisplay::TextDisplay() {}

TextDisplay::~TextDisplay() {}

TextDisplay::TextDisplay(std::vector<std::string> modules)
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
    nodelay(stdscr, true);

    getmaxyx(stdscr, _winHeight, _winWidth);

    getHeightSlots(modules);

    this->_modules = modules;

    _lastTick = 0;

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);

    this->_osMod = print_os_info();
    this->_cpuMod = cpu();
    this->_ramMod = ram();
    this->_netMod = network();
    this->_hostname = get_hostname();
    this->_username = get_username();
    this->_time = get_time();
    this->_cpuinfoMod = cpuinfo();
}

TextDisplay::TextDisplay(TextDisplay const & other)
{
    *this = other;
}

TextDisplay const & TextDisplay::operator=(TextDisplay const & rhs)
{
    if (this != &rhs)
    {
        this->_heightSlots = rhs._heightSlots;
        this->_modules = rhs._modules;
        this->_winWidth = rhs._winWidth;
        this->_winHeight = rhs._winHeight;
        this->_lastTick = rhs._lastTick;
        this->_osMod = rhs._osMod;
        this->_cpuMod = rhs._cpuMod;
        this->_ramMod = rhs._ramMod;
        this->_netMod = rhs._netMod;
        this->_cpuinfoMod = rhs._cpuinfoMod;
        this->_hostname = rhs._hostname;
        this->_username = rhs._username; 
        this->_time = rhs._time;
    }
    return (*this);
}

void TextDisplay::render()
{
    std::cout << _winHeight << std::endl;
    while (1)
    {
        usleep(10000);
        clear();
        for (unsigned long i = 0; i < this->_modules.size(); i++)
        {
            //draw titles/headers
            attron(COLOR_PAIR(1));
            move(_heightSlots[i], 0);
            hline(ACS_HLINE, _winWidth);
            mvprintw(_heightSlots[i], 5, " %s ", _modules[i].c_str());
            attroff(COLOR_PAIR(1));

            //draw module info
            if (_modules[i] == "Hostname")
                mvprintw(_heightSlots[i] + 1, 0, "%s", _hostname.c_str());
            else if (_modules[i] == "Username")
                mvprintw(_heightSlots[i] + 1, 0, "%s", _username.c_str());
            else if (_modules[i] == "Date/Time")
                mvprintw(_heightSlots[i] + 1, 0, "%s", _time.c_str());
            else if (_modules[i] == "Operating System")
            {
               mvprintw(_heightSlots[i] + 1, 0, "%s:%s:%s:%s:%s", _osMod->sysname.c_str(), _osMod->nodename.c_str(), 
                                                                _osMod->release.c_str(), _osMod->version.c_str(), _osMod->machine.c_str());
            }
            else if (_modules[i] == "CPU Usage")
                mvprintw(_heightSlots[i] + 1, 0, "User: %.1lf%%, Sys: %.1lf%%, Idle: %.1lf%%", _cpuMod->user, _cpuMod->sys, _cpuMod->idle);
            else if (_modules[i] == "Ram")
                mvprintw(_heightSlots[i] + 1, 0, "%d Gb (Used) / %d Gb (Total) (%d0%%)", 
                                                        _ramMod->used, _ramMod->total, _ramMod->used / static_cast<double>(_ramMod->total));
            else if (_modules[i] == "Network")
                mvprintw(_heightSlots[i] + 1, 0, "%s in, %s out, %s in, %s out", _netMod->network_mb_in.c_str(), _netMod->network_mb_out.c_str(), 
                                                                    _netMod->packets_mb_in.c_str(), _netMod->packets_mb_out.c_str());
            else if (_modules[i] == "CPU Info")
                mvprintw(_heightSlots[i] + 1, 0, "Model: %s; Clock: %s; Cores: %d; Threads: %d", _cpuinfoMod->brand.c_str(), _cpuinfoMod->clock.c_str(),
                                                                                                _cpuinfoMod->cores, _cpuinfoMod->threads);

        }

        //tick
        if (clock() > _lastTick + 1000)
        {
            _lastTick = clock();
            this->_time = get_time();
            this->_cpuMod = cpu();
            this->_ramMod = ram();
            this->_netMod = network();
        }
        refresh();

        //q key exits gracefully closes monitor
        int ch;
        ch = getch();
        if (ch == 'Q' || ch == 'q')
            break;
    }
    endwin();
}

//copy pasted from graphics. will probably have to scale with terminal size
void TextDisplay::getHeightSlots(std::vector<std::string> modules)
{
    _heightSlots.push_back(0);
    for (unsigned long i = 1; i < modules.size(); i++)
    {
        double percent = i / static_cast<double>(modules.size());
        _heightSlots.push_back(percent * static_cast<double>(_winHeight));
    }    
}