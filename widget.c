#include <SDL3/SDL.h>

#include <stdbool.h>
#include <stdio.h>

#include "uis/widget.h"

#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_INCLUDE_COMMAND_USERDATA
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT

#include "nuklear.h"
#include "nuklear_sdl3_renderer.h"

bool hello_world(struct nk_context *ctx) {
  if (nk_begin(ctx, "Template", nk_rect(50, 50, 220, 120),
               NK_WINDOW_BORDER | NK_WINDOW_TITLE | NK_WINDOW_CLOSABLE |
                   NK_WINDOW_MOVABLE)) {
    nk_layout_row_dynamic(ctx, 30, 1);
    nk_label(ctx, "Hello, Nuklear + SDL3!", NK_TEXT_CENTERED);
  }
  nk_end(ctx);

  return !nk_window_is_hidden(ctx, "Template");
}

bool example(struct nk_context *ctx) {
  enum { EASY, HARD };
  static int option = EASY;
  static float value = 0.6f;
  static int i = 20;

  if (nk_begin(ctx, "example", nk_rect(400, 50, 220, 220),
               NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_CLOSABLE)) {
    nk_layout_row_static(ctx, 30, 80, 1);
    if (nk_button_label(ctx, "button"))
      printf("button clicked\n");

    nk_layout_row_dynamic(ctx, 30, 2);
    if (nk_option_label(ctx, "easy", option == EASY))
      option = EASY;
    if (nk_option_label(ctx, "hard", option == HARD))
      option = HARD;

    nk_layout_row_begin(ctx, NK_STATIC, 30, 2);
    {
      nk_layout_row_push(ctx, 50);
      nk_label(ctx, "volume", NK_TEXT_LEFT);
      nk_layout_row_push(ctx, 110);
      nk_slider_float(ctx, 0, &value, 1.0f, 0.1f);
    }
    nk_layout_row_end(ctx);
  }
  nk_end(ctx);

  return !nk_window_is_hidden(ctx, "example");
}
