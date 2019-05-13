/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OSModule.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 22:21:14 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/12 20:12:43 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OSMODULE_HPP
#define OSMODULE_HPP

#include "IMonitorModule.hpp"
#include <string>
#include <stdio.h>

class OSModule : public IMonitorModule {

private:
    std::string _osInfoLineOne;
    std::string _osInfoLineTwo;
    t_os_module* _osMod;
    SDL_Color _black;

public:
    OSModule();
    ~OSModule();
    OSModule(OSModule const &);
    OSModule const & operator=(OSModule const &);

    void executeGUIDisplay(SDL_Rect curRect, SDL_Renderer *renderer);
    int getHeight();

    void getStringFromCommand();
    void removeNewLinesFromOSInfo();
    std::string getName();
};

#endif