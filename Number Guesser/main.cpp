#include <iostream>
#include <random>

int getRandomNumber() {
	std::mt19937 mt{ std::random_device{}() };

	return std::uniform_int_distribution{ 0, 6 }(mt);
}

bool playAgain() {
	while (true) {
		std::cout << "Play again(y/n)?: ";

		char option{};
		std::cin >> option;

		switch (option) {
		case 'y': return true;
		case 'n': return false;
		default: continue;
		}
	}
}

void mainGame(int tries) {
	int number{ getRandomNumber() };

	for (int i{ 1 }; i <= tries; i++) {
		std::cout << "Guess #" << i << ": ";

		int guess{};
		std::cin >> guess;

		if (guess == number) {
			std::cout << "You guessed the correct number!\n";
			
			return;
		}
		else if (guess < number) {
			std::cout << "Low\n";
			continue;
		}
		else if (guess > number) {
			std::cout << "High\n";
			continue;
		}
	}

	std::cout << "You lost. The correct number was " << number << ".\n";
}

int main() {
	std::cout << "Welcome to cpp number guesser!\n";
	std::cout << "You basically need to guess a number between 0 and 6 with only 3 tries.\n";

	do {
		mainGame(3);
	} while (playAgain());

	return 0;
}
