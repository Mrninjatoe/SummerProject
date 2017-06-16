#include <cstdlib>
#include <ctime>
#include "engine.hpp"

int main(int argc, char** argv) {
	srand(time(NULL));

	return Engine::getInstance().run();
}