/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UsernameModule.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 20:12:59 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/12 20:18:03 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UsernameModule.hpp"

UsernameModule::UsernameModule() 
{
    this->_username = get_username();
    this->_name = "Username";
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
}

UsernameModule::~UsernameModule() {}

UsernameModule::UsernameModule(UsernameModule const & other)
{
    *this = other;
}

UsernameModule const & UsernameModule::operator=(UsernameModule const & rhs)
{
    if (this != &rhs)
    {
        this->_username = rhs._username;
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

void UsernameModule::executeGUIDisplay(SDL_Rect curRect, SDL_Renderer *renderer)
{
    SDL_Rect header = {0, curRect.y, curRect.w, curRect.h / 2};
    GraphicsDisplay::drawBorderedRect(header, renderer, _border, _inner);
    header.x += 10;
    header.w -= 10;
    GraphicsDisplay::drawText(_name.c_str(), header, header.w / 3, renderer, _text);
    SDL_Rect block = {20, curRect.y + header.h, curRect.w / 3, curRect.h - header.h};
    GraphicsDisplay::drawText(this->_username.c_str(), block, block.w, renderer, _black);
}

int UsernameModule::getHeight() { return (this->_height); }

std::string UsernameModule::getName() { return (this->_name); }