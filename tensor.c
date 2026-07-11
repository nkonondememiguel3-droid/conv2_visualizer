#include "tensor.h"

#include <stdlib.h>

#ifdef _WIN32
#define _USE_MATH_DEFINES
#else
#define _GNU_SOURCE
#endif
#include <math.h>

static void compute_strides(_tensor_t *tensor)
{
    // the stride are computed from right to left.
    tensor->strides[tensor->dimension - 1] = 1;
    for (int i = tensor->dimension - 2; i >= 0; i--)
        tensor->strides[i] = tensor->strides[i + 1] * tensor->shape[i + 1];
}

_tensor_t *tensor_create(_ds_arena_t_ *arena, int dimension, const int shape[])
{
    // validate the dimension
    if (dimension <= 0 || dimension >= TENSOR_MAX_DIMS)
    {
        fprintf(stderr, "tensor_create: invalid dimension %d (max %d)\n", dimension, TENSOR_MAX_DIMS);
        return NULL;
    }

    // valide the shape
    for (int i = 0; i < dimension; i++)
        if (shape[i] <= 0)
        {
            fprintf(stderr, "tensor_create: invalid shape[%d] = %d\n", i + 1, shape[i]);
            return NULL;
        }

    // create the tensor
    _tensor_t *tensor = ARENA_NEW(arena, _tensor_t);
    tensor->dimension = dimension;
    tensor->size = 1;

    // fill the shape and compute the size
    for (int i = 0; i < dimension; i++)
    {
        tensor->shape[i] = shape[i];
        tensor->size *= shape[i];
    }
    compute_strides(tensor); // compute the strides for this tensor.

    // allocate just enough memory for the actual tensor data.
    tensor->data = ARENA_ARRAY(arena, float, tensor->size);

    return tensor;
}

_tensor_t *tensor_zeros(_ds_arena_t_ *arena, int dimension, const int shape[])
{
    // this is so 'cause the ARENA_NEW already zero the allocated buffer for us.
    return tensor_create(arena, dimension, shape);
}

_tensor_t *tensor_ones(_ds_arena_t_ *arena, int dimension, const int shape[])
{
    _tensor_t *tensor = tensor_create(arena, dimension, shape);
    if (!tensor)
        return NULL;

    for (int i = 0; i < tensor->size; i++)
        tensor->data[i] = 1.0f;

    return tensor;
}

// this is a box-muller transformation.
_tensor_t *tensor_random_normal(_ds_arena_t_ *arena, int dimension, const int shape[], float mean, float std)
{
    _tensor_t *tensor = tensor_create(arena, dimension, shape);
    if (!tensor)
    {
        fprintf(stderr, "tensor_random_normal: failed to create the tensor.");
        return NULL;
    }

    for (int i = 0; i < tensor->size; i += 2)
    {
        float u_1 = (float)rand() / (float)RAND_MAX;
        float u_2 = (float)rand() / (float)RAND_MAX;

        if (u_1 < 1e-7f)
            u_1 = 1e-7f;
        float mag = std * sqrtf(-2.0f * logf(u_1));
        float z_0 = mag * cosf(2.0f * (float)M_PI * u_2) + mean;
        float z_1 = mag * sinf(2.0f * (float)M_PI * u_2) + mean;

        tensor->data[i] = z_0;
        if (i + 1 < tensor->size)
            tensor->data[i + 1] = z_1;
    }

    return tensor;
}

_tensor_t *tensor_random_uniform(_ds_arena_t_ *arena, int dimension, const int shape[], float min, float max)
{
    _tensor_t *tensor = tensor_create(arena, dimension, shape);
    if (!tensor)
    {
        fprintf(stderr, "tensor_random_uniform: failed to create the tensor.");
        return NULL;
    }

    float range = max - min;
    for (int i = 0; i < tensor->size; i++)
    {
        float u = (float)rand() / (float)RAND_MAX;
        tensor->data[i] = range * u + min;
    }

    return tensor;
}
