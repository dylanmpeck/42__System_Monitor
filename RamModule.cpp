/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RamModule.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 13:54:05 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/12 20:18:15 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RamModule.hpp"
#include <iostream>

RamModule::RamModule() 
{
    this->_name = "Ram";
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

    this->_ramMod = ram();
    buildRamStr();
}

RamModule::~RamModule() {}

RamModule::RamModule(RamModule const & other)
{
    *this = other;
}

RamModule const & RamModule::operator=(RamModule const & rhs)
{
    if (this != &rhs)
    {
        this->_ramMod = rhs._ramMod;
        this->_ramStr = rhs._ramStr;
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

void RamModule::executeGUIDisplay(SDL_Rect curRect, SDL_Renderer *renderer)
{
    SDL_Rect header = {0, curRect.y, curRect.w, curRect.h / 2};
    GraphicsDisplay::drawBorderedRect(header, renderer, _border, _inner);
    header.x += 10;
    header.w -= 10;
    GraphicsDisplay::drawText(_name.c_str(), header, header.w / 4, renderer, _text);
    SDL_Rect block = {20, curRect.y + header.h, curRect.w - 50, curRect.h - header.h};
    GraphicsDisplay::drawText(this->_ramStr.c_str(), block, block.w, renderer, _black);
}

void RamModule::buildRamStr()
{
    std::ostringstream ss;
    ss << _ramMod->used << " Gb (Used) / " << _ramMod->total << " Gb (Total)";
    this->_ramStr = ss.str();
}

int RamModule::getHeight() { return (this->_height); }

std::string RamModule::getName() { return (this->_name); }