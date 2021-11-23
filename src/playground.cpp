#include "playground.h"
#include "check.h"
#include "tetrimino.h"
#include <algorithm>
#include <stdlib.h>

#define DEBUG false


void Playground::print_tetris_array()
{
    std::cout << "##########################\n";
    std::cout << "    ";
    for (int i = 0; i < nb_column; i++)
    {
        std::cout << " i ";
    }
    std::cout << "\n";
    for (int i = 0; i < nb_line; i++)
    {
        std::cout << i << " : ";
        for (int j = 0; j < nb_column; j++)
        {
            if (tetris_array[i][j])
            {
                std::cout << " 1 ";
            }
            else
            {
                std::cout << " 0 ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n\n";

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect test{100,40+40*19,40,40};
    SDL_RenderFillRect(renderer, &test);
}


void Playground::print_current_tetrimino_info()
{
    std::cout << "curr : " << current_tetrimino->get_speed() << "\n";
    for (int i = 0; i < 4; i++)
    {
        std::cout << i << " line : " << current_tetrimino->get_shape(i)->get_line()
            << " col : " << current_tetrimino->get_shape(i)->get_column() << "\n";
        std::cout << i << " x : " << current_tetrimino->get_shape(i)->get_box().x << " y : "
            << current_tetrimino->get_shape(i)->get_box().y << "\n";
    }
}


Playground::Playground()
{
    window = SDL_CreateWindow("TETRIS Playground", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              800, 900, SDL_WINDOW_SHOWN);
    check(window);
    renderer = SDL_CreateRenderer(window, -1, 0);
    check(renderer);
    for (int i = 0; i < nb_line; i++)
    {
        for (int j = 0; j < nb_column; j++)
        {
            Square * empty = nullptr;
            tetris_array[i][j] = empty;
        }
    }
    srand((unsigned) time(&t));
    tetrimino_cache[0] = new Tetri_Z(6,1);
    tetrimino_cache[1] = new Tetri_T(1,1);

    font = TTF_OpenFont("font/arial.ttf",10);
    if (font == nullptr)
    {
        std::cout << "TTF_OpenFont: " <<  TTF_GetError() << "\n";
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    end_texture = IMG_LoadTexture(renderer, "png_models/game_over.png");
    if (end_texture == nullptr)
    {
        std::cout << "IMG_LoadTexture: " <<  TTF_GetError() << "\n";
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    start_texture = IMG_LoadTexture(renderer, "png_models/nuclear_explosion.png");
    if (end_texture == nullptr)
    {
        std::cout << "IMG_LoadTexture: " <<  TTF_GetError() << "\n";
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

}


Playground::~Playground()
{
    if (renderer != nullptr)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window != nullptr)
    {
        SDL_DestroyWindow(window);
    }
    for (int i = 0; i < nb_line; i++)
    {
        for (int j = 0; j < nb_column; j++)
        {
            if (tetris_array[i][j] != nullptr)
            {
                delete tetris_array[i][j];
            }
        }
    }
    TTF_CloseFont(font);
}


void Playground::write_texte(const char * text, int x, int y, int w, int h, SDL_Color color)
{
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect{x,y,w,h};

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}



void Playground::draw_start_screen()
{
    int w, h;
    SDL_QueryTexture(start_texture, NULL, NULL, &w, &h);
    SDL_Rect texr; texr.x = 0; texr.y = 0; texr.w = w; texr.h = h;

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, start_texture, NULL, &texr);

    write_texte("We are at war comrade !", 50,20,700,150, red);
    write_texte("You must protect motherland !",50,550,700,150, white);
    write_difficulty(300,800,200,100);
    write_texte("N -> menu",75,800,100,40, white);
    write_texte("C -> continue",600,800,100,40, white);
    SDL_RenderPresent(renderer);
}


void Playground::draw_start_screen_ia()
{
    int w, h;
    SDL_QueryTexture(start_texture, NULL, NULL, &w, &h);
    SDL_Rect texr; texr.x = 0; texr.y = 0; texr.w = w; texr.h = h;

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, start_texture, NULL, &texr);

    write_texte("We are at war comrade !", 50,20,700,150, red);
    write_texte("Place the pieces by turns and", 50,550,700,150, white);
    write_texte("complete as many lines as possible !", 50,650,700,150, white);

    write_difficulty(300, 800, 200, 100);

    write_texte("N -> menu",50,800,100,40, white);
    write_texte("C -> continue",600,800,100,40, white);
    SDL_RenderPresent(renderer);
}



void Playground::draw_game_over_screen()
{
    int w, h;
    SDL_QueryTexture(end_texture, NULL, NULL, &w, &h);
    SDL_Rect texr; texr.x = 0; texr.y = 0; texr.w = w; texr.h = h;

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, end_texture, NULL, &texr);

    write_texte("You have failed the CCCP comrade !", 50,100,700,125, white);
    write_texte("You lost the war against the capitalist pigs !", 50,250,700,125, white);
    write_texte("C -> continue", 550,700,200,75, white);
    draw_score(300,500,200,100);
}


void Playground::draw_game_over_screen_ia()
{
    int w, h;
    SDL_QueryTexture(end_texture, NULL, NULL, &w, &h);
    SDL_Rect texr; texr.x = 0; texr.y = 0; texr.w = w; texr.h = h;

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, end_texture, NULL, &texr);

    write_texte("The war is over comrade !", 50,100,700,150, white);
    write_texte("C -> continue", 550,700,200,100, white);
    draw_score_ia(300,300,200,100);
}


void Playground::write_difficulty(int x, int y, int w, int h)
{
    switch (difficulty)
    {
    case 0:
        write_texte("Sandbox",x,y,w,h,white);
        break;
    case 1:
        write_texte("Medium",x,y,w,h,white);
        break;
    case 2:
        write_texte("Hard",x,y,w,h,white);
        break;
    case 3:
        write_texte("Real Soviet !",x,y,w,h,white);
        break;
    default:
        break;
    }
}

void Playground::draw_playground()
{
    int line = 0;
    int column = 0;
    SDL_Color tmp;
    SDL_Rect box{100,40,400,800};
    SDL_Rect new_box;

    check_0(SDL_SetRenderDrawColor(renderer, gray.r, gray.g, gray.b, gray.a));
    check_0(SDL_RenderClear(renderer));


    SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
    SDL_RenderFillRect(renderer, &box);


    for (int i = 0; i < 4; i++)
    {
        tmp = tetrimino_cache[1]->get_shape(i)->get_color();
        SDL_SetRenderDrawColor(renderer, tmp.r, tmp.g, tmp.b, tmp.a);

        line = tetrimino_cache[1]->get_shape(i)->get_line();
        column = tetrimino_cache[1]->get_shape(i)->get_column();
        tetrimino_cache[1]->get_shape(i)->set_box_x(450 + column * 40);
        tetrimino_cache[1]->get_shape(i)->set_box_y(650 + line * 40);
	new_box = tetrimino_cache[1]->get_shape(i)->get_box();
        SDL_RenderFillRect(renderer, &(new_box));
    }

    for (int i = 0; i < 4; i++)
    {
        tmp = current_tetrimino->get_shape(i)->get_color();
        SDL_SetRenderDrawColor(renderer, tmp.r, tmp.g, tmp.b, tmp.a);

        line = current_tetrimino->get_shape(i)->get_line();
        column = current_tetrimino->get_shape(i)->get_column();
        current_tetrimino->get_shape(i)->set_box_x(100 + column * 40);
        current_tetrimino->get_shape(i)->set_box_y(40 + line * 40);
	new_box = current_tetrimino->get_shape(i)->get_box();
        SDL_RenderFillRect(renderer, &(new_box));
    }


    for (int i = 0; i < nb_line; i++)
    {
        for (int j = 0; j < nb_column; j++)
        {
            if (tetris_array[i][j] != nullptr)
            {
                tmp = tetris_array[i][j]->get_color();
                SDL_SetRenderDrawColor(renderer, tmp.r, tmp.g, tmp.b, tmp.a);
		new_box = tetris_array[i][j]->get_box();
                SDL_RenderFillRect(renderer, &(new_box));
            }
        }
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < nb_line+1; i++)
    {
        SDL_RenderDrawLine(renderer, 100, 40+i*40, 500,40+i*40);
    }
    for (int j = 0; j < nb_column+1; j++)
    {
        SDL_RenderDrawLine(renderer, 100+j*40, 40, 100+j*40, 840);
    }

    write_texte("commands : ", 550,50,200,50, white);
    write_texte("up : rotate left", 550,110,200,50, white);
    write_texte("down : rotate right : ", 550,160,200,50, white);
    write_texte("space : quick falling", 550,210,200,50, white);
    write_texte("N : return to menu", 550,270,200,50, white);
    write_texte("next tetrimino", 550,575,200,50, white);
    if (difficulty == 3)
    {
        char level_str[50];
        if(snprintf(level_str, 50, "level %i", next_level[0]) < 0) {std::cout << "no level\n";}
        write_texte(level_str, 550,350,200,50, white);
    }
    SDL_RenderPresent(renderer);

    if (DEBUG)
    {
        print_tetris_array();
        print_current_tetrimino_info();
    }
}


void Playground::draw_score(int x, int y, int w, int h)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    char score_str[50];
    if(snprintf(score_str, 50, "score : %li", score) < 0) {std::cout << "no score\n";}
    write_texte(score_str, x,y,w,h, white);

    SDL_RenderPresent(renderer);
}


