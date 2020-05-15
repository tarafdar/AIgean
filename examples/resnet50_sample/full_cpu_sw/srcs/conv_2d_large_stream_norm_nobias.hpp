#ifndef CONV_2D_LARGE_STREAM_NOBIAS_HPP
#define CONV_2D_LARGE_STREAM_NOBIAS_HPP

#include <iostream>

#include "_conv_2d_large_stream_norm_nobias.hpp"

template <class INPUT_T, class LAYER_T, typename CONFIG, int N_INPUT, int N_OUTPUT> 
void conv_2d_large_stream_norm_nobias ( 
                                           hls::stream<resnet50_packet> input[N_INPUT], 
                                           hls::stream<resnet50_packet> output[N_OUTPUT], 
        typename CONFIG::weight_t weights[CONFIG::filt_height * CONFIG::filt_width * CONFIG::n_chan * CONFIG::n_filt], 
        typename CONFIG::norm_config::scale_t scale[CONFIG::n_filt], 
        typename CONFIG::norm_config::bias_t sbiases[CONFIG::n_filt]
        ){

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis both port=input
#pragma HLS INTERFACE axis both port=output

#pragma HLS DATAFLOW


    _conv_2d_large_stream_norm_nobias <INPUT_T, LAYER_T, CONFIG, N_INPUT, N_OUTPUT> (input, output, weights, scale, sbiases);

}
#endif
