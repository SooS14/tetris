#include <string>
#include <iostream>
#include "game.h"
#include "check.h"
#include <SDL_mixer.h>
#include "SDL2/SDL_ttf.h"


//https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf

// valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./test
//valgrind --tool=memcheck --leak-check=full --track-origins=yes ./test

//utiliser valgrind + gdb
//valgrind --vgdb=yes --vgdb-error=0 prog
//gdb prog
//(gdb) target remote | vgdb

//gdb, commandes utiles
//(gdb) info symbol <addr>
//printf("myvar = %d\n", myvar);


//erreur à :
//0x000000000010a6b6 -> break point
// 0x000000000010b69d


int main(int argc, char const *argv[])
{
    check_0(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO));

    int flags = IMG_INIT_PNG;
    if ((IMG_Init(flags) & flags) != flags)
    {
        std::cout << "error IMG_init, exiting, " <<  IMG_GetError() << "\n";
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error SDL_mixer : %s", Mix_GetError());
        IMG_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    if(TTF_Init()==-1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        Mix_CloseAudio();
        IMG_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    Game g;
    g.loop();

    TTF_Quit();
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
