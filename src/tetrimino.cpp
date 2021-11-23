#include "tetrimino.h"
#include <iostream>


SDL_Color black = {0,0,0,255};
SDL_Color white = {255,255,255,255};
SDL_Color red = {255,0,0,255};
SDL_Color lime = {0,255,0,255};
SDL_Color blue = {0,0,255,255};
SDL_Color yellow = {255,255,0,255};
SDL_Color cyan = {0,255,255,255};
SDL_Color magenta = {255,0,255,255};
SDL_Color silver = {192,192,192,255};
SDL_Color gray = {128,128,128,255};
SDL_Color maroon {128,0,0,255};
SDL_Color olive = {128,128,0,255};
SDL_Color green = {0,128,0,255};
SDL_Color purple = {128,0,128,255};
SDL_Color teal = {0,128,128,255};
SDL_Color navy = {0,0,128,255};



Tetrimino::Tetrimino(int type_, int speed_):
    type(type_), speed(speed_), etat (0)
{}

Tetrimino::~Tetrimino() {}

int Tetrimino::get_type() {return type;}
int Tetrimino::get_speed() {return speed;}
int Tetrimino::get_etat() {return etat;}
int Tetrimino::get_prev_etat() {return prev_etat;}

Square * Tetrimino::get_shape(int i) {return shape[i];}


void Tetrimino::set_speed(int speed_) {speed = speed_;}
void Tetrimino::set_etat(int etat_) {etat = etat_;}
void Tetrimino::set_prev_etat(int prev_etat_) {prev_etat = prev_etat_;}

bool Tetrimino::check_out(Square* tetris_array_[20][10])
{
	int line, column;

	for (int i = 0; i < 4; i++)
	{
		line = shape[i]->get_line();
		column = shape[i]->get_column();

		if (line < 0 || line >= 20 || column < 0 || column >= 10)
			return true;

		if (tetris_array_[line][column] != nullptr)
			return true;
	}
	return false;
}


Tetri_O::Tetri_O(int type_, int speed_):
    Tetrimino(type_, speed_)
{
    shape[0] = new Square(blue,  0, 3);
    shape[1] = new Square(blue,  0, 4);
    shape[2] = new Square(blue,  1, 4);
    shape[3] = new Square(blue, 1, 3);
};

Tetri_O::~Tetri_O()
{
	for (int i=0; i < 4; i++)
		delete shape[i];
}

void Tetri_O::rotate(Square* tetris_array_[20][10])
{

	int line = shape[2]->get_line();
	int column= shape[2]->get_column();
	bool out = true;

	while (out)
	{
		switch (etat)
		{
			case 0 :
				shape[0]->set_column(column - 1);
				shape[0]->set_line(line - 1);

			        shape[1]->set_column(column);
				shape[1]->set_line(line - 1);

				shape[3]->set_column(column - 1);
				shape[3]->set_line(line);
				break;

			case 1 :
			case -3 :
			        shape[0]->set_column(column + 1);
				shape[0]->set_line(line - 1);

			        shape[1]->set_column(column + 1);
				shape[1]->set_line(line);

				shape[3]->set_column(column);
				shape[3]->set_line(line - 1);
				break;
			case 2 :
			case -2:
				shape[0]->set_column(column + 1);
			        shape[0]->set_line(line + 1);

			        shape[1]->set_column(column);
				shape[1]->set_line(line + 1);

				shape[3]->set_column(column + 1);
				shape[3]->set_line(line);
				break;
			case 3 :
			case -1:
			        shape[0]->set_column(column - 1);
				shape[0]->set_line(line + 1);

			        shape[1]->set_column(column - 1);
				shape[1]->set_line(line);

				shape[3]->set_column(column);
				shape[3]->set_line(line + 1);
				break;

		}
		if ((out = check_out( tetris_array_ )))
			etat = prev_etat;
	}

}


Tetri_T::Tetri_T(int type_, int speed_) :
    Tetrimino(type_, speed_)
{
    shape[0] = new Square(red,  0, 4);
    shape[1] = new Square(red,  1, 3);
    shape[2] = new Square(red,  1, 4);
    shape[3] = new Square(red,  1, 5);
}

Tetri_T::~Tetri_T()
{
	for (int i=0; i < 4; i++)
		delete shape[i];
}

