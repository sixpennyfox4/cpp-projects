#include <iostream>
#include <vector>
#include <random>

#include "raylib.h"

int getRandomNumber(int min, int max) {
	std::mt19937 mt{ std::random_device{}() };

	return std::uniform_int_distribution<int>{ min, max }(mt);
}

int main() {
	constexpr int count{ 100 };
	constexpr int width{ 500 };
	constexpr int height{ 500 };
	bool lost{ false };
	int outs{ 0 };

	std::vector<Rectangle> objects{};
	for (int i{ 0 }; i < count; i++) {
		objects.push_back(Rectangle{(float)getRandomNumber(0, width-25), (float)i*-50, 50, 50});
	}

	InitWindow(width, height, "Dodge The Rectangles");
	SetTargetFPS(60);

	Rectangle player{ (width / 2) - 25, height - 50, 50, 50 };
	while (!WindowShouldClose() && !lost) {
		BeginDrawing();
		ClearBackground(RAYWHITE);

		if (IsKeyDown(KEY_A)) player.x -= 10;
		if (IsKeyDown(KEY_D)) player.x += 10;

		if (player.x > width - player.width) player.x = width - player.width;
		if (player.x < 0 ) player.x = 0;

		DrawRectangleRec(player, BLUE);
		for (Rectangle& obj : objects) {
			DrawRectangleRec(obj, BROWN);
			obj.y += 5;

			if (CheckCollisionRecs(player, obj)) {
				lost = true;
			}

			if (obj.y == height + obj.height) {
				outs++;
			}

			if (outs == objects.size()) {
				DrawText("YOU WIN!", (width / 2) - 44, (height / 2) - 22, 22, BLACK);
			}
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
