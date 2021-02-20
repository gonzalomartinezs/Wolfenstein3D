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
		std::cerr << e.what() << std::endl;
	} catch (...) {
		std::cerr << "Unknown error." << std::endl;
	}

	return 0;
}
