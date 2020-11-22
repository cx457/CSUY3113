#include "Level2.h"
#define LEVEL2_WIDTH 14
#define LEVEL2_HEIGHT 8

#define LEVEL2_ENEMY_COUNT 3

unsigned int level2_data[] =
{
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3,
 3, 1, 1, 1, 1, 1, 1, 1, 0, 3, 3, 3, 3, 3,
 3, 2, 2, 2, 2, 2, 2, 2, 0, 3, 3, 3, 3, 3
};

int* live2;
GLuint font2;

Level2::Level2(int* lives) {
    state.player = new Entity();
    live2 = lives;
}


void Level2::Initialize() {

    state.nextScene = -1;

    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL2_WIDTH, LEVEL2_HEIGHT, level2_data, mapTextureID, 1.0f, 4, 1);
    // Move over all of the player and enemy code from initialization.
    
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(3, 0, 0);
    state.player->movement = glm::vec3(0);
    state.player->accelration = glm::vec3(0, -9.81, 0);
    state.player->speed = 3.0f;

    state.player->textureID = Util::LoadTexture("george_0.png");

    state.player->animRight = new int[4]{ 3, 7, 11, 15 };
    state.player->animLeft = new int[4]{ 1, 5, 9, 13 };
    state.player->animUp = new int[4]{ 2, 6, 10, 14 };
    state.player->animDown = new int[4]{ 0, 4, 8, 12 };

    state.player->animIndices = state.player->animRight;
    state.player->animFrames = 4;
    state.player->animIndex = 0;
    state.player->animTime = 0;
    state.player->animCols = 4;
    state.player->animRows = 4;

    state.player->height = 0.8f;
    state.player->width = 0.5f;
    state.player->jumpPower = 7.0f;
    
    
    GLuint font = Util::LoadTexture("font1.png");

    font2 = Util::LoadTexture("font1.png");

    state.enemies = new Entity[LEVEL2_ENEMY_COUNT];
    
    GLuint enemyTextureID = Util::LoadTexture("ctg.png");
    
    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(7, -5, 0);
    state.enemies[0].speed = 1;
    state.enemies[0].aiType = WAITANDGO;
    state.enemies[0].aiState = IDLE;

    state.enemies[1].entityType = ENEMY;
    state.enemies[1].textureID = enemyTextureID;
    state.enemies[1].position = glm::vec3(6, -2, 0);
    state.enemies[1].speed = 1;
    state.enemies[1].aiType = JUMPER;
    state.enemies[1].aiState = JUMP;
    

    state.enemies[2].entityType = ENEMY;
    state.enemies[2].textureID = enemyTextureID;
    state.enemies[2].position = glm::vec3(9, -4, 0);
    state.enemies[2].speed = 1;
    state.enemies[2].aiType = PATROLLER;
    state.enemies[2].aiState = WALKING;
    state.enemies[2].originalPos = 9;
    
}


bool Level2::enemyAlldied() {
    for (int i = 0; i < LEVEL2_ENEMY_COUNT; i++) {
        if (state.enemies[i].isActive == true) {
            return false;
        }
    }
    return true;
}

void Level2::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.map);
    for (int i = 0; i < LEVEL2_ENEMY_COUNT;i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, 1, state.map);
    }
    if (enemyAlldied()) {
        state.nextScene = 1;
    }
    if (state.player->gotKilled == true) {
        state.player->isActive = false;
        if (*(live2) > 1) {
            state.player->position = glm::vec3(3, -4, 0);
        }
        state.player->isActive = true;
        (*live2)--;
        state.player->gotKilled = false;
        if (*live2 == 0) {
            state.player->isActive = false;
            state.player->failed = true;
        }
    }
}
void Level2::Render(ShaderProgram* program) {
    state.map->Render(program);
    for (int i = 0; i < LEVEL2_ENEMY_COUNT;i++) {
        state.enemies[i].Render(program);
    }
    state.player->Render(program);
    if (state.player->failed == true) {
        Util::DrawText(program, font2, "You Lose", 1.0f, -0.5f, glm::vec3(state.player->position.x, -2, 0));
    }
}