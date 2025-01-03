#include <iostream>
#include <random>
#include <chrono>
#include <thread>

struct RR {
	int rounds{};
	int blanks{};
	int lives{}; // ye idk better name
	int turn{}; // 0 = player | 1 = dealer
};

int getRandomNumber(int min, int max) {
	std::mt19937 mt{ std::random_device{}() };

	return std::uniform_int_distribution{ min, max }(mt);
}

bool playAgain() {
	while (true) {
		char choice{};
		std::cout << "Play again(y/n): ";

		std::cin >> choice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (choice) {
		case 'y': return true;
		case 'n': return false;
		default: continue;
		}
	}
}

void mainGame() {
	RR game{ 6, 5, 1, 0 };

	while (true) {
		std::cout << "\nRounds: " << game.rounds << '\n';
		std::cout << "Blanks left: " << game.blanks << '\n';
		std::cout << "Lives left: " << game.lives << "\n\n";

		if (game.turn == 0) {
			std::cout << "Turn: Player\n";
			std::cout << "Shoot yourself(m)/Shoot dealer(d): ";

			char option{};
			std::cin >> option;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			if (option == 'm') {
				int chosenRound{ getRandomNumber(0, game.rounds) };

				if (chosenRound <= game.lives) {
					std::cout << "It was a live!\n";
					std::cout << "You lost!\n";

					return;
				}
				else {
					game.lives++;
					game.blanks--;
					game.turn = 1;

					std::cout << "It was a blank!\n";
					std::this_thread::sleep_for(std::chrono::seconds(1));
				}
			}
			else if (option == 'd') {
				int chosenRound{ getRandomNumber(0, game.rounds) };

				if (chosenRound <= game.lives) {
					std::cout << "It was a live!\n";
					std::cout << "You win!\n";

					return;
				}
				else {
					game.lives++;
					game.blanks--;
					game.turn = 1;

					std::cout << "It was a blank!\n";
					std::this_thread::sleep_for(std::chrono::seconds(1));
				}
			}
			else {
				continue;
			}
		}
		else if (game.turn == 1) {
			int choice{ getRandomNumber(0, 1) }; // 0 = shoot player | 1 = shoot dealer
			int chosenRound{ getRandomNumber(0, game.rounds) };

			std::cout << "Turn: Dealer\n";
			if (choice == 0) {
				std::cout << "Dealer choose to shoot player!\n\n";

				std::this_thread::sleep_for(std::chrono::seconds(1));
				if (chosenRound <= game.lives) {
					std::cout << "It was a live!\n";
					std::cout << "You lost!\n";

					return;
				}
				else {
					std::cout << "It was a blank!\n";
					game.lives++;
					game.blanks--;
					game.turn = 0;
					
					std::this_thread::sleep_for(std::chrono::seconds(1));
					continue;
				}
			}
			else if (choice == 1) {
				std::cout << "Dealer choose to shoot himself!\n\n";

				std::this_thread::sleep_for(std::chrono::seconds(1));
				if (chosenRound <= game.lives) {
					std::cout << "It was a live!\n";
					std::cout << "You win!\n";

					return;
				}
				else {
					std::cout << "It was a blank!\n";
					game.lives++;
					game.blanks--;
					game.turn = 0;

					std::this_thread::sleep_for(std::chrono::seconds(1));
					continue;
				}
			}
		}
	}
}

int main() {
	std::cout << "Welcome to cpp roullete!\n";

	do {
		mainGame();
	} while (playAgain());

	return 0;
}
