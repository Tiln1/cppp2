#pragma once
#include "Actor.h"
#include "core.h"
#include <list>
#include <vector>


class Game;
namespace nc {
	class Scene {
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw(Core::Graphics& graphics);
		
		template <typename T>
		T* GetActor() {
			T* actor = nullptr;
			for (Actor* a : m_actors) {
				actor = dynamic_cast<T*>(a);
				if(actor){
					break;
				}
				
			}
			return actor;
		}

		template <typename T>
		std::vector<T*> GetActors() {
			std::vector<T*> actors;
			for (Actor* a : m_actors) {
				T* actor = dynamic_cast<T*>(a);
				if (actor) {
					actors.push_back(actor);
				}
			}
			return actors;
		}


		void AddActor(Actor* actor);
		void RemoveActor(Actor* actor);
		void RemoveAllActors();
		Game* GetGame() { return m_game; }
		void SetGame(Game* game) { m_game = game; }
	private: 
		Game* m_game;
		std::list<class Actor*> m_actors;
	};
}