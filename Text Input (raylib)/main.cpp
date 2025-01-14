#include <iostream>
#include <string>

#include "raylib.h"

bool isAnyKeyPressed()
{
	bool keyPressed = false;
	int key = GetKeyPressed();

	if ((key >= 32) && (key <= 126)) keyPressed = true;

	return keyPressed;
}

int main() {
	int height{ 500 };
	int width{ 500 };
	InitWindow(width, height, "Input");

	std::string enteredText{};

	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		Vector2 mousePosition{ GetMousePosition() };

		BeginDrawing();
		ClearBackground(RAYWHITE);

		Rectangle InputBox{ static_cast<float>((width / 2) - 30), static_cast<float>((height / 2) - 10), 100, 20};
		DrawRectangleRec(InputBox, LIGHTGRAY);

		DrawText(enteredText.c_str(), static_cast<int>(InputBox.x), static_cast<int>(InputBox.y), 20, BLACK);
		if (CheckCollisionRecs(InputBox, Rectangle{ mousePosition.x, mousePosition.y, 1, 1 })) {
			SetMouseCursor(MOUSE_CURSOR_IBEAM);

			if (enteredText.size() < 8) {
				if (isAnyKeyPressed()) {
					enteredText.push_back(GetCharPressed());
				}
			}

			if (IsKeyPressed(KEY_BACKSPACE) && !enteredText.empty()) {
				enteredText.pop_back();
			}
		}
		else {
			SetMouseCursor(MOUSE_CURSOR_ARROW);
		}

		EndDrawing();
	}

	return 0;
}
