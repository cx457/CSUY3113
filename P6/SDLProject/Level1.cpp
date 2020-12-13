#include "Level1.h"
#define GAME_WIDTH 41
#define GAME_HEIGHT 41

#define GAME_ENEMY_COUNT 4
#define GAME_COIN_COUNT 4

unsigned int level1_data[] =
{
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

int* live;
GLuint font1;
int totalGold = 0;

Level1::Level1(int* lives) {
	state.player = new Entity();
	live = lives;
}

void Level1::Initialize() {

	state.nextScene = -1;

	GLuint mapTextureID = Util::LoadTexture("MasterSimple.png");
	font1 = Util::LoadTexture("font1.png");
	state.map = new Map(GAME_WIDTH, GAME_HEIGHT, level1_data, mapTextureID, 1.0f, 10, 10);
	// Move over all of the player and enemy code from initialization.

	state.player->entityType = PLAYER;
	state.player->position = glm::vec3(5, -4, 0);
	state.player->movement = glm::vec3(0);
	state.player->accelration = glm::vec3(0, 0, 0);
	state.player->speed = 2.0f;

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
	GLuint enemyTextureID = Util::LoadTexture("zombie.png");

	for (int i = 0; i < GAME_ENEMY_COUNT;i++) {
		state.enemies[i].animRight = new int[4]{ 0, 10, 8, 11 };
		state.enemies[i].animLeft = new int[4]{ 5, 6, 4, 7 };
		state.enemies[i].animUp = new int[4]{ 13, 14, 12, 15 };
		state.enemies[i].animDown = new int[4]{ 1, 2, 0, 3 };

		state.enemies[i].animIndices = state.enemies[i].animRight;
		state.enemies[i].animFrames = 4;
		state.enemies[i].animIndex = 0;
		state.enemies[i].animTime = 0;
		state.enemies[i].animCols = 9;
		state.enemies[i].animRows = 3;
	}

	state.enemies[0].entityType = ENEMY;
	state.enemies[0].textureID = enemyTextureID;
	state.enemies[0].position = glm::vec3(22, -24, 0);
	state.enemies[0].speed = 1;
	state.enemies[0].aiType = WAITANDGO;
	state.enemies[0].aiState = IDLE;

	state.enemies[1].entityType = ENEMY;
	state.enemies[1].textureID = enemyTextureID;
	state.enemies[1].position = glm::vec3(37, -2, 0);
	state.enemies[1].speed = 1;
	state.enemies[1].aiType = WAITANDGO;
	state.enemies[1].aiState = IDLE;


	state.enemies[2].entityType = ENEMY;
	state.enemies[2].textureID = enemyTextureID;
	state.enemies[2].position = glm::vec3(6.2, -38.6, 0);
	state.enemies[2].speed = 1;
	state.enemies[2].aiType = WAITANDGO;
	state.enemies[2].aiState = IDLE;

	state.enemies[3].entityType = ENEMY;
	state.enemies[3].textureID = enemyTextureID;
	state.enemies[3].position = glm::vec3(16, -16, 0);
	state.enemies[3].speed = 1;
	state.enemies[3].aiType = WAITANDGO;
	state.enemies[3].aiState = IDLE;

	state.coin = new Entity[GAME_COIN_COUNT];
	GLuint coinTextureID = Util::LoadTexture("coin1.png");

	state.coin[0].entityType = COIN;
	state.coin[0].position = glm::vec3(25, -21, 0);
	state.coin[0].textureID = Util::LoadTexture("coin1.png");

	state.coin[1].entityType = COIN;
	state.coin[1].position = glm::vec3(35, -1, 0);
	state.coin[1].textureID = Util::LoadTexture("coin1.png");

	state.coin[2].entityType = COIN;
	state.coin[2].position = glm::vec3(7.2, -37.6, 0);
	state.coin[2].textureID = Util::LoadTexture("coin1.png");

	state.coin[3].entityType = COIN;
	state.coin[3].position = glm::vec3(19, -18, 0);
	state.coin[3].textureID = Util::LoadTexture("coin1.png");

	state.gate = new Entity();
	GLuint gateTextureID = Util::LoadTexture("Door02.png");

	state.gate->entityType = GATE;
	state.gate->position = glm::vec3(28, -2, 0);
	state.gate->textureID = gateTextureID;
	state.gate->isActive = false;
}

bool Level1::enemyAlldied() {
	for (int i = 0; i < GAME_ENEMY_COUNT; i++) {
		if (state.enemies[i].isActive == true) {
			return false;
		}
	}
	return true;
}

void Level1::Update(float deltaTime) {
	state.player->Update(deltaTime, state.player, state.enemies, GAME_ENEMY_COUNT, state.map);
	state.gate->Update(deltaTime, state.player, state.gate, 1, state.map);
	for (int i = 0; i < GAME_ENEMY_COUNT;i++) {
		state.enemies[i].Update(deltaTime, state.player, state.enemies, GAME_ENEMY_COUNT, state.map);
		state.coin[i].Update(deltaTime, state.player, state.coin, GAME_COIN_COUNT, state.map);
	}
	if (state.player->gotKilled == true) {
		state.player->isActive = false;
		if (*(live) > 1) {
			state.player->position = glm::vec3(4, -4, 0);
		}
		state.player->isActive = true;
		(*live)--;
		state.player->gotKilled = false;
		if (*live == 0) {
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

	if (state.player->goldCollected == GAME_COIN_COUNT) {
		//state.player->win = true;
		state.player->gateOpen = true;
		state.gate->isActive = true;
	}

	if (state.player->collideDoor == true && state.player->gateOpen == true) {
		state.nextScene = 1;
	}
}

void Level1::Render(ShaderProgram* program) {
	state.map->Render(program);
	state.player->Render(program);

	state.gate->Render(program);


	for (int i = 0; i < GAME_ENEMY_COUNT;i++) {
		state.enemies[i].Render(program);
		state.coin[i].Render(program);
	}
	if (state.player->failed == true) {
		Util::DrawText(program, font1, "You Lose", 1.0f, -0.5f, glm::vec3(state.player->position.x, state.player->position.y, 0));
	}
	else if (state.player->win == true) {
		Util::DrawText(program, font1, "You Win", 1.0f, -0.5f, glm::vec3(state.player->position.x - 2, state.player->position.y + 2, 0));
	}
}