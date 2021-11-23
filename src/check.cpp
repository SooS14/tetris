#include "check.h"

void check(void * ptr)
{
    if (ptr == nullptr)
    {
        std::cout << SDL_GetError() << "\n";
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

void check_0(int ret)
{
    if (ret != 0)
    {
        std::cout << SDL_GetError() << "\n";
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}
