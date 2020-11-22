#include "Menu.h"

GLuint font;

void Menu::Initialize() {

    state.nextScene = -1;
    state.map = NULL;
    // Move over all of the player and enemy code from initialization.
    state.enemies = new Entity[0];
    state.player = new Entity();
    font = Util::LoadTexture("font1.png");

}
void Menu::Update(float deltaTime) {
}
void Menu::Render(ShaderProgram* program) {
    Util::DrawText(program, font, "George v.s Evil", 1.0f, -0.5f, glm::vec3(-4.25f, 1, 0));
}