#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <vector>

#include "raylib.h"

struct Tube {
	Rectangle top;
	Rectangle bottom;
};

int getRandomNumber(int min, int max) {
	std::mt19937 mt{ std::random_device{}() };

	if (min > max) {
		std::swap(max, min);
	}

	return std::uniform_int_distribution<int>{ min, max }(mt);
}

int main() {
	constexpr int width{ 500 };
	constexpr int height{ 500 };

	constexpr int tubeCount{ 100 };
	constexpr float tubeWidth{ 50.0f };
	constexpr float gapSize{ 150.0f };
	const float tubeSpacing{ static_cast<float>(width) - 320.0f };

	InitWindow(width, height, "Flappy Circle");
	SetTargetFPS(60);

	std::vector<Tube> tubes(tubeCount);
	for (int i{ 0 }; i < tubeCount; i++) {
		// thank you mr. chatgpt
		float xPos{ width + i * tubeSpacing };
		float gapY{ static_cast<float>(getRandomNumber(100, height - 100 - static_cast<int>(gapSize))) };

		Tube t{
			{ xPos, 0.0f, tubeWidth, gapY },
			{ xPos, gapY + gapSize, tubeWidth, static_cast<float>(height) - (gapY + gapSize) }
		};

		tubes.push_back(t);
	}

	bool gameOver{ false };
	Vector2 circlePos{ static_cast<float>(width / 2), static_cast<float>(height / 2) };
	while (!WindowShouldClose() && !gameOver) {
		BeginDrawing();
		ClearBackground(SKYBLUE);

		for (Tube& t : tubes) {
			t.top.x -= 5;
			t.bottom.x -= 5;

			if (CheckCollisionRecs(Rectangle{ circlePos.x, circlePos.y, 20, 20 }, t.bottom) || CheckCollisionRecs(Rectangle{ circlePos.x, circlePos.y, 24, 24 }, t.top)) {
				gameOver = true;
			}

			DrawRectangleRec(t.top, GREEN);
			DrawRectangleRec(t.bottom, GREEN);
		}

		circlePos.y += 5;
		if (IsKeyPressed(KEY_SPACE)) {
			circlePos.y -= 30;
		}

		if (circlePos.y < 0) {
			circlePos.y = 0;
		}

		if (circlePos.y > height) {
			circlePos.y = static_cast<float>(height);
		}

		DrawCircleV(circlePos, 20.0f, YELLOW);

		std::this_thread::sleep_for(std::chrono::milliseconds(80));
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
