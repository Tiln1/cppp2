#include <iostream>
#include <string>
#include <array>
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Transform.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Locator.h"
#include "Graphics/ParticleSystem.h"
#include "Game.h"

void Game::Initialize() {
	m_scene.Startup();
	m_scene.SetGame(this);
}
bool Game::Update(float dt) {
	m_frametime = dt;
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	if (m_paused) dt = 0;

	switch (m_state)
	{
	case Game::eState::TITLE:
		if (Core::Input::IsPressed(VK_SPACE)) {
			m_state = eState::START_GAME;
		}
		break;
	case Game::eState::START_GAME:
	{
		Player* player = new Player;
		player->Load("player.txt");
		m_scene.AddActor(player);

		Locator* locator = new Locator;
		locator->GetTransform().position = nc::Vector2{ 2, 2 };
		player->AddChild(locator);
		locator = new Locator;
		locator->GetTransform().position = nc::Vector2{ -2, 2 };
		player->AddChild(locator);

		for (size_t i = 0; i < 10; i++) {
			Enemy* enemy = new Enemy;
			enemy->Load("enemy.txt");
			enemy->SetTarget(m_scene.GetActor<Player>());

			float distance = nc::random(200, 500);
			float angle = nc::random(0, nc::TAU);
			nc::Vector2 position = nc::Vector2::Rotate({ 0.0f, distance }, angle);

			enemy->GetTransform().position = nc::Vector2{ 400, 300 } + position;
			m_scene.AddActor(enemy);
		}
		if (m_score > m_highscore) { m_highscore = m_score; }

		if (Core::Input::IsPressed('P') && !m_prevPauseButtonPressed) { m_paused = !m_paused; }
		m_prevPauseButtonPressed = Core::Input::IsPressed('P');

		m_state = eState::GAME;
	}
		break;
	case Game::eState::GAME:
		m_spawnTimer += dt;
		if (m_spawnTimer >= 3.0f) {
			m_spawnTimer = 0;

			Enemy* enemy = new Enemy;
			enemy->Load("enemy.txt");
			enemy->SetTarget(m_scene.GetActor<Player>());
			enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
			m_scene.AddActor(enemy);
		}

		m_scene.Update(dt);
		break;
	case Game::eState::PLAYER_DEAD:
		m_lives = m_lives - 1;
		m_state = (m_lives <= 0) ? eState::GAME_OVER : eState::GAME_WAIT;
		m_stateTimer = 3;
		break;
	case Game::eState::GAME_WAIT:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) {
			m_scene.RemoveAllActors();
			m_state = eState::START_GAME;
		}
		break;
	case Game::eState::GAME_OVER:
		m_stateTimer += dt;
		if (m_stateTimer >= 3.0f) {
			m_scene.RemoveAllActors();
			m_state = eState::TITLE;
		}
		break;
	default:
		break;
	}

	int x, y;
	Core::Input::GetMousePos(x, y);
	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT)) {
		std::array<nc::Color, 4> colors{ nc::Color{1,1,1}, nc::Color::red, {1,1,0}, {0,1,1} };
		nc::Color color = colors[rand() % colors.size()];
		g_particleSystem.Create({ x, y }, 0, 180, 30, 1, color, 100, 200);
	}

	g_particleSystem.Update(dt);

	m_scene.Update(dt);

	return quit;

}

void Game::Draw(Core::Graphics& graphics) {
	graphics.SetColor(nc::Color{ 1,1,1 });
	graphics.DrawString(10, 10, std::to_string(m_frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / m_frametime).c_str());

	switch (m_state) {
	case Game::eState::TITLE:
		graphics.DrawString(400, 300, "VECTREX");
		break;
	case Game::eState::START_GAME:
		break;
	case Game::eState::GAME:
	{
		std::string score = "SCORE: " + std::to_string(m_score);
		graphics.DrawString(700, 10, score.c_str());
		m_scene.Draw(graphics);
	}
	break;
	case Game::eState::GAME_OVER:
		break;
	default:
		break;
	}

	graphics.SetColor(nc::Color{1,1,1});

	std::string score = "SCORE: " + std::to_string(m_score);
	graphics.DrawString(700, 10, score.c_str());
	std::string lives = "LIVES: " + std::to_string(m_score);
	graphics.DrawString(700, 25, lives.c_str());
	score = "HIGH SCORE: " + std::to_string(m_score);
	graphics.DrawString(350, 10, score.c_str());
	
	if (m_paused) {
		graphics.DrawString(380, 300, "PAUSED");
	}

	m_scene.Draw(graphics);
	g_particleSystem.Draw(graphics);
}

