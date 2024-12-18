{{if eq .Variables.STARTER_SRC "raylib basic usage"}}
#include "raylib.h"

int main(void)
{
    InitWindow(500, 500, "ktjst!");
    SetTargetFPS(60);               
    while (!WindowShouldClose())    
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("KTJST!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();        
    return 0;
}
{{ end }}
{{if eq .Variables.STARTER_SRC "hello world"}}
#include "stdio.h"
int main() {
    printf("Hello wlrd\n");
    return 0;
}
{{ end }}
