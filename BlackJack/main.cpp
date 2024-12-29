#include <iostream>
#include <random>
#include <thread>
#include <chrono>

int getRandomNumber(int max) {
	std::mt19937 mt{ std::random_device{}() };

	return std::uniform_int_distribution{ 1, max }(mt);
}

struct BlackJack {
	int dealerPoints;
	int playerPoints;
	int nextDealerPoints;
};

bool playAgain() {
	while (true) {
		std::cout << "Play again(y/n): ";

		char option{};
		std::cin >> option;

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (option == 'y' || option == 'n') {
			return option == 'y';
		}

		std::cout << "Invalid option!\n";
	}
}

void mainGame() {
	BlackJack bj{ getRandomNumber(10), getRandomNumber(10) + getRandomNumber(10) };
	bj.nextDealerPoints = getRandomNumber(10);

	bool ask{ true };
	while (true) {
		std::cout << "Dealer: " << bj.dealerPoints << '\n';
		std::cout << "Player: " << bj.playerPoints << '\n';

		char hs{};
		if (ask) {
			while (true) {
				std::cout << "Hit(h) or Stand(s): ";

				std::cin >> hs;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				if (hs == 'h' || hs == 's') {
					break;
				}

				std::cout << "Invalid option!\n";
			}

			if (hs == 'h') {
				bj.playerPoints += getRandomNumber(10);

				if (bj.playerPoints > 21) {
					std::cout << "You loose!\n";
					break;
				}
			}
		}

		if (hs == 's' || !ask) {
			ask = false;
			while (true) {
				if (bj.dealerPoints > bj.playerPoints) {
					std::cout << "Dealer wins!\n";
					return;
				}

				if ((bj.dealerPoints + bj.nextDealerPoints) > 21) {
					std::cout << "You win!\n";
					return;
				}
				else {
					bj.dealerPoints += bj.nextDealerPoints;
					bj.nextDealerPoints = getRandomNumber(10);

					std::this_thread::sleep_for(std::chrono::seconds(1));
					break;
				}
			}
		}

		std::cout << '\n';
	}
}

int main() {

	std::cout << "Welcome to cpp blackjack!\n\n";

	do {
		mainGame();
	} while (playAgain());

	return 0;
}
