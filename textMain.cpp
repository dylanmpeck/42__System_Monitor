/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textMain.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 20:26:21 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/12 21:44:07 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Configuration.hpp"
#include "TextDisplay.hpp"
#include <vector>

int main()
{
    std::vector<std::string> textModules;

#ifdef _HostnameModule
	textModules.push_back("Hostname");
#endif

#ifdef _UsernameModule 
	textModules.push_back("Username");
#endif

#ifdef _OSModule 
	textModules.push_back("Operating System");
#endif

#ifdef _DateTimeModule 
	textModules.push_back("Date/Time");
#endif

#ifdef _CPUModule 
	textModules.push_back("CPU Usage");
	
#endif

#ifdef _RamModule 
	textModules.push_back("Ram");
#endif

#ifdef _NetModule 
	textModules.push_back("Network");
#endif

#ifdef _CPUInfoModule 
	textModules.push_back("CPU Info");
#endif

	TextDisplay td(textModules);

	td.render();

    return (0);
}