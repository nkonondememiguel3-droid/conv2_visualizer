#ifndef app_h
#define app_h

#include <SDL3/SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 640

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;

  bool is_running;
} app_t;

extern void error(const char *fmt, ...) __attribute__((format(printf, 1, 2)));

#endif // !app_h