void Playground::draw_score_ia(int x, int y, int w, int h)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    char score_str[50];
    if(snprintf(score_str, 50, "your score : %li", score) < 0) {std::cout << "no score\n";}
    write_texte(score_str, x,y,w,h, white);

    char score_ia_str[50];
    if(snprintf(score_ia_str, 50, "ia score : %li", score_ia) < 0) {std::cout << "no score\n";}
    write_texte(score_ia_str, x,y+75,w,h, white);

    SDL_RenderPresent(renderer);
}


void Playground::stop_tetrimino()
{
    int line, column;
    for (int i = 0; i < 4; i++)
    {
        line = current_tetrimino->get_shape(i)->get_line();
        column = current_tetrimino->get_shape(i)->get_column();
        if ((line == nb_line-1) || (tetris_array[line+1][column] != nullptr))
        {
            current_tetrimino->set_speed(0);
            break;
        }
    }
}

void Playground::tetrimino_descent(bool *quit)
{
    int line, column;
    if (current_tetrimino->get_speed() == 0)
    {
        for (int i = 0; i < 4; i++)
        {
            line = current_tetrimino->get_shape(i)->get_line();
            column = current_tetrimino->get_shape(i)->get_column();
            if (line == 0)
            {
                std::cout << "game over !\n";
                *quit = true;
                break;
            }
            tetris_array[line][column] = current_tetrimino->get_shape(i);
        }
        current_tetrimino = nullptr;
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            int line = current_tetrimino->get_shape(i)->get_line();
            current_tetrimino->get_shape(i)->set_line(line + 1);
            current_tetrimino->get_shape(i)->set_box_y(40 + line * 40);
        }
    }
}


