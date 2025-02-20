#include "../raylib.h"
#include "../headers/game.h"

const GameState DefaultState = {
    .state = MENU,
    .playerHeight = 150,
    .playerWidth = 50,
    .playerPos = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f},
    .playerSpeed = 500.0f,
};

int main() {
    // Initialize the window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Forage Game");
    SetTargetFPS(120);

    // Initialize game state
    GameState gameState = DefaultState;

    // Grid setup
    const int tileSize = 32;
    const int gridWidth = SCREEN_WIDTH / tileSize;
    const int gridHeight = SCREEN_HEIGHT / tileSize;

    int grid[gridHeight][gridWidth] = { 0 };

    // Place some objects in the grid (will randomize later)
    grid[5][5] = 1;
    grid[10][15] = 2;

    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGREEN);

        // Handle game state
        switch (gameState.state) {
        case MENU: {
            DrawText("PRESS ENTER", SCREEN_WIDTH / 2 - MeasureText("PRESS ENTER", 20) / 2, 20, 20, WHITE);
            if (IsKeyPressed(KEY_ENTER)) {
                gameState = DefaultState;
                gameState.state = GAME;
            }
            break;
        }
        case GAME: {
            // Player Movement
            if (IsKeyDown(KEY_W)) {
                gameState.playerPos.y -= gameState.playerSpeed * GetFrameTime();
            }
            if (IsKeyDown(KEY_S)) {
                gameState.playerPos.y += gameState.playerSpeed * GetFrameTime();
            }
            if (IsKeyDown(KEY_A)) {
                gameState.playerPos.x -= gameState.playerSpeed * GetFrameTime();
            }
            if (IsKeyDown(KEY_D)) {
                gameState.playerPos.x += gameState.playerSpeed * GetFrameTime();
            }

            // Draw player
            DrawRectangle(gameState.playerPos.x, gameState.playerPos.y, gameState.playerWidth, gameState.playerHeight, WHITE);

            // Draw grid and objects
            for (int y = 0; y < gridHeight; y++) {
                for (int x = 0; x < gridWidth; x++) {
                    // Define player hitbox
                    Rectangle playerRect = {
                        gameState.playerPos.x,
                        gameState.playerPos.y,
                        gameState.playerWidth,
                        gameState.playerHeight
                    };

                    // Define pickup hitbox
                    Rectangle cellRect = {
                        x * tileSize,
                        y * tileSize,
                        tileSize,
                        tileSize
                    };

                    // Collision check
                    if (CheckCollisionRecs(playerRect, cellRect)) {
                        grid[y][x] = 0;
                    }
                    if (grid[y][x] == 1) {
                        DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, RED);
                    }
                    if (grid[y][x] == 2) {
                        DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, BLUE);
                    }
                }
            }
            break;
        }
        }

        EndDrawing();
    }

    // Cleanup
    CloseWindow();
    return 0;
}
