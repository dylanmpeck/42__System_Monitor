/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HostnameModule.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 19:30:52 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/12 20:10:31 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOSTNAMEMODULE_HPP
#define HOSTNAMEMODULE_HPP

#include "IMonitorModule.hpp"
#include <unistd.h>

class HostnameModule : public IMonitorModule {

private:
    std::string _hostname;
    SDL_Color _black;

public:
    HostnameModule();
    ~HostnameModule();
    HostnameModule(HostnameModule const &);
    HostnameModule const & operator=(HostnameModule const &);

    void executeGUIDisplay(SDL_Rect curRect, SDL_Renderer *renderer);
    int getHeight();
    std::string getName();
};

#endif