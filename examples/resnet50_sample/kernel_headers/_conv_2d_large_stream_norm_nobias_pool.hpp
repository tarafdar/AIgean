#ifndef _CONV_2D_LARGE_STREAM_NOBIAS_POOL_HPP
#define _CONV_2D_LARGE_STREAM_NOBIAS_POOL_HPP

#include <iostream>

#include "parameters_full.h"
#include "resnet50.hpp"
#include "_conv_2d_large_stream_norm_nobias.hpp"
#include "_pool.hpp"


template <class _INPUT_T, class _POOL_LAYER_T, class _CONV_LAYER_T, typename _CONFIG_CONV, typename _CONFIG_POOL, int _N_INPUT, int _N_OUTPUT, int _N_CONV_OUTPUT> 
void _conv_2d_large_stream_norm_nobias_pool ( 
                                           hls::stream<resnet50_packet> input[_N_INPUT], 
                                           hls::stream<resnet50_packet> output[_N_OUTPUT], 
        typename _CONFIG_CONV::weight_t weights[_CONFIG_CONV::filt_height * _CONFIG_CONV::filt_width * _CONFIG_CONV::n_chan * _CONFIG_CONV::n_filt], 
        typename _CONFIG_CONV::norm_config::scale_t scale[_CONFIG_CONV::n_filt], 
        typename _CONFIG_CONV::norm_config::bias_t sbiases[_CONFIG_CONV::n_filt]
        ){

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis both port=input
#pragma HLS INTERFACE axis both port=output

#pragma HLS DATAFLOW



    hls::stream<resnet50_packet> conv_output[_N_OUTPUT];
 #pragma HLS stream variable=conv_output      depth=1
    _conv_2d_large_stream_norm_nobias <_INPUT_T, _CONV_LAYER_T, _CONFIG_CONV, _N_INPUT, _N_CONV_OUTPUT>(input, conv_output, weights, scale, sbiases);
    _pool<_CONV_LAYER_T, _POOL_LAYER_T, _CONFIG_POOL, _N_CONV_OUTPUT, _N_OUTPUT> (conv_output, output);

}
#endif
