/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graphics.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tditshwe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 14:43:54 by tditshwe          #+#    #+#             */
/*   Updated: 2017/09/11 14:44:30 by rmoswela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Graphics.hpp"

Graphics::Graphics()
{
	drawMode = MAINMENU;
}

Graphics::~Graphics() { }
 
void Graphics::setDrawMode(GameMode mode)
{
	drawMode = mode;
}

GameMode Graphics::getDrawMode()
{
	return drawMode;
}
