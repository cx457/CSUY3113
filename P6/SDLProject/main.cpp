#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <vector>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

#include "Entity.h"
#include "Map.h"
#include "Util.h"
#include "Scene.h"
#include "Menu.h"
#include "Level1.h"
#include "Level2.h"


// There are two levels for this game. For the first level, player simply collects the golds and escape
// the zombies. There are 4 AIs in the first level. They will chase the player until they can't see the 
// players. Also, there are 4 golds in this level. After collecting all the coins, a gate will be opened
// to go to the next level. For the last level, there is only one AI and your goal is run(yes just run)! 
// But this AI is a boss who ignores gravity(but player can't ignore gravity!). If a player die and still 
// has lives, the player will go back to the born position. If you want to test the game, you can look
// at the position of the golds and gate but it might cause the gametime to be less than 2 minutes if
// player knows the position of everything.Thanks for playing!

SDL_Window* displayWindow;
bool gameIsRunning = true;

int lives = 3;

bool entered = false;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;

Scene* currentScene;
Scene* sceneList[4];
int sceneTrack = 1;

void SwitchToScene(Scene* scene) {
	currentScene = scene;
	currentScene->Initialize();
}

Mix_Music* music;
Mix_Chunk* fail;


void Initialize() {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	displayWindow = SDL_CreateWindow("Project 6", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

#ifdef _WINDOWS
	glewInit();
#endif

	glViewport(0, 0, 640, 480);

	program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	music = Mix_LoadMUS("ch.mp3");
	Mix_PlayMusic(music, -1);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 4);

	fail = Mix_LoadWAV("15.wav");

	viewMatrix = glm::mat4(1.0f);

	modelMatrix = glm::mat4(1.0f);
	projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);

	program.SetProjectionMatrix(projectionMatrix);
	program.SetViewMatrix(viewMatrix);

	glUseProgram(program.programID);

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	sceneList[0] = new Menu();

	sceneList[1] = new Level1(&lives);
	sceneList[2] = new Level2(&lives);

	SwitchToScene(sceneList[0]);
}

void ProcessInput() {

	currentScene->state.player->movement = glm::vec3(0);

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
		case SDL_WINDOWEVENT_CLOSE:
			gameIsRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				// Move the player left
				break;

			case SDLK_RIGHT:
				// Move the player right
				break;

			case SDLK_SPACE:
				if (currentScene->state.player->win == false) {
					if (currentScene->state.player->collidedBottom) {
						currentScene->state.player->jump = true;
					}
				}
				break;
			case SDLK_RETURN:
				if (currentScene == sceneList[0]) {
					currentScene->state.nextScene = 1;
				}
			}
			break; // SDL_KEYDOWN
		}
	}

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_LEFT]) {
		if (currentScene->state.player->moveLeft == true) {
			if (currentScene->state.player->win == false) {
				currentScene->state.player->movement.x = -1.0f;
				currentScene->state.player->animIndices = currentScene->state.player->animLeft;
			}
		}
	}
	else if (keys[SDL_SCANCODE_RIGHT]) {
		if (currentScene->state.player->moveRight == true) {
			if (currentScene->state.player->win == false) {
				currentScene->state.player->movement.x = 1.0f;
				currentScene->state.player->animIndices = currentScene->state.player->animRight;
			}
		}
	}
	else if (keys[SDL_SCANCODE_UP]) {
		if (currentScene->state.player->moveUp == true) {
			if (currentScene->state.player->win == false) {
				currentScene->state.player->movement.y = 1.0f;
				currentScene->state.player->animIndices = currentScene->state.player->animUp;
			}
		}
	}
	else if (keys[SDL_SCANCODE_DOWN]) {
		if (currentScene->state.player->moveDown == true) {
			if (currentScene->state.player->win == false) {
				currentScene->state.player->movement.y = -1.0f;
				currentScene->state.player->animIndices = currentScene->state.player->animDown;
			}
		}
	}


	if (glm::length(currentScene->state.player->movement) > 1.0f) {
		currentScene->state.player->movement = glm::normalize(currentScene->state.player->movement);
	}

}




#define FIXED_TIMESTEP 0.0166666f
float lastTicks = 0;
float accumulator = 0.0f;

bool playTime = 1;
bool playSuccessTime = 1;

