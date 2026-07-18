#ifndef conv2_visualizer_operation_h
#define conv2_visualizer_operation_h

#include "tensor.h"
#include "ds_arena.h"

// compute the im2col transformation on a tensor feature with respect to the kernel tensor and output the feature_map
_tensor_t *im2col(_ds_arena_t_ *arena, _tensor_t *input, _tensor_t *kernel, int stride);

// compute the col2im transformation: the inverse/adjoint of im2col, scattering (accumulating) a column
// matrix back into an input-shaped tensor. Used to route gradients back to the input during backprop,
// since overlapping kernel windows must have their contributions summed, not overwritten.
_tensor_t *col2im(_ds_arena_t_ *arena, _tensor_t *col, const int input_shape[4], _tensor_t *kernel, int stride);

#endif // conv2_visualizer_operation_h