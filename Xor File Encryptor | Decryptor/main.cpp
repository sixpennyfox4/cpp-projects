#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {
	std::string fPath;
	int key;

	std::cout << "File path: ";
	std::getline(std::cin >> std::ws, fPath);

	std::cout << "Key: ";
	std::cin >> key;

	std::ifstream iF(fPath);
	std::vector<char> contents((std::istreambuf_iterator<char>(iF)), std::istreambuf_iterator<char>());
	iF.close();

	for (char& c : contents)
		c ^= key;

	std::ofstream oF(fPath);
	oF.write(contents.data(), contents.size());
	oF.close();

	return 0;
}
