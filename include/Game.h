#include "SDL/SDL.h"

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
        // Game should vontinus to run
        bool mIsRunning; 
};