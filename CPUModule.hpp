/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CPUModule.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 20:14:43 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/12 20:04:51 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPUMODULE_HPP
#define CPUMODULE_HPP

#include "IMonitorModule.hpp"
#include <deque>
#include <sstream>
#include <iomanip>

class GraphicsDisplay;

class CPUModule : public IMonitorModule {

private:
    std::deque<double> _idleNums;
    std::deque<double> _sysNums;
    std::deque<double> _userNums;
    t_cpu_module* _cpuMod;
    double _lastTick;
    std::string _idleUsage;
    std::string _sysUsage;
    std::string _userUsage;

    SDL_Color _idle;
    SDL_Color _sys;
    SDL_Color _user;

public:
    CPUModule();
    ~CPUModule();
    CPUModule(CPUModule const &);
    CPUModule const & operator=(CPUModule const &);
    
    void executeGUIDisplay(SDL_Rect curRect, SDL_Renderer *renderer);

    void getCPUUsage();

    void convertDoublesToStr();

    int getHeight();
    std::string getName();
};

#endif