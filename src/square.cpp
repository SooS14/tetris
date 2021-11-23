#include "square.h"



Square::Square(SDL_Color color_, int line_, int column_):
    line(line_), column(column_), color(color_)
{
	box.x = 100 + column * 40;
	box.y = 40 + line * 40;
	box.h = 40;
	box.w = 40;
}

Square::~Square()
{
}

int Square::get_line() {return line;}
int Square::get_column() {return column;}
SDL_Rect Square::get_box() {return box;}
SDL_Color Square::get_color() {return color;}

void Square::set_line(int line_) {line = line_;}
void Square::set_column(int column_) {column = column_;}
void Square::set_box_x(int x) {box.x = x;}
void Square::set_box_y(int y) {box.y = y;}
