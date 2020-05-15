#ifndef SPLIT_ONE_CONV_2D_LARGE_STREAM_NORM_NOBIAS_HPP
#define SPLIT_ONE_CONV_2D_LARGE_STREAM_NORM_NOBIAS_HPP

#include <iostream>


#include "parameters_full.h"
#include "resnet50.hpp"
#include "_stream_resnet50_conversion.hpp"

template <typename _INPUT_T, typename _CONFIG, int _N_INPUT>
void _split_resnet50 (
                                            hls::stream<resnet50_packet>  input[_N_INPUT],
                                            hls::stream<resnet50_packet> out_1[_N_INPUT],
                                            hls::stream<resnet50_packet> out_2[_N_INPUT]
        )
{

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis both port=input
#pragma HLS INTERFACE axis both port=out_1
#pragma HLS INTERFACE axis both port=out_2
    
    static hls::stream<_INPUT_T>  split_in[_N_INPUT];
    #pragma HLS stream variable=split_in      depth=1

    std::cout << "BEFORE STREAM TO INPUT" << std::endl; 
    bool reset = _stream_to_input<_INPUT_T, _N_INPUT>(input, split_in);
    std::cout << "AFTER STREAM TO INPUT"  << std::endl;
    
    static hls::stream<_INPUT_T> split_out_1[_N_INPUT];
    #pragma HLS stream variable=split_out_1      depth=1
    static hls::stream<_INPUT_T> split_out_2[_N_INPUT];
    #pragma HLS stream variable=split_out_2      depth=1

    if(!split_in[0].empty())nnet::split<_INPUT_T, _INPUT_T, _CONFIG>(split_in,split_out_1,split_out_2);
    

    if(!split_out_1[0].empty())_output_to_stream<_INPUT_T, _N_INPUT>( reset, split_out_1, out_1 );
    
    if(!split_out_2[0].empty())_output_to_stream<_INPUT_T, _N_INPUT>( reset, split_out_2, out_2 );
    
}

#endif
