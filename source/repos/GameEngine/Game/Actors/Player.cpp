#include <fstream>
#include "Player.h"
#include "Enemy.h"
#include "Math/Math.h"
#include "Header Files/pch.h"
#include "Math/Random.h"
#include "Math/Color.h"
#include "Math/Vector2.h"
#include "Graphics/Particle.h"
#include "Graphics/ParticleSystem.h"
#include "Object/Scene.h"
#include "Projectile.h"
#include "../Game.h"

void Player::Update(float dt) {

	if (Core::Input::IsPressed(VK_SPACE)) {

	}

	int const MAX_X = 800;
	int const MAX_Y = 600;

	nc::Vector2 force;
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward* m_thrust; }
	force = nc::Vector2::Rotate(force, m_transform.angle);

	m_velocity = m_velocity + (force * dt);
	m_velocity = m_velocity * 0.98f;

	m_transform.position = m_transform.position + (m_velocity * dt);

	if (m_transform.position.x > MAX_X) { m_transform.position.x = 0; }
	if (m_transform.position.x < 0) { m_transform.position.x = MAX_X; }
	if (m_transform.position.y > MAX_Y) { m_transform.position.y = 0; }
	if (m_transform.position.y < 0) { m_transform.position.y = MAX_Y; }

	float torque{ 0 };
	if (Core::Input::IsPressed('A')) { torque = -20.0f;  m_transform.angle -= dt * nc::DegreesToRadians(120.0f); }
	if (Core::Input::IsPressed('D')) { torque = 20.0f;  m_transform.angle += dt * nc::DegreesToRadians(120.0f); }

	m_angularVelocity = m_angularVelocity + (torque * dt);
	m_angularVelocity = m_angularVelocity * 0.95f;
	m_transform.angle = m_transform.angle + (m_angularVelocity * dt);



	if (force.LengthSqr() > 0 && !m_children.empty()) {
		Actor* child = m_children[0];
		//g_particleSystem.Create(child->GetTransform().matrix.GetPosition(), child->GetTransform().matrix.GetAngle() + nc::PI, 10, 1, 1, nc::Color{ 0,0.5,1 }, 100, 200);

		child = m_children[1];
		//g_particleSystem.Create(child->GetTransform().matrix.GetPosition(), child->GetTransform().matrix.GetAngle() + nc::PI, 10, 1, 1, nc::Color{ 0,0.5,1 }, 100, 200);
	}
	if (Core::Input::IsPressed('E') && !m_prevButtonPress) {
		m_transform.position = nc::Vector2{ nc::random(0, MAX_X), nc::random(0, MAX_Y) };
		m_transform.angle = nc::random(0, nc::TAU);
	}

	m_prevButtonPress = Core::Input::IsPressed('E');
	m_transform.Update();
	for (auto child : m_children) {
		child->Update(dt);
	}
}

bool Player::Load(const std::string& filename) {
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open()) {
		stream >> m_transform;

		std::string shapename;
		stream >> shapename;
		m_shape.Load(shapename);

		success = true;
	}

	return success;
}

void Player::OnCollision(Actor* actor) {
	if (!m_destroy && actor->GetType() == eType::ENEMY) {
		m_destroy = true;
		m_scene->GetGame()->SetState(Game::eState::PLAYER_DEAD);

		auto enemies = m_scene->GetActors<Enemy>();
		for (auto enemy : enemies) {
			enemy->SetTarget(nullptr);
		}

		nc::Color colors[] = { nc::Color::white, nc::Color::red, nc::Color::yellow, nc::Color::cyan };
		nc::Color color = colors[rand() % 4];
		g_particleSystem.Create(m_transform.position, 0, 180, 100, 2, color, 100, 200);
	}

}