void Playground::right_shift()
{
    int line, column;
    bool cond = true;
    for (int i = 0; i < 4; i++)
    {
        line = current_tetrimino->get_shape(i)->get_line();
        column = current_tetrimino->get_shape(i)->get_column();
        if ((tetris_array[line][column+1] != nullptr) ||
            (column == 9))
        {
            cond = false;
        }
    }
    if (cond)
    {
        for (int i = 0; i < 4; i++)
        {
            column = current_tetrimino->get_shape(i)->get_column();
            current_tetrimino->get_shape(i)->set_column(column + 1);
        }
    }
}

void Playground::left_shift()
{
    int line, column;
    bool cond = true;
    for (int i = 0; i < 4; i++)
    {
        line = current_tetrimino->get_shape(i)->get_line();
        column = current_tetrimino->get_shape(i)->get_column();
        if ((tetris_array[line][column-1] != nullptr) ||
            (column == 0))
        {
            cond = false;
        }
    }
    if (cond)
    {
        for (int i = 0; i < 4; i++)
        {
            column = current_tetrimino->get_shape(i)->get_column();
            current_tetrimino->get_shape(i)->set_column(column - 1);
        }
    }
}


int Playground::line_completed()
{
    int add_2_score = 0;
    int new_line = 0;
    unsigned int line_deleted = 0;
    bool test;
    for (int i = 0; i < nb_line; i++)
    {
        test = true;
        for (int j = 0; j < nb_column; j++)
        {
            if (tetris_array[i][j] == nullptr)
            {
                test = false;
                break;
            }
        }
        if (test)
        {
            line_deleted++;
            for (int k = 0; k < nb_column; k++)
            {
                delete tetris_array[i][k];
                tetris_array[i][k] = nullptr;
            }
            for (int l = i-1; l >= 0; l--)
            {
                for (int m = 0; m < nb_column; m++)
                {
                    if (tetris_array[l][m] != nullptr)
                    {
                        new_line = l+1;
                        if (difficulty == 0)
                        {
                            while ((tetris_array[new_line][m] == nullptr) &&
                                (new_line < 19))
                            {
                                new_line++;
                            }
                        }
                        tetris_array[new_line][m] = new Square(tetris_array[l][m]->get_color(), new_line, m);
                        delete tetris_array[l][m];
                        tetris_array[l][m] = nullptr;
                    }
                }
            }
        }
    }
    switch (line_deleted)
    {
    case 0:
        break;
    case 1:
        add_2_score += 40;
        break;
    case 2:
        add_2_score += 100;
        break;
    case 3:
        add_2_score += 300;
        break;
    case 4:
        add_2_score += 1200;
        break;
    default:
        add_2_score += 1200;
        break;
    }
    return add_2_score;
}

