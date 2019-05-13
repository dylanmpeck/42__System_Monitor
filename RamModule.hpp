/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RamModule.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 13:53:28 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/12 20:14:03 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAMMODULE_HPP
#define RAMMODULE_HPP

#include "IMonitorModule.hpp"
#include <unistd.h>

class RamModule : public IMonitorModule {

private:
    t_ram_module* _ramMod;
    std::string _ramStr;
    SDL_Color _black;

public:
    RamModule();
    ~RamModule();
    RamModule(RamModule const &);
    RamModule const & operator=(RamModule const &);

    void executeGUIDisplay(SDL_Rect curRect, SDL_Renderer *renderer);
    int getHeight();
    std::string getName();

    void buildRamStr();
};

#endif