#include "Game.h"
#include "cstdio"

const Uint8* state = SDL_GetKeyboardState(NULL);

Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mIsRunning(true)
{

}

Game::~Game()
{
}

bool Game::Initialize()
{
    
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    if (sdlResult != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    
    mWindow = SDL_CreateWindow("ProciusEngine", // Window title
                             100,   // Top left x-coordinate of window
                             100,   // top left y-coordiante of window
                             1024,  // Width of window
                             768,   // Height of window
                             0);    // Flags (0 for no flags set)

    if (!mWindow)
    {
        printf("dont work");
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(
        mWindow, // Window to create renderer for
        -1,     // Usually -1
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!mRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    } else {
        return true;
    }
}

void Game::RunLoop()
{
    
    while (mIsRunning)
    {
        
        ProcessInput();
        UpdateGame();
        GenerateOuput();
    }
}

void Game::Shutdown()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);

    SDL_Quit();
}

void Game::ProcessInput()
{
    SDL_Event event;
    //While there are still events in the queue
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            // Handle different event types here
            case SDL_QUIT:
                mIsRunning = false;

                break;
        }
    }

    if (state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }
}

void Game::UpdateGame()
{
}

void Game::GenerateOuput()
{
    SDL_SetRenderDrawColor(
        mRenderer,
        0,      //R
        0,      //G
        255,    //B
        255     //A
    );

    SDL_RenderClear(mRenderer);

    SDL_RenderPresent(mRenderer);
}
