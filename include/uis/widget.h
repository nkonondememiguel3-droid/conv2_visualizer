#ifndef widget_h
#define widget_h

#include <stdbool.h>
struct nk_context;

bool hello_world(struct nk_context *ctx);
bool example(struct nk_context *ctx);

void image_view(struct nk_context *ctx, float x, float y, float width, float height);

#endif // !widget_h
