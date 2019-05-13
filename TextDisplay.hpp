/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextDisplay.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 23:29:27 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/12 18:19:15 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTDISPLAY_HPP
#define TEXTDISPLAY_HPP

#include "IMonitorDisplay.hpp"
#include <curses.h>
#include <string>
#include <vector>

class TextDisplay : public IMonitorDisplay {

private:
    TextDisplay();
    std::vector<int> _heightSlots;
    std::vector<std::string> _modules;
    int _winWidth;
    int _winHeight;
    double _lastTick;

    t_os_module* _osMod;
    t_cpu_module* _cpuMod;
    t_ram_module* _ramMod;
    t_network_module* _netMod;
    t_cpuinfo_module* _cpuinfoMod;
    std::string _hostname;
    std::string _username;
    std::string _time;

public:
    TextDisplay(std::vector<std::string>);
    ~TextDisplay();
    TextDisplay(TextDisplay const &);
    TextDisplay const & operator=(TextDisplay const &);

    void render();
    void getHeightSlots(std::vector<std::string>);
};

#endif