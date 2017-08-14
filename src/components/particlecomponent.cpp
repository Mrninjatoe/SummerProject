#include "particlecomponent.hpp"
#include "../engine.hpp"
#include <algorithm>

#define ROW 8

ParticleComponent::ParticleComponent(int pps) {
	_pps = pps;
	_accumulator = 0.f;
	_mesh = std::make_shared<PrimitiveMeshes>(PrimitiveMeshes::QUAD);
	_texture = std::make_shared<Texture>("assets/textures/fireAtlas.png");
}

ParticleComponent::~ParticleComponent() {
	
}

void ParticleComponent::update(float delta) {
	if (_particles.size() > 0) {
		_particlePhysics(delta);
	}
	_accumulator += delta;
	_generateParticles();
}

void ParticleComponent::_generateParticles() {
	if (_accumulator > 1.0f / _pps) {
		_emmitParticle();
		_accumulator -= 1.0 / _pps;
	}
}

void ParticleComponent::_emmitParticle() {
	std::shared_ptr<Particle> p = std::make_shared<Particle>();
	float dirX = (1 * 2.f - 1.f);
	float dirZ = (_frand(1, 2) * 2.f - 1.f);
	float dirY = (_frand(1, 5) * 2.f - 1.f);
	p->spawn(glm::vec3(0), glm::vec3(dirX, dirY, dirZ), glm::vec3(_frand(0.1f, 5), _frand(0.1f, 2), _frand(0.1f, 3.5f)), 3.f, -0.5f);
	p->_vel = glm::normalize(p->_vel);
	p->_scale = glm::vec3(2.0f);
	_particles.push_back(p);
}

void ParticleComponent::_particlePhysics(float delta) {
	for (int i = 0; i < _particles.size(); i++) {
		auto p = _particles[i];
		if (p->_life <= p->_elapsedTime)
			p->setDead();
		if (p->_dead)
			continue;
		p->_vel += p->_affGrav * delta;
		p->_pos += (p->_vel * delta);
		_updateTextureCoordInfo(p, delta);
		p->_elapsedTime += delta;
		p->fixMX();
	}
	_clearDeadParticles();
}

void ParticleComponent::render() {
	auto shader = Engine::getInstance().getShader();

	for (int i = 0; i < _particles.size(); i++) {
		shader->bind().setUniform("model", _particles[i]->_m)
			.setUniform("texOffset1", _particles[i]->_texOffset1)
			.setUniform("texOffset2", _particles[i]->_texOffset2)
			.setUniform("texCoordInfo", _particles[i]->_texCoordInfo)
			.setUniform("particleColor", _particles[i]->_color);
		_beforeRender();
		glBindVertexArray(_mesh->getVAO());
		glDrawElementsInstanced(GL_TRIANGLES, _mesh->getIndices().size(), GL_UNSIGNED_INT, NULL, 1);
		_afterRender();
	}
}

void ParticleComponent::_clearDeadParticles() {
	_particles.erase(std::remove_if(
		_particles.begin(), _particles.end(),
		[](const std::shared_ptr<Particle>& p) {
		return p->_dead;
	}), _particles.end());
}

void ParticleComponent::_beforeRender() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDepthMask(GL_FALSE);
}

void ParticleComponent::_afterRender() {
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
}

void ParticleComponent::_updateTextureCoordInfo(std::shared_ptr<Particle> particle, float delta){
	float lifeFactor = particle->_elapsedTime / particle->_life;
	int stageCount = ROW*ROW; // rows * rows
	float atlasProg = lifeFactor * stageCount;
	int index1 = (int) floor(atlasProg);
	int index2 = index1 < stageCount - 1 ? index1 + 1 : index1;
	particle->_texCoordInfo = glm::vec2(ROW, fmod(atlasProg, 1));
	_setTextureOffset(particle->_texOffset1, index1);
	_setTextureOffset(particle->_texOffset2, index2);
}

void ParticleComponent::_setTextureOffset(glm::vec2& offset, int index){
	int column = index % ROW;
	int row = index / ROW;
	offset.x = column / (float)ROW;
	offset.y = row / (float)ROW;
}

float ParticleComponent::_frand(float min, float max) {
	double f = (double)rand() / RAND_MAX;
	return min + f * (max - min);
}