void Playground::select_tetrimino()
{
    int type = rand()%7;
    Tetrimino * next_next_tetrimino;

    if ((type == tetrimino_cache[0]->get_type()) && (type == tetrimino_cache[1]->get_type()))
    {
        type = (rand())%7;
    }

    switch (type)
    {
    case 0:
        next_next_tetrimino = new Tetri_O(0,1);
        break;
    case 1:
        next_next_tetrimino = new Tetri_T(1,1);
        break;
    case 2:
        next_next_tetrimino = new Tetri_L(2,1);
        break;
    case 3:
        next_next_tetrimino = new Tetri_J(3,1);
        break;
    case 4:
        next_next_tetrimino = new Tetri_I(4,1);
        break;
    case 5:
        next_next_tetrimino = new Tetri_S(5,1);
        break;
    case 6:
        next_next_tetrimino = new Tetri_Z(6,1);
        break;
    default:
        break;
    }

    tetrimino_cache[0] = tetrimino_cache[1];
    tetrimino_cache[1] = next_next_tetrimino;
    current_tetrimino = tetrimino_cache[0];
}



bool Playground::introduction()
{
    bool quit1 = false;
    bool quit2 = false;
    SDL_Event event;
    draw_start_screen();
    while(!quit1)
    {
        while (!quit1 && SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    quit1 = true;
                    quit2 = true;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_N:
                        quit1 = true;
                        quit2 = true;
                        break;
                    case SDL_SCANCODE_ESCAPE:
                        quit1 = true;
                        quit2 = true;
                        break;
                    case SDL_SCANCODE_C:
                        quit1 = true;
                        quit2 = false;
                        break;
                    case SDL_SCANCODE_UP:
                        difficulty = (difficulty+1) %4;
                        draw_start_screen();
                        break;
                    case SDL_SCANCODE_DOWN:
                        difficulty = (difficulty-1);
                        if (difficulty == -1)
                            {difficulty = 3;}
                        draw_start_screen();
                        break;
                    }
            }
        }
    }
    return quit2;
}


void Playground::outroduction()
{
    SDL_Event event;
    bool quit = false;
    draw_game_over_screen();

    while (!quit)
    {
        while (!quit && SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_N:
                        quit = true;
                        break;
                    case SDL_SCANCODE_ESCAPE:
                        quit = true;
                        break;
                    case SDL_SCANCODE_C:
                        quit = true;
                        break;
                    default :
                        break;
                    }
                default :
                    break;
            }
        }
    }
}

