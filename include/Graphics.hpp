/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graphics.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tditshwe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 14:44:19 by tditshwe          #+#    #+#             */
/*   Updated: 2017/09/11 14:39:35 by rmoswela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _GRAPHICS_HPP
#define _GRAPHICS_HPP

#include "Bomberman.hpp"

enum GameMode
{
	MAINMENU,
	GAMEPLAY,
	GAMEPAUSE,
	SETTINGS
};

class Graphics
{
public:
	Graphics();
	~Graphics();
	void setDrawMode(GameMode mode);
    GameMode getDrawMode();

private:
	GameMode drawMode;
};

#endif
