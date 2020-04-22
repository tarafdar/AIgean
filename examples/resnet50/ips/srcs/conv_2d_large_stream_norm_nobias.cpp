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
//N_INPUT, N_OUTPUT
//CONFIG
//LAYER_T
//WEIGHTS, SCALES, BIASES 
void conv_2d_large_stream_norm_nobias (
	                                        bool iReset,
                                            hls::stream<INPUT_T> input[N_INPUT], 
                                            hls::stream<LAYER_T> output[N_OUTPUT] 
        ){

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE ap_ctrl_none port=iReset
#pragma HLS INTERFACE axis both port=input
#pragma HLS INTERFACE axis both port=output

#pragma HLS DATAFLOW


    
    if(!input[0].empty()) nnet::conv_2d_large_stream_norm_nobias<INPUT_T,LAYER_T,CONFIG>(iReset,input,output, WEIGHTS, SCALES, BIASES);
    

}
