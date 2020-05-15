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






template <typename CONV_IN_T, typename ADD_IN_T, typename OUTPUT_T, typename WEIGHTS, typename SCALES, tyepname BIASES, int N_CONV, int N_ADD, int N_OUTPUT>
void one_conv_2d_large_stream_norm_nobias_addrelu (bool iReset,
                                            hls::stream<CONV_IN_T> conv_in[N_CONV],
                                            hls::stream<ADD_IN_T> add_in[N_ADD],
                                            hls::stream<OUTPUT_T>  output[N_OUTPUT]
        )
{

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE ap_ctrl_none port=iReset
#pragma HLS INTERFACE axis both port=conv_in
#pragma HLS INTERFACE axis both port=add_in
#pragma HLS INTERFACE axis both port=output



    static hls::stream<ADD_IN_T> conv_out[N_CONV_OUT];
    #pragma HLS stream variable=conv_out      depth=1
    
    if(!conv_in[0].empty()) nnet::conv_2d_large_stream_norm_nobias<CONV_IN_T,ADD_IN_T,CONFIG>(iReset,conv_in,conv_out,WEIGHTS,SCALES,BIASES);


    if(!conv_out[0].empty() && !add_in[0].empty()) nnet::addrelu<ADD_IN_T,OUTPUT_T,CONFIG>(add_in,conv_out,output);


}

