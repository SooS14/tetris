#ifndef _TETRIMINO_H
#define _TETRIMINO_H

#include <vector>
#include "square.h"


extern SDL_Color black;
extern SDL_Color white;
extern SDL_Color red;
extern SDL_Color lime;
extern SDL_Color blue;
extern SDL_Color yellow;
extern SDL_Color cyan;
extern SDL_Color magenta;
extern SDL_Color silver;
extern SDL_Color gray;
extern SDL_Color maroon;
extern SDL_Color olive;
extern SDL_Color green;
extern SDL_Color purple;
extern SDL_Color teal;
extern SDL_Color navy;



class Tetrimino
{
private:
	int type;
	int speed;
protected:
	int prev_etat;
	int etat;

	Square * shape[4];

public:
	/**
	 * \brief Construction d'un tetrimino
	 *
	 * Cette fonction permet de créer un tetrimino
	 *
	 * \param type_ entier indiquant le type du tetrimino
	 * \param speed_ entier indiquant la vitesse du tetrimino
	 * \return Constructeur de Tetrimino
	 */
	Tetrimino(int type_, int speed_);

	/**
	 * \brief Détruire un tetrimino
	 *
	 * Cette fonction permet de "détruire" un tetrimino.
	 *
	 * \return Destructeur de Tetrimino
	 */
	~Tetrimino();

	/**
	 * \brief Obtention type du tetrimino
	 *
	 * Cette fonction permet d'obtenir le type du tetrimino (barre, carré,
	 * escalier...).
	 *
	 * \return 0 si le tetrimino est un carré
	 * 	   1 si le tetrimino est un T à l'envers
	 * 	   2 si le tetrimino est un L
	 * 	   3 si le tetrimino est un J
	 * 	   4 si le tetrimino est un I
	 * 	   5 si le tetrimino est un S
	 * 	   6 si le tetrimino est un Z
	 */
	int get_type();

	/**
	 * \brief Obtention vitesse du tetrimino
	 *
	 * Cette fonction permet d'obtenir la vitesse du tetrimino.
	 *
	 * \return entier indiquant la vitesse du tetrimino
	 */
	int get_speed();

	/**
	 * \brief Obtention état de rotation du tetrimino
	 *
	 * Cette fonction permet d'obtenir l'état de rotation dans lequel
	 * se trouve le tetrimino.
	 *
	 * \return entier indiquant l'état de rotation' du tetrimino
	 */
	int get_etat();

	/**
	 * \brief Obtention précédent état de rotation du tetrimino
	 *
	 * Cette fonction permet d'obtenir l'état de rotation précédent
	 * l'actuel. Cela permet de gérer des problèmes d'affichage lié à une
	 * collision avec une autre pièce ou avec un bord du terrain de jeu.
	 *
	 * \return entier indiquant le précédent état de rotation' du tetrimino
	 */
	int get_prev_etat();

	/**
	 * \brief Obtention de la forme du tetrimino
	 *
	 * Cette fonction permet d'obtenir la forme dans lequel se trouve le
	 * tetrimino.
	 *
	 * \return Tableau de Square renseignant la forme du tetrimino
	 */
	Square * get_shape (int i);

	/**
	 * \brief Paramétrer la vitesse du tetrimino
	 *
	 * Cette fonction permet de modifier la vitesse du tetrimino.
	 *
	 * \param speed_ entier indiquant la vitesse souhaitée du tetrimino
	 */
	void set_speed(int speed_);

	/**
	 * \brief Paramétrer l'état de rotation' du tetrimino
	 *
	 * Cette fonction permet de modifier l'état de rotation du tetrimino.
	 *
	 * \param etat_ entier indiquant l'état de rotation souhaitée
	 * du tetrimino
	 */
	void set_etat(int etat_);

	/**
	 * \brief Paramétrer le précédent état de rotation' du tetrimino
	 *
	 * Cette fonction permet de modifier le précédent état de rotation
	 * du tetrimino'.
	 *
	 * \param prev_etat_ entier indiquant le précédent état de rotation
	 * du tetrimino
	 */
	void set_prev_etat(int prev_etat_);

	/**
	 * \brief Vérification bon paramétrage tetrimino
	 *
	 * Cette fonction permet de déterminer si le tetrimino ne sort pas du
	 * terrain de jeu.
	 *
	 * \param tetris_array_ pointeur vers le terrain de jeu, ayant pour
	 * valeur nullptr s'il n'y a aucun carré de tetrimino présent sur la
	 * case
	 * \return un booléen true si le tetrimino sort du terrain de jeu,
	 * false sinon
	 */
	bool check_out(Square* tetris_array_[20][10]);