void Tetri_T::rotate(Square* tetris_array_[20][10])
{
	int line = shape[2]->get_line();
	int column= shape[2]->get_column();
	bool out = true;

    std::vector<std::pair<int,int>> prev_shape(4, std::pair<int,int>(0,0));
    for (int i = 0; i < 4; i++)
    {
        prev_shape.at(i).first = shape[i]->get_line();
        prev_shape.at(i).second = shape[i]->get_column();
    }
    
    switch (etat)
    {
        case 0 :
        shape[0]->set_column(column);
        shape[0]->set_line(line - 1);

        shape[1]->set_column(column - 1);
        shape[1]->set_line(line);

        shape[3]->set_column(column + 1);
        shape[3]->set_line(line);
            break;

        case 1 :
    case -3 :
        shape[0]->set_column(column + 1);
        shape[0]->set_line(line);

        shape[1]->set_column(column);
        shape[1]->set_line(line - 1);

        shape[3]->set_column(column);
        shape[3]->set_line(line + 1);
            break;
        case 2 :
    case -2 :
        shape[0]->set_column(column);
        shape[0]->set_line(line + 1);

        shape[1]->set_column(column + 1);
        shape[1]->set_line(line);

        shape[3]->set_column(column - 1);
        shape[3]->set_line(line);
            break;
        case 3 :
    case -1:
        shape[0]->set_column(column - 1);
        shape[0]->set_line(line);

        shape[1]->set_column(column);
        shape[1]->set_line(line + 1);

        shape[3]->set_column(column);
        shape[3]->set_line(line - 1);
            break;

    }
    if (check_out( tetris_array_ ))
    {
        etat = prev_etat;
        for (int i = 0; i < 4; i++)
        {
            shape[i]->set_column(prev_shape.at(i).second);
            shape[i]->set_line(prev_shape.at(i).first);
        }
        
    }
}


Tetri_L::Tetri_L(int type_, int speed_):
    Tetrimino(type_, speed_)
{
    shape[0] = new Square(lime,  0, 4);
    shape[1] = new Square(lime,  1, 4);
    shape[2] = new Square(lime,  2, 4);
    shape[3] = new Square(lime,  2, 5);
}

Tetri_L::~Tetri_L()
{
	for (int i=0; i < 4; i++)
		delete shape[i];
}

void Tetri_L::rotate(Square* tetris_array_[20][10])
{

	int line = shape[2]->get_line();
	int column= shape[2]->get_column();
	
    std::vector<std::pair<int,int>> prev_shape(4, std::pair<int,int>(0,0));
    for (int i = 0; i < 4; i++)
    {
        prev_shape.at(i).first = shape[i]->get_line();
        prev_shape.at(i).second = shape[i]->get_column();
    }

    switch (etat)
    {
        case 0 :
        shape[0]->set_column(column);
        shape[0]->set_line(line - 2);

        shape[1]->set_column(column);
        shape[1]->set_line(line - 1);

        shape[3]->set_column(column + 1);
        shape[3]->set_line(line);
            break;

        case 1 :
    case -3:
        shape[0]->set_column(column + 2);
        shape[0]->set_line(line);

        shape[1]->set_column(column + 1);
        shape[1]->set_line(line);

        shape[3]->set_column(column);
        shape[3]->set_line(line + 1);
            break;
        case 2 :
    case -2:
        shape[0]->set_column(column);
        shape[0]->set_line(line + 2);

        shape[1]->set_column(column);
        shape[1]->set_line(line + 1);

        shape[3]->set_column(column - 1);
        shape[3]->set_line(line);
            break;
        case 3 :
    case -1 :
        shape[0]->set_column(column - 2);
        shape[0]->set_line(line);

        shape[1]->set_column(column - 1);
        shape[1]->set_line(line);

        shape[3]->set_column(column);
        shape[3]->set_line(line - 1);
            break;

    }
    if (check_out( tetris_array_ ))
    {
        etat = prev_etat;
        for (int i = 0; i < 4; i++)
        {
            shape[i]->set_column(prev_shape.at(i).second);
            shape[i]->set_line(prev_shape.at(i).first);
        }
        
    }
}



Tetri_J::Tetri_J(int type_, int speed_):
    Tetrimino(type_, speed_)
{
	shape[0] = new Square(yellow,  0, 4);
        shape[1] = new Square(yellow,  1, 4);
        shape[2] = new Square(yellow,  2, 4);
        shape[3] = new Square(yellow,  2, 3);
}

