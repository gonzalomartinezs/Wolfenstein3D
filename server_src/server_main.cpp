#include <iostream>

//Test
#include <thread>

#define EMPTY ' '
#define END_CHAR 'q'

//Test

#include "GameManager.h"

#define MIN_ARGS 2

#define POS_CONFIG 1

int main(int argc, char const *argv[]) {
	if (argc < MIN_ARGS) {
		std::cout << "./server config.[yaml/yml]" << std::endl;
		return 0;
	}

	try {
		GameManager manager(argv[POS_CONFIG]);
		std::thread main_thread(&GameManager::operator(), &manager);

		char c = EMPTY;

		while (c != END_CHAR) {
			std::cin >> c;
		}

		manager.stop();
		main_thread.join();
	} catch (const std::exception& e) {
		printf("%s", e.what());
	} catch (...) {
		printf("Unkown error.\n");
	}

	return 0;
}
