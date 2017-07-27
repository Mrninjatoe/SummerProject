#include <cstdlib>
#include <ctime>
#include "engine.hpp"
#include <string>

int main(int argc, char** argv) {
	srand(time(NULL));
	return Engine::getInstance().run();
}