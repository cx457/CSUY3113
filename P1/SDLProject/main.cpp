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

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, strikerMatrix, projectionMatrix, soccerMatrix, gkMatrix;

float soccer_x = 0;
float soccer_rotate = 0;
float gk_pos_x = 0;
int back = 0; //decides if goalkeeper comes back

GLuint textureID1, textureID2, textureID3;

GLuint LoadTexture(const char* filePath) {
	int w, h, n;
	unsigned char* image = stbi_load(filePath, &w, &h, &n, STBI_rgb_alpha);

	if (image == NULL) {
		std::cout << "Unable to load image. Make sure the path is correct\n";
		assert(false);
	}

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_image_free(image);
	return textureID;
}

void Initialize() {
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("Project1!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

#ifdef _WINDOWS
	glewInit();
#endif

	glViewport(0, 0, 640, 480);

	// load the shaders for handling textures!
	program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");

	//load our image

	viewMatrix = glm::mat4(1.0f);
	strikerMatrix = glm::mat4(1.0f);
	soccerMatrix = glm::mat4(1.0f);


	projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
	program.SetProjectionMatrix(projectionMatrix);

	program.SetViewMatrix(viewMatrix);

	glUseProgram(program.programID);

	glClearColor(0.0f, 2.0f, 0.0f, 1.0f);

	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	textureID1 = LoadTexture("player.png");
	textureID2 = LoadTexture("soccer.png");
	textureID3 = LoadTexture("gk.png");
}

void ProcessInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			gameIsRunning = false;
		}
	}
}

float lastTicks = 0.0f;

void Update() {
	float ticks = (float)SDL_GetTicks() / 1000.0f;
	float deltaTime = ticks - lastTicks;
	lastTicks = ticks;

	soccer_x += -1.0f * deltaTime;
	soccer_rotate += 90.0f * deltaTime;

	if (gk_pos_x < 5.0f && back == 0) {
		gk_pos_x += 1.0f * deltaTime;
		if (gk_pos_x == 5.0f) {
			back = 1;
		}
	}
	else if (back == 1) {
		gk_pos_x -= 1.0f * deltaTime;
		if (gk_pos_x == 0.0f) {
			back = 0;
		}
	}

	strikerMatrix = glm::mat4(1.0f);

	soccerMatrix = glm::mat4(1.0f);

	gkMatrix = glm::mat4(1.0f);

	soccerMatrix = glm::rotate(soccerMatrix, glm::radians(soccer_rotate), glm::vec3(0.0f, 0.0f, 1.0f));

	gkMatrix = glm::translate(gkMatrix, glm::vec3(gk_pos_x, 0.0f, 0.0f));

}

void Render() {
	glClear(GL_COLOR_BUFFER_BIT);

	program.SetModelMatrix(strikerMatrix);

	float vertices[] = { 2.5, 2.5, 3.5, 2.5, 3.5, 3.5,2.5,2.5,3.5,3.5,2.5,3.5 };
	float texCoords[] = { 0.0,1.0,1.0,1.0,1.0,0.0,0.0,1.0,1.0,0.0,0.0,0.0 };

	glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
	glEnableVertexAttribArray(program.positionAttribute);
	glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
	glEnableVertexAttribArray(program.texCoordAttribute);

	glBindTexture(GL_TEXTURE_2D, textureID1);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	program.SetModelMatrix(soccerMatrix);

	float vertices2[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5,-0.5,-0.5,0.5,0.5,-0.5,0.5 };
	float texCoords2[] = { 0.0,1.0,1.0,1.0,1.0,0.0,0.0,1.0,1.0,0.0,0.0,0.0 };

	glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices2);
	glEnableVertexAttribArray(program.positionAttribute);
	glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords2);
	glEnableVertexAttribArray(program.texCoordAttribute);

	glBindTexture(GL_TEXTURE_2D, textureID2);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	program.SetModelMatrix(gkMatrix);

	float vertices3[] = { -2.5, -2.5, -1.5, -2.5, -1.5, -1.5,-2.5,-2.5,-1.5,-1.5,-2.5,-1.5 };
	float texCoords3[] = { 0.0,1.0,1.0,1.0,1.0,0.0,0.0,1.0,1.0,0.0,0.0,0.0 };

	glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices3);
	glEnableVertexAttribArray(program.positionAttribute);
	glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords3);
	glEnableVertexAttribArray(program.texCoordAttribute);

	glBindTexture(GL_TEXTURE_2D, textureID3);
	glDrawArrays(GL_TRIANGLES, 0, 6);


	glDisableVertexAttribArray(program.positionAttribute);
	glDisableVertexAttribArray(program.texCoordAttribute);

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