/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NetModule.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 14:15:25 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/12 20:11:40 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETMODULE_HPP
#define NETMODULE_HPP

#include "IMonitorModule.hpp"

class NetModule : public IMonitorModule {

private:
    t_network_module* _netMod;
    std::string _netStr;
    std::string _packetStr;
    double _lastTick;
    SDL_Color _black;

public:
    NetModule();
    ~NetModule();
    NetModule(NetModule const &);
    NetModule const & operator=(NetModule const &);

    void executeGUIDisplay(SDL_Rect curRect, SDL_Renderer *renderer);
    int getHeight();
    std::string getName();

    void buildNetStrs();
};


#endif