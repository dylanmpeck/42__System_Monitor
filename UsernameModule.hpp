/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UsernameModule.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 20:11:34 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/12 20:16:43 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERNAMEMODULE_HPP
#define USERNAMEMODULE_HPP

#include "IMonitorModule.hpp"

#include <unistd.h>

class GraphicsDisplay;

class UsernameModule : public IMonitorModule {

private:
    std::string _username;
    SDL_Color _black;

public:
    UsernameModule();
    ~UsernameModule();
    UsernameModule(UsernameModule const &);
    UsernameModule const & operator=(UsernameModule const &);

    void executeGUIDisplay(SDL_Rect curRect, SDL_Renderer *renderer);
    int getHeight();
    std::string getName();
};

#endif