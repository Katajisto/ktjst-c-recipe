{{if eq .Variables.STARTER_SRC "raylib basic usage"}}
{{if .Variables.INCLUDE_LIBS | has "microui"}}
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>

#include "microui.h"
#include "murl.h"

int main(void) {
  InitWindow(800, 600, "microui + raylib");
  SetTargetFPS(60);

  mu_Context *ctx = malloc(sizeof(mu_Context));
  mu_init(ctx);
  murl_setup_font(ctx);

  while (!WindowShouldClose()) {
    murl_handle_input(ctx);

    mu_begin(ctx);

    if (mu_begin_window(ctx, "Hello", mu_rect(20, 20, 200, 150))) {
      mu_label(ctx, "Hello, raylib");

      if (mu_button(ctx, "The button")) {
        mu_open_popup(ctx, "popup");
      }

      if (mu_begin_popup(ctx, "popup")) {
        mu_label(ctx, "This is a popup");
        mu_end_popup(ctx);
      }

      mu_end_window(ctx);
    }

    mu_end(ctx);

    BeginDrawing();
    ClearBackground(BLACK);
    murl_render(ctx);
    EndDrawing();
  }

  free(ctx);
  CloseWindow();
  return 0;
}
{{ else }}
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
{{ end }}
{{if eq .Variables.STARTER_SRC "hello world"}}
#include "stdio.h"
int main() {
    printf("Hello wlrd\n");
    return 0;
}
{{ end }}
