#ifndef _PLAYGROUND_H_
#define _PLAYGROUND_H_


#include <vector>
#include <array>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <zlib.h>
#include <png.h>
#include "SDL2/SDL_ttf.h"
#include "square.h"
#include "tetrimino.h"
#include <math.h>


class Playground
{
private:
	long int score = 0;
	long int score_ia = 0;
	int difficulty = 0;
    	int next_level[2];

	SDL_Window* window = nullptr;
	SDL_Renderer * renderer = nullptr;
	SDL_Texture * end_texture = nullptr;
	SDL_Texture * start_texture = nullptr;

	int nb_line = 20;
	int nb_column = 10;
	time_t t;
	Tetrimino * tetrimino_cache[2];

	Square * tetris_array[20][10];
	Tetrimino * current_tetrimino = nullptr;

	TTF_Font* font = nullptr;

public:

	/**
	 * \brief Construction de la fenêtre de jeu
	 *
	 * Cette fonction permet de créer la fenêtre afin de commencer à
	 * jouer.
	 *
	 * \return Constructeur de Playground
	 */
	Playground();

	/**
	 * \brief Quitter le jeu en cours
	 *
	 * Cette fonction permet de quitter la fenêtre du jeu en cours.
	 *
	 * \return Destructeur de Playground
	 */
	~Playground();

	/**
	 * \brief Affichage de texte
	 *
	 * Cette fonction permet l'affichage de texte sur une fenêtre.
	 *
	 * \param text chaîne de caractères à afficher
	 * \param x entier indiquant l'abscisse du coin supérieur gauche du texte
	 * \param y entier indiquant l'ordonnée du coin supérieur gauche du texte
	 * \param w entier indiquant la largeur du rectangle contenant le texte
	 * \param h entier indiquant la hauteur du rectangle contenant le texte
	 * \param color SDL_color indiquant la couleur souhaitée du texte
	 */
	void write_texte(const char * text, int x, int y, int w, int h, SDL_Color color);

	/**
	 * \brief Affichage de la difficulté
	 *
	 * Cette fonction permet l'affichage de difficulté sur une fenêtre.
	 *
	 * \param x entier indiquant l'abscisse du coin supérieur gauche du texte
	 * \param y entier indiquant l'ordonnée du coin supérieur gauche du texte
	 * \param w entier indiquant la largeur du rectangle contenant le texte
	 * \param h entier indiquant la hauteur du rectangle contenant le texte
	 */
	void write_difficulty(int x, int y, int w, int h);

	/**
	 * \brief Design de la fenêtre de début de jeu
	 *
	 * Cette fonction permet de designer la fenêtre de début de jeu.
	 *
	 */
	void draw_start_screen();

	/**
	 * \brief Design de la fenêtre de fin de jeu
	 *
	 * Cette fonction permet de designer la fenêtre de fin de jeu.
	 *
	 */
	void draw_game_over_screen();

	/**
	 * \brief Design de la fenêtre de jeu
	 *
	 * Cette fonction permet de designer la fenêtre de jeu.
	 *
	 */
	void draw_playground();

	/**
	 * \brief Transition de fenêtres
	 *
	 * Cette fonction permet de passer de la fenêtre de début de jeu à
	 * celle de jeu, via des touches indiquées sur la fenêtre de début de
	 * jeu.
	 *
	 */
	bool introduction();

	/**
	 * \brief Transition de fenêtres
	 *
	 * Cette fonction permet de passer de la fenêtre de fin de jeu à
	 * celle du menu principal, via des touches indiquées sur la fenêtre
	 * de début de jeu.
	 *
	 */
	void outroduction();

	/**
	 * \brief Jouer jusqu'au game over
	 *
	 * Cette fonction permet au joueur de pouvoir jouer jusqu'à ce qu'il
	 * perde ou qu'il quitte la partie.
	 *
	 */
	void loop();

	/**
	 * \brief Détermination du tetrimino à jouer
	 *
	 * Cette fonction permet de déterminer quel tetrimino le joueur va
	 * devoir jouer. Cette détermination se fait au hasard avec le fonction
	 * rand.
	 *
	 */
	void select_tetrimino();

	/**
	 * \brief Descente des tetriminos
	 *
	 * Cette fonction permet au tetrimino, qui est en train d'être joué, de
	 * simuler sa descente sur le terrain de jeu. Si elle ne peut pas
	 * descendre alors le jeu est terminé.
	 *
	 *\param quit pointeur sur un booléen qui va se voir assigné la valeur
	 *true si la pièce ne peut descendre.
	 */
	void tetrimino_descent(bool *quit);

	/**
	 * \brief Arrêt des tetriminos
	 *
	 * Cette fonction permet au tetrimino, qui est en train d'être joué,
	 * de stopper sa descente suite à son arrivée soit sur le "plancher" du
	 * terrain de jeu, soit sur une autre pièce déjà posée.
	 *
	 */
	void stop_tetrimino();

