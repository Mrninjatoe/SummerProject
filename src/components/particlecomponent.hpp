#pragma once
#include "component.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "../entities/primitivemeshes.hpp"
#include "../texture.hpp"
#include <vector>
#include <memory>

class ParticleComponent : public Component {
	struct Particle {
		glm::vec3 _pos;
		glm::vec3 _vel;
		glm::vec3 _scale;
		glm::vec3 _color;
		glm::mat4 _m;
		float _affGrav; // Gravity affecting the particle.
		float _life;
		glm::vec2 _texOffset1;
		glm::vec2 _texOffset2;
		glm::vec2 _texCoordInfo;
		float _elapsedTime;
		bool _dead;
		void spawn(glm::vec3 pos, glm::vec3 vel, glm::vec3 color, float life, float grav) {
			_pos = pos;
			_vel = vel;
			_life = life;
			_color = color;
			_affGrav = grav;
			_scale = glm::vec3(2.0f);
			_elapsedTime = 0;
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
	std::shared_ptr<Texture> getTexture() { return _texture; }
	void render();
private:
	int _pps; // Particle Per Second
	float _accumulator;
	std::vector<std::shared_ptr<Particle>> _particles;
	std::shared_ptr<PrimitiveMeshes> _mesh;
	std::shared_ptr<Texture> _texture;

	void _generateParticles();
	void _clearDeadParticles();
	void _emmitParticle();
	void _particlePhysics(float delta);
	void _beforeRender();
	void _afterRender();
	void _updateTextureCoordInfo(std::shared_ptr<Particle> particle, float delta);
	void _setTextureOffset(glm::vec2& offset, int index);
	float _frand(float min, float max);
};