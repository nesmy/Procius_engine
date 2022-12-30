#pragma once
#include "SDL/SDL.h"


struct Vector2
    {
        float x;
        float y;   /* data */
    };

class Game {
    public:
        Game();
        ~Game();
        // Initialize the game
        bool Initialize();
        // Runs the game loop until the game is over
        void RunLoop();
        // Shutdown the game
        void Shutdown();
    private:
        // Helper functions for the game loop
        void ProcessInput();
        void UpdateGame();
        void GenerateOuput();

        // Window created by SDL
        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;

        Vector2 mPaddlePos;
        Vector2 mBallPos;
        Vector2 mBallVel;
        Uint32 mTicksCount;
        int mPaddleDir;
        // Game should vontinus to run
        bool mIsRunning; 
};

