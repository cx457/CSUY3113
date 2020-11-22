#include "Level1.h"
#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 8

#define LEVEL1_ENEMY_COUNT 1

unsigned int level1_data[] =
{
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
 3, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2,
 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

int* live;
GLuint font1;

Level1::Level1(int* lives) {
    state.player = new Entity();
    live = lives;
}

void Level1::Initialize() {

    state.nextScene = -1;

	GLuint mapTextureID = Util::LoadTexture("tileset.png");
    font1 = Util::LoadTexture("font1.png");
	state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 4, 1);
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

    state.enemies = new Entity[LEVEL1_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("ctg.png");

    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(10, -4, 0);
    state.enemies[0].speed = 1;
    state.enemies[0].aiType = JUMPER;
    state.enemies[0].aiState = JUMP;
 
}

bool Level1::enemyAlldied() {
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
        if (state.enemies[i].isActive == true) {
            return false;
        }
    }
    return true;
}

void Level1::Update(float deltaTime) {
	state.player->Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map);
    for (int i = 0; i < LEVEL1_ENEMY_COUNT;i++) {
        state.enemies[i].Update(deltaTime, state.player,state.enemies, 1, state.map);
    }
    if (state.player->gotKilled == true) {
        state.player->isActive = false;
        if (*(live) > 1) {
            state.player->position = glm::vec3(3, -4, 0);
        }
        state.player->isActive = true;
        (*live)--;
        state.player->gotKilled = false;
        if (*live == 0) {
            state.player->isActive = false;
            state.player->failed = true;
        }
    }

    if(enemyAlldied()){
        state.nextScene = 1;
    }
}
void Level1::Render(ShaderProgram* program) {
	state.map->Render(program);
    state.enemies[0].Render(program);
	state.player->Render(program);
    if (state.player->failed == true) {
        Util::DrawText(program, font1, "You Lose", 1.0f, -0.5f, glm::vec3(state.player->position.x, -2, 0));
    }
}