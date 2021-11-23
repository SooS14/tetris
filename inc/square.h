#ifndef _SQUARE_H_
#define _SQUARE_H_

#include <SDL.h>

class Square
{
private:
	int line;
	int column;
	SDL_Rect box;
	SDL_Color color;

public:

	/**
	 * \brief Construction d'un carré permmettant de former un tetrimino
	 *
	 * Cette fonction permet de créer un carré, qui va servir à la création
	 * d'un tetrimino. 4 carrés permettent la formation d'un tetrimino.
	 *
	 * \param color_ SDL_Color donnant la couleur souhaitée du carré
	 * \param line_ entier indiquant la ligne où poser le carré
	 * \param column_ entier indiquant la colonne où poser le carré
	 * \return Constructeur de Square
	 */
	Square(SDL_Color color_, int line_, int column_);

	/**
	 * \brief Détruire un carré
	 *
	 * Cette fonction permet de "détruire" un carré.
	 *
	 * \return Destructeur de Square
	 */
	~Square();

	/**
	 * \brief Obtention ligne du carré
	 *
	 * Cette fonction permet d'obtenir la ligne où se situe actuellement
	 * le carré.
	 *
	 * \return un entier indiquant la ligne où se situe le carré
	 */
	int get_line();

	/**
	 * \brief Obtention colonne du carré
	 *
	 * Cette fonction permet d'obtenir la colonne où se situe actuellement
	 * le carré.
	 *
	 * \return un entier indiquant la colonne où se situe le carré
	 */
	int get_column();

	/**
	 * \brief Obtention coordonnées pour l'affichage du carré
	 *
	 * Cette fonction permet d'obtenir les coordonnées du carré permettant
	 * d'avoir un bon affichage pour le jeu.
	 *
	 * \return SDL_Rect les coordonnées du carré pour l'affichage
	 */
	SDL_Rect get_box();

	/**
	 * \brief Obtention couleur du carré
	 *
	 * Cette fonction permet d'obtenir la couleur du carré.
	 *
	 * \return SDL_Color la couleur du carré
	 */
	SDL_Color get_color();

	/**
	 * \brief Paramétrer la ligne du carré
	 *
	 * Cette fonction permet de modifier la ligne où se situe le carré.
	 *
	 * \param line_ entier indiquant la ligne où l'on souhaite placer le
	 * carré
	 */
	void set_line(int line_);

	/**
	 * \brief Paramétrer la colonne du carré
	 *
	 * Cette fonction permet de modifier la colonne où se situe le carré.
	 *
	 * \param column_ entier indiquant la colonne où l'on souhaite placer le
	 * carré
	 */
	void set_column(int column_);

	/**
	 * \brief Paramétrer l'abscisse pour l'affichage du carré'
	 *
	 * Cette fonction permet de modifier l'abscisse du carré permmettant
	 * d'avoir un bon affichage pour le jeu.
	 *
	 * \param x_ entier indiquant l'abscisse pour le bon affichage du carré
	 */
	void set_box_x(int x_);

	/**
	 * \brief Paramétrer l'ordonnée pour l'affichage du carré'
	 *
	 * Cette fonction permet de modifier l'ordonnée du carré permmettant
	 * d'avoir un bon affichage pour le jeu.
	 *
	 * \param y_ entier indiquant l'ordonnée pour le bon affichage du carré
	 */
	void set_box_y(int y_);
};

#endif
