#ifndef _POOL_HPP
#define _POOL_HPP

#include <iostream>

#include "parameters_full.h"
#include "resnet50.hpp"
#include "_stream_resnet50_conversion.hpp"

template <class _INPUT_T, class _LAYER_T,  
          typename _CONFIG,
          int _N_INPUT, int _N_OUTPUT> 
void _pool ( 
                                           hls::stream<resnet50_packet> input[_N_INPUT], 
                                           hls::stream<resnet50_packet> output[_N_OUTPUT]
        ){

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis both port=input
#pragma HLS INTERFACE axis both port=output

#pragma HLS DATAFLOW
    
    hls::stream<_INPUT_T> pool_input[_N_INPUT];
 #pragma HLS stream variable=pool_input      depth=1
   
    bool reset = _stream_to_input<_INPUT_T, _N_INPUT>(input, pool_input);


    hls::stream<_LAYER_T> pool_output[_N_OUTPUT];
 #pragma HLS stream variable=pool_output      depth=1
    if(!pool_input[0].empty()) nnet::pool_2d_large_stream<_INPUT_T, _LAYER_T, _CONFIG>(pool_input,pool_output);

    if(!pool_output[0].empty())_output_to_stream<_LAYER_T, _N_OUTPUT>(reset, pool_output, output);
}
#endif
