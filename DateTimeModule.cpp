/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DateTimeModule.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 21:33:34 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/12 20:18:45 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DateTimeModule.hpp"
#include <iostream>

DateTimeModule::DateTimeModule() 
{
    this->_name = "Date/Time";
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

    this->_timeStamp = get_time();
    this->_lastTick = 0;
}

DateTimeModule::~DateTimeModule() {}

DateTimeModule::DateTimeModule(DateTimeModule const & other)
{
    *this = other;
}

DateTimeModule const & DateTimeModule::operator=(DateTimeModule const & rhs)
{
    if (this != &rhs)
    {
        this->_timeStamp = rhs._timeStamp;
        this->_black = rhs._black;
        this->_lastTick = rhs._lastTick;
        this->_name = rhs._name;
        this->_height = rhs._height;
        this->_width = rhs._width;
        this->_border = rhs._border;
        this->_inner = rhs._inner;
        this->_text = rhs._text;
    }
    return (*this);
}

void DateTimeModule::executeGUIDisplay(SDL_Rect curRect, SDL_Renderer *renderer)
{
    if (clock() > _lastTick + 500)
    {
        _lastTick = clock();
        _timeStamp = get_time();
    }

    SDL_Rect header = {0, curRect.y, curRect.w, curRect.h / 2};
    GraphicsDisplay::drawBorderedRect(header, renderer, _border, _inner);
    header.x += 10;
    header.w -= 10;
    GraphicsDisplay::drawText(_name.c_str(), header, header.w / 3, renderer, _text);
    SDL_Rect block = {20, curRect.y + header.h, curRect.w - 50, curRect.h - header.h};
    GraphicsDisplay::drawText(this->_timeStamp.c_str(), block, block.w, renderer, _black);
}

int DateTimeModule::getHeight() { return (this->_height); }

std::string DateTimeModule::getName() { return (this->_name); }