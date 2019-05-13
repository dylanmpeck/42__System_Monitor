/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMonitorModule.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 19:25:18 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/12 20:36:55 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMONITORMODULE_HPP
#define IMONITORMODULE_HPP

#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "GraphicsDisplay.hpp"

class GraphicsDisplay;

class IMonitorModule {

protected:
    //these variables will be used to set the GUI rectangles.
    int _width;
    int _height;
    std::string _name;
    SDL_Color _border;
    SDL_Color _inner;
    SDL_Color _text;

public:
    virtual ~IMonitorModule() {return;};
    virtual void executeGUIDisplay(SDL_Rect r, SDL_Renderer * renderer) = 0;
    virtual int getHeight() = 0;
    virtual std::string getName() = 0;
};

#endif
