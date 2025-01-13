#include <iostream>
#include <vector>
#include <string>
#include <random>

bool playAgain() {
	while (true) {
		std::cout << "Play again(y/n)?: ";

		char c{};
		std::cin >> c;

		switch (c) {
		case 'y': return true;
		case 'n': return false;
		default:
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
	}
}

void mainGame(int tries, const std::vector<std::string>& words) {
	std::mt19937 mt{ std::random_device{}() };
	int rN{ std::uniform_int_distribution<int>{ 0, static_cast<int>(words.size() - 1) }(mt)};
	std::string chosenWord{ words[static_cast<std::size_t>(rN)] };

	std::vector<bool> cCheck{};
	for (int i{ 0 }; i < chosenWord.size(); i++) {
		cCheck.push_back(false);
	}

	int guessedChars{};
	while (true) {
		system("cls");
		if (tries == 0) {
			std::cout << "You lost!\n";
			break;
		}

		if (guessedChars == chosenWord.size()) {
			std::cout << "You win!\n";
			break;
		}

		bool found{ false };
		for (int i{ 0 }; i < chosenWord.size(); i++) {
			if (cCheck[static_cast<std::size_t>(i)] == false) {
				std::cout << '*';
			}
			else {
				std::cout << chosenWord[i];
			}
		}

		std::cout << " | ";
		for (int i{ 1 }; i <= tries; i++) {
			std::cout << "+";
		}

		std::cout << "\n> ";
		char enteredC{};
		std::cin >> enteredC;

		for (int i{ 0 }; i < chosenWord.size(); i++) {
			if (chosenWord[i] == enteredC) {
				guessedChars++;

				cCheck[static_cast<std::size_t>(i)] = true;
				found = true;
			}
		}

		if (!found) {
			tries--;
		}
	}
}

int main() {
	constexpr int tries{ 5 };
	const std::vector<std::string> wList{ "gun", "star", "diddy" };

	do {
		mainGame(tries, wList);
	} while (playAgain());

	return 0;
}
