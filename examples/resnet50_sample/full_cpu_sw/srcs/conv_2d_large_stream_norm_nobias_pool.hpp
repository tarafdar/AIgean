#ifndef CONV_2D_LARGE_STREAM_NOBIAS_POOL_HPP
#define CONV_2D_LARGE_STREAM_NOBIAS_POOL_HPP

#include <iostream>

#include "_conv_2d_large_stream_norm_nobias_pool.hpp"


template <class INPUT_T, class POOL_LAYER_T, class CONV_LAYER_T, 
          typename CONFIG_CONV, typename CONFIG_POOL,
          int N_INPUT, int N_OUTPUT, int N_CONV_OUTPUT> 
void conv_2d_large_stream_norm_nobias_pool ( 
                                           hls::stream<resnet50_packet> input[N_INPUT], 
                                           hls::stream<resnet50_packet> output[N_OUTPUT], 
        typename CONFIG_CONV::weight_t weights[CONFIG_CONV::filt_height * CONFIG_CONV::filt_width * CONFIG_CONV::n_chan * CONFIG_CONV::n_filt], 
        typename CONFIG_CONV::norm_config::scale_t scale[CONFIG_CONV::n_filt], 
        typename CONFIG_CONV::norm_config::bias_t sbiases[CONFIG_CONV::n_filt]
        ){



    _conv_2d_large_stream_norm_nobias_pool <INPUT_T, POOL_LAYER_T, CONV_LAYER_T, CONFIG_CONV, CONFIG_POOL, N_INPUT, N_OUTPUT, N_CONV_OUTPUT> (input, output, weights, scale, sbiases);
    std::cout << "END OF CONV_WRAPPER" << std::endl;
    
}
#endif