int Playground::compute_score(int score_2_update)
{
    if ((current_tetrimino != nullptr) && (current_tetrimino->get_speed() == 0))
    {
        int max = 0;
        for (int j = 0; j < 4; j++)
        {
            if (max < current_tetrimino->get_shape(j)->get_line())
            {
                max = current_tetrimino->get_shape(j)->get_line();
            }
        }
        score_2_update += max;
    }
    return score_2_update;
}


void Playground::loop()
{
    int line = 0;
    int column = 0;
    int count = 0;
    int count_limit = 100000;
    int game_speed = 100000;

    bool right_shift_cond = false;
    bool left_shift_cond = false;
    bool rotate_right = false;
    bool rotate_left = false;
    bool rotation_ok = false;

    bool quit = introduction();
    switch (difficulty)
    {
    case 0:
        game_speed = 100000;
        break;
    case 1:
        game_speed = 60000;
        break;
    case 2:
        game_speed = 30000;
        break;
    case 3:
        game_speed = 100000;
        next_level[0] = 1;
        next_level[1] = 500;
        break;
    default:
        break;
    }

    SDL_Event event;

    while (!quit)
    {
        while (!quit && SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_N:
                        quit = true;
                        break;
                    case SDL_SCANCODE_ESCAPE:
                        quit = true;
                        break;
                    case SDL_SCANCODE_SPACE:
                        count_limit = 15000;
                        break;
                    case SDL_SCANCODE_LEFT:
                        left_shift_cond = true;
                        break;
                    case SDL_SCANCODE_RIGHT:
                        right_shift_cond = true;
                        break;
                    case SDL_SCANCODE_UP:
		                rotate_left = true;
                        break;
                    case SDL_SCANCODE_DOWN:
	                    rotate_right = true;
                        break;
                    default:
                        break;
                    }

                default:
                    break;
            }
        }

        if (count > count_limit)
        {
            count = 0;
            if (current_tetrimino == nullptr)
            {
                select_tetrimino();
                count_limit = game_speed;
            }
            if (right_shift_cond) {right_shift();}
            if (left_shift_cond){left_shift();}
            if (rotate_right)
            {
                current_tetrimino->set_prev_etat(current_tetrimino->get_etat());
                current_tetrimino->set_etat(((current_tetrimino->get_etat())+1) % 4);
                current_tetrimino->rotate(tetris_array);

            }
            if (rotate_left)
            {
                current_tetrimino->set_prev_etat(current_tetrimino->get_etat());
                current_tetrimino->set_etat(((current_tetrimino->get_etat())-1) % 4);
                current_tetrimino->rotate(tetris_array);
            }
            draw_playground();
            draw_score(600,450,100,50);
            stop_tetrimino();

            score = compute_score(score);
            tetrimino_descent(&quit);
            score += line_completed();

            if ((difficulty == 3) &&
                (score > next_level[0] * next_level[1]) &&
                (next_level[0] < 49))
            {
                next_level[0] += 1;
                game_speed -= 2000;
            }

            right_shift_cond = false;
            left_shift_cond = false;
            rotate_left = false;
            rotate_right = false;
        }
        else {count += 1;}
    }
    outroduction();
}


bool Playground::introduction_ia()
{
    bool quit1 = false;
    bool quit2 = false;
    SDL_Event event;
    draw_start_screen_ia();
    while(!quit1)
    {
        while (!quit1 && SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    quit1 = true;
                    quit2 = true;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_N:
                        quit1 = true;
                        quit2 = true;
                        break;
                    case SDL_SCANCODE_ESCAPE:
                        quit1 = true;
                        quit2 = true;
                        break;
                    case SDL_SCANCODE_C:
                        quit1 = true;
                        quit2 = false;
                        break;
                    case SDL_SCANCODE_UP:
                        difficulty = (difficulty+1) %4;
                        draw_start_screen_ia();
                        break;
                    case SDL_SCANCODE_DOWN:
                        difficulty = (difficulty-1);
                        if (difficulty == -1)
                            {difficulty = 3;}
                        draw_start_screen_ia();
                        break;
                    }
            }
        }
    }
    return quit2;
}


