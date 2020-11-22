#include "Scene.h"
class Level1 : public Scene {

public:
	Level1(int* lives);
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render(ShaderProgram* program) override;
	bool enemyAlldied();
};