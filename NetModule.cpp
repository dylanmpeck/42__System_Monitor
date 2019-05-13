/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NetModule.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 14:16:19 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/12 20:18:29 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NetModule.hpp"
#include <iostream>

NetModule::NetModule() 
{
    this->_name = "Network";
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

    this->_netMod = network();
    buildNetStrs();
    this->_lastTick = 0;
}

NetModule::~NetModule() {}

NetModule::NetModule(NetModule const & other)
{
    *this = other;
}

NetModule const & NetModule::operator=(NetModule const & rhs)
{
    if (this != &rhs)
    {
        this->_lastTick = rhs._lastTick;
        this->_black = rhs._black;
        this->_netMod = rhs._netMod;
        this->_netStr = rhs._netStr;
        this->_packetStr = rhs._packetStr;
        this->_name = rhs._name;
        this->_height = rhs._height;
        this->_width = rhs._width;
        this->_border = rhs._border;
        this->_inner = rhs._inner;
        this->_text = rhs._text;
    }
    return (*this);
}

void NetModule::executeGUIDisplay(SDL_Rect curRect, SDL_Renderer *renderer)
{
    if (clock() > _lastTick + 1000)
    {
        this->_netMod = network();
        buildNetStrs();
    }

    SDL_Rect header = {0, curRect.y, curRect.w, curRect.h / 3};
    GraphicsDisplay::drawBorderedRect(header, renderer, _border, _inner);
    header.x += 10;
    header.w -= 10;
    GraphicsDisplay::drawText(_name.c_str(), header, header.w / 3, renderer, _text);
    SDL_Rect block = {20, curRect.y + header.h, curRect.w - 50, curRect.h - header.h};
    block.h /= 2;
    GraphicsDisplay::drawText(this->_netStr.c_str(), block, block.w, renderer, _black);
    block.y += block.h;
    GraphicsDisplay::drawText(this->_packetStr.c_str(), block, block.w, renderer, _black);
}

void NetModule::buildNetStrs()
{
    std::ostringstream ss;
    ss << this->_netMod->network_mb_in << " in, " << this->_netMod->network_mb_out << " out";
    this->_netStr = ss.str();
    ss.str("");
    ss << this->_netMod->packets_mb_in << " in, " << this->_netMod->packets_mb_out << " out";
    this->_packetStr = ss.str();
}

int NetModule::getHeight() { return (this->_height); }

std::string NetModule::getName() { return (this->_name); }