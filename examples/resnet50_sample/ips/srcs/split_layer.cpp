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
//#include "layer_params.h"


//NEED TO DEFINE 
//N_INPUT, N_OUTPUT
//CONFIG
//INPUT_T, OUTPUT_T
void split_layer(bool iReset,
                                            hls::stream<LAYER_T>  input[N],
                                            hls::stream<LAYER_T> output_1[N],
                                            hls::stream<LAYER_T> output_2[N]
        )
{

#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE ap_ctrl_none port=iReset
#pragma HLS INTERFACE axis both port=input
#pragma HLS INTERFACE axis both port=output_1
#pragma HLS INTERFACE axis both port=output_2
    

    nnet::split<LAYER_T, LAYER_T, CONFIG>(input,output_1,output_2);
    



}
