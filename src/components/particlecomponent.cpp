#include "particlecomponent.hpp"
#include "../engine.hpp"

ParticleComponent::ParticleComponent(int pps) {
	_pps = pps;
	_accumulator = 0.f;
	_mesh = std::make_shared<PrimitiveMeshes>(PrimitiveMeshes::QUAD);
}

ParticleComponent::~ParticleComponent() {
	
}

void ParticleComponent::update(float delta) {
	// make it particle per second instead of just one.
	if (_particles.size() > 0) {
		_particlePhysics(delta);
	}
	_accumulator += delta;
	_generateParticles();
	_render();
}

void ParticleComponent::_generateParticles() {
	if (_accumulator > 1.0f / _pps) {
		_emmitParticle();
		_accumulator -= 1.0 / _pps;
	}
}

void ParticleComponent::_emmitParticle() {
	std::shared_ptr<Particle> p = std::make_shared<Particle>();
	float dirX = (float)(rand() % 10 + 0 * 2.f - 1.f);
	float dirZ = (float)(rand() % 10 + 0 * 2.f - 1.f);
	p->spawn(glm::vec3(0), glm::vec3(dirX, 1, dirZ), 5, -0.5f);
	p->_vel = glm::normalize(p->_vel);
	p->_scale = glm::vec3(1.f);
	_particles.push_back(p);
}

void ParticleComponent::_particlePhysics(float delta) {
	for (int i = 0; i < _particles.size(); i++) {
		auto p = _particles[i];
		if (_particles[i]->_life <= 0)
			p->setDead();
		if (p->_dead)
			continue;
		p->_vel += p->_affGrav * delta;
		p->_pos += (p->_vel * delta);
		p->fixMX();
	}
}

void ParticleComponent::_render() {
	auto shader = Engine::getInstance().getShader();

	for (int i = 0; i < _particles.size(); i++) {
		shader->bind().setUniform("model", _particles[i]->_m);
		_beforeRender();
		glBindVertexArray(_mesh->getVAO());
		glDrawElementsInstanced(GL_TRIANGLES, _mesh->getIndices().size(), GL_UNSIGNED_INT, NULL, 1);
		_afterRender();
	}
}

void ParticleComponent::_beforeRender() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);
}

void ParticleComponent::_afterRender() {
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
}

float ParticleComponent::_frand(float min, float max) {
	double f = (double)rand() / RAND_MAX;
	return min + f * (max - min);
}