	/**
	 * \brief Déplacement sur la gauche des tetriminos
	 *
	 * Cette fonction permet de déplacer vers la gauche le tetrimino qui
	 * est en train d'être joué, dans la limite des bordures définies par
	 * le terrain de jeu et les autres pièces déjà posées.
	 *
	 */
	void left_shift();

	/**
	 * \brief Déplacement sur la droite des tetriminos
	 *
	 * Cette fonction permet de déplacer vers la droite le tetrimino qui
	 * est en train d'être joué, dans la limite des bordures définies par
	 * le terrain de jeu et les autres pièces déjà posées.
	 *
	 */
	void right_shift();

	/**
	 * \brief Détection + Suppression de ligne complétée + Score associé
	 *
	 * Cette fonction permet de détecter les lignes complétées, de les détruire
	 *  et d'y associer le score adapté. De plus, elle gère la descente des
	 *  autres pièces posées suite à la destruction.
	 *
	 */
	int line_completed();

	/**
	 * \brief Affichage du score
	 *
	 * Cette fonction permet l'affichage du score.
	 *
	 * \param x entier indiquant l'abscisse du coin supérieur gauche du score
	 * \param y entier indiquant l'ordonnée du coin supérieur gauche du score
	 * \param w entier indiquant la largeur du rectangle contenant le score
	 * \param h entier indiquant la hauteur du rectangle contenant le score
	 */
	void draw_score(int x, int y, int w, int h);

	/**
	 * \brief Design de la fenêtre de début de jeu mode versus
	 *
	 * Cette fonction permet de designer la fenêtre de début de jeu du mode
	 * versus.
	 *
	 */
	void draw_start_screen_ia();

	/**
	 * \brief Design de la fenêtre de fin de jeu mode versus
	 *
	 * Cette fonction permet de designer la fenêtre de fin de jeu du mode
	 * versus.
	 *
	 */
	void draw_game_over_screen_ia();

	/**
	 * \brief Transition de fenêtres du mode versus
	 *
	 * Cette fonction permet de passer de la fenêtre de début de jeu à
	 * celle de jeu, via des touches indiquées sur la fenêtre de début de
	 * jeu. Le tout concernant les fenêtres du mode versus.
	 *
	 */
	bool introduction_ia();

	/**
	 * \brief Transition de fenêtres
	 *
	 * Cette fonction permet de passer de la fenêtre de fin de jeu à
	 * celle du menu principal, via des touches indiquées sur la fenêtre
	 * de début de jeu. Le tout concernant les fenêtres du mode versus.
	 *
	 */
	void outroduction_ia();

	/**
	 * \brief Affichage du score du mode versus
	 *
	 * Cette fonction permet l'affichage du score du mode versus.
	 *
	 * \param x entier indiquant l'abscisse du coin supérieur gauche du score
	 * \param y entier indiquant l'ordonnée du coin supérieur gauche du score
	 * \param w entier indiquant la largeur du rectangle contenant le score
	 * \param h entier indiquant la hauteur du rectangle contenant le score
	 */
	void draw_score_ia(int x, int y, int w, int h);

	/**
	 * \brief Calcul du score.
	 *
	 * Le score dépends de la dernière ligne occupé par la pièce et des
	 * lignes éventuellement complétées
	 *
	 * \param score_2_update pour différencier le score de l'ia, de celui du joueur.
	 * \param line_completed Si des lignes ont été complétées.
	 */
	int compute_score(int score_2_update);

	/**
	 * \brief Jouer jusqu'au game over du mode versus
	 *
	 * Cette fonction permet au joueur de pouvoir jouer jusqu'à ce qu'il
	 * perde ou qu'il quitte la partie dans le mode versus.
	 *
	 */
	void loop_ia();

	/**
	 * \brief Choix de l'ordinateur
	 *
	 * Cette fonction permet à l'ordinateur de choisir où poser sa pièce.
	 * Cela grâce à des valeurs associées aux positions.
	 *
	 * \return un vecteur de pair indiquant la ligne et la colonne choisie
	 */
	std::vector<std::pair<int,int>> compute_ia();

	/**
	 * \brief Déplacement du tetrimino vers la position choisie
	 *
	 * Cette fonction permet à l'ordinateur de déplacer le tetrimino
	 * jusqu'à la position qu'il lui a choisi.
	 *
	 * \param position vecteur de pair indiquant la ligne
	 * et la colonne choisie
	 */
	void move_ia(std::vector<std::pair<int,int>> position);

	/**
	 * \brief Fonction de debug affichant le terrain de jeu
	 *
	 * Cette fonction permet d'afficher le terrain de jeu avec des 0,
	 * s'il n'y a pas de pièce sur la case, et de 1, s'il y en a une.
	 *
	 */
	void print_tetris_array();

	/**
	 * \brief Fonction de debug donnant des infos sur la pièce jouée
	 *
	 * Cette fonction permet d'obtenir des informations sur la pièce jouée.
	 * Notamment sa vitesse et sa forme.
	 *
	 */
	void print_current_tetrimino_info();

};



#endif
