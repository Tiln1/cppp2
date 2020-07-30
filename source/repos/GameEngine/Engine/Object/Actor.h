#pragma once
#include "../Graphics/Shape.h"
#include "../Math/Transform.h"
#include <vector>

namespace nc {
	class Scene;
	class Actor {
	public:
		enum class eType {
			PLAYER, ENEMY, PROJECTILE
		};

		Actor() {}
		Actor(const Transform& transform, const Shape& shape) : m_transform{transform}, m_shape{shape} {}
		~Actor() {}

		virtual void OnCollision(Actor* actor) {}
		virtual bool Load(const std::string& filename);
		//virtual void Load(std::string& stream);
		void SetScene(Scene* scene) { m_scene = scene; }

		Transform& GetTransform() { return m_transform; }
		Shape& GetShape() { return m_shape; }

		Actor* GetParent() { m_parent; }
		virtual void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);
		float GetRadius();
		void AddChild(Actor* child);
		virtual eType GetType() = 0;
	protected:
		bool m_destroy{ false };
		Scene* m_scene{ nullptr };
		Transform m_transform;
		Shape m_shape;

		Actor* m_parent{ nullptr };
		std::vector<Actor*> m_children;
	};
}