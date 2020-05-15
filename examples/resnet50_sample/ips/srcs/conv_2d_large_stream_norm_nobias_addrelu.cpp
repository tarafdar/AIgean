
#ifndef CONV_2D_LARGE_STREAM_NORM_NOBIAS_ADDRELU
#define CONV_2D_LARGE_STREAM_NORM_NOBIAS_ADDRELU

#include <iostream>
#include "myproject_full.h"

#include "_conv_2d_large_stream_norm_nobias_addrelu.hpp"
#include "layer_params.h"

void conv_2d_large_stream_norm_nobias_addrelu (
                                            hls::stream<resnet50_packet> conv_in[N_CONV],
                                            hls::stream<resnet50_packet> add_in[N_ADD],
                                            hls::stream<resnet50_packet>  output[N_OUTPUT]
        )
{

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis both port=conv_in
#pragma HLS INTERFACE axis both port=add_in
#pragma HLS INTERFACE axis both port=output


        _conv_2d_large_stream_norm_nobias_addrelu<CONV_IN_T, ADD_IN_T, OUTPUT_T, CONFIG, N_CONV, N_ADD, N_OUTPUT>(conv_in, add_in, output, WEIGHTS, SCALES, BIASES);



}

#endif
