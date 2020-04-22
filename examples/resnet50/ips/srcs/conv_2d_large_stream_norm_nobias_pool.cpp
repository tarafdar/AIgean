//
//
//    Copyright (C) 2017 EJ Kreinar
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include <iostream>

#include "myproject_full.h"

#include "layer_params.h"


//NEED TO DEFINE INPUT_T,  
//N_INPUT, N_CONV_OUTPUT, N_OUTPUT
//CONFIG_CONV, CONFIG_POOL
//CONV_LAYER_T, POOL_LAYER_T
//WEIGHTS, SCALES, BIASES 
void conv_2d_large_stream_norm_nobias_pool (
	                                        bool iReset,
                                            hls::stream<INPUT_T> input[N_INPUT], 
                                            hls::stream<POOL_LAYER_T> output[N_OUTPUT] 
                                            //galapagos_interface * in_net,
                                            //galapagos_interface * out_net
        ){

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE ap_ctrl_none port=iReset
#pragma HLS INTERFACE axis both port=input
#pragma HLS INTERFACE axis both port=output

#pragma HLS DATAFLOW


    
    hls::stream<CONV_LAYER_T> conv_output[N_CONV_OUTPUT];
 #pragma HLS stream variable=conv_output      depth=1
    
    if(!input[0].empty()) nnet::conv_2d_large_stream_norm_nobias<INPUT_T,CONV_LAYER_T,CONFIG_CONV>(iReset,input,conv_output, WEIGHTS, SCALES, BIASES);
    


    if(!conv_output[0].empty()) nnet::pool_2d_large_stream<CONV_LAYER_T, POOL_LAYER_T, CONFIG_POOL>(conv_output,output);
    

}
