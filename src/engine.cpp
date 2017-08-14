#include "engine.hpp"
#include "components/modelcomponent.hpp"

Engine::~Engine() {
	
}

int Engine::run() {
	_init();
	SDL_Event event;
	bool quit = false;
	uint32_t lastTime = SDL_GetTicks();
	float time = 0.f;

	while (!quit) {
		SDL_GL_SwapWindow(_window);
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				quit = true;
		}
		uint32_t curTime = SDL_GetTicks();
		float delta = (curTime - lastTime) / 1000.0f;
		lastTime = curTime;

		if (time >= M_PI * 2)
			time = 0.f;

		// Rendering and updating etc... Updating renders, which is pretty stupid.
		_basicShader->bind();
		_imageBuffer->bind();
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_world->update(delta);
		_world->render();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_toScreenShader->bind();
		_imageBuffer->bindTexture(0);
		_finalScreen->render();


		time += 1 * delta;
	}

	return 0;
}

void Engine::_init() {
	_width = 800;
	_height = 800;
	_initSDL();
	_initGL();
	_initVariables();
}

void Engine::_initSDL() {
	if (SDL_INIT_EVERYTHING < 0)
		printf("Could not initialize SDL\n");
	else {
		if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
			printf("Failed to initialize PNG usage for SDL! IMG Error: %s\n", IMG_GetError());

		_window = SDL_CreateWindow("Summer Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (_window == nullptr)
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	}
}

void Engine::_initGL() {
	SDL_GL_LoadLibrary(NULL);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

	_context = SDL_GL_CreateContext(_window);
	if (_context == nullptr)
		printf("Failed to create context! SDL Error: %s\n", SDL_GetError());

	gladLoadGLLoader(SDL_GL_GetProcAddress);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(openglCallbackFunction, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true);
	
	SDL_GL_SetSwapInterval(true);
	glDisable(GL_DEPTH_TEST);
	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);*/
	glEnable(GL_PROGRAM_POINT_SIZE);
	
	glViewport(0, 0, _width, _height);
}

void Engine::_initVariables() {
	_basicShader = std::make_shared<ShaderProgram>("assets/shaders/firstPass.vert", "assets/shaders/firstPass.frag");
	_basicShader->bind().addUniform("proj")
		.addUniform("view")
		.addUniform("model")
		.addUniform("lightPos")
		.addUniform("texOffset1")
		.addUniform("texOffset2")
		.addUniform("texCoordInfo")
		.addUniform("particleColor");
	
	_toScreenShader = std::make_shared<ShaderProgram>("assets/shaders/grass.vert","assets/shaders/grass.geom", "assets/shaders/grass.frag");

	_toScreenShader = std::make_shared<ShaderProgram>("assets/shaders/screen.vert", "assets/shaders/screen.frag");

	_imageBuffer = std::make_shared<FrameBuffer>();
	_imageBuffer->bind().addTexture(0, GL_TEXTURE_2D, GL_RGB, _width, _height, false, GL_UNSIGNED_BYTE);

	_world = std::make_shared<World>();
	_finalScreen = std::make_shared<PrimitiveMeshes>(PrimitiveMeshes::QUAD);

}