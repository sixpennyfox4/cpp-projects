#include <iostream>
#include "raylib.h"

int main() {
	InitWindow(800, 600, "3D Test");
	SetTargetFPS(60);

	Vector3 cubePos{ 0.0f, 0.0f, 0.0f };

	Camera3D cam{ 0 };
	cam.position = { 0.0f, 10.0f, 10.0f };
	cam.up = { 0.0f, 1.0f, 0.0f };
	cam.fovy = 45;
	cam.projection = CAMERA_PERSPECTIVE;

	while (!WindowShouldClose()) {

		/* KEY INPUTS */
		if (IsKeyDown(KEY_W)) cubePos.z -= 0.4f;
		if (IsKeyDown(KEY_S)) cubePos.z += 0.4f;

		if (IsKeyDown(KEY_A)) cubePos.x -= 0.4f;
		if (IsKeyDown(KEY_D)) cubePos.x += 0.4f;

		if (IsKeyPressed(KEY_Q)) break;

		cam.target = cubePos;
		cam.position.z -= (int)GetMouseWheelMove() * 6;

		if (cam.position.z > 100) {
			cam.position.z = 100;
		}

		if (cam.position.z < 10) {
			cam.position.z = 10;
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);

		BeginMode3D(cam);

		DrawCube(cubePos, 2.0f, 2.0f, 2.0f, RED);
		DrawCubeWires(cubePos, 2.0f, 2.0f, 2.0f, BLACK);
		DrawGrid(10, 2.0f);

		EndMode3D();

		DrawFPS(10, 10);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
