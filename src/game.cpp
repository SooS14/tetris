#include "game.h"
#include "playground.h"
#include "check.h"


Game::~Game()
{
    if (versus != nullptr) {delete versus;}
    if (window_surf != nullptr) {SDL_FreeSurface(window_surf); window_surf = nullptr;}
    if (window != nullptr) {SDL_DestroyWindow(window);}
    if (music != nullptr) {Mix_FreeMusic(music);}
}

Game::Game()
{
    window = SDL_CreateWindow("TETRIS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 900, SDL_WINDOW_SHOWN);
    check(window);
    window_surf = SDL_GetWindowSurface(window);
    check(window_surf);

    menu_surf = SDL_LoadBMP("bmp_models/menu_final.bmp");
    if (menu_surf == nullptr) {
        std::cout << "SDL_LoadBMP: " << IMG_GetError() << "\n";
        Mix_CloseAudio();
        IMG_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    check_0(SDL_BlitSurface(menu_surf, NULL, window_surf, NULL));

    music = Mix_LoadMUS("music/Katyusha_8bit.MP3");
    if (music == nullptr)
    {
        std::cout << "Mix_LoadMUS: " << Mix_GetError() << "exiting";
        Mix_CloseAudio();
        IMG_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    check_0(SDL_UpdateWindowSurface(window));
}



void Game::loop(void)
{
    SDL_Event event;
    bool quit = false;

    Mix_PlayMusic(music, -1);
    Mix_PauseMusic();
    int volume = 20;
    bool is_playing = false;
    Mix_VolumeMusic(volume);

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
                        case SDL_SCANCODE_S:
                            solo = new Playground();
                            solo->loop();
                            delete solo;
                            solo = nullptr;
                            break;

                        case SDL_SCANCODE_V:
                            versus = new Playground();
                            versus->loop_ia();
                            delete versus;
                            versus = nullptr;
                            break;

                        case SDL_SCANCODE_P:
                            if (is_playing) 
                            {
                                Mix_PauseMusic();
                                is_playing = false;
                            }
                            else
                            {
                                Mix_ResumeMusic();
                                is_playing = true;
                            }
                            break;
                            
                        case SDL_SCANCODE_ESCAPE:
                            quit = true;
                            break;

                        default:
                            break;
                    }

                default:
                    break;

            }
        }

    }
}
