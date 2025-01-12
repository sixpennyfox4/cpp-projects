#include <iostream>
#include <random>

int randomNum(int max) {
	std::mt19937 mt{ std::random_device{}() };

	return std::uniform_int_distribution{ 0, max }(mt);
}

int checkWin(const int grid[3][3]) {
	for (int i{ 0 }; i < 3; ++i) {
		if (grid[i][0] != 0 && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) {
			return grid[i][0];
		}
		if (grid[0][i] != 0 && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]) {
			return grid[0][i];
		}
	}

	if (grid[0][0] != 0 && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) {
		return grid[0][0];
	}
	if (grid[0][2] != 0 && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) {
		return grid[0][2];
	}

	return 0;
}

bool playAgain() {
	while (true) {
		std::cout << "Play again(y/n)?: ";

		char option{};
		std::cin >> option;

		switch (option) {
		case 'y': system("cls");
			return true;

		case 'n': return false;

		default: continue;
		}
	}
}

void mainGame() {
	// 0 = nothing(!) | 1 = O | 2 = X
	int grid[3][3]{
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
	};

	int tC{}; // player choice
	int cTC{}; // computer choice
	while (true) {
		std::cout << "X or O: ";

		char tTC{};
		std::cin >> tTC;

		switch (tTC) {
		case 'X':
			tC = 2;
			cTC = 1;

			break;

		case 'O':
			tC = 1;
			cTC = 2;

			break;

		default:
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		system("cls");
		break;
	}

	int turn{ 0 }; // 0 = player | 1 = computer
	while (true) {
		for (const auto& l : grid) {
			std::cout << " - - - - - - -\n";
			std::cout << " |";

			for (const auto& c : l) {
				if (c == 1) {
					std::cout << " O";
				}
				else if (c == 2) {
					std::cout << " X";
				}
				else {
					std::cout << " !";
				}

				std::cout << " |";
			}

			std::cout << '\n';
		}

		std::cout << " - - - - - - -\n";

		int winner{ checkWin(grid) };
		if (winner != 0) {
			std::cout << (winner == tC ? "You win!\n" : "Computer Wins!\n");
			break;
		}

		if (turn == 0) {
			while (true) {
				std::cout << "Pick from 1-9: ";

				int choice{};
				std::cin >> choice;

				if (choice < 1 || choice > 9) {
					std::cout << "Invalid Choice!\n";
					continue;
				}
				else {
					if (choice <= 3) {
						if (grid[0][choice - 1] == 0) {
							grid[0][choice - 1] = tC;
						}
						else {
							std::cout << "Already picked!\n";
							continue;
						}
					}
					else if (choice >= 4 && choice <= 6) {
						if (grid[1][choice - 4] == 0) {
							grid[1][choice - 4] = tC;
						}
						else {
							std::cout << "Already picked!\n";
							continue;
						}
					}
					else if (choice >= 7) {
						if (grid[2][choice - 7] == 0) {
							grid[2][choice - 7] = tC;
						}
						else {
							std::cout << "Already picked!\n";
							continue;
						}
					}

					turn = 1;
					break;
				}
			}
		}
		else if (turn == 1) {
			int gL{ randomNum(2) };
			int gLN{ randomNum(2) };

			if (grid[gL][gLN] == 0) {
				grid[gL][gLN] = cTC;
				turn = 0;
			}
		}

		system("cls");
	}
}

int main() {
	
	do {
		mainGame();
	} while (playAgain());

	return 0;
}
