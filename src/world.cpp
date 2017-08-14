#include "world.hpp"
#include "components/cameracomponent.hpp"
#include "components/transformcomponent.hpp"
#include "components/particlecomponent.hpp"
#include "engine.hpp"

World::World() {
	auto e = createEntity(glm::vec3(0, 0, 0));
	CameraComponent* cc = new CameraComponent();
	cc->setCameraPos(glm::vec3(0, 0, -10));
	cc->setLookAt(glm::vec3(0, 0, 0));
	e->addComponent(std::type_index(typeid(CameraComponent)), cc);

	ParticleComponent* pc = new ParticleComponent(10);
	e->addComponent(std::type_index(typeid(ParticleComponent)), pc);
}

World::~World() {

}

void World::render() {
	for (std::shared_ptr<Entity> e : _entities) {
		auto mc = e->get<ModelComponent>();
		if (mc)
			mc->render();
		auto pc = e->get<ParticleComponent>();
		if (pc)
			pc->render();
	}
}

void World::update(float delta) {
	auto shader = Engine::getInstance().getShader();
	for (std::shared_ptr<Entity> e : _entities) {
		auto tc = e->get<TransformComponent>();
		if (!tc)
			continue;

		tc->rotate(0.01f, glm::vec3(0, 1, 0));
		shader->bind().setUniform("model", tc->getModelMX());

		auto cc = e->get<CameraComponent>();
		if (cc)
			shader->bind().setUniform("lightPos", cc->getCameraPos());
		
		auto pc = e->get<ParticleComponent>();
		if (pc)
			pc->getTexture()->bind(0);

		e->update(delta);
	}
}

std::shared_ptr<Entity> World::createEntity(glm::vec3 pos) {
	std::shared_ptr<Entity> e = std::make_shared<Entity>();

	//ModelComponent* mc = new ModelComponent(PrimitiveMeshes::QUAD);
	//e->addComponent(std::type_index(typeid(ModelComponent)), mc);
	//
	TransformComponent* tc = new TransformComponent(pos);
	//tc->rotate(90, glm::vec3(0, 0, 1));
	e->addComponent(std::type_index(typeid(TransformComponent)), tc);
	
	_entities.push_back(e);
	return e;
}