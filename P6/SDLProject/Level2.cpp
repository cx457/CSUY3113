#include "Level2.h"

#define GAME_WIDTH 41
#define GAME_HEIGHT 3

#define GAME_ENEMY_COUNT 1
#define GAME_COIN_COUNT 4

unsigned int level2_data[] =
{
 0, 0,1,1,1,1,1,1,1,1,1,0,0,0,0,0, 0,0,1,1,1,1,1,0,1,1,1,1,0,0,1,1,0,0,1,0,0,1,0,0,0,
 1, 1,1,1,0,0,0,0,1,0,0,0,0,1,1,1, 1,0,1,0,0,1,0,0,1,0,0,1,1,0,1,1,1,0,1,1,1,1,1,1,1,
 0, 0,1,1,1,1,1,1,1,1,1,1,1,1,0,0, 1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0
};

int* live2;
GLuint font2;
int totalGold2 = 0;

Level2::Level2(int* lives) {
    state.player = new Entity();
    live2 = lives;
}

void Level2::Initialize() {

    state.nextScene = -1;

    GLuint mapTextureID = Util::LoadTexture("MasterSimple.png");
    font2 = Util::LoadTexture("font1.png");
    state.map = new Map(GAME_WIDTH, GAME_HEIGHT, level2_data, mapTextureID, 1.0f, 10, 10);
    // Move over all of the player and enemy code from initialization.

    state.player->entityType = PLAYER;
    state.player->wantWait = false;
    state.player->position = glm::vec3(3, -1, 0);
    state.player->movement = glm::vec3(0);
    state.player->accelration = glm::vec3(0, 0, 0);
    state.player->speed = 2.0f;
    state.player->gateOpen = true;

    state.player->textureID = Util::LoadTexture("kid01_walk.png");

    state.player->animRight = new int[4]{ 9, 10, 8, 11 };
    state.player->animLeft = new int[4]{ 5, 6, 4, 7 };
    state.player->animUp = new int[4]{ 13, 14, 12, 15 };
    state.player->animDown = new int[4]{ 1, 2, 0, 3 };

    state.player->animIndices = state.player->animDown;
    state.player->animFrames = 4;
    state.player->animIndex = 0;
    state.player->animTime = 0;
    state.player->animCols = 4;
    state.player->animRows = 4;

    state.player->height = 0.8f;
    state.player->width = 0.5f;
    state.player->jumpPower = 7.0f;

    GLuint font = Util::LoadTexture("font1.png");

    state.enemies = new Entity[GAME_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("Dragonlord.png");

    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(1, -1, 0);
    state.enemies[0].speed = 1.5f;
    state.enemies[0].aiType = WAITANDGO;
    state.enemies[0].aiState = IDLE;

    state.coin = new Entity[GAME_COIN_COUNT];
    GLuint coinTextureID = Util::LoadTexture("coin1.png");

    state.gate = new Entity();
    GLuint gateTextureID = Util::LoadTexture("Door01.png");

    state.gate->entityType = GATE;
    state.gate->position = glm::vec3(39, -1, 0);
    state.gate->textureID = gateTextureID;

}


void Level2::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, GAME_ENEMY_COUNT, state.map);
    state.gate->Update(deltaTime, state.player, state.gate, 1, state.map);
    for (int i = 0; i < GAME_ENEMY_COUNT;i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, GAME_ENEMY_COUNT, state.map);
    }
    if (state.player->gotKilled == true) {
        state.player->isActive = false;
        if (*(live2) > 1) {
            state.player->position = glm::vec3(3, -2, 0);
            state.enemies[0].position = glm::vec3(1, -1, 0);
        }
        state.player->isActive = true;
        (*live2)--;
        state.player->gotKilled = false;
        if (*live2 == 0) {
            state.player->isActive = false;
            state.player->failed = true;
        }
    }


    if (state.player->position.x >= 39.1) {
        state.player->moveRight = false;
    }

    if (state.player->position.x <= 0) {
        state.player->moveLeft = false;
    }
    if (state.player->position.x < 39.1 && state.player->position.x > 0) {
        state.player->moveRight = true;
        state.player->moveLeft = true;
    }
    if (state.player->position.y >= 0.5) {
        state.player->moveUp = false;
    }
    if (state.player->position.y <= -38.8) {
        state.player->moveDown = false;
    }

    if (state.player->position.y < 0 && state.player->position.y > -38.8) {
        state.player->moveUp = true;
        state.player->moveDown = true;
    }

    if (state.player->collidedBottom == false) {
        state.player->accelration.y = -900.81;
    }
    
    if (state.player->position.y <= -40) {
        if (*(live2) > 1) {
            state.player->position = glm::vec3(3, -2, 0);
            state.enemies[0].position = glm::vec3(1, -1, 0);
        }
        state.player->isActive = false;
        state.player->accelration.y = 0;
        state.player->isActive = true;
        (*live2)--;

        if (*live2 == 0) {
            state.player->position =glm::vec3(3, -2, 0);
            state.player->isActive = false;
            state.player->failed = true;
        }
    }

    if (state.player->collideDoor == true) {
        state.player->win = true;
        state.enemies[0].isActive = false;
    }
}

void Level2::Render(ShaderProgram* program) {
    state.map->Render(program);
    state.player->Render(program);
    state.gate->Render(program);

    for (int i = 0; i < GAME_ENEMY_COUNT;i++) {
        state.enemies[i].Render(program);
    }
    if (state.player->failed == true) {
        Util::DrawText(program, font2, "You Lose", 1.0f, -0.5f, glm::vec3(state.player->position.x, state.player->position.y, 0));
    }
    else if (state.player->win == true) {
        Util::DrawText(program, font2, "You Win", 1.0f, -0.5f, glm::vec3(state.player->position.x - 5, state.player->position.y, 0));
    }
}