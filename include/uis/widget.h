#ifndef widget_h
#define widget_h

#include <stdbool.h>
#include "tensor.h"

struct nk_context;

bool hello_world(struct nk_context *ctx);
bool example(struct nk_context *ctx);

void render_image_pixels(struct nk_context *ctx, const float *tensor_data, int width, int height);
void render_image(struct nk_context *ctx, _tensor_t *tensor);

#endif // !widget_h
