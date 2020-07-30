#pragma once
#include "core.h"
#include "Object/Scene.h"

class Game
{
public:
	enum class eState
	{
		TITLE,
		INIT_GAME,
		START_GAME,
		GAME,
		PLAYER_DEAD,
		GAME_WAIT,
		GAME_OVER
	};
public:
	void Initialize();

	bool Update(float dt);
	void Draw(Core::Graphics& graphics);

	void SetState(eState state) { m_state = state; }

	void AddPoints(int points) { m_score += points; }

protected:
	bool m_prevPauseButtonPressed{ false };
	bool m_paused{ false };

	int m_score{ 0 };
	int m_lives{ 3 };
	int m_highscore{ 0 };


	nc::Scene m_scene;
	eState m_state{ eState::TITLE };

	float m_frametime;
	float m_spawnTimer{ 0 };
	float m_stateTimer{ 0 };
};