void Playground::outroduction_ia()
{
    SDL_Event event;
    bool quit = false;
    draw_game_over_screen_ia();

    while (!quit)
    {
        while (!quit && SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_N:
                        quit = true;
                        break;
                    case SDL_SCANCODE_ESCAPE:
                        quit = true;
                        break;
                    case SDL_SCANCODE_C:
                        quit = true;
                        break;
                    default :
                        break;
                    }
                default :
                    break;
            }
        }
    }
}


std::vector<std::pair<int,int>> Playground::compute_ia()
{
    int line, column;
    bool cond = true;
    int grade = 0;
    int rotation_state = 0;
    std::vector<std::pair<int,int>> positions(4,std::pair<int,int>(0,0));
    std::vector<std::pair<int,int>> result(4,std::pair<int,int>(0,0));

    for (int h = 0; h < 4; h++)
    {
        current_tetrimino->set_prev_etat(current_tetrimino->get_etat());
        current_tetrimino->set_etat(((current_tetrimino->get_etat())+1) % 4);
        current_tetrimino->rotate(tetris_array);

        for (int i = -20; i < 20; i++)
        {
            for (int j = -10; j < 10; j++)
            {
                cond = true;
                for (int k = 0; k < 4; k++)
                {
                    line = current_tetrimino->get_shape(k)->get_line();
                    column = current_tetrimino->get_shape(k)->get_column();
                    if ((line + i >= 20) ||
                        (line + i < 0) ||
                        (column + j >= 10) ||
                        (column + j < 0) ||
                        (tetris_array[i+line][j+column] != nullptr))
                    {
                        cond = false;
                        break;
                    }
                    positions.at(k).first = line + i;
                    positions.at(k).second = column + j;
                } // Here we compute a valid position for the ai

                if (cond)
                {
                    int position_grade = 0;
                    for (int k = 0; k < 4; k++)
                    {
                        position_grade += 10*(positions.at(k).first);
                    } // The further the better !



                    for (int k = 0; k < 20; k++)
                    {
                        cond = true;
                        for (int l = 0; l < 10; l++)
                        {
                            if (tetris_array[k][l] == nullptr)
                            {
                                std::pair <int,int> test (k,l);
                                if (*std::find(positions.begin(), positions.end(), test) != test)
                                {
                                    cond = false;
                                }
                            }
                        }
                        if (cond) {position_grade += 400;}
                    }// This section encourages the ai to complete lines


                    for (int k = 0; k < 4; k++)
                    {
                        line = positions.at(k).first+1;
                        column = positions.at(k).second;
                        if ((line < 20) && (tetris_array[line][column] == nullptr))
                        {
                            std::pair <int,int> test (line,column);
                            if (*std::find(positions.begin(), positions.end(), test) != test)
                            {
                                position_grade -= 200;
                            }
                        }
                    }// This section deters the ai from creating holes


                    for (int k = 0; k < positions.at(2).first; k++)
                    {
                        for (int l = 0; l < 4; l++)
                        {
                            if (tetris_array[k][positions.at(l).second] != nullptr)
                            {
                                position_grade -= 4000;
                            }
                        }
                    }// This section deters the ai trying to fit pieces into unaccessible positions



                    if (position_grade > grade)
                    {
                        grade = position_grade;
                        result = positions;
                        rotation_state = current_tetrimino->get_etat();
                    }
                }
            }
        }
    }
    result.push_back(std::pair<int, int> (rotation_state,rotation_state));
    return result;
}



void Playground::move_ia(std::vector<std::pair<int,int>> position)
{
    int column, end_column;
    column = current_tetrimino->get_shape(2)->get_column();
    end_column = position.at(2).second;

    if (end_column > column)
    {
        for (int i = 0; i < 4; i++)
        {
            column = current_tetrimino->get_shape(i)->get_column();
            current_tetrimino->get_shape(i)->set_column(column + 1);
            current_tetrimino->get_shape(i)->set_box_y(column * 40 + 40);
        }
    }
    if (end_column < column)
    {
        for (int i = 0; i < 4; i++)
        {
            column = current_tetrimino->get_shape(i)->get_column();
            current_tetrimino->get_shape(i)->set_column(column - 1);
            current_tetrimino->get_shape(i)->set_box_y(column * 40 - 40);
        }
    }
    if (position.at(4).first != current_tetrimino->get_etat())
    {
        current_tetrimino->set_prev_etat(current_tetrimino->get_etat());
        current_tetrimino->set_etat(((current_tetrimino->get_etat())+1) % 4);
        current_tetrimino->rotate(tetris_array);
    }

}


