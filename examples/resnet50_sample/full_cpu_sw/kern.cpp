#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "packet_size.h"
#include "galapagos_interface.hpp"
#include "kern.hpp"
#include "galapagos_resnet_bridge.hpp"
#include "conv_2d_large_stream_norm_nobias_pool.hpp"
#include "split_conv_2d_large_stream_norm_nobias.hpp"
#include "conv_2d_large_stream_norm_nobias.hpp"
#include "conv_2d_large_stream_norm_nobias_addrelu.hpp"

#include "weights/w2.h"
#include "weights/s3.h"
#include "weights/b3.h"
#include "weights/w6.h"
#include "weights/s7.h"
#include "weights/b7.h"
#include "weights/w9.h"
#include "weights/s10.h"
#include "weights/b10.h"
#include "weights/w12.h"
#include "weights/s13.h"
#include "weights/b13.h"
#include "weights/w14.h"
#include "weights/s15.h"
#include "weights/b15.h"


#define TEST_SIZE 2048 

void kern_send(short id, 
        galapagos_interface * in, 
        galapagos_interface  * out
        )
{


#pragma HLS INTERFACE axis register both port=out
#pragma HLS INTERFACE axis register both port=in
    
    int j=0;
    for(int i=0; i< N_INPUT_1_1; i++){
        for(int j=0; j< N_INPUT_2_1; j++){
            hls::stream<resnet50_packet> input[N_INPUT_3_1];
            resnet50_packet packet;
            if(j==0)
                packet.id = 1;

            packet.data.range() = ap_fixed<8,6>(4.2);
            input[0].write(packet);
            packet.data.range() = (ap_fixed<8,6>)6.5;
            input[1].write(packet);
            packet.data.range() = (ap_fixed<8,6>)9.5;
            input[2].write(packet);
            hls4ml_galapagos_output_bridge <3> ((ap_uint<16>) 1, input, out, 1);

        }
    }
    std::cout << "end of send" << std::endl;
    
//    for(int i=0; i< N_INPUT_1_1; i++){
//        for(int j=0; j< N_INPUT_2_1; j++){
            static hls::stream<resnet50_packet> test[TEST_SIZE];
            hls4ml_galapagos_input_bridge <N_FILT_14> (in, test);
            for(int k=0; k<N_FILT_14; k++){
                if(!test[k].empty()){
                    resnet50_packet temp = test[k].read();
                }
            }
//        }
//    }
    
    //for(int i=0; i< N_INPUT_1_1; i++){
    //    for(int j=0; j< N_INPUT_2_1; j++){
    //        static hls::stream<resnet50_packet> test[TEST_SIZE];
    //        hls4ml_galapagos_input_bridge <TEST_SIZE> (in, test);
    
    //        for(int k=0; k<TEST_SIZE; k++){
    //            if(!test[k].empty()){
    //                resnet50_packet temp = test[k].read();
    //            }
    //        }
    //    }
    //}
    //std::cout << "received everything" << std::endl;
    
}

void kern_aigean(short id,
        galapagos_interface * in, 
        galapagos_interface  * out
)
{


    
    
    static hls::stream<resnet50_packet> input[N_INPUT_3_1];
    for(int i=0; i< N_INPUT_1_1; i++){
        for(int j=0; j< N_INPUT_2_1; j++){
            hls4ml_galapagos_input_bridge <3> (in, input);
            //Now input has stream
            hls::stream<resnet50_packet> layer2_out[N_FILT_2];
    
            conv_2d_large_stream_norm_nobias_pool <input_t, layer5_t, layer2_t, config2, config5, N_INPUT_3_1, N_FILT_2, N_FILT_2> 
                               (input, layer2_out, w2, s3, b3);
    
            std::cout << " after layer2 " << std::endl;
            hls::stream<resnet50_packet> layer6_out[N_FILT_6];
            hls::stream<resnet50_packet> layer6_out_2[N_FILT_6];
            split_conv_2d_large_stream_norm_nobias <layer2_t, layer6_t, config6, N_FILT_2, N_FILT_6> 
                         (layer2_out, layer6_out, layer6_out_2, w6, s7, b7);
            std::cout << "after layer6" << std::endl;
            hls::stream<resnet50_packet> layer9_out[N_FILT_9];
            conv_2d_large_stream_norm_nobias <layer6_t, layer9_t, config9, N_FILT_6, N_FILT_9>(layer6_out, layer9_out, w9, s10, b10);
            std::cout << "after layer9" << std::endl;
            hls::stream<resnet50_packet> layer12_out[N_FILT_12];
            conv_2d_large_stream_norm_nobias <layer9_t, layer12_t, config12, N_FILT_9, N_FILT_12>(layer9_out, layer12_out, w12, s13, b13);
            std::cout << "after layer12" << std::endl;
            hls::stream<resnet50_packet> layer14_out[N_FILT_14];
            conv_2d_large_stream_norm_nobias_addrelu <layer12_t, layer6_t, layer14_t, config14,  N_FILT_6, N_FILT_12, N_FILT_14>  (layer6_out_2, layer12_out, layer14_out, w14, s15, b15);
            std::cout << "after layer14" << std::endl;
            hls4ml_galapagos_output_bridge <N_FILT_14> ((ap_uint<16>) 0, layer14_out, out, 0);
            std::cout << "after final out" << std::endl;
            
            //hls::stream<resnet50_packet> test[TEST_SIZE];
            //for(int k=0; k<TEST_SIZE;k++){
            //    resnet50_packet temp;
            //    temp.data = 42.0;
            //    temp.id = 1;
            //    test[k].write(temp);
            //}
            //hls4ml_galapagos_output_bridge <TEST_SIZE> ((ap_uint<16>) 0, test, out, 0);
            //std::cout << TEST_SIZE << "sent out" << std::endl;
        }
    }


       


}
