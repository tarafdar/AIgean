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

//hls-fpga-machine-learning insert weights
#include "layer_params.h"



//NEED TO DEFINE INPUT_T 
//N_SPLIT_1, N_SPLIT_2, N_CONV_1, N_CONV_2
//CONFIG_SPLIT, CONFIG_CONV_1, CONFIG_CONV_2
//CONV_1_LAYER_T, CONV_2_LAYER_T
//IN_64, OUT_1_64, OUT_2_64 
//CONV_1_W,  CONV_1_S, CONV_1_B
//CONV_2_W,  CONV_2_S, CONV_2_B
//CONV_1_DEST, CONV_2_DEST
void split_two_conv_2d_large_stream_norm_nobias (bool iReset,
                                            hls::stream<INPUT_T>  input[N_INPUT],
                                            hls::stream<CONV_1_LAYER_T> conv_1_out[N_CONV_1],
                                            hls::stream<CONV_2_LAYER_T> conv_2_out[N_CONV_2]
        )
{

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE ap_ctrl_none port=iReset
#pragma HLS INTERFACE axis both port=input
#pragma HLS INTERFACE axis both port=conv_1_out
#pragma HLS INTERFACE axis both port=conv_2_out
    
    static hls::stream<INPUT_T>  split_out_1[N_SPLIT_1];
    #pragma HLS stream variable=split_out_1      depth=1
    static hls::stream<INPUT_T>  split_out_2[N_SPLIT_2];
    #pragma HLS stream variable=split_out_2     depth=1

    nnet::split<INPUT_T, INPUT_T, CONFIG_SPLIT>(input,split_out_1,split_out_2);
    
    if(!split_out_1[0].empty()) nnet::conv_2d_large_stream_norm_nobias<INPUT_T,CONV_1_LAYER_T, CONFIG_CONV_1>(iReset,split_out_1,conv_1_out,CONV_1_W,CONV_1_S,CONV_1_B);

    if(!split_out_2[0].empty()) nnet::conv_2d_large_stream_norm_nobias<CONV_1_LAYER_T,CONV_2_LAYER_T, CONFIG_CONV_2>(iReset,split_out_2,conv_2_out,CONV_2_W,CONV_2_S,CONV_2_B);


}

