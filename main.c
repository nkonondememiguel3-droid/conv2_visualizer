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
#include "ds_arena.h"

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
#include "tensor.h"
#include "uis/widget.h"

int main( int argc, char *argv[] )
{

<<<<<<< HEAD
  int window_width = 1600, window_height = 900;
  app_t app = (app_t){.is_running = true};
=======
  (void)argc;
  (void)argv;
>>>>>>> main

  srand( time( NULL ) );
  app_t app = ( app_t ){
    .is_running = true,
  };
  struct nk_context *ctx = NULL;

  /* _ds_arena_t_ arena = ds_arena_new(0); */
  _ds_arena_t_ arena = ds_arena_new_with_allocator( 0, alloc_mkl, realloc_mkl, free_mkl, NULL );
  const int shape[] = { 64, 64 };
  _tensor_t *tensor = tensor_create( &arena, 2, shape );

<<<<<<< HEAD
  if (!SDL_CreateWindowAndRenderer("Nuklear Template", window_width,
                                   window_height, SDL_WINDOW_RESIZABLE,
                                   &app.window, &app.renderer)) {
    error("Failed to create window/renderer. [%s]", SDL_GetError());
=======
  if ( !SDL_Init( SDL_INIT_VIDEO ) ) { error( "Failed to initialized the sdl3 library. [%s]", SDL_GetError() ); }

  if ( !SDL_CreateWindowAndRenderer( "Nuklear Template", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE, &app.window, &app.renderer ) )
  {
    error( "Failed to create window/renderer. [%s]", SDL_GetError() );
>>>>>>> main
  }

  // gui
  ctx = nk_sdl_init( app.window, app.renderer, nk_sdl_allocator() );

  // Load font
  load_font( ctx );

  while ( app.is_running )
  {
    // event handler
    nk_input_begin( ctx );
    SDL_Event event;
<<<<<<< HEAD
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT ||
          (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)) {
        app.is_running = false;
      }
      switch (event.type) {
        /* case SDL_EVENT_WINDOW_RESIZED: */
        /*   window_width = event.window.data1; */
        /*   window_height = event.window.data2; */
        /*   break; */
      }
      nk_sdl_handle_event(ctx, &event);
    }
    SDL_GetWindowSize(app.window, &window_width, &window_height);
    nk_sdl_update_TextInput(ctx);
    nk_input_end(ctx);
=======
    while ( SDL_PollEvent( &event ) )
    {
      if ( event.type == SDL_EVENT_QUIT || ( event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE ) ) { app.is_running = false; }
      nk_sdl_handle_event( ctx, &event );
    }
    nk_sdl_update_TextInput( ctx );
    nk_input_end( ctx );
>>>>>>> main

    // render
    SDL_SetRenderDrawColor( app.renderer, 250, 250, 250, 250 );
    SDL_RenderClear( app.renderer );

<<<<<<< HEAD
    // main window
    if (nk_begin(ctx, "main_window", nk_rect(0, 0, window_width, window_height),
                 NK_WINDOW_NO_SCROLLBAR)) {
      nk_layout_row_dynamic(ctx, 30, 1);
      nk_label(ctx, "Hello, world", NK_TEXT_CENTERED);
    }
    nk_end(ctx);
    nk_sdl_render(ctx, NK_ANTI_ALIASING_ON);
=======
    // render_image_pixels(ctx, tensor_data, 64, 64);
    render_image( ctx, tensor );
>>>>>>> main

    nk_sdl_render( ctx, NK_ANTI_ALIASING_ON );

    SDL_RenderPresent( app.renderer );
  }

  ds_arena_destroy( &arena );
  if ( ctx ) nk_sdl_shutdown( ctx );
  SDL_DestroyRenderer( app.renderer );
  SDL_DestroyWindow( app.window );
  SDL_Quit();
  return EXIT_SUCCESS;
}
