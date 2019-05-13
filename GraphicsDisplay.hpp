/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicsDisplay.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 14:09:43 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/12 20:08:58 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICSDISPLAY_HPP
#define GRAPHICSDISPLAY_HPP

#define WINWIDTH 600

#include "SDL.h"
#include "SDL_ttf.h"
#include "IMonitorModule.hpp"
#include "IMonitorDisplay.hpp"
#include <deque>
#include <vector>
#include <string>
#include <unistd.h>

class IMonitorModule;

class GraphicsDisplay : public IMonitorDisplay {

private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    static TTF_Font *_font;
    std::vector<IMonitorModule *> _modules;
    std::vector<int> _heightSlots;
    bool _quit;

    GraphicsDisplay();

public:
    GraphicsDisplay(std::vector<IMonitorModule *>);
    ~GraphicsDisplay();
    GraphicsDisplay(GraphicsDisplay const &);
    GraphicsDisplay const & operator=(GraphicsDisplay const &);

    void render();

    static void drawRect(SDL_Rect r, SDL_Renderer* renderer, SDL_Color color);
    static void drawBorderedRect(SDL_Rect r, SDL_Renderer* renderer, SDL_Color border, SDL_Color inner);
    static void drawBlockText(const char *message, SDL_Rect r, int mWidth, SDL_Renderer* renderer, SDL_Color border, SDL_Color inner, SDL_Color text);
    static void drawText(const char *message, SDL_Rect r, int mWidth, SDL_Renderer* renderer, SDL_Color text);
    static void drawLine(int x1, int y1, int x2, int y2, SDL_Renderer* renderer, SDL_Color lineColor);

    //graphs are drawn with rectangle of cur module, a deque of values, and an offset madeup of current Y position plus header Y
    static void drawHistogram(SDL_Rect module, SDL_Renderer * renderer, std::deque<double> randNums, int offset, SDL_Color barColor);
    static void drawLineGraph(SDL_Rect module, SDL_Renderer * renderer, std::deque<double> randNums, int offset);

    void getHeightSlots(std::vector<IMonitorModule *>);
    void pollEvents();

    SDL_Renderer * getRenderer();
};

#endif