#ifndef conv2_visualizer_tensor_h
#define conv2_visualizer_tensor_h

#include <ds_arena.h>

#define TENSOR_MAX_DIMS 8

// The tensor data type.
typedef struct
{
    float *data;
    int dimension;
    int shape[TENSOR_MAX_DIMS];
    int strides[TENSOR_MAX_DIMS];
    int size;
} _tensor_t;

// create a tensor
extern _tensor_t *tensor_create(_ds_arena_t_ *arena, int dimension, const int shape[]);

// zeroed tensor/oned tensor
extern _tensor_t *tensor_zeros(_ds_arena_t_ *arena, int dimension, const int shape[]);
extern _tensor_t *tensor_ones(_ds_arena_t_ *arena, int dimension, const int shape[]);

// randomdly initialize the learnable parameters of the neuron network
extern _tensor_t *tensor_random_normal(_ds_arena_t_ *arena, int dimension, const int shape[], float mean, float std);
extern _tensor_t *tensor_random_uniform(_ds_arena_t_ *arena, int dimension, const int shape[], float min, float mex);

#define T1(t, i) ((t)->data[(i) * (t)->strides[0]])
#define T2(t, i, j) ((t)->data[(i) * (t)->strides[0] + (j) * (t)->strides[1]])
#define T3(t, i, j, k) ((t)->data[(i) * (t)->strides[0] + (j) * (t)->strides[1] + (k) * (t)->strides[2]])
#define T4(t, n, c, h, w) \
    ((t)->data[(n) * (t)->strides[0] + (c) * (t)->strides[1] + (h) * (t)->strides[2] + (w) * (t)->strides[3]])

#endif // conv2_visualizer_tensor_h