void Update() {
	float ticks = (float)SDL_GetTicks() / 1000.0f;
	float deltaTime = ticks - lastTicks;
	lastTicks = ticks;

	deltaTime += accumulator;
	if (deltaTime < FIXED_TIMESTEP) {
		accumulator = deltaTime;
		return;
	}

	while (deltaTime >= FIXED_TIMESTEP) {
		// Update. Notice it's FIXED_TIMESTEP. Not deltaTime
		currentScene->Update(FIXED_TIMESTEP);

		deltaTime -= FIXED_TIMESTEP;
	}

	accumulator = deltaTime;

	if (currentScene->state.player->isActive == false && playTime == 1) {
		Mix_PlayChannel(-1, fail, 0);
		playTime = 0;
	}

	if (sceneTrack == 3 && currentScene->state.player->win == true && playSuccessTime == 1) {
		music = Mix_LoadMUS("victory.mp3");
		Mix_PlayMusic(music, -1);
		Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
		playSuccessTime = 0;
	}

	if (sceneTrack == 3 && entered == false) {
		music = Mix_LoadMUS("oneWing.mp3");
		Mix_PlayMusic(music, -1);
		Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
		entered = true;
	}

	viewMatrix = glm::mat4(1.0f);

	if (sceneTrack > 1) {
		if (currentScene->state.player->position.x >= 4.4 && currentScene->state.player->position.x <= 34.6 && currentScene->state.player->position.y <= -3.25 && currentScene->state.player->position.y >= -35.6) {
			viewMatrix = glm::translate(viewMatrix, glm::vec3(-currentScene->state.player->position.x, -currentScene->state.player->position.y, 0));
		}
		else {
			if (currentScene->state.player->position.x < 4.4) {
				if (currentScene->state.player->position.y > -3.25) {
					viewMatrix = glm::translate(viewMatrix, glm::vec3(-4.4, 3.25, 0));
				}
				else if (currentScene->state.player->position.y < -35.6) {
					viewMatrix = glm::translate(viewMatrix, glm::vec3(-4.4, 35.6, 0));
				}
				else {
					viewMatrix = glm::translate(viewMatrix, glm::vec3(-4.4, -currentScene->state.player->position.y, 0));
				}
			}
			else if (currentScene->state.player->position.x > 34.6) {
				if (currentScene->state.player->position.y > -3.25) {
					viewMatrix = glm::translate(viewMatrix, glm::vec3(-34.6, 3.25, 0));
				}
				else if (currentScene->state.player->position.y < -35.6) {
					viewMatrix = glm::translate(viewMatrix, glm::vec3(-34.6, 35.6, 0));
				}
				else {
					viewMatrix = glm::translate(viewMatrix, glm::vec3(-34.6, -currentScene->state.player->position.y, 0));
				}
			}

			else if (currentScene->state.player->position.y > -3.25) {
				if (currentScene->state.player->position.x < 4.4) {
					viewMatrix = glm::translate(viewMatrix, glm::vec3(-4.4, 3.25, 0));
				}
				else if (currentScene->state.player->position.x > 34.6) {
					viewMatrix = glm::translate(viewMatrix, glm::vec3(-34.6, 3.25, 0));
				}
				else {
					viewMatrix = glm::translate(viewMatrix, glm::vec3(-currentScene->state.player->position.x, 3.25, 0));
				}
			}
			else if (currentScene->state.player->position.y < -35.6) {
				if (currentScene->state.player->position.x < 4.4) {
					viewMatrix = glm::translate(viewMatrix, glm::vec3(-4.4, 35.6, 0));
				}
				else if (currentScene->state.player->position.x > 34.6) {
					viewMatrix = glm::translate(viewMatrix, glm::vec3(-34.6, 35.6, 0));
				}
				else {
					viewMatrix = glm::translate(viewMatrix, glm::vec3(-currentScene->state.player->position.x, 35.6, 0));
				}
			}

		}
	}
}

void Render() {
	glClear(GL_COLOR_BUFFER_BIT);

	program.SetViewMatrix(viewMatrix);

	currentScene->Render(&program);

	SDL_GL_SwapWindow(displayWindow);
}


void Shutdown() {
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	Initialize();

	while (gameIsRunning) {
		ProcessInput();
		Update();
		if (currentScene->state.nextScene >= 0) {
			SwitchToScene(sceneList[sceneTrack]);
			sceneTrack++;
		}
		Render();
	}

	Shutdown();
	return 0;
}