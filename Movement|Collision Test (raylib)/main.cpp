#include <iostream>
#include <vector>
#include <random>

#include "raylib.h"

struct Player {
	Vector2 position{};
	float radius{};
	int speed{};
};

float getRandomNumber(int min, int max) {
	std::mt19937 mt{ std::random_device{}() };

	return std::uniform_int_distribution{ min, max }(mt);
}

void randomCircles(const std::vector<Vector2>& circlesA, int count) {
	for (int i{ 1 }; i <= count; ++i) {
		circlesA.push_back({ getRandomNumber(10, 480), getRandomNumber(10, 480) });
	}
}

int main() {
	InitWindow(500, 500, "Movement | Collision Test");
	SetTargetFPS(60);

	std::vector<Vector2> circlesArr{};
	randomCircles(circlesArr, 6);

	Player plr{ {250, 250}, 20.0f, 200 };

	bool lost{ false };
	while (!WindowShouldClose()) {

		float dt{ GetFrameTime() };
		Vector2 mousePos{ GetMousePosition() };

		if (IsKeyDown(KEY_W)) plr.position.y -= plr.speed * dt;
		if (IsKeyDown(KEY_S)) plr.position.y += plr.speed * dt;
		if (IsKeyDown(KEY_A)) plr.position.x -= plr.speed * dt;
		if (IsKeyDown(KEY_D)) plr.position.x += plr.speed * dt;

		if (IsKeyPressed(KEY_P)) {
			if (!lost) {
				circlesArr.clear();
				randomCircles(circlesArr, 6);
			}
		}

		if (IsKeyPressed(KEY_R)) {
			if (!lost) {
				circlesArr.clear();
				randomCircles(circlesArr, 6);
				plr.position = { 250, 250 };
			}
		}

		if (plr.position.x - plr.radius < 0) plr.position.x = plr.radius;
		if (plr.position.x + plr.radius > 500) plr.position.x = 500 - plr.radius;
		if (plr.position.y - plr.radius < 0) plr.position.y = plr.radius;
		if (plr.position.y + plr.radius > 500) plr.position.y = 500 - plr.radius;

		BeginDrawing();
		ClearBackground(RAYWHITE);

		if (lost) {
			DrawText("Lost!", 226, 200, 20, BLACK);

			Rectangle playAgain{ 220, 220, 60, 30 };
			DrawRectangleRec(playAgain, BLUE);
			DrawText("Play Again!", 224, 228, 10, BLACK);

			if (CheckCollisionRecs(Rectangle{ mousePos.x, mousePos.y, 1, 1 }, playAgain) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				circlesArr.clear();
				randomCircles(circlesArr, 6);

				plr.position = { 250, 250 };
				lost = false;
			}
		}
		else {

			for (const auto& circle : circlesArr) {
				DrawCircleV(circle, 20.0f, RED);

				if (CheckCollisionCircles(circle, 20.0f, plr.position, plr.radius)) {
					lost = true;
				}
			}

			DrawCircleV(plr.position, plr.radius, BLUE);
			DrawText("Use WASD To Move.", 10, 10, 18, BLACK);
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
