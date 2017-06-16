#pragma once
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "lib/glad.h"
#include <SDL2/SDL_image.h>
#include <iostream>

class Engine {
public:
	static Engine& getInstance() {
		static Engine instance;

		return instance;
	}
	Engine(Engine const&) = delete;
	void operator=(Engine const&) = delete;
	int run();
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

	Engine() {}
	virtual ~Engine();
	void _init();
	void _initSDL();
	void _initGL();
};