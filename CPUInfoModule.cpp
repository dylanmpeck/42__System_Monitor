/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CPUInfoModule.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 18:26:48 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/12 20:18:57 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CPUInfoModule.hpp"
#include <iostream>

CPUInfoModule::CPUInfoModule() 
{
    this->_name = "CPU Info";
    this->_height = 100; // arbitrary height for each module
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
    this->_black.r = 0;
    this->_black.g = 0;
    this->_black.b = 0;

    this->_cpuinfoMod = cpuinfo();
    buildInfoStrs();
}

CPUInfoModule::~CPUInfoModule() {}

CPUInfoModule::CPUInfoModule(CPUInfoModule const & other)
{
    *this = other;
}

CPUInfoModule const & CPUInfoModule::operator=(CPUInfoModule const & rhs)
{
    if (this != &rhs)
    {
        this->_cpuinfoMod = rhs._cpuinfoMod;
        this->_lineOne = rhs._lineOne;
        this->_lineTwo = rhs._lineTwo;
        this->_black = rhs._black;
        this->_name = rhs._name;
        this->_height = rhs._height;
        this->_width = rhs._width;
        this->_border = rhs._border;
        this->_inner = rhs._inner;
        this->_text = rhs._text;
    }
    return (*this);
}

void CPUInfoModule::executeGUIDisplay(SDL_Rect curRect, SDL_Renderer *renderer)
{
    SDL_Rect header = {0, curRect.y, curRect.w, curRect.h / 3};
    GraphicsDisplay::drawBorderedRect(header, renderer, _border, _inner);
    header.x += 10;
    header.w -= 10;
    GraphicsDisplay::drawText(_name.c_str(), header, header.w / 3, renderer, _text);
    SDL_Rect block = {20, curRect.y + header.h, curRect.w - 50, curRect.h - header.h};
    block.h /= 2;
    GraphicsDisplay::drawText(this->_lineOne.c_str(), block, block.w, renderer, _black);
    block.y += block.h;
    GraphicsDisplay::drawText(this->_lineTwo.c_str(), block, block.w, renderer, _black);
}

void CPUInfoModule::buildInfoStrs()
{
    std::ostringstream ss;
    ss << "Model:" << _cpuinfoMod->brand;
    this->_lineOne = ss.str();
    ss.str("");
    ss << "Clock:" << _cpuinfoMod->clock << ";Cores:" << _cpuinfoMod->cores << ";Threads:" << _cpuinfoMod->threads;
    this->_lineTwo = ss.str();
}

int CPUInfoModule::getHeight() { return (this->_height); }

std::string CPUInfoModule::getName() { return (this->_name); }