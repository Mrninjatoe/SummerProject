#pragma once
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <vector>
#include "lib/glad.h"
#include <SDL2/SDL_image.h>
#include <iostream>

#include "entities/primitivemeshes.hpp"
#include "framebuffer.hpp"
#include "shaderprogram.hpp"
#include "world.hpp"

class Engine {
public:
	static Engine& getInstance() {
		static Engine instance;

		return instance;
	}
	Engine(Engine const&) = delete;
	void operator=(Engine const&) = delete;
	int run();
	std::shared_ptr<ShaderProgram> getShader() const { return _basicShader; } // gonna be a vector of the shaders.
	static void APIENTRY openglCallbackFunction(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam
	) {
		(void)source; (void)type; (void)id;
		(void)severity; (void)length; (void)userParam;
		fprintf(stderr, "%s\n", message);
		if (severity == GL_DEBUG_SEVERITY_HIGH) {
			fprintf(stderr, "Aborting...\n");
			abort();
		}
	}
private:
	int _width;
	int _height;
	SDL_Window* _window;
	SDL_GLContext _context;
	std::shared_ptr<ShaderProgram> _basicShader;
	std::shared_ptr<ShaderProgram> _toScreenShader;
	std::shared_ptr<ShaderProgram> _grassShader;
	std::shared_ptr<FrameBuffer> _imageBuffer;
	std::shared_ptr<World> _world;
	std::shared_ptr<PrimitiveMeshes> _finalScreen;
	
	Engine() {}
	virtual ~Engine();
	void _init();
	void _initSDL();
	void _initGL();
	void _initVariables();
};