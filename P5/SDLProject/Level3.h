#include "Scene.h"
class Level3 : public Scene {

public:
	Level3(int* lives);
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render(ShaderProgram* program) override;
	bool enemyAlldied();
};