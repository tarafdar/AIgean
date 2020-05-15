#ifndef _CONV_2D_LARGE_STREAM_NOBIAS_HPP
#define _CONV_2D_LARGE_STREAM_NOBIAS_HPP

#include <iostream>

#include "parameters_full.h"
#include "resnet50.hpp"
#include "_stream_resnet50_conversion.hpp"


template <class _INPUT_T, class _LAYER_T, typename _CONFIG, int _N_INPUT, int _N_OUTPUT> 
void _conv_2d_large_stream_norm_nobias ( 
                                           hls::stream<resnet50_packet> input[_N_INPUT], 
                                           hls::stream<resnet50_packet> output[_N_OUTPUT], 
        typename _CONFIG::weight_t weights[_CONFIG::filt_height * _CONFIG::filt_width * _CONFIG::n_chan * _CONFIG::n_filt], 
        typename _CONFIG::norm_config::scale_t scale[_CONFIG::n_filt], 
        typename _CONFIG::norm_config::bias_t sbiases[_CONFIG::n_filt]
        ){

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis both port=input
#pragma HLS INTERFACE axis both port=output

#pragma HLS DATAFLOW


    hls::stream<_INPUT_T> conv_input[_N_INPUT];
 #pragma HLS stream variable=conv_input      depth=1
    
   
    bool reset = _stream_to_input<_INPUT_T, _N_INPUT>(input, conv_input);

    static hls::stream<_LAYER_T> conv_output[_N_OUTPUT];
 #pragma HLS stream variable=conv_output      depth=1

    
    if(!conv_input[0].empty()){
        std::cout << "RUNNING CONV" << std::endl;
        nnet::conv_2d_large_stream_norm_nobias<_INPUT_T,_LAYER_T,_CONFIG>(reset,conv_input,conv_output, weights, scale, sbiases);
    }

    if(!conv_output[0].empty())_output_to_stream<_LAYER_T, _N_OUTPUT>( reset, conv_output, output );

    std::cout << "END CONV" << std::endl;

}
#endif