void Playground::loop_ia()
{
    int line = 0;
    int column = 0;
    int count = 0;
    int count_limit = 160000000;
    int game_speed = 160000000;

    bool quit = introduction_ia();
    switch (difficulty)
    {
    case 0:
        game_speed = 140000000;
        break;
    case 1:
        game_speed = 70000000;
        break;
    case 2:
        game_speed = 30000000;
        break;
    case 3:
        game_speed = 120000000;
        next_level[0] = 1;
        next_level[1] = 1000;
        break;
    default:
        break;
    }

    bool right_shift_cond = false;
    bool left_shift_cond = false;
    bool rotate_right = false;
    bool rotate_left= false;
    bool ia_turn = true;

    std::vector<std::pair<int,int>> position_ia(4,std::pair<int,int>(0,0));
    SDL_Event event;

    while (!quit)
    {
        if (count > count_limit)
        {
            count = 0;
            if (current_tetrimino == nullptr)
            {
                select_tetrimino();
                position_ia = compute_ia();

                if (ia_turn)
                {
                    ia_turn = false;
                    count_limit = game_speed;
                }
                else
                {
                    count_limit = 30000000;
                    ia_turn = true;
                    position_ia = compute_ia();
                }
            }
            if (ia_turn)
            {
                move_ia(position_ia);
                draw_playground();
                draw_score_ia(600,450,100,50);
                stop_tetrimino();
                score_ia = compute_score(score_ia);
                tetrimino_descent(&quit);
                score_ia += line_completed();
            }
            else
            {
                while (!quit && SDL_PollEvent(&event))
                {
                    switch(event.type)
                    {
                        case SDL_QUIT:
                            quit = true;
                            break;

                        case SDL_KEYDOWN:
                            switch (event.key.keysym.scancode)
                            {
                            case SDL_SCANCODE_N:
                                quit = true;
                                break;
                            case SDL_SCANCODE_ESCAPE:
                                quit = true;
                                break;
                            case SDL_SCANCODE_SPACE:
                                count_limit = 20000000;
                                break;
                            case SDL_SCANCODE_LEFT:
                                left_shift_cond = true;
                                break;
                            case SDL_SCANCODE_RIGHT:
                                right_shift_cond = true;
                                break;
                            case SDL_SCANCODE_UP:
                        rotate_left = true;
                                break;
                            case SDL_SCANCODE_DOWN:
                        rotate_right = true;
                                break;
                            default:
                                break;
                            }

                        default:
                            break;
                    }
                }
                if (right_shift_cond) {right_shift();}
                if (left_shift_cond) {left_shift();}

                if (rotate_right)
                {
                    current_tetrimino->set_prev_etat(current_tetrimino->get_etat());
                    current_tetrimino->set_etat(((current_tetrimino->get_etat())+1) % 4);
                    current_tetrimino->rotate(tetris_array);
                }
                if (rotate_left)
                {
                    current_tetrimino->set_prev_etat(current_tetrimino->get_etat());
                    current_tetrimino->set_etat(((current_tetrimino->get_etat())-1) % 4);
                    current_tetrimino->rotate(tetris_array);
                }
                draw_playground();
                draw_score_ia(600,450,100,50);
                stop_tetrimino();
                score = compute_score(score);
                tetrimino_descent(&quit);
                score += line_completed();

                if ((difficulty == 3) &&
                    (score + score_ia > next_level[0] * next_level[1]) &&
                    (next_level[0] < 49))
                {
                    next_level[0] += 1;
                    game_speed -= 2000000;
                }

                right_shift_cond = false;
                left_shift_cond = false;
                rotate_left = false;
                rotate_right = false;
            }
        }
        else {count += 1;}
    }
    outroduction_ia();
}
