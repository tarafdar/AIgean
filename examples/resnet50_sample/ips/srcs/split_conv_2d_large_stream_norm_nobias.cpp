#ifndef SPLIT_CONV_2D_LARGE_STREAM_NORM_NOBIAS_HPP
#define SPLIT_CONV_2D_LARGE_STREAM_NORM_NOBIAS_HPP

#include <iostream>


#include "_split_conv_2d_large_stream_norm_nobias.hpp"
#include "layer_params.h"

void split_conv_2d_large_stream_norm_nobias (
                                            hls::stream<resnet50_packet>  input[N_INPUT],
                                            hls::stream<resnet50_packet> conv_out[N_CONV],
                                            hls::stream<resnet50_packet> split_out[N_INPUT]
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





    _split_conv_2d_large_stream_norm_nobias<INPUT_T, CONV_LAYER_T, CONFIG, N_INPUT, N_CONV>(input,conv_out,split_out, WEIGHTS, SCALES, BIASES);
    

}

#endif
