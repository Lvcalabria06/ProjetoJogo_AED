#include "menu.h"
#include "raylib.h"

int exibirMenu() {
    InitWindow(800, 600, "Blackjack - Menu");
    SetTargetFPS(60);

    int opcao = 0; // 1 para iniciar, 2 para sair

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGREEN);

        DrawText("BLACKJACK", 280, 100, 40, RAYWHITE);

        // Botão: Iniciar Jogo
        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){300, 250, 200, 50})) {
            DrawRectangle(300, 250, 200, 50, LIGHTGRAY);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                opcao = 1;
                break;
            }
        } else {
            DrawRectangle(300, 250, 200, 50, GRAY);
        }
        DrawText("Iniciar Jogo", 330, 265, 20, BLACK);

        // Botão: Sair
        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){300, 330, 200, 50})) {
            DrawRectangle(300, 330, 200, 50, LIGHTGRAY);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                opcao = 2;
                break;
            }
        } else {
            DrawRectangle(300, 330, 200, 50, GRAY);
        }
        DrawText("Sair", 370, 345, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return opcao;
}
