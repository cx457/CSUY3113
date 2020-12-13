#pragma once
#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Map.h"

enum EntityType { PLAYER, COIN, ENEMY, GATE };

enum AIType {WALKER, WAITANDGO,JUMPER,PATROLLER};
enum AIState {IDLE, WALKING,JUMP, TERMINATE};

class Entity {
public:
    EntityType entityType;
    AIType aiType;
    AIState aiState;

    bool gotKilled = false;

    bool lifeUsed = false;
    glm::vec3 position;
    glm::vec3 movement;
    glm::vec3 accelration;
    glm::vec3 velocity;
    bool win;
    bool failed;
    bool AIJump = true;
    bool enemyAlive = true;
    bool jump = false;
    bool goRight = false;
    bool goLeft = false;
    bool firstMove = true;
    int originalPos;
    int goldCollected = 0;
    bool gateOpen = false;
    bool collideDoor = false;
    bool wantWait = true;

    float jumpPower = 0;

    float width = 1;
    float height = 1;

    float speed;

    GLuint textureID;

    glm::mat4 modelMatrix;

    int* animRight = NULL;
    int* animLeft = NULL;
    int* animUp = NULL;
    int* animDown = NULL;

    int* animIndices = NULL;
    int animFrames = 0;
    int animIndex = 0;
    float animTime = 0;
    int animCols = 0;
    int animRows = 0;

    bool isActive = true;
    bool collidedTop = false;
    bool collidedBottom = false;
    bool collidedLeft = false;
    bool collidedRight = false;


    bool collidedEnemyTop = false;
    bool collidedEnemyBottom = false;
    bool collidedEnemyLeft = false;
    bool collidedEnemyRight = false;

    bool moveRight = true;
    bool moveLeft = true;
    bool moveUp = true;
    bool moveDown = true;

    Entity();

    bool CheckCollision(Entity* other);
    void CheckCollisionsY(Entity* objects, int objectCount);
    void CheckCollisionsX(Entity* objects, int objectCount);
    void CheckCollisionsX(Map* map);
    void CheckCollisionsY(Map* map);


    void Update(float deltaTime,Entity* player, Entity* objects, int objectCount,Map* map);
    void Render(ShaderProgram* program);
    void DrawSpriteFromTextureAtlas(ShaderProgram* program, GLuint textureID, int index);
    
    void AI(Entity* player);
    void AIWalker();
    void AIJumper();
    void AIPatroller();
    void AIWaitAndGo(Entity* player);
};