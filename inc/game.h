#ifndef _GAME_H_
#define _GAME_H_


#include <SDL.h>
#include <SDL_image.h>
#include <zlib.h>
#include <png.h>
#include <iostream>
#include "playground.h"
#include "check.h"
#include "iostream"
#include <SDL_mixer.h>

class Game
{
private:

	SDL_Window* window = nullptr;
	SDL_Surface* window_surf = nullptr;
	SDL_Surface* menu_surf = nullptr;

	Playground *solo = nullptr;
	Playground *versus = nullptr;

	Mix_Music *music = nullptr;

public:
	/**
	 * \brief Construction du menu principal
	 *
	 * Cette fonction permet de construire le menu principal,
	 * qui permettra notamment de choisir le mode de jeu.
	 *
	 * \return Constructeur de Game
	 */
	Game();

	/**
	 * \brief Quitter le menu
	 *
	 * Cette fonction permet de sortir du jeu une fois que l'on est
	 * dans le menu principal
	 *
	 * \return Destructeur de Game
	 */
	~Game();

	/**
	 * \brief Interactivité du menu
	 *
	 * Cette fonction permet de choisir les modes de jeu dans le menu
	 * en gardant le fenêtre du menu principal ouverte
	 *
	 */
	void loop();

};


#endif
