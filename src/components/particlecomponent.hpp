#pragma once
#include "component.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "../entities/primitivemeshes.hpp"
#include <vector>
#include <memory>

class ParticleComponent : public Component {
	struct Particle {
		glm::vec3 _pos;
		glm::vec3 _vel;
		glm::vec3 _scale;
		glm::mat4 _m;
		float _affGrav; // Gravity affecting the particle.
		float _life;
		bool _dead;
		void spawn(glm::vec3 pos, glm::vec3 vel, float life, float grav) {
			_pos = pos;
			_vel = vel;
			_life = life;
			_affGrav = grav;
			_scale = glm::vec3(0);
			_dead = false;
			_m = glm::translate(pos) * glm::scale(_scale);
		}
		void fixMX() {
			_m = glm::translate(_pos) * glm::scale(_scale);
		}
		void setDead() { _dead = true; }
	};
public:
	ParticleComponent(int pps);
	virtual ~ParticleComponent();
	void update(float delta);
private:
	int _pps; // Particle Per Second
	float _accumulator;
	std::vector<std::shared_ptr<Particle>> _particles;
	std::shared_ptr<PrimitiveMeshes> _mesh;

	void _generateParticles();
	void _emmitParticle();
	void _particlePhysics(float delta);
	void _render();
	void _beforeRender();
	void _afterRender();
	float _frand(float min, float max);
};