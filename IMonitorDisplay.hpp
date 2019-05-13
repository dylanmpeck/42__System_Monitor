/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMonitorDisplay.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 11:48:14 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/12 20:11:08 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMONITORDISPLAY_HPP
#define IMONITORDISPLAY_HPP

#include "gkrellm.hpp"

class IMonitorDisplay {

public:
    virtual ~IMonitorDisplay() { return; }
    
    virtual void render() = 0;
};

#endif