	/**
	 * \brief Rotation du tetrimino
	 *
	 * Cette fonction va permettre l'héritage de la rotation.
	 *
	 * \param tetris_array_ pointeur vers le terrain de jeu, ayant pour
	 * valeur nullptr s'il n'y a aucun carré de tetrimino présent sur la
	 * case
	 */
	virtual void rotate(Square* tetris_array_[20][10]) = 0;
};



class Tetri_O : public Tetrimino
{
public:
	/**
	 * \brief Construction du tetrimino carré
	 *
	 * Cette fonction permet de créer le tetrimino carré.
	 *
	 * \param type_ entier indiquant le type du tetrimino
	 * \param speed_ entier indiquant la vitesse du tetrimino
	 * \return Constructeur de Tetri_0
	 */
	Tetri_O(int type_, int speed_);

	/**
	 * \brief Détruire le tetrimino carré
	 *
	 * Cette fonction permet de désallouer le tableau de forme du tetrimino.
	 *
	 * \return Destructeur de Tetri_O
	 */
	~Tetri_O();

	/**
	 * \brief Rotation du tetrimino carré
	 *
	 * Cette fonction énumère les différentes rotations de ce tetrimino.
	 * Et avec la valeur de etat, elle en déduit la bonne rotation, en plus
	 * de déterminer si l'on ne sort pas du terrain de jeu.
	 *
 	 * \param tetris_array_ pointeur vers le terrain de jeu, ayant pour
 	 * valeur nullptr s'il n'y a aucun carré de tetrimino présent sur la
 	 * case
	 */
	void rotate(Square* tetris_array_[20][10]);
};



class Tetri_T : public Tetrimino
{
public:
	/**
	 * \brief Construction du tetrimino en forme de T à l'envers
	 *
	 * Cette fonction permet de créer le tetrimino en forme de T à l'envers.
	 *
	 * \param type_ entier indiquant le type du tetrimino
	 * \param speed_ entier indiquant la vitesse du tetrimino
	 * \return Constructeur de Tetri_T
	 */
	Tetri_T(int type_, int speed_);

	/**
	 * \brief Détruire le tetrimino en forme de T à l'envers
	 *
	 * Cette fonction permet de désallouer le tableau de forme du tetrimino.
	 *
	 * \return Destructeur de Tetri_T
	 */
	~Tetri_T();

	/**
	 * \brief Rotation du tetrimino en forme de T à l'envers
	 *
	 * Cette fonction énumère les différentes rotations de ce tetrimino.
	 * Et avec la valeur de etat, elle en déduit la bonne rotation, en plus
	 * de déterminer si l'on ne sort pas du terrain de jeu.
	 *
  	 * \param tetris_array_ pointeur vers le terrain de jeu, ayant pour
 	 * valeur nullptr s'il n'y a aucun carré de tetrimino présent sur la
 	 * case
	 */
	void rotate(Square* tetris_array_[20][10]);
};




class Tetri_L : public Tetrimino
{
public:
	/**
	 * \brief Construction du tetrimino en forme de L
	 *
	 * Cette fonction permet de créer le tetrimino en forme de L.
	 *
	 * \param type_ entier indiquant le type du tetrimino
	 * \param speed_ entier indiquant la vitesse du tetrimino
	 * \return Constructeur de Tetri_L
	 */
	Tetri_L(int type_, int speed_);

	/**
	 * \brief Détruire le tetrimino en forme de L
	 *
	 * Cette fonction permet de désallouer le tableau de forme du tetrimino.
	 *
	 * \return Destructeur de Tetri_L
	 */
	~Tetri_L();

	/**
	 * \brief Rotation du tetrimino en forme de L
	 *
	 * Cette fonction énumère les différentes rotations de ce tetrimino.
	 * Et avec la valeur de etat, elle en déduit la bonne rotation, en plus
	 * de déterminer si l'on ne sort pas du terrain de jeu.
	 *
  	 * \param tetris_array_ pointeur vers le terrain de jeu, ayant pour
 	 * valeur nullptr s'il n'y a aucun carré de tetrimino présent sur la
 	 * case
	 */
	void rotate(Square* tetris_array_[20][10]);
};




class Tetri_J : public Tetrimino
{
public:
	/**
	 * \brief Construction du tetrimino en forme de J
	 *
	 * Cette fonction permet de créer le tetrimino en forme de J.
	 *
	 * \param type_ entier indiquant le type du tetrimino
	 * \param speed_ entier indiquant la vitesse du tetrimino
	 * \return Constructeur de Tetri_J
	 */
	Tetri_J(int type_, int speed_);

