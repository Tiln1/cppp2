#include <list>
#include "../Header Files/pch.h"
#include "Scene.h"
#include "Actor.h"



namespace nc {
	void Scene::Startup() {

	}

	void Scene::Shutdown() {

	}

	void Scene::Update(float dt) {
		for (Actor* actor : m_actors) {
			actor->Update(dt);
		}
	}

	void Scene::Draw(Core::Graphics& graphics) {
		for (Actor* actor : m_actors) {
			actor->Draw(graphics);
		}
	}

	void Scene::AddActor(Actor* actor) {
		actor->SetScene(this);
		m_actors.push_back(actor);
	}

	void Scene::RemoveActor(Actor* actor) {
		
	}
	void Scene::RemoveAllActors(){

	}
}