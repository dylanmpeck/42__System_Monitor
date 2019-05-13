/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OSModule.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 22:24:12 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/12 20:18:22 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OSModule.hpp"
#include <iostream>

OSModule::OSModule() 
{
    this->_name = "Operating System";
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
    this->_black.r = 0;
    this->_black.g = 0;
    this->_black.b = 0;

    _osMod = print_os_info();
    unsigned long i = 0;
    for (; i < _osMod->version.size() && _osMod->version[i] != ';'; i++)
        _osInfoLineOne.push_back(_osMod->version[i]);
    _osInfoLineOne.push_back(_osMod->version[i]);
    i += 2;
    for (; i < _osMod->version.size(); i++)
        _osInfoLineTwo.push_back(_osMod->version[i]);
}

OSModule::~OSModule() {}

OSModule::OSModule(OSModule const & other)
{
    *this = other;
}

OSModule const & OSModule::operator=(OSModule const & rhs)
{
    if (this != &rhs)
    {
        this->_osMod = rhs._osMod;
        this->_black = rhs._black;
        this->_osInfoLineOne = rhs._osInfoLineOne;
        this->_osInfoLineTwo = rhs._osInfoLineTwo;
        this->_name = rhs._name;
        this->_height = rhs._height;
        this->_width = rhs._width;
        this->_border = rhs._border;
        this->_inner = rhs._inner;
        this->_text = rhs._text;
    }
    return (*this);
}

void OSModule::executeGUIDisplay(SDL_Rect curRect, SDL_Renderer *renderer)
{
    SDL_Rect header = {0, curRect.y, curRect.w, curRect.h / 3};
    GraphicsDisplay::drawBorderedRect(header, renderer, _border, _inner);
    header.x += 10;
    header.w -= 10;
    GraphicsDisplay::drawText(_name.c_str(), header, header.w / 2, renderer, _text);
    SDL_Rect block = {20, curRect.y + header.h, curRect.w - 50, curRect.h - header.h};
    block.h /= 2;
    GraphicsDisplay::drawText(this->_osInfoLineOne.c_str(), block, block.w, renderer, _black);
    block.y += block.h;
    GraphicsDisplay::drawText(this->_osInfoLineTwo.c_str(), block, block.w, renderer, _black);
}

int OSModule::getHeight() { return (this->_height); }

std::string OSModule::getName() { return (this->_name); }