#pragma once
#include <vector>

class Actor
{
    public:
    enum State
    {
        EActive,
        EPaused,
        EDead
    };

    // Constructor/destructor
    Actor(class Game* game);
    virtual ~Actor();

    // Update function called from Game (not overridable)
    void Update(float deltaTime);

    // Update all the components attached to the actor (not overridable)
    void UpdateComponents(float deltaTime);

    // Any actor-specific update code (overridable)
    virtual void UpdateActor(float deltaTime);

    // Getters/setters
    // ...

    // Add/remove components
    void AddComponent(class Component* component);
    void RemoveComponent(class Component* Component);
    private:
    // Actor's state
    State mState;

    // Transform
    Vector2 mPositon;   // Center position of actor
    float mScale;       // Uniforms scale of actor (1.0f for 100%)
    float mRotation;    // Rotation angle (in radians)

    // Components held by this actor
    std::vector<class Component*> mComponents;
    class Game* mGame;
};