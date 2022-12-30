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

        void AddActor(class Actor* actor);
        void RemoveActor(class Actor* actor);
    private:
        // Helper functions for the game loop
        void ProcessInput();
        void UpdateGame();
        void GenerateOuput();

        // Window created by SDL
        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;

        // All the actors in the game
	    std::vector<class Actor*> mActors;
	    // Any pending actors
	    std::vector<class Actor*> mPendingActors;

        Vector2 mPaddlePos;
        Vector2 mPaddlePos2;
        Vector2 mBallPos;
        Vector2 mBallVel;
        Uint32 mTicksCount;
        int mPaddleDir;
        int mPaddleDir2;
        // Game should vontinus to run
        bool mIsRunning; 
        // Track if we're updating actors right now
	    bool mUpdatingActors;
};