	/**
	 * \brief Détruire le tetrimino en forme de J
	 *
	 * Cette fonction permet de désallouer le tableau de forme du tetrimino.
	 *
	 * \return Destructeur de Tetri_J
	 */
	~Tetri_J();

	/**
	 * \brief Rotation du tetrimino en forme de J
	 *
	 * Cette fonction énumère les différentes rotations de ce tetrimino.
	 * Et avec la valeur de etat, elle en déduit la bonne rotation, en plus
	 * de déterminer si l'on ne sort pas du terrain de jeu.
	 *
  	 * \param tetris_array_ pointeur vers le terrain de jeu, ayant pour
 	 * valeur nullptr s'il n'y a aucun carré de tetrimino présent sur la
 	 * case
	 */
	void rotate(Square* tetris_array_[20][10]);
};




class Tetri_Z : public Tetrimino
{
public:
	/**
	 * \brief Construction du tetrimino en forme de Z
	 *
	 * Cette fonction permet de créer le tetrimino en forme de Z.
	 *
	 * \param type_ entier indiquant le type du tetrimino
	 * \param speed_ entier indiquant la vitesse du tetrimino
	 * \return Constructeur de Tetri_Z
	 */
	Tetri_Z(int type_, int speed_);

	/**
	 * \brief Détruire le tetrimino en forme de Z
	 *
	 * Cette fonction permet de désallouer le tableau de forme du tetrimino.
	 *
	 * \return Destructeur de Tetri_Z
	 */
	~Tetri_Z();

	/**
	 * \brief Rotation du tetrimino en forme de Z
	 *
	 * Cette fonction énumère les différentes rotations de ce tetrimino.
	 * Et avec la valeur de etat, elle en déduit la bonne rotation, en plus
	 * de déterminer si l'on ne sort pas du terrain de jeu.
	 *
  	 * \param tetris_array_ pointeur vers le terrain de jeu, ayant pour
 	 * valeur nullptr s'il n'y a aucun carré de tetrimino présent sur la
 	 * case
	 */
	void rotate(Square* tetris_array_[20][10]);
};



class Tetri_S : public Tetrimino
{
public:
	/**
	 * \brief Construction du tetrimino en forme de S
	 *
	 * Cette fonction permet de créer le tetrimino en forme de S.
	 *
	 * \param type_ entier indiquant le type du tetrimino
	 * \param speed_ entier indiquant la vitesse du tetrimino
	 * \return Constructeur de Tetri_S
	 */
	Tetri_S(int type_, int speed_);

	/**
	 * \brief Détruire le tetrimino en forme de S
	 *
	 * Cette fonction permet de désallouer le tableau de forme du tetrimino.
	 *
	 * \return Destructeur de Tetri_S
	 */
	~Tetri_S();

	/**
	 * \brief Rotation du tetrimino en forme de S
	 *
	 * Cette fonction énumère les différentes rotations de ce tetrimino.
	 * Et avec la valeur de etat, elle en déduit la bonne rotation, en plus
	 * de déterminer si l'on ne sort pas du terrain de jeu.
	 *
  	 * \param tetris_array_ pointeur vers le terrain de jeu, ayant pour
 	 * valeur nullptr s'il n'y a aucun carré de tetrimino présent sur la
 	 * case
	 */
	void rotate(Square* tetris_array_[20][10]);
};




class Tetri_I : public Tetrimino
{
public:
	/**
	 * \brief Construction du tetrimino en forme de I
	 *
	 * Cette fonction permet de créer le tetrimino en forme de I.
	 *
	 * \param type_ entier indiquant le type du tetrimino
	 * \param speed_ entier indiquant la vitesse du tetrimino
	 * \return Constructeur de Tetri_I
	 */
	Tetri_I(int type_, int speed_);

	/**
	 * \brief Détruire le tetrimino en forme de I
	 *
	 * Cette fonction permet de désallouer le tableau de forme du tetrimino.
	 *
	 * \return Destructeur de Tetri_I
	 */
	~Tetri_I();

	/**
	 * \brief Rotation du tetrimino en forme de I
	 *
	 * Cette fonction énumère les différentes rotations de ce tetrimino.
	 * Et avec la valeur de etat, elle en déduit la bonne rotation, en plus
	 * de déterminer si l'on ne sort pas du terrain de jeu.
	 *
  	 * \param tetris_array_ pointeur vers le terrain de jeu, ayant pour
 	 * valeur nullptr s'il n'y a aucun carré de tetrimino présent sur la
 	 * case
	 */
	void rotate(Square* tetris_array_[20][10]);
};


#endif
