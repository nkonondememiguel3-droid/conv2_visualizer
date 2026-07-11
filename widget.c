#include <SDL3/SDL.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "uis/widget.h"

#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_INCLUDE_COMMAND_USERDATA
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT

#include "nuklear.h"
#include "nuklear_sdl3_renderer.h"

bool hello_world(struct nk_context *ctx)
{
  if (nk_begin(ctx, "Template", nk_rect(50, 50, 220, 120),
               NK_WINDOW_BORDER | NK_WINDOW_TITLE | NK_WINDOW_CLOSABLE |
                   NK_WINDOW_MOVABLE))
  {
    nk_layout_row_dynamic(ctx, 30, 1);
    nk_label(ctx, "Hello, Nuklear + SDL3!", NK_TEXT_CENTERED);
  }
  nk_end(ctx);

  return !nk_window_is_hidden(ctx, "Template");
}

bool example(struct nk_context *ctx)
{
  enum
  {
    EASY,
    HARD
  };
  static int option = EASY;
  static float value = 0.6f;
  static int i = 20;

  if (nk_begin(ctx, "example", nk_rect(400, 50, 220, 220),
               NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_CLOSABLE))
  {
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

void render_image_pixels(struct nk_context *ctx, const float *tensor_data, int width, int height)
{
  if (!tensor_data || width < 0 || height < 0)
    return;

  if (nk_begin(ctx, "Pixels", nk_rect(100, 100, 500, 500), NK_WINDOW_TITLE | NK_WINDOW_SCALABLE | NK_WINDOW_MOVABLE | NK_WINDOW_MINIMIZABLE))
  {
    nk_layout_row_static(ctx, 40, 40, width);

    char digit_buffer[4];
    for (int i = 0; i < width; i++)
      for (int j = 0; j < height; j++)
      {
        int index = i * width + j;
        float pixel_data = tensor_data[index];

        SDL_snprintf(digit_buffer, sizeof(digit_buffer), "%.0f", pixel_data);
        nk_label(ctx, digit_buffer, NK_TEXT_CENTERED);
      }
  }
  nk_end(ctx);
}

void render_image(struct nk_context *ctx, _tensor_t *tensor)
{
  render_image_pixels(ctx, tensor->data, tensor->shape[0], tensor->shape[1]);
}
