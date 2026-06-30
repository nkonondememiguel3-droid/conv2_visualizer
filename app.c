#include "app.h"
#include <stdlib.h>

void error(const char *fmt, ...) {
  va_list args;
  char *msg = NULL;
  char *full = NULL;

  va_start(args, fmt);
  SDL_vasprintf(&msg, fmt, args);
  va_end(args);

  if (msg) {
    SDL_asprintf(&full, "ERROR: %s", msg);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "error", full, NULL);
    SDL_free(msg);
    SDL_free(full);

    exit(EXIT_FAILURE);
  }
}
