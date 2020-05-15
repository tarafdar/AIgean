#ifndef _SPLIT_CONV_2D_LARGE_STREAM_NORM_NOBIAS_HPP
#define _SPLIT_CONV_2D_LARGE_STREAM_NORM_NOBIAS_HPP

#include <iostream>

#include "parameters_full.h"
#include "resnet50.hpp"
#include "_stream_resnet50_conversion.hpp"
#include "_split_resnet50.hpp"
#include "_conv_2d_large_stream_norm_nobias.hpp"

template <typename _INPUT_T, typename _CONV_LAYER_T, typename _CONFIG, int _N_INPUT, int _N_CONV>
void _split_conv_2d_large_stream_norm_nobias (
                                            hls::stream<resnet50_packet>  input[_N_INPUT],
                                            hls::stream<resnet50_packet> conv_out[_N_CONV],
                                            hls::stream<resnet50_packet> split_out[_N_INPUT],
        typename _CONFIG::weight_t weights[_CONFIG::filt_height * _CONFIG::filt_width * _CONFIG::n_chan * _CONFIG::n_filt], 
        typename _CONFIG::norm_config::scale_t scale[_CONFIG::n_filt], 
        typename _CONFIG::norm_config::bias_t sbiases[_CONFIG::n_filt]
        )
{

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis both port=input
#pragma HLS INTERFACE axis both port=conv_out
#pragma HLS INTERFACE axis both port=split_out
    
    static hls::stream<_INPUT_T>  split_input[_N_INPUT];
    #pragma HLS stream variable=split_input      depth=1
    
    static hls::stream<_INPUT_T>  split_out_conv[_N_INPUT];
    #pragma HLS stream variable=split_out_conv      depth=1
    
    static hls::stream<_INPUT_T>  _split_out[_N_INPUT];
    #pragma HLS stream variable=_split_out      depth=1

     bool reset = _stream_to_input<_INPUT_T, _N_INPUT>(input, split_input);

    if(!split_input[0].empty())nnet::split<_INPUT_T, _INPUT_T, _CONFIG>(split_input,split_out_conv,_split_out);
    
    static hls::stream<_CONV_LAYER_T>  _conv_out[_N_CONV];
    #pragma HLS stream variable=_conv_out      depth=1
    
    if(!split_out_conv[0].empty()){
        nnet::conv_2d_large_stream_norm_nobias<_INPUT_T,_CONV_LAYER_T,_CONFIG>(reset,split_out_conv,_conv_out, weights, scale, sbiases);
    }

    if(!_split_out[0].empty())_output_to_stream<_INPUT_T, _N_INPUT>( reset, _split_out, split_out );
    
    if(!_conv_out[0].empty())_output_to_stream<_CONV_LAYER_T, _N_CONV>( reset, _conv_out, conv_out );
}

#endif
