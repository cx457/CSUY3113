#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "stb_image.h"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

//press the space bar to move the ball

SDL_Window* displayWindow;
bool gameIsRunning = true;
bool start = false;

ShaderProgram program;
glm::mat4 viewMatrix, projectionMatrix, ballMatrix, player1Matrix, player2Matrix;


glm::vec3 ball_position = glm::vec3(0, 0, 0);
glm::vec3 ball_movement = glm::vec3(0, 0, 0);
float player_speed = 2.0f;

glm::vec3 player1_position = glm::vec3(0, 0, 0);
glm::vec3 player1_movement = glm::vec3(0, 0, 0);

glm::vec3 player2_position = glm::vec3(0, 0, 0);
glm::vec3 player2_movement = glm::vec3(0, 0, 0);

void Initialize() {
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("Project2!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

#ifdef _WINDOWS
	glewInit();
#endif

	glViewport(0, 0, 640, 480);


	program.Load("shaders/vertex.glsl", "shaders/fragment.glsl");

	viewMatrix = glm::mat4(1.0f);

	ballMatrix = glm::mat4(1.0f);
	player1Matrix = glm::mat4(1.0f);
	player2Matrix = glm::mat4(1.0f);

	projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
	program.SetProjectionMatrix(projectionMatrix);

	program.SetViewMatrix(viewMatrix);

	program.SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	glUseProgram(program.programID);

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ProcessInput() {

	player1_movement = glm::vec3(0);
	player2_movement = glm::vec3(0);

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
				//player1_movement.x = 1.0f;
				break;

			case SDLK_SPACE:
				// Some sort of action
				break;
			}
			break; // SDL_KEYDOWN
		}
	}

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_S]) {
		if (player1_position.y >= -3.75f){
			player1_movement.y = -1.0f;
		}
	}
	else if (keys[SDL_SCANCODE_W]) {
		if (player1_position.y <= 3.75f) {
			player1_movement.y = 1.0f;
		}
	}

	if (keys[SDL_SCANCODE_DOWN]) {
		if (player2_position.y >= -3.75f) {
			player2_movement.y = -1.0f;
		}
	}
	else if (keys[SDL_SCANCODE_UP]) {
		if (player2_position.y <= 3.75f) {
			player2_movement.y = 1.0f;
		}
	}

	if (start == false) {
		if (keys[SDL_SCANCODE_SPACE]) {
			ball_movement.x = 2.0f;
			ball_movement.y = 2.0f;
			start = true;
		}
	}


	if (glm::length(player1_movement) > 1.0f) {
		player1_movement = glm::normalize(player1_movement);
	}

	if (glm::length(player2_movement) > 1.0f) {
		player2_movement = glm::normalize(player2_movement);
	}

	if (ball_position.y >= 3.75f) {
		ball_movement.y = -2.0f;
	}
	if (ball_position.y <= -3.75f) {
		ball_movement.y = 2.0f;
	}
	if (ball_position.x > 5.0f) {
		ball_movement.x = 0.0f;
		ball_movement.y = 0.0f;
		player1_movement.y = 0.0f;
		player2_movement.y = 0.0f;
	}
	if (ball_position.x < -5.0f) {
		ball_movement.x = 0.0f;
		ball_movement.y = 0.0f;
		player1_movement.y = 0.0f;
		player2_movement.y = 0.0f;
	}

}

float lastTicks = 0.0f;

void Update() {
	float ticks = (float)SDL_GetTicks() / 1000.0f;
	float deltaTime = ticks - lastTicks;
	lastTicks = ticks;
	
	ball_position += ball_movement * deltaTime;

	player1Matrix = glm::mat4(1.0f);
	player1_position.x = -5.0f;

	player2Matrix = glm::mat4(1.0f);
	player2_position.x = 5.0f;

	player1_position += player1_movement * player_speed * deltaTime;
	player2_position += player2_movement * player_speed * deltaTime;

	if (ball_movement.x != 0.0f) {
		float p1distx = fabs(ball_position.x - player1_position.x) - ((0.5f + 0.5f) / 2.0f);
		float p1disty = fabs(ball_position.y - player1_position.y) - ((1.0f + 0.5f) / 2.0f);

		float p2distx = fabs(ball_position.x - player2_position.x) - ((0.5f + 0.5f) / 2.0f);
		float p2disty = fabs(ball_position.y - player2_position.y) - ((1.0f + 0.5f) / 2.0f);

		if (p1distx < 0 && p1disty < 0) {
			ball_movement.x = 2.0f;
		}
		if (p2distx < 0 && p2disty < 0) {
			ball_movement.x = -2.0f;
		}
	}

	player1Matrix = glm::translate(player1Matrix, player1_position);
	player2Matrix = glm::translate(player2Matrix, player2_position);
	ballMatrix = glm::translate(ballMatrix, glm::vec3(ball_movement.x*deltaTime, ball_movement.y*deltaTime, 0.0f));
}

void Render() {
	glClear(GL_COLOR_BUFFER_BIT);

	program.SetModelMatrix(ballMatrix);

	float vertices[] = { -0.25,-0.25, 0.25,-0.25, 0.25,0.25, -0.25,-0.25, 0.25,0.25, -0.25,0.25};

	glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
	glEnableVertexAttribArray(program.positionAttribute);
	
	glDrawArrays(GL_TRIANGLES, 0, 6);

	program.SetModelMatrix(player1Matrix);

	float player1vertices[] ={ -0.25,-0.75, 0.25,-0.75, 0.25,0.75, -0.25,-0.75, 0.25,0.75, -0.25,0.75 };

	glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, player1vertices);
	glEnableVertexAttribArray(program.positionAttribute);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	program.SetModelMatrix(player2Matrix);

	float player2vertices[] = { -0.25,-0.75, 0.25,-0.75, 0.25,0.75, -0.25,-0.75, 0.25,0.75, -0.25,0.75 };

	glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, player2vertices);
	glEnableVertexAttribArray(program.positionAttribute);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(program.positionAttribute);

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
		Render();
	}

	Shutdown();
	return 0;
}
