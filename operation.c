#include "operation.h"
#include <stdlib.h>

_tensor_t *im2col(_ds_arena_t_ *arena, _tensor_t *input, _tensor_t *kernel, int stride)
{
    if (input->dimension != 4 || kernel->dimension != 4)
    {
        // the input and/or the kernel does not have the dimension of 04.
        fprintf(stderr, "im2col: the input must have the dimension 04 and so does the kernel.");
        return NULL;
    }

    if (stride <= 0)
    {
        // the stride is less than 0.
        fprintf(stderr, "im2col: the stride should not be less or equal to zero.");
        return NULL;
    }

    int input_dim0 = input->shape[0]; // the batch_size
    int input_dim1 = input->shape[1]; // the chanel of the input matrix
    int input_dim2 = input->shape[2]; // the sample
    int input_dim3 = input->shape[3]; // the features of the sample

    int kernel_dim0 = kernel->shape[0]; // the output chanel
    int kernel_dim1 = kernel->shape[1]; // the input chanel
    int kernel_dim2 = kernel->shape[2]; // the kernel height
    int kernel_dim3 = kernel->shape[3]; // the kernel width

    if (input_dim1 != kernel_dim1)
    {
        // the chanel of the input doesn't match the kernel chanel
        fprintf(stderr, "im2col: the chanel of the input should match the chanel of the output.");
        return NULL;
    }

    int out_dim2 = (input_dim2 - kernel_dim2) / stride + 1; // the height of the output tensor
    int out_dim3 = (input_dim3 - kernel_dim3) / stride + 1; // the width of the output tensor

    if (out_dim2 <= 0 || out_dim3 <= 0)
    {
        // the dimensions are less than zero
        fprintf(stderr, "im2col: the dimension of the output matrix should not be less or equal to zero.");
        return NULL;
    }

    // compute the shape of the output tensor
    const int col_shape[] = {input_dim0 * out_dim2 * out_dim3, input_dim1 * kernel_dim2 * kernel_dim3};

    _tensor_t *col_tensor = tensor_zeros(arena, 2, col_shape);
    if (!col_tensor)
        return NULL;

    int current_row = 0;

    for (int n = 0; n < input_dim0; n++)
    {
        // iterate over each element in the batch of input.
        for (int r = 0; r < out_dim2; r++)
        {
            // iterate over the row of the output strided tensor.
            for (int c = 0; c < out_dim3; c++)
            {
                // iterate over the column of the output strided tensor.
                int current_col = 0;

                for (int ch = 0; ch < input_dim1; ch++)
                {
                    // iterate over each chanel on the input tensor.
                    for (int kh = 0; kh < kernel_dim2; kh++)
                    {
                        // iterate over the row of the kernel.
                        for (int kw = 0; kw < kernel_dim3; kw++)
                        {
                            // iterate over the column of the kernel.

                            int target_dim2 = r * stride + kh;
                            int target_dim3 = c * stride + kw;

                            // extract the value from the input.
                            float value = T4(input, n, ch, target_dim2, target_dim3);

                            T2(col_tensor, current_row, current_col) = value;

                            current_col++;
                        }
                    }
                }

                current_row++;
            }
        }
    }

    return col_tensor;
}

_tensor_t *col2im(_ds_arena_t_ *arena, _tensor_t *col, const int input_shape[4], _tensor_t *kernel, int stride)
{
    if (!col || !kernel)
    {
        // col and/or kernel is a null pointer.
        fprintf(stderr, "col2im: the col matrix and the kernel must not be NULL.");
        return NULL;
    }

    if (col->dimension != 2 || kernel->dimension != 4)
    {
        // the col matrix must be 2D and the kernel must have the dimension of 04.
        fprintf(stderr, "col2im: the col matrix must have the dimension 02 and the kernel the dimension 04.");
        return NULL;
    }

    if (stride <= 0)
    {
        // the stride is less than 0.
        fprintf(stderr, "col2im: the stride should not be less or equal to zero.");
        return NULL;
    }

    int input_dim0 = input_shape[0]; // the batch_size
    int input_dim1 = input_shape[1]; // the chanel of the input matrix
    int input_dim2 = input_shape[2]; // the height of the input matrix
    int input_dim3 = input_shape[3]; // the width of the input matrix

    int kernel_dim0 = kernel->shape[0]; // the output chanel
    int kernel_dim1 = kernel->shape[1]; // the input chanel
    int kernel_dim2 = kernel->shape[2]; // the kernel height
    int kernel_dim3 = kernel->shape[3]; // the kernel width

    if (input_dim1 != kernel_dim1)
    {
        // the chanel of the input doesn't match the kernel chanel
        fprintf(stderr, "col2im: the chanel of the input should match the chanel of the kernel.");
        return NULL;
    }

    int out_dim2 = (input_dim2 - kernel_dim2) / stride + 1; // the height of the output tensor
    int out_dim3 = (input_dim3 - kernel_dim3) / stride + 1; // the width of the output tensor

    if (out_dim2 <= 0 || out_dim3 <= 0)
    {
        // the dimensions are less than zero
        fprintf(stderr, "col2im: the dimension of the output matrix should not be less or equal to zero.");
        return NULL;
    }

    // the col matrix must have exactly the shape that im2col would have produced for this input/kernel/stride.
    int expected_rows = input_dim0 * out_dim2 * out_dim3;
    int expected_cols = input_dim1 * kernel_dim2 * kernel_dim3;

    if (col->shape[0] != expected_rows || col->shape[1] != expected_cols)
    {
        // the shape of the col matrix does not match what is expected from the given input shape/kernel/stride.
        fprintf(stderr, "col2im: the col matrix shape does not match the expected (%d, %d).\n", expected_rows, expected_cols);
        return NULL;
    }

    _tensor_t *img_tensor = tensor_zeros(arena, 4, input_shape);
    if (!img_tensor)
        return NULL;

    int current_row = 0;

    for (int n = 0; n < input_dim0; n++)
    {
        // iterate over each element in the batch of input.
        for (int r = 0; r < out_dim2; r++)
        {
            // iterate over the row of the output strided tensor.
            for (int c = 0; c < out_dim3; c++)
            {
                // iterate over the column of the output strided tensor.
                int current_col = 0;

                for (int ch = 0; ch < input_dim1; ch++)
                {
                    // iterate over each chanel on the input tensor.
                    for (int kh = 0; kh < kernel_dim2; kh++)
                    {
                        // iterate over the row of the kernel.
                        for (int kw = 0; kw < kernel_dim3; kw++)
                        {
                            // iterate over the column of the kernel.

                            int target_dim2 = r * stride + kh;
                            int target_dim3 = c * stride + kw;

                            // fetch the value stored by im2col for this (row, col) position.
                            float value = T2(col, current_row, current_col);

                            // accumulate rather than overwrite: overlapping kernel windows (stride < kernel
                            // size) must have their contributions summed, since that's what the chain rule
                            // requires when routing gradients back through a shared input location.
                            T4(img_tensor, n, ch, target_dim2, target_dim3) += value;

                            current_col++;
                        }
                    }
                }

                current_row++;
            }
        }
    }

    return img_tensor;
}
