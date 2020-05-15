
#ifndef CONV_2D_LARGE_STREAM_NORM_NOBIAS_ADDRELU
#define CONV_2D_LARGE_STREAM_NORM_NOBIAS_ADDRELU

#include <iostream>


#include "_conv_2d_large_stream_norm_nobias_addrelu.hpp"




template <typename CONV_IN_T, typename ADD_IN_T, typename OUTPUT_T, typename CONFIG, int N_CONV, int N_ADD, int N_OUTPUT>
void conv_2d_large_stream_norm_nobias_addrelu (
                                            hls::stream<resnet50_packet> conv_in[N_CONV],
                                            hls::stream<resnet50_packet> add_in[N_ADD],
                                            hls::stream<resnet50_packet>  output[N_OUTPUT],
        typename CONFIG::weight_t weights[CONFIG::filt_height * CONFIG::filt_width * CONFIG::n_chan * CONFIG::n_filt], 
        typename CONFIG::norm_config::scale_t scale[CONFIG::n_filt], 
        typename CONFIG::norm_config::bias_t sbiases[CONFIG::n_filt]
        )
{

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis both port=conv_in
#pragma HLS INTERFACE axis both port=add_in
#pragma HLS INTERFACE axis both port=output


    _conv_2d_large_stream_norm_nobias_addrelu <CONV_IN_T, ADD_IN_T, OUTPUT_T, CONFIG, N_CONV, N_ADD, N_OUTPUT> (conv_in, add_in, output, weights, scale, sbiases);




}

#endif
