#include "Level3.h"
#define LEVEL3_WIDTH 17
#define LEVEL3_HEIGHT 8

#define LEVEL3_ENEMY_COUNT 1

GLuint font3;

unsigned int level3_data[] =
{
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,
 3, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,1,1,1,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,0,0,0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 , 0, 0, 0, 0,0,0,
 3, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0,0,0,0,
 3, 2, 2, 2, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,1,1,1
};

int* live3;

Level3::Level3(int* lives) {
    state.player = new Entity();
    live3 = lives;
}

void Level3::Initialize() {

    state.nextScene = -1;

    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL3_WIDTH, LEVEL3_HEIGHT, level3_data, mapTextureID, 1.0f, 4, 1);
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


    font3 = Util::LoadTexture("font1.png");


    state.enemies = new Entity[LEVEL3_ENEMY_COUNT];

    GLuint enemyTextureID = Util::LoadTexture("ctg.png");

    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(12, -6, 0);
    state.enemies[0].originalPos = 13;
    state.enemies[0].speed = 1;
    state.enemies[0].aiType = PATROLLER;
    state.enemies[0].aiState = WALKING;
}

bool Level3::enemyAlldied() {
    for (int i = 0; i < LEVEL3_ENEMY_COUNT; i++) {
        if (state.enemies[i].isActive == true) {
            return false;
        }
    }
    return true;
}

void Level3::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.map);
    for (int i = 0; i < LEVEL3_ENEMY_COUNT;i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, 1, state.map);
    }
    if (enemyAlldied()) {
        state.player->win = true;
    }
    if (state.player->gotKilled == true) {
        state.player->isActive = false;
        if (*(live3) > 1) {
            state.player->position = glm::vec3(3, -4, 0);
        }
        state.player->isActive = true;
        (*live3)--;
        state.player->gotKilled = false;
        if (*live3 == 0) {
            state.player->isActive = false;
            state.player->failed = true;
        }
    }
}
void Level3::Render(ShaderProgram* program) {
    state.map->Render(program);
    for (int i = 0; i < LEVEL3_ENEMY_COUNT;i++) {
        state.enemies[i].Render(program);
    }
    state.player->Render(program);

    if (state.player->win == true) {
        Util::DrawText(program, font3, "You Win", 1.0f, -0.5f, glm::vec3(state.player->position.x, -2, 0));
    }
    if (state.player->failed == true) {
        Util::DrawText(program, font3, "You Lose", 1.0f, -0.5f, glm::vec3(state.player->position.x, -2, 0));
    }
}