Tetri_J::~Tetri_J()
{
	for (int i=0; i < 4; i++)
		delete shape[i];
}

void Tetri_J::rotate(Square* tetris_array_[20][10])
{

	int line = shape[2]->get_line();
	int column= shape[2]->get_column();

    std::vector<std::pair<int,int>> prev_shape(4, std::pair<int,int>(0,0));
    for (int i = 0; i < 4; i++)
    {
        prev_shape.at(i).first = shape[i]->get_line();
        prev_shape.at(i).second = shape[i]->get_column();
    }

    switch (etat)
    {
    case 0 :
        shape[0]->set_column(column);
        shape[0]->set_line(line - 2);

        shape[1]->set_column(column);
        shape[1]->set_line(line - 1);

        shape[3]->set_column(column - 1);
        shape[3]->set_line(line);
        break;

        case 1 :
            case -3:
        shape[0]->set_column(column + 2);
        shape[0]->set_line(line);

        shape[1]->set_column(column + 1);
        shape[1]->set_line(line);

        shape[3]->set_column(column);
        shape[3]->set_line(line - 1);
        break;

        case 2 :
            case -2:
        shape[0]->set_column(column);
        shape[0]->set_line(line + 2);

        shape[1]->set_column(column);
        shape[1]->set_line(line + 1);

        shape[3]->set_column(column + 1);
        shape[3]->set_line(line);
        break;

        case 3 :
            case -1 :
        shape[0]->set_column(column - 2);
        shape[0]->set_line(line);

        shape[1]->set_column(column - 1);
        shape[1]->set_line(line);

        shape[3]->set_column(column);
        shape[3]->set_line(line + 1);
        break;

    }
    if (check_out( tetris_array_ ))
    {
        etat = prev_etat;
        for (int i = 0; i < 4; i++)
        {
            shape[i]->set_column(prev_shape.at(i).second);
            shape[i]->set_line(prev_shape.at(i).first);
        }
        
    }
}

Tetri_Z::Tetri_Z(int type_, int speed_):
    Tetrimino(type_, speed_)
{
    shape[0] = new Square(cyan,  0, 3);
    shape[1] = new Square(cyan,  0, 4);
    shape[2] = new Square(cyan,  1, 4);
    shape[3] = new Square(cyan,  1, 5);
}

Tetri_Z::~Tetri_Z()
{
	for (int i=0; i < 4; i++)
		delete shape[i];
}

void Tetri_Z::rotate(Square* tetris_array_[20][10])
{

	int line = shape[2]->get_line();
	int column= shape[2]->get_column();

    std::vector<std::pair<int,int>> prev_shape(4, std::pair<int,int>(0,0));
    for (int i = 0; i < 4; i++)
    {
        prev_shape.at(i).first = shape[i]->get_line();
        prev_shape.at(i).second = shape[i]->get_column();
    }

    switch (etat)
    {
        case 0 :
        shape[0]->set_column(column - 1);
        shape[0]->set_line(line-1);

        shape[1]->set_column(column);
        shape[1]->set_line(line - 1);

        shape[3]->set_column(column + 1);
        shape[3]->set_line(line);
            break;
        case 1 :
    case -3:
        shape[0]->set_column(column+1);
        shape[0]->set_line(line - 1);

        shape[1]->set_column(column + 1);
        shape[1]->set_line(line);

        shape[3]->set_column(column);
        shape[3]->set_line(line + 1);
            break;
        case 2 :
    case -2:
        shape[0]->set_column(column + 1);
        shape[0]->set_line(line + 1);

        shape[1]->set_column(column);
        shape[1]->set_line(line + 1);

        shape[3]->set_column(column - 1);
        shape[3]->set_line(line);
            break;
        case 3 :
    case -1:
        shape[0]->set_column(column-1);
        shape[0]->set_line(line + 1);

        shape[1]->set_column(column - 1);
        shape[1]->set_line(line);

        shape[3]->set_column(column);
        shape[3]->set_line(line - 1);
            break;

    }

    if (check_out( tetris_array_ ))
    {
        etat = prev_etat;
        for (int i = 0; i < 4; i++)
        {
            shape[i]->set_column(prev_shape.at(i).second);
            shape[i]->set_line(prev_shape.at(i).first);
        }
        
    }
}

Tetri_S::Tetri_S(int type_, int speed_):
    Tetrimino(type_, speed_)
{
    shape[0] = new Square(magenta,  0, 5);
    shape[1] = new Square(magenta,  0, 4);
    shape[2] = new Square(magenta,  1, 4);
    shape[3] = new Square(magenta,  1, 3);
}

