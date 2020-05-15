#ifndef SPLIT_ONE_CONV_2D_LARGE_STREAM_NORM_NOBIAS_HPP
#define SPLIT_ONE_CONV_2D_LARGE_STREAM_NORM_NOBIAS_HPP

#include <iostream>


#include "_conv_2d_large_stream_norm_nobias_pool.hpp"

template <typename INPUT_T, typename CONV_LAYER_T, typename CONFIG, typename WEIGHTS, typename SCALES, typename BIASES, int N_INPUT, int N_CONV>
void split_one_conv_2d_large_stream_norm_nobias (
                                            hls::stream<resnet50_packet>  input[N_INPUT],
                                            hls::stream<resnet50_packet> conv_out[N_CONV],
                                            hls::stream<resnet50_packet> split_out[N_INPUT]
        )
{

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE ap_ctrl_none port=iReset
#pragma HLS INTERFACE axis both port=input
#pragma HLS INTERFACE axis both port=conv_out
#pragma HLS INTERFACE axis both port=split_out
    
    static hls::stream<INPUT_T>  split_out_conv[N_INPUT];
    #pragma HLS stream variable=split_out_conv      depth=1

    nnet::split<INPUT_T, INPUT_T, CONFIG>(input,split_out_conv,split_out);
    
    if(!split_out_conv[0].empty()) nnet::conv_2d_large_stream_norm_nobias<INPUT_T,CONV_LAYER_T, CONFIG>(split_out_conv,conv_out,WEIGHTS,SCALES,BIASES);

}

#endif
