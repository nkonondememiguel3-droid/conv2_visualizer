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

void image_view(struct nk_context *ctx, float x, float y, float width, float height) {
  if (!nk_begin(ctx, "viewer", nk_rect(x, y, width, height),
                NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR)) {
    nk_end(ctx);
    return;
  }

  /* nk_layout_row_dynamic(app->nk, 28, 1); */
  /* nk_labelf(app->nk, NK_TEXT_CENTERED, "Image %u / %u     Label: %u", */
  /*           app->current_index + 1, total, app->current_label); */

  /* nk_layout_row_dynamic(app->nk, 32, 2); */
  /* if (nk_button_label(app->nk, "<  Prev")) */
  /*   navigate_viewer(app, -1); */
  /* if (nk_button_label(app->nk, "Next  >")) */
  /*   navigate_viewer(app, +1); */

  /* float ch = h - 100.0f; */
  /* if (ch < 80.0f) */
  /*   ch = 80.0f; */

  /* nk_layout_row_begin(app->nk, NK_DYNAMIC, ch, 2); */

  /* struct nk_style_item orig = app->nk->style.window.fixed_background; */
  /* app->nk->style.window.fixed_background = nk_style_item_color(nk_rgb(0, 0, 0)); */

  /* nk_layout_row_push(app->nk, 0.42f); */
  /* if (nk_group_begin(app->nk, "img_g", NK_WINDOW_BORDER | NK_WINDOW_TITLE)) { */
  /*   nk_layout_row_dynamic(app->nk, ch - 38.0f, 1); */
  /*   nk_image(app->nk, app->nk_mnist_image); */
  /*   nk_group_end(app->nk); */
  /* } */
  /* app->nk->style.window.fixed_background = orig; */

  /* nk_layout_row_push(app->nk, 0.58f); */
  /* if (nk_group_begin(app->nk, "pix_g", NK_WINDOW_BORDER | NK_WINDOW_TITLE)) { */
  /*   nk_style_set_font(app->nk, &app->mono_font->handle); */
  /*   uint32_t rows = app->train_ds->rows; */
  /*   uint32_t cols = app->train_ds->cols; */
  /*   const _tensor_t *img = app->current_image; */

  /*   for (uint32_t r = 0; r < rows; r++) { */
  /*     nk_layout_row_static(app->nk, 16, 18, (int)cols); */
  /*     for (uint32_t c = 0; c < cols; c++) { */
  /*       uint8_t v = (uint8_t)(img->data[r * cols + c] * 255.0f + 0.5f); */
  /*       char buf[4]; */
  /*       SDL_snprintf(buf, sizeof(buf), "%u", v); */
  /*       nk_label(app->nk, buf, NK_TEXT_CENTERED); */
  /*     } */
  /*   } */
  /*   nk_style_set_font(app->nk, &app->ui_font->handle); */
  /*   nk_group_end(app->nk); */
  /* } */
  /* nk_layout_row_end(app->nk); */
  nk_end(ctx);
}
