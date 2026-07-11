#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_messagebox.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>

#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "app.h"

#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_INCLUDE_COMMAND_USERDATA
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_IMPLEMENTATION
#include "nuklear.h"

#define NK_SDL3_RENDERER_IMPLEMENTATION
#include "nuklear_sdl3_renderer.h"

#include "config.h"
#include "uis/widget.h"
#include "tensor.h"

int main(int argc, char *argv[])
{
  srand(time(NULL));
  app_t app = (app_t){
      .is_running = true,
  };
  struct nk_context *ctx = NULL;

  _ds_arena_t_ arena = ds_arena_new(0);
  const int shape[] = {64, 64};
  _tensor_t *tensor = tensor_create(&arena, 2, shape);

  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    error("Failed to initialized the sdl3 library. [%s]", SDL_GetError());
  }

  if (!SDL_CreateWindowAndRenderer(
          "Nuklear Template",
          WINDOW_WIDTH,
          WINDOW_HEIGHT,
          SDL_WINDOW_RESIZABLE,
          &app.window, &app.renderer))
  {
    error("Failed to create window/renderer. [%s]", SDL_GetError());
  }

  // gui
  ctx = nk_sdl_init(app.window, app.renderer, nk_sdl_allocator());

  // Load font
  load_font(ctx);

  bool show_template = true, show_example = true;

  while (app.is_running)
  {
    // event handler
    nk_input_begin(ctx);
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_EVENT_QUIT ||
          (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE))
      {
        app.is_running = false;
      }
      nk_sdl_handle_event(ctx, &event);
    }
    nk_sdl_update_TextInput(ctx);
    nk_input_end(ctx);

    // render
    SDL_SetRenderDrawColor(app.renderer, 250, 250, 250, 250);
    SDL_RenderClear(app.renderer);

    // render_image_pixels(ctx, tensor_data, 64, 64);
    render_image(ctx, tensor);

    nk_sdl_render(ctx, NK_ANTI_ALIASING_ON);

    SDL_RenderPresent(app.renderer);
  }

  ds_arena_destroy(&arena);
  if (ctx)
    nk_sdl_shutdown(ctx);
  SDL_DestroyRenderer(app.renderer);
  SDL_DestroyWindow(app.window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
