// GameEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Shape.h"

//Player player;
//std::initializer_list<nc::Actors*> sceneActors;

//int main()
//{    
//    std::cout << "Hello World!\n";
//}

std::vector<nc::Vector2> points = { { -5, -5 }, { 5, -5 }, { 9, 3 }, { 5, 11 }, { -5, 11 }, {-9, 3 }, {-5, -5} };
nc::Color color{ 0, 0.5, 1.0 };

float scale = 5.0f;
float position = 0.0f;

float speed = 300.0f;
float frameTime;
float roundTime{ 0 };
bool gameOver{ false };

//using time_t = DWORD;
DWORD prevTime;
DWORD deltaTime;

bool Update(float dt)
{
	frameTime = dt;
	roundTime += dt;
	if (roundTime >= 5) {
		gameOver = true;
	}


	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;

	int x, y;
	//Core::Input
	//for (size_t i = 0; i < points.size(); i++) {
	//	points[i] = nc::Vector2{ nc::random(0.0f, 800.0f), nc::random(0.0f, 600.0f) };
	//}
	return false;
}


void Draw(Core::Graphics& graphics)
{

	nc::Vector2 pos = nc::Vector2(400.0f, 300.0f);
	nc::Shape ship{ {points}, {color} };
	ship.Draw(graphics, pos, scale);

}

int main()

{
	DWORD time = GetTickCount();

	//ship.load("ship.txt");

	char name[] = "CSC196 - Ben D";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}


