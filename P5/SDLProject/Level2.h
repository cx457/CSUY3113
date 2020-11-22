#include "Scene.h"
class Level2 : public Scene {

public:
	Level2(int* lives);
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render(ShaderProgram* program) override;
	bool enemyAlldied();
};