#include "Game.h"
#include "cstdio"

const int thickness = 15;
const float paddleH = 100.0f;

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
    }
    

    mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f/2.0f;
    mPaddlePos2.x = 1000.0f;
    mPaddlePos2.y = 768.0f/2.0f;
	mBallPos.x = 1024.0f/2.0f;
	mBallPos.y = 768.0f/2.0f;
	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;

    return true;
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

void Game::AddActor(Actor *actor)
{
    // If updating actors, need to add to pending
    if (mUpdatingActors)
    {
        mPendingActors.emplace_back(actor);
    }
    else
    {
        mActors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor *actor)
{
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

    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }

    mPaddleDir = 0;
    mPaddleDir2 = 0;

    if (state[SDL_SCANCODE_W])
    {
        mPaddleDir -= 1;
    }

    if (state[SDL_SCANCODE_S])
    {
        mPaddleDir += 1;
    }

    if (state[SDL_SCANCODE_UP])
    {
        mPaddleDir2 -= 1;
    }

    if (state[SDL_SCANCODE_DOWN])
    {
        mPaddleDir2 += 1;
    }

    // Bounce if needed
	// Did we intersect with the paddle?
	float diff = mPaddlePos.y - mBallPos.y;
    float diff2 = mPaddlePos2.y - mBallPos.y;
	// Take absolute value of difference
	diff = (diff > 0.0f) ? diff : -diff;
    diff2 = (diff2 > 0.0f) ? diff2 : -diff2;
	if (
		// Our y-difference is small enough
		diff <= paddleH / 2.0f &&
		// We are in the correct x-position
		mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
		// The ball is moving to the left
		mBallVel.x < 0.0f)
	{
		mBallVel.x *= -1.0f;
	} else if (
		// Our y-difference is small enough
		diff2 >= paddleH / 2.0f &&
		// We are in the correct x-position
		mBallPos.x >= 25.0f && mBallPos.x <= 20.0f &&
		// The ball is moving to the right
		mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1.0f;
	}
	// Did the ball go off the screen? (if so, end game)
	else if (mBallPos.x <= 0.0f)
	{
		mIsRunning = false;
	}
	// Did the ball collide with the right wall?
	else if (mBallPos.x >= (1024.0f - thickness) && mBallVel.x > 0.0f)
	{
		mIsRunning = false;
	}
	
	// Did the ball collide with the top wall?
	if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1;
	}
	// Did the ball collide with the bottom wall?
	else if (mBallPos.y >= (768 - thickness) &&
		mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1;
	}
}

void Game::UpdateGame()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    mTicksCount = SDL_GetTicks();

    if (mPaddleDir != 0)
    {
        mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;

        if (mPaddlePos.y < (paddleH/2.0f + thickness))
        {
            mPaddlePos.y - paddleH / 2.0f + thickness;
        }
        else if (mPaddlePos.y > (768 - paddleH/2.0f - thickness))
        {
            mPaddlePos.y = 768.0f - paddleH / 2.0f - thickness;
        }
    } else if (mPaddleDir2 != 0)
    {
        mPaddlePos2.y += mPaddleDir2 * 300.0f * deltaTime;

        if (mPaddlePos2.y < (paddleH/2.0f + thickness))
        {
            mPaddlePos2.y - paddleH / 2.0f + thickness;
        }
        else if (mPaddlePos2.y > (768 - paddleH/2.0f - thickness))
        {
            mPaddlePos2.y = 768.0f - paddleH / 2.0f - thickness;
        } 
    }

    mBallPos.x += mBallVel.x * deltaTime;
    mBallPos.y += mBallVel.y * deltaTime;

    // Update all actors
    mUpdatingActors = true;
    for (auto actor : mActors)
    {
        actor -> Update(deltaTime);
    }
    mUpdatingActors = false;

    // Move any pending actors to mActors
    for (auto pending : mPendingActors)
    {
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();

    // Add any dead actors to a temp vector
    std::vector<Actor*> deadActors;
    for (auto actor : mActors)
    {
        if(actor -> GetState() == Actor::EDead)
        (
            deadActors.emplace_back(actor);
        )
    }

    // Delete dead actors (which removes them from mActors)
    for (auto actor : deadActors)
    {
        delete actor;
    }

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

    // Clear back buffer
	SDL_RenderClear(mRenderer);

	// Draw walls
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	
	// Draw top wall
	SDL_Rect wall{
		0,			// Top left x
		0,			// Top left y
		1024,		// Width
		thickness	// Height
	};
	SDL_RenderFillRect(mRenderer, &wall);
	
	// Draw bottom wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);
	
	
	// Draw paddle
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH/2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);

    // Draw paddle
	SDL_Rect paddle2{
		static_cast<int>(mPaddlePos2.x),
		static_cast<int>(mPaddlePos2.y - paddleH/2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle2);
	
	// Draw ball
	SDL_Rect ball{	
		static_cast<int>(mBallPos.x - thickness/2),
		static_cast<int>(mBallPos.y - thickness/2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);
	
	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}
