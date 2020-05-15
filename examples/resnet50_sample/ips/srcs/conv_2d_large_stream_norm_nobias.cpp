#include <iostream>

#include "myproject_full.h"

#include "_conv_2d_large_stream_norm_nobias_pool.hpp"
#include "layer_params.h"

//NEED TO DEFINE INPUT_T,  
//N_INPUT, N_CONV_OUTPUT, N_OUTPUT
//CONFIG_CONV, CONFIG_POOL
//CONV_LAYER_T, POOL_LAYER_T
//WEIGHTS, SCALES, BIASES

void conv_2d_large_stream_norm_nobias ( 
                                           hls::stream<resnet50_packet> input[N_INPUT], 
                                           hls::stream<resnet50_packet> output[N_OUTPUT] 
        ){

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis both port=input
#pragma HLS INTERFACE axis both port=output

#pragma HLS DATAFLOW
    _conv_2d_large_stream_norm_nobias<INPUT_T, LAYER_T, CONFIG, N_INPUT, N_OUTPUT> (input, output, WEIGHTS, SCALES, BIASES); 

}
