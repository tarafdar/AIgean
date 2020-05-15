#ifndef SPLIT_CONV_2D_LARGE_STREAM_NORM_NOBIAS_HPP
#define SPLIT_CONV_2D_LARGE_STREAM_NORM_NOBIAS_HPP

#include <iostream>


#include "_split_conv_2d_large_stream_norm_nobias.hpp"
#include "layer_params.h"

void split_conv_2d_large_stream_norm_nobias (
                                            hls::stream<resnet50_packet>  input[N_INPUT],
                                            hls::stream<resnet50_packet> conv_out[N_CONV],
                                            hls::stream<resnet50_packet> split_out[N_INPUT]
//        typename CONFIG::weight_t weights[CONFIG::filt_height * CONFIG::filt_width * CONFIG::n_chan * CONFIG::n_filt], 
//        typename CONFIG::norm_config::scale_t scale[CONFIG::n_filt], 
//        typename CONFIG::norm_config::bias_t sbiases[CONFIG::n_filt]
        )
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis both port=input 
#pragma HLS INTERFACE axis both port=conv_out
#pragma HLS INTERFACE axis both port=split_out
#if N_INPUT==2048
#pragma HLS array_partition variable=input block factor=2
#pragma HLS array_partition variable=split_out block factor=2
#else
#pragma HLS array_partition variable=input
#pragma HLS array_partition variable=split_out
#endif
#if N_CONV==2048
#pragma HLS array_partition variable=conv_out block factor=2
#else
#pragma HLS array_partition variable=conv_out
#endif



    static hls::stream<resnet50_packet>  split_out_conv[N_INPUT];
    #pragma HLS stream variable=split_out_conv      depth=1

    _split_conv_2d_large_stream_norm_nobias<INPUT_T, CONV_LAYER_T, CONFIG, N_INPUT, N_CONV>(input,split_out_conv,split_out, weights, scale, sbiases);
    

}

#endif
