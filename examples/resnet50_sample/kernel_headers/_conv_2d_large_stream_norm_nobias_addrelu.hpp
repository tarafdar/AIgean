
#ifndef _CONV_2D_LARGE_STREAM_NORM_NOBIAS_ADDRELU
#define _CONV_2D_LARGE_STREAM_NORM_NOBIAS_ADDRELU

#include <iostream>

#include "parameters_full.h"
#include "resnet50.hpp"
#include "_stream_resnet50_conversion.hpp"




template <typename _CONV_IN_T, typename _ADD_IN_T, typename _OUTPUT_T, typename _CONFIG, int _N_CONV, int _N_ADD, int _N_OUTPUT>
void _conv_2d_large_stream_norm_nobias_addrelu (
                                            hls::stream<resnet50_packet> conv_in[_N_CONV],
                                            hls::stream<resnet50_packet> add_in[_N_ADD],
                                            hls::stream<resnet50_packet>  output[_N_OUTPUT],
        typename _CONFIG::weight_t weights[_CONFIG::filt_height * _CONFIG::filt_width * _CONFIG::n_chan * _CONFIG::n_filt], 
        typename _CONFIG::norm_config::scale_t scale[_CONFIG::n_filt], 
        typename _CONFIG::norm_config::bias_t sbiases[_CONFIG::n_filt]
        )
{

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis both port=conv_in
#pragma HLS INTERFACE axis both port=add_in
#pragma HLS INTERFACE axis both port=output

    static hls::stream<_CONV_IN_T> _conv_in[_N_CONV];
    #pragma HLS stream variable=_conv_in      depth=1
    bool reset = _stream_to_input<_CONV_IN_T, _N_CONV>(conv_in, _conv_in);

    static hls::stream<_ADD_IN_T> conv_out[_N_ADD];
    #pragma HLS stream variable=conv_out      depth=1
    
    if(!conv_in[0].empty()) nnet::conv_2d_large_stream_norm_nobias<_CONV_IN_T,_ADD_IN_T,_CONFIG>(reset,_conv_in,conv_out,weights,scale,sbiases);


    static hls::stream<_ADD_IN_T> _add_in[_N_ADD];
    #pragma HLS stream variable=_add_in      depth=1
    reset = _stream_to_input<_ADD_IN_T, _N_ADD>(add_in, _add_in);
    
    
    static hls::stream<_OUTPUT_T> _output[_N_OUTPUT];
    #pragma HLS stream variable=_output      depth=1
    
    if(!conv_out[0].empty() && !add_in[0].empty()) nnet::addrelu<_ADD_IN_T,_OUTPUT_T,_CONFIG>(_add_in,conv_out,_output);

    std::cout << "ADD RELU  output " << std::endl; 
    if(!_output[0].empty())_output_to_stream<_OUTPUT_T, _N_OUTPUT>(reset, _output, output);


}

#endif
