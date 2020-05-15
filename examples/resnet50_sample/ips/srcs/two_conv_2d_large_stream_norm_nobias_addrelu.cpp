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



//NEED TO DEFINE
// N_CONV, N_ADD, N_OUTPUT
// ADD_IN_T, CONV_IN_T, OUTPUT_T
// WEIGHTS, SCALES, BIASES
// N_CONV_OUT

void two_conv_2d_large_stream_norm_nobias_addrelu (bool iReset,
                                            hls::stream<CONV_1_IN_T> conv_1_in[N_CONV_1],
                                            hls::stream<CONV_2_IN_T> conv_2_in[N_CONV_2],
                                            hls::stream<OUTPUT_T>  output[N_OUTPUT]
        )
{

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE ap_ctrl_none port=iReset
#pragma HLS INTERFACE axis both port=conv_in
#pragma HLS INTERFACE axis both port=add_in
#pragma HLS INTERFACE axis both port=output

//    static hls::stream<layer9_t> layer9_out[N_FILT_9];
//    #pragma HLS stream variable=layer9_out      depth=1
//    if(!layer6_out[0].empty()) nnet::conv_2d_large_stream_norm_nobias<layer6_t,layer9_t,config9>(iReset,layer6_out,layer9_out,w9,s10,b10);
//
//    static hls::stream<layer12_t> layer12_out[N_FILT_12];
//    #pragma HLS stream variable=layer12_out      depth=1
//    if(!layer9_out[0].empty()) nnet::conv_2d_large_stream_norm_nobias<layer9_t,layer12_t,config12>(iReset,layer9_out,layer12_out,w12,s13,b13);
//
//    static hls::stream<layer14_t> layer14_out2[N_FILT_14];
//    #pragma HLS stream variable=layer14_out2      depth=1
//    if(!layer12_out[0].empty() && !layer14_out[0].empty()) nnet::addrelu<layer12_t,result_t,config14>(layer12_out,layer14_out,layer14_out2);
//

    if(!conv_in[0].empty()) nnet::conv_2d_large_stream_norm_nobias<CONV_IN_T,ADD_IN_T,CONFIG_CONV>(iReset,conv_in,conv_out,WEIGHTS,SCALES,BIASES);

    static hls::stream<ADD_IN_T> conv_out[N_CONV_OUT];
    #pragma HLS stream variable=conv_out      depth=1

    if(!conv_out[0].empty() && !add_in[0].empty()) nnet::addrelu<ADD_IN_T,OUTPUT_T,CONFIG_ADD>(add_in,conv_out,output);


}

