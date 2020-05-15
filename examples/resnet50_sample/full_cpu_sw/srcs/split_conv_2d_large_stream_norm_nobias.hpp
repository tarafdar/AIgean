#ifndef SPLIT_CONV_2D_LARGE_STREAM_NORM_NOBIAS_HPP
#define SPLIT_CONV_2D_LARGE_STREAM_NORM_NOBIAS_HPP

#include <iostream>

#include "parameters_full.h"
#include "resnet50.hpp"
#include "_split_conv_2d_large_stream_norm_nobias.hpp"

template <typename _INPUT_T, typename _CONV_LAYER_T, typename _CONFIG, int _N_INPUT, int _N_CONV>
void split_conv_2d_large_stream_norm_nobias (
                                            hls::stream<resnet50_packet>  input[_N_INPUT],
                                            hls::stream<resnet50_packet> conv_out[_N_CONV],
                                            hls::stream<resnet50_packet> split_out[_N_INPUT],
        typename _CONFIG::weight_t weights[_CONFIG::filt_height * _CONFIG::filt_width * _CONFIG::n_chan * _CONFIG::n_filt], 
        typename _CONFIG::norm_config::scale_t scale[_CONFIG::n_filt], 
        typename _CONFIG::norm_config::bias_t sbiases[_CONFIG::n_filt]
        )
{

    

    _split_conv_2d_large_stream_norm_nobias<_INPUT_T, _CONV_LAYER_T, _CONFIG, _N_INPUT, _N_CONV>(input,conv_out,split_out, weights, scale, sbiases);
    

}

#endif
