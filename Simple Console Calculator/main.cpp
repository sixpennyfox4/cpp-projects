#include <iostream>

int main() {
	std::cout << "Welcome to simple cpp console calculator!\n";
	std::cout << "Number #1: ";

	double num1{};
	double num2{};
	std::cin >> num1;

	std::cout << "Number #2: ";
	std::cin >> num2;

	char opr{};
	std::cout << "Operator(-, +, *, /): ";;
	std::cin >> opr;

	switch (opr) {
	case '-':
		std::cout << "\nResult: " << num1 - num2;
		break;
	case '+':
		std::cout << "\nResult: " << num1 + num2;
		break;
	case '*':
		std::cout << "\nResult: " << num1 * num2;
		break;
	case '/':
		std::cout << "\nResult: " << num1 / num2;
		break;
	default: std::cout << "\nOperator not found!";
	}

	return 0;
}
