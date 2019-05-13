/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicsDisplay.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 14:13:33 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/12 20:10:17 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GraphicsDisplay.hpp"
#include <iostream>

TTF_Font * GraphicsDisplay::_font = nullptr;

GraphicsDisplay::GraphicsDisplay() {}

GraphicsDisplay::GraphicsDisplay(std::vector<IMonitorModule *> modules)
{
    SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
    GraphicsDisplay::_font = TTF_OpenFont("SourceCodePro-Regular.ttf", 32);

    this->_quit = false;
    this->_window = NULL;

    int winHeight = 0;
    for (unsigned long i = 0; i < modules.size(); i++)
        winHeight += modules[i]->getHeight();

    _window = SDL_CreateWindow
    (
        "ft_gkrellm", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINWIDTH, // width
        winHeight, // height
        0
    );

    this->_modules = modules;

    this->_renderer = NULL;
    this->_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

    //sets background color for window
    SDL_SetRenderDrawColor(_renderer, 212, 212, 209, 255);
    SDL_RenderClear(_renderer);  
}

GraphicsDisplay::~GraphicsDisplay()
{
    TTF_CloseFont(_font);
    SDL_DestroyWindow(this->_window);
	TTF_Quit();
    SDL_Quit();
}

GraphicsDisplay::GraphicsDisplay(GraphicsDisplay const & other)
{
    *this = other;
}

GraphicsDisplay const & GraphicsDisplay::operator=(GraphicsDisplay const & rhs)
{
    if (this != &rhs)
    {
        this->_window = rhs._window;
        this->_renderer = rhs._renderer;
        this->_quit = rhs._quit;
        this->_modules = rhs._modules;
        this->_heightSlots = rhs._heightSlots;
        this->_font = rhs._font;
    }
    return (*this);
}

//header inner color 74, 110, 124, 255
void GraphicsDisplay::drawBorderedRect(SDL_Rect r, SDL_Renderer* renderer, SDL_Color border, SDL_Color inner)
{
   SDL_SetRenderDrawColor(renderer, inner.r, inner.g, inner.b, 255);
   SDL_RenderFillRect(renderer, &r);
   SDL_SetRenderDrawColor(renderer, border.r, border.g, border.b, 255);
   SDL_RenderDrawRect(renderer, &r);    
}

void GraphicsDisplay::drawRect(SDL_Rect r, SDL_Renderer* renderer, SDL_Color color)
{
   SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
   SDL_RenderFillRect(renderer, &r);    
}

void GraphicsDisplay::drawLine(int x1, int y1, int x2, int y2, SDL_Renderer* renderer, SDL_Color lineColor)
{
    SDL_SetRenderDrawColor(renderer, lineColor.r, lineColor.g, lineColor.b, 255);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void GraphicsDisplay::drawText(const char *message, SDL_Rect r, int mWidth, SDL_Renderer* renderer, SDL_Color text)
{
    SDL_Surface *surfaceMessage;

    surfaceMessage = TTF_RenderText_Solid(_font, message, text);

	SDL_Texture *messageTex = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_FreeSurface(surfaceMessage);

	SDL_Rect MessageRect = {r.x, r.y, mWidth, r.h};

	SDL_RenderCopy(renderer, messageTex, NULL, &MessageRect); 

    SDL_DestroyTexture(messageTex);    
}

//unused but could be useful for bonus modules?
void GraphicsDisplay::drawLineGraph(SDL_Rect module, SDL_Renderer *renderer, std::deque<double> values, int offset)
{
    SDL_Color lineColor = {171, 124, 55, 255};
    SDL_Rect r = {0, module.y, 10, module.h - (module.h / 3)};
    int lastY = r.h;
    int lastX = r.x;

    for (unsigned long i = 0; i < values.size(); i++)
    {
        double percent = static_cast<double>(100.0f - values[i]) / 100.0f;
        r.y = static_cast<double>(percent * static_cast<double>(r.h)) + offset;
        drawLine(lastX, lastY, r.x, r.y, renderer, lineColor);
        lastY = r.y;
        lastX = r.x;
        r.x += 10;
    }
}

void GraphicsDisplay::drawHistogram(SDL_Rect module, SDL_Renderer *renderer, std::deque<double> values, int offset, SDL_Color color)
{
    SDL_Rect r = {0, module.y, 10, module.h - (module.h / 3)}; // might want to pass in the actual header height instead of divide by 3

    int maxHeight = r.h;

    for (unsigned long i = 0; i < values.size(); i++)
    {
        double percent = static_cast<double>(100.0f - values[i]) / 100.0f;
        r.y = static_cast<double>(percent * static_cast<double>(maxHeight)) + offset;
        r.h = static_cast<double>(values[i] / 100.0f) * maxHeight + 1; // extra padding gets disguised by header. might have to change if design changes
        GraphicsDisplay::drawRect(r, renderer, color);
        r.x += 10;
    }    
}

void GraphicsDisplay::render()
{
    getHeightSlots(_modules);

	while (_quit == false)
	{
        //reset with background color
		SDL_SetRenderDrawColor(_renderer, 212, 212, 209, 255);
    	SDL_RenderClear(_renderer);

        for (unsigned long i = 0; i < _modules.size(); i++)
        {
            SDL_Rect curRect = {0, _heightSlots[i], WINWIDTH, _modules[i]->getHeight()};
            _modules[i]->executeGUIDisplay(curRect, this->_renderer);
        }

		SDL_RenderPresent(_renderer);

		this->pollEvents();
	}
}

void GraphicsDisplay::getHeightSlots(std::vector<IMonitorModule *> modules)
{
    _heightSlots.push_back(0);
    for (unsigned long i = 1; i < modules.size(); i++)
        _heightSlots.push_back(modules[i - 1]->getHeight() + _heightSlots[i - 1]);
}

void GraphicsDisplay::pollEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			_quit = true;
		/*switch (event.key.keysym.sym)
		{
			case SDLK_ESCAPE: _quit = true; break;
		}*/
	}    
}

SDL_Renderer * GraphicsDisplay::getRenderer() { return (this->_renderer); }
