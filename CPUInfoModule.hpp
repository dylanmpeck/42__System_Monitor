/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CPUInfoModule.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 18:25:58 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/12 20:18:59 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPUINFOMODULE_HPP
#define CPUINFOMODULE_HPP

#include "IMonitorModule.hpp"

class CPUInfoModule : public IMonitorModule {

private:
    t_cpuinfo_module* _cpuinfoMod;
    std::string _lineOne;
    std::string _lineTwo;
    SDL_Color _black;

public:
    CPUInfoModule();
    ~CPUInfoModule();
    CPUInfoModule(CPUInfoModule const &);
    CPUInfoModule const & operator=(CPUInfoModule const &);

    void executeGUIDisplay(SDL_Rect curRect, SDL_Renderer *renderer);
    int getHeight();
    std::string getName();

    void buildInfoStrs();
};

#endif