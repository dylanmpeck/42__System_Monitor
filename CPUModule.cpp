/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CPUModule.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 20:15:23 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/12 20:18:50 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CPUModule.hpp"

CPUModule::CPUModule() 
{
    this->_lastTick = SDL_GetTicks();
    this->_name = "CPU Usage";
    this->_height = 200; // arbitrary height for each module
    this->_width = WINWIDTH;
    this->_border.r = 0;
    this->_border.g = 0;
    this->_border.b = 0;
    this->_inner.r = 74;
    this->_inner.g = 110;
    this->_inner.b = 124;
    this->_text.r = 233;
    this->_text.g = 225;
    this->_text.b = 209;
    this->_idle.r = 212;
    this->_idle.g = 163;
    this->_idle.b = 90;
    this->_sys.r = 80;
    this->_sys.g = 107;
    this->_sys.b = 119;
    this->_user.r = 88;
    this->_user.g = 179;
    this->_user.b = 180;

    this->_cpuMod = cpu();
    _idleNums.push_back(_cpuMod->idle);
    _sysNums.push_back(_cpuMod->sys);
    _userNums.push_back(_cpuMod->user);
    convertDoublesToStr();
}

CPUModule::~CPUModule() {}

CPUModule::CPUModule(CPUModule const & other)
{
    *this = other;
}

CPUModule const & CPUModule::operator=(CPUModule const & rhs)
{
    if (this != &rhs)
    {
        this->_idleNums = rhs._idleNums;
        this->_sysNums = rhs._sysNums;
        this->_userNums = rhs._userNums;
        this->_cpuMod = rhs._cpuMod;
        this->_lastTick = rhs._lastTick;
        this->_idleUsage = rhs._idleUsage;
        this->_sysUsage = rhs._sysUsage;
        this->_userUsage = rhs._userUsage;
        this->_idle = rhs._idle;
        this->_sys = rhs._sys;
        this->_user = rhs._user;
        this->_name = rhs._name;
        this->_height = rhs._height;
        this->_width = rhs._width;
        this->_border = rhs._border;
        this->_inner = rhs._inner;
        this->_text = rhs._text;
    }
    return (*this);
}

//TODO: currently random numbers. might want to display different info here too
void CPUModule::getCPUUsage()
{
    if (SDL_GetTicks() > _lastTick + 1000)
    {
        _lastTick = SDL_GetTicks();
        this->_cpuMod = cpu();

        if (_idleNums.size() > 35 || _sysNums.size() > 35 || _userNums.size() > 35)
        {
            _idleNums.pop_front();
            _sysNums.pop_front();
            _userNums.pop_front();
        }

        _idleNums.push_back(_cpuMod->idle);
        _sysNums.push_back(_cpuMod->sys);
        _userNums.push_back(_cpuMod->user);
    }

    convertDoublesToStr();
}

void CPUModule::convertDoublesToStr()
{
    std::ostringstream strs;
    strs << "Idle: " << std::setprecision(3) << this->_cpuMod->idle << "% ";
    _idleUsage = strs.str();
    strs.str("");
    strs << "Sys: " << this->_cpuMod->sys << "% ";
    _sysUsage = strs.str();
    strs.str("");
    strs << "User: " << this->_cpuMod->user << "% ";
    _userUsage = strs.str();
}

void CPUModule::executeGUIDisplay(SDL_Rect curRect, SDL_Renderer *renderer)
{
    getCPUUsage();
    SDL_Rect header = {0, curRect.y, curRect.w, curRect.h / 3};
    GraphicsDisplay::drawBorderedRect(header, renderer, _border, _inner);
    header.x += 10;
    header.w -= 10;
    GraphicsDisplay::drawText(_name.c_str(), header, header.w / 3, renderer, _text);
    SDL_Rect messageRect = curRect;
    messageRect.h = (messageRect.h - header.h) / 4;
    messageRect.y += header.h;
    messageRect.x += static_cast<double>(static_cast<double>(messageRect.w) * 0.75);
    GraphicsDisplay::drawText(_idleUsage.c_str(), messageRect, messageRect.w / 4, renderer, _idle);
    messageRect.y += messageRect.h;
    GraphicsDisplay::drawText(_sysUsage.c_str(), messageRect, messageRect.w / 4, renderer, _sys);
    messageRect.y += messageRect.h;
    GraphicsDisplay::drawText(_userUsage.c_str(), messageRect, messageRect.w / 4, renderer, _user);

    GraphicsDisplay::drawHistogram(curRect, renderer, _idleNums, curRect.y + header.h, _idle);
    GraphicsDisplay::drawHistogram(curRect, renderer, _sysNums, curRect.y + header.h, _sys);
    GraphicsDisplay::drawHistogram(curRect, renderer, _userNums, curRect.y + header.h, _user);
}

int CPUModule::getHeight() { return (this->_height); }

std::string CPUModule::getName() { return (this->_name); }