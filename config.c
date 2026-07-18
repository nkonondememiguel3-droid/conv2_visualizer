#include <SDL3/SDL.h>
#include <mkl_service.h>

#include "config.h"

#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_INCLUDE_COMMAND_USERDATA
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT

#include "nuklear.h"
#include "nuklear_sdl3_renderer.h"

void load_font( struct nk_context *ctx )
{
  struct nk_font *font = NULL;
  {
    struct nk_font_atlas *atlas = nk_sdl_font_stash_begin( ctx );
    font = nk_font_atlas_add_from_file( atlas, "../assets/IosevkaTermNerdFont-Regular.ttf", 20, NULL );
    nk_sdl_font_stash_end( ctx );
  }
  if ( font ) nk_style_set_font( ctx, &font->handle );
  else nk_sdl_style_set_debug_font( ctx );
}

void *alloc_mkl( size_t bytes, void *user_data )
{
  (void)user_data;
  return mkl_malloc( bytes, 64 );
}

void *realloc_mkl( void *ptr, size_t new_size, void *user_data )
{
  (void)user_data;
  return mkl_realloc( ptr, new_size );
}

void free_mkl( void *ptr, void *user_data )
{
  (void)user_data;
  MKL_free( ptr );
}
