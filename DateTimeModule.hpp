/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DateTimeModule.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 21:32:37 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/12 20:10:40 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATETIMEMODULE_HPP
#define DATETIMEMODULE_HPP

#include "IMonitorModule.hpp"
#include <time.h>
#include <string>

class DateTimeModule : public IMonitorModule {

private:
    std::string _timeStamp;
    double _lastTick;
    SDL_Color _black;

public:
    DateTimeModule();
    ~DateTimeModule();
    DateTimeModule(DateTimeModule const &);
    DateTimeModule const & operator=(DateTimeModule const &);

    void executeGUIDisplay(SDL_Rect curRect, SDL_Renderer *renderer);
    int getHeight();

    std::string getName();
};

#endif