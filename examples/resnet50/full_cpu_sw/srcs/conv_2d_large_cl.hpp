#ifndef CONV_2D_LARGE_CL_HPP
#define CONV_2D_LARGE_CL_HPP

#include <iostream>

#include "_conv_2d_large_cl.hpp"

template <class INPUT_T, class LAYER_T, typename CONFIG, int N_INPUT, int N_OUTPUT> 
void conv_2d_large_cl ( 
        hls::stream<INPUT_T> input[N_INPUT], 
        hls::stream<LAYER_T> output[N_OUTPUT], 
        typename CONFIG::weight_t weights[CONFIG::filt_height * CONFIG::filt_width * (CONFIG::n_chan-1) * (CONFIG::n_filt-1)/2],
        typename CONFIG::bias_t biases[CONFIG::n_filt]
        ){


    _conv_2d_large_cl <INPUT_T, LAYER_T, CONFIG, N_INPUT, N_OUTPUT> (input, output, weights, biases);

}
#endif
