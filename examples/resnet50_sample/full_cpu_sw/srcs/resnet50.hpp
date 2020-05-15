#ifndef RESNET50_FULL_H_
#define RESNET50_FULL_H_

#include <complex>
#include "ap_int.h"
#include "ap_fixed.h"
#include "galapagos_packet.h"

#include "parameters_full.h"
//#include "galapagos_resnet_bridge.hpp"
//#include "conv_2d_large_stream_norm_nobias_pool.hpp"

#define BRIDGE_WIDTH_3 3
#define BRIDGE_WIDTH_64 64 
#define BRIDGE_WIDTH_128 128 
#define BRIDGE_WIDTH_256 256 
#define BRIDGE_WIDTH_512 512 
#define BRIDGE_WIDTH_1024 1024
#define BRIDGE_WIDTH_2048 2048 

struct resnet50_packet{
    ap_uint<8> data;
    ap_int <1> id;
};


//void hls4ml_galapagos_input_bridge_one_in_3 (galapagos_interface * bridge_in,
//                                           hls::stream<ap_fixed<8,6> > input[BRIDGE_WIDTH_3],
//                                           volatile ap_uint <1> * iReset_out);
//                    
//void hls4ml_galapagos_input_bridge_one_in_64 (galapagos_interface * bridge_in,
//                                           hls::stream<ap_fixed<8,6> > input[BRIDGE_WIDTH_64],
//                                           volatile ap_uint <1> * iReset_out);
//                    
//void hls4ml_galapagos_input_bridge_one_in_128 (galapagos_interface * bridge_in,
//                                           hls::stream<ap_fixed<8,6> > input[BRIDGE_WIDTH_128],
//                                           volatile ap_uint <1> * iReset_out);
//                    
//
//void hls4ml_galapagos_input_bridge_one_in_256 (galapagos_interface * bridge_in,
//                                           hls::stream<ap_fixed<8,6> > input[BRIDGE_WIDTH_256],
//                                           volatile ap_uint <1> * iReset_out);
//                    
//void hls4ml_galapagos_input_bridge_one_in_512 (galapagos_interface * bridge_in,
//                                           hls::stream<ap_fixed<8,6> > input[BRIDGE_WIDTH_512],
//                                           volatile ap_uint <1> * iReset_out);
//                    
//void hls4ml_galapagos_input_bridge_one_in_1024 (galapagos_interface * bridge_in,
//                                           hls::stream<ap_fixed<8,6> > input[BRIDGE_WIDTH_1024],
//                                           volatile ap_uint <1> * iReset_out);
//                    
//
//void hls4ml_galapagos_input_bridge_one_in_2048 (galapagos_interface * bridge_in,
//                                           hls::stream<ap_fixed<8,6> > input[BRIDGE_WIDTH_2048],
//                                           volatile ap_uint <1> * iReset_out);
//                    
//void hls4ml_galapagos_output_bridge_3 (
//                                    		hls::stream<ap_fixed<8,6> > output[BRIDGE_WIDTH_3],
//                                    		galapagos_interface * bridge_output,
//                                    		const ap_uint <8> dest
//                                           );
//                    
//void hls4ml_galapagos_output_bridge_64 (
//                                    		hls::stream<ap_fixed<8,6> > output[BRIDGE_WIDTH_64],
//                                    		galapagos_interface * bridge_output,
//                                    		const ap_uint <8> dest
//                                           );
//                    
//void hls4ml_galapagos_output_bridge_128 (
//                                    		hls::stream<ap_fixed<8,6> > output[BRIDGE_WIDTH_128],
//                                    		galapagos_interface * bridge_output,
//                                    		const ap_uint <8> dest
//                                           );
//
//
//void hls4ml_galapagos_output_bridge_256 (
//                                    		hls::stream<ap_fixed<8,6> > output[BRIDGE_WIDTH_256],
//                                    		galapagos_interface * bridge_output,
//                                    		const ap_uint <8> dest
//                                           );
//
//
//void hls4ml_galapagos_output_bridge_512 (
//                                    		hls::stream<ap_fixed<8,6> > output[BRIDGE_WIDTH_512],
//                                    		galapagos_interface * bridge_output,
//                                    		const ap_uint <8> dest
//                                           );
//
//void hls4ml_galapagos_output_bridge_1024 (
//                                    		hls::stream<ap_fixed<8,6> > output[BRIDGE_WIDTH_1024],
//                                    		galapagos_interface * bridge_output,
//                                    		const ap_uint <8> dest
//                                           );
//
//void hls4ml_galapagos_output_bridge_2048 (
//                                    		hls::stream<ap_fixed<8,6> > output[BRIDGE_WIDTH_2048],
//                                    		galapagos_interface * bridge_output,
//                                    		const ap_uint <8> dest
//                                           );
//                    
//
//
////template <typename CONV_IN_T, typename ADD_IN_T, typename OUTPUT_T, typename WEIGHTS, typename SCALES, typename BIASES, int N_CONV, int N_ADD, int N_OUTPUT>
////void one_conv_2d_large_stream_norm_nobias_addrelu (bool iReset,
////                                            hls::stream<CONV_IN_T> conv_in[N_CONV],
////                                            hls::stream<ADD_IN_T> add_in[N_ADD],
////                                            hls::stream<OUTPUT_T>  output[N_OUTPUT]);
////
////template <typename CONV_IN_T, typename ADD_IN_T, typename OUTPUT_T, typename WEIGHTS, typename SCALES, typename BIASES, int N_CONV, int N_ADD, int N_OUTPUT>
////void one_conv_2d_large_stream_norm_resnet_addrelu (bool iReset,
////                                            hls::stream<CONV_IN_T> conv_in[N_CONV],
////                                            hls::stream<ADD_IN_T> add_in[N_ADD],
////                                            hls::stream<OUTPUT_T>  output[N_OUTPUT]);
////
//template <class INPUT_T, class POOL_LAYER_T, class CONV_LAYER_T, 
//          typename CONFIG_CONV, typename CONFIG_POOL,
//          int N_INPUT, int N_OUTPUT, int N_CONV_OUTPUT> 
////void conv_2d_large_stream_norm_nobias_pool (
////	                                        bool iReset,
////                                            hls::stream<INPUT_T> input[N_INPUT], 
////                                            hls::stream<POOL_LAYER_T> output[N_OUTPUT] 
////        );
//void conv_2d_large_stream_norm_nobias_pool (bool iReset, hls::stream<INPUT_T> input[N_INPUT], hls::stream<POOL_LAYER_T> output[N_OUTPUT], typename CONFIG_CONV::weight_t weights[CONFIG_CONV::filt_height * CONFIG_CONV::filt_width * CONFIG_CONV::n_chan * CONFIG_CONV::n_filt], typename CONFIG_CONV::norm_config::scale_t scale[CONFIG_CONV::n_filt], typename CONFIG_CONV::norm_config::bias_t sbiases[CONFIG_CONV::n_filt]);
//
//template <typename INPUT_T, typename LAYER_T, typename WEIGHTS, typename SCALES, typename BIASES, int N_INPUT, int N_OUTPUT>
//void conv_2d_large_stream_norm_nobias (
//	                                        bool iReset,
//                                            hls::stream<INPUT_T> input[N_INPUT], 
//                                            hls::stream<LAYER_T> output[N_OUTPUT] 
//        );
//
//void split_layer(bool iReset,
//                                            hls::stream<LAYER_T>  input[N],
//                                            hls::stream<LAYER_T> output_1[N],
//                                            hls::stream<LAYER_T> output_2[N]
//        );

//template <typename INPUT_T, typename CONV_LAYER_T, typename CONFIG, typename WEIGHTS, typename SCALES, typename BIASES, int N_INPUT, int N_CONV>
//void split_one_conv_2d_large_stream_norm_nobias (bool iReset,
//                                            hls::stream<INPUT_T>  input[N_INPUT],
//                                            hls::stream<CONV_LAYER_T> conv_out[N_CONV],
//                                            hls::stream<INPUT_T> split_out[N_INPUT]
//        );
//

#endif