Tetri_S::~Tetri_S()
{
	for (int i=0; i < 4; i++)
		delete shape[i];
}

void Tetri_S::rotate(Square* tetris_array_[20][10])
{

	int line = shape[2]->get_line();
	int column= shape[2]->get_column();
    std::vector<std::pair<int,int>> prev_shape(4, std::pair<int,int>(0,0));
    for (int i = 0; i < 4; i++)
    {
        prev_shape.at(i).first = shape[i]->get_line();
        prev_shape.at(i).second = shape[i]->get_column();
    }

    switch (etat)
    {
        case 0 :
        shape[0]->set_column(column + 1);
        shape[0]->set_line(line - 1);

        shape[1]->set_column(column);
        shape[1]->set_line(line - 1);

        shape[3]->set_column(column - 1);
        shape[3]->set_line(line);
        break;

        case 1 :
    case -3:
        shape[0]->set_column(column + 1);
        shape[0]->set_line(line + 1);

        shape[1]->set_column(column + 1);
        shape[1]->set_line(line);

        shape[3]->set_column(column);
        shape[3]->set_line(line - 1);
        break;
        case 2 :
    case -2:
        shape[0]->set_column(column - 1);
        shape[0]->set_line(line + 1);

        shape[1]->set_column(column);
        shape[1]->set_line(line + 1);

        shape[3]->set_column(column + 1);
        shape[3]->set_line(line);
        break;
        case 3 :
    case -1:
        shape[0]->set_column(column - 1);
        shape[0]->set_line(line - 1);

        shape[1]->set_column(column - 1);
        shape[1]->set_line(line);

        shape[3]->set_column(column);
        shape[3]->set_line(line + 1);
        break;

    }

    if (check_out( tetris_array_ ))
    {
        etat = prev_etat;
        for (int i = 0; i < 4; i++)
        {
            shape[i]->set_column(prev_shape.at(i).second);
            shape[i]->set_line(prev_shape.at(i).first);
        }
        
    }
}

Tetri_I::Tetri_I(int type_, int speed_):
    Tetrimino(type_, speed_)
{
    shape[0] = new Square(teal, 0, 5);
    shape[1] = new Square(teal, 1, 5);
    shape[2] = new Square(teal, 2, 5);
    shape[3] = new Square(teal, 3, 5);
}

Tetri_I::~Tetri_I()
{
	for (int i=0; i < 4; i++)
		delete shape[i];
}

void Tetri_I::rotate(Square* tetris_array_[20][10])
{

	int line = shape[2]->get_line();
	int column= shape[2]->get_column();

    std::vector<std::pair<int,int>> prev_shape(4, std::pair<int,int>(0,0));
    for (int i = 0; i < 4; i++)
    {
        prev_shape.at(i).first = shape[i]->get_line();
        prev_shape.at(i).second = shape[i]->get_column();
    }

    switch (etat)
    {
        case 3 :
    case -1:
        shape[0]->set_column(column - 2);
        shape[0]->set_line(line);

        shape[1]->set_column(column - 1);
        shape[1]->set_line(line);

        shape[3]->set_column(column + 1);
        shape[3]->set_line(line);
            break;
        case 0 :
        shape[0]->set_column(column);
        shape[0]->set_line(line - 2);

        shape[1]->set_column(column);
        shape[1]->set_line(line - 1);

        shape[3]->set_column(column);
        shape[3]->set_line(line + 1);
            break;
        case 1 :
    case -3 :
        shape[0]->set_column(column + 2);
        shape[0]->set_line(line);

        shape[1]->set_column(column + 1);
        shape[1]->set_line(line);

        shape[3]->set_column(column - 1);
        shape[3]->set_line(line);
            break;
        case 2 :
    case -2:
        shape[0]->set_column(column);
        shape[0]->set_line(line + 2);

        shape[1]->set_column(column);
        shape[1]->set_line(line + 1);

        shape[3]->set_column(column);
        shape[3]->set_line(line - 1);
            break;

    }

    if (check_out( tetris_array_ ))
    {
        etat = prev_etat;
        for (int i = 0; i < 4; i++)
        {
            shape[i]->set_column(prev_shape.at(i).second);
            shape[i]->set_line(prev_shape.at(i).first);
        }
        
    }
}
