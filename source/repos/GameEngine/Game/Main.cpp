#include <iostream>
#include <string>
#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"
#include "Graphics/ParticleSystem.h"
#include "Game.h"

//Player player;
//std::initializer_list<nc::Actors*> sceneActors;

//int main()
//{    
//    std::cout << "Hello World!\n";
//}

//std::vector<nc::Vector2> points = { { -5, -5 }, { 5, -5 }, { 9, 3 }, { 5, 11 }, { -5, 11 }, {-9, 3 }, {-5, -5} };
//nc::Color color{ 0, 0.5, 1.0 };
//nc::Shape ship;
//
//float scale = 5.0f;
//float position = 0.0f;
//
//float speed = 300.0f;
//float frameTime;
//float roundTime{ 0 };
//bool gameOver{ false };
//
////using time_t = DWORD;
//DWORD prevTime;
//DWORD deltaTime;
//

nc::Scene scene;

float frametime;
float spawnTimer{ 0 };

Game game;

bool Update(float dt)
{
	bool quit = game.Update(dt);
	return quit;
}


void Draw(Core::Graphics& graphics)
{
	game.Draw(graphics);
}

int main()

{
	game.Initialize();

	//ship.Load("ship.txt");

	char name[] = "CSC196 - Ben D";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}


