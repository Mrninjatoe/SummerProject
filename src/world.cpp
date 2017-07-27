#include "world.hpp"
#include "components/cameracomponent.hpp"
#include "components/transformcomponent.hpp"
#include "engine.hpp"

World::World() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			createEntity(glm::vec3(i * -5, 0, j * 5));
		}
	}
}

World::~World() {

}

void World::update(float delta) {
	auto shader = Engine::getInstance().getShader();
	for (std::shared_ptr<Entity> e : _entities) {
		auto tc = e->get<TransformComponent>();
		if (!tc)
			continue;

		tc->rotate(0.001f, glm::vec3(0, 1, 0));
		shader->bind().setUniform("model", tc->getModelMX());

		auto cc = e->get<CameraComponent>();
		if (!cc)
			continue;

		shader->bind().setUniform("lightPos", cc->getCameraPos());
		e->update(delta);
	}
}

std::shared_ptr<Entity> World::createEntity(glm::vec3 pos) {
	std::shared_ptr<Entity> e = std::make_shared<Entity>();

	ModelComponent* mc = new ModelComponent("assets/models/cube.obj");
	e->addComponent(std::type_index(typeid(ModelComponent)), mc);

	CameraComponent* cc = new CameraComponent();
	cc->setCameraPos(glm::vec3(-25, 50, 25));
	cc->setLookAt(glm::vec3(-25, 0, 25));
	e->addComponent(std::type_index(typeid(CameraComponent)), cc);

	TransformComponent* tc = new TransformComponent(pos);
	e->addComponent(std::type_index(typeid(TransformComponent)), tc);
	
	_entities.push_back(e);
	return e;
}