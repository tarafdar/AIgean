#include <cstddef>
#include <cstring>
#include <fstream>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "parameters_full.h"
#include "packet_size.h"
#include "galapagos_interface.hpp"
#include "kern.hpp"
#include "galapagos_resnet_bridge.hpp"
#include "conv_2d_large_cl.hpp"

#include "weights/w2.h"
#include "weights/b2.h"


#define TEST_SIZE 2048 


void send_image(input_t data_in[N_INPUT_2_1][N_INPUT_3_1][N_INPUT_1_1], galapagos_interface * out){
    

    int sub_image_size = 128;


    std::vector < std::vector<int> > image_index;

    for(int i=0; i<N_INPUT_3_1; i++){
        for(int j=0; j<N_INPUT_2_1; j++){
            std::vector<int> temp;
            temp.push_back(i);
            temp.push_back(j);
            image_index.push_back(temp);
        }
    }


    int num_sub_images = image_index.size()/sub_image_size;
    int remainder= image_index.size() % sub_image_size;

    for(int i=0; i<num_sub_images; i++){
        std::vector <std::vector<int>> sub_image;
        for(int ii=0; ii < sub_image_size; ii++){
            sub_image.push_back(image_index[i*sub_image_size + ii]);        
        }
        hls4ml_galapagos_output_bridge_4 (8, data_in, sub_image, out, 1);
    }

    std::vector <std::vector<int>> sub_image;
    for(int ii=0; ii< remainder; ii++){
        sub_image.push_back(image_index[num_sub_images*sub_image_size + ii]);        
    }

    if(remainder != 0) 
        hls4ml_galapagos_output_bridge_4 (8, data_in, sub_image, out, 1);


    //for(int i=0; i<N_INPUT_3_1 * N_INPUT_2_1; i+=sub_image_size){
    ////for(int i=0; i<4 * N_INPUT_2_1; i+=sub_image_size){
    //    std::vector <std::vector<int>> sub_image;
    //    for(int k=0; k<sub_image_size; k++){
    //        int ii=i/(N_INPUT_3_1+k);
    //        int jj=i%(N_INPUT_3_1+k);
    //        std::vector<int> temp;
    //        temp.push_back(ii);
    //        temp.push_back(jj);
    //        sub_image.push_back(temp);
    //    }
    //    hls4ml_galapagos_output_bridge_4 (8, data_in, sub_image, out, 1);

    //}

}

void read_tb_image(input_t image[N_INPUT_3_1][N_INPUT_2_1][N_INPUT_1_1]){

    std::ifstream fin("../tb_data/layer.in");
    for(int i2 = 0; i2 < N_INPUT_1_1-1; i2++) { 
        for(int i0 = 0; i0 < N_INPUT_2_1; i0++) { 
            for(int i1 = 0; i1 < N_INPUT_3_1; i1++) { 
	            input_t var;
	            fin >> var;
                image[i0][i1][i2+1] = var;
                if(i0 == 0 && i1== 0){
                    image[i0][i1][0] = 0;
                }
                else{
                    image[i0][i1][0] = 1;
                }
            }
        }
    }

    //for(int i0 = 0; i0 < N_INPUT_2_1; i0++) { 
    //    for(int i1 = 0; i1 < N_INPUT_3_1; i1++) { 
    //        for(int i2 = 0; i2 < N_INPUT_1_1; i2++) { 
    //            std::cout << "IMAGE PIXEL[" << i0 << "][" << i1 << "][" << i2 << "]=" << image[i0][i1][i2] << std::endl;
    //        }
    //    }
    //}
}

void write_tb_image_to_stream_file(input_t image[N_INPUT_3_1][N_INPUT_2_1][N_INPUT_1_1]){

    std::ofstream myFile[3];
    myFile[0].open("data_0.bin", std::ios::out | std::ios::binary);
    myFile[1].open("data_1.bin", std::ios::out | std::ios::binary);
    myFile[2].open("data_2.bin", std::ios::out | std::ios::binary);

    bool bigEndian = true;
    int offset = 1;
    //int end = (N_INPUT_1_1 * N_INPUT_2_1) - 1;
    int end = (N_INPUT_1_1 * N_INPUT_2_1);
    int pixel_index =0;
    for(int i0 = 0; i0 < N_INPUT_1_1; i0++) { 
        for(int i1 = 0; i1 < N_INPUT_2_1; i1++) { 
            for(int i2 = 0; i2 < N_INPUT_3_1; i2++) {
                ap_uint <32> temp = 0;
                if(bigEndian){
                    temp.range(31,24) = image[i0][i1][i2].range();
                    temp.range(23, 0) = 0;
                }
                else{
                    temp.range(7,0) = image[i0][i1][i2];
                    temp.range(31, 24) = 0;
                }
                if(pixel_index> offset && pixel_index < end)
                    myFile[i2].write((char *)&temp, sizeof(ap_uint<32>));
                else{
                    std::cout << "PIXEL: " << pixel_index << " CHANNEL: " << i2 << " " <<  std::hex << temp << std::dec << std::endl;

                }
            }
            pixel_index++;
        }
    }
    myFile[0].close();
    myFile[1].close();
    myFile[2].close();
}



void kern_send(short id, 
        galapagos_interface * in, 
        galapagos_interface  * out
        )
{


#pragma HLS INTERFACE axis register both port=out
#pragma HLS INTERFACE axis register both port=in


input_t image[N_INPUT_3_1][N_INPUT_2_1][N_INPUT_1_1];
read_tb_image(image);
//write_tb_image_to_stream_file(image);
send_image(image, out);

//for(int i=0; i< N_INPUT_1_1; i++){
//    for(int j=0; j< N_INPUT_2_1; j++){
//        if(i==0 && j==0)
//            send_pixel(true, image[i][j], out);
//        else
//            send_pixel(false, image[i][j], out);
//    }
//}

std::cout << "end of send" << std::endl;
    
//    for(int i=0; i< N_INPUT_1_1; i++){
//        for(int j=0; j< N_INPUT_2_1; j++){
//            static hls::stream<ap_uint<8> > test[TEST_SIZE];
//            hls4ml_galapagos_input_bridge <N_FILT_14> (in, test);
//            for(int k=0; k<N_FILT_14; k++){
//                if(!test[k].empty()){
//                    ap_uint<8> temp = test[k].read();
//                }
//            }
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

template <int size, class LAYER_T>
void print_buffer(std::string buffer_name, hls::stream<LAYER_T > buff[size]){

    while(!buff[0].empty()){
        for(int k=0; k<size; k++){
            LAYER_T data;
            data.range() = buff[k].read();
            std::cout << buffer_name << "[" << k << "]: " << std::hex << data.range() << std::dec << std::endl; 
            buff[k].write(data);
       }
    }

}

template <int size, class LAYER_T>
void drain_print_buffer(std::string buffer_name, hls::stream<LAYER_T > buff[size]){

    while(!buff[0].empty()){
        for(int k=0; k<size; k++){
        
            LAYER_T data;
            data.range() = buff[k].read();
            //if(k == 1){
                //std::cout << "SIZE OF " << buffer_name << std::dec << "[" << k << "]:" << buff[k].size() << std::endl;
                std::cout << buffer_name << "[" << k << "]: " << std::hex << data.range() << std::dec << std::endl; 
            //}
       }
    }

}


void kern_aigean(short id,
        galapagos_interface * in, 
        galapagos_interface  * out
)
{

    nnet::load_weights_from_txt<model_default_t, 4704>(w2, "w2.txt");
    nnet::load_weights_from_txt<bias2_t, 64>(b2, "b2.txt");

#if LOG_LEVEL>0
    std::cout << "FIRST:NUM WEIGHTS: " << std::dec << config2::filt_height * config2::filt_width * (config2::n_chan-1) * (config2::n_filt-1)/2 << std::endl;
    for(int w=0; w<config2::filt_height * config2::filt_width * (config2::n_chan-1) * (config2::n_filt-1)/2; w++){
        std::cout << "W[" << w << "]: " << w2[w] << std::endl;
    }

    std::cout << "FIRST:NUM BIASES: " << std::dec <<  config2::n_filt << std::endl;
    for(int b=0; b< config2::n_filt; b++){
        std::cout << "B[" << b << "]: " << b2[b] << std::endl;
    }
#endif
    
    static int counter = 0;
    static int pixel_index = 0;
    hls::stream<input_t > input[N_INPUT_1_1];


    for(int ii=0; ii<1; ii++){
        for(int i=0; i< N_INPUT_3_1; i++){
            for(int j=0; j< N_INPUT_2_1;){
                //std::cout << "PIXEL " << std::dec << pixel_index << std::endl; 
                if(!in->empty()){
                    hls4ml_galapagos_input_bridge <N_INPUT_1_1> (in, input);
                    j+=input[0].size();
                    pixel_index+=input[0].size(); 
                    //print_buffer<N_INPUT_1_1, input_t> (std::string("INPUT"), input);      
                }
            }
        }
    }

    std::cout << "STREAMED ENTIRE IMAGE" << std::endl;
    //Now we have entire image
    
    static hls::stream<layer4_t> layer4_out[N_FILT_2];
    while(!input[0].empty()){
        conv_2d_large_cl <input_t, layer4_t, config2, N_INPUT_1_1, N_FILT_2>
            (input, layer4_out, w2, b2);
        drain_print_buffer<N_FILT_2, layer4_t> (std::string("LAYER_2_OUT"), layer4_out);      
    }


    int conv_reps = 1000;
    std::cout << "INPUT DRAINED, RUNNING ANOTHER " << std::dec << conv_reps <<  " TIMES " << std::endl;

    for(int i=0;i<conv_reps;i++){
        conv_2d_large_cl <input_t, layer4_t, config2, N_INPUT_1_1, N_FILT_2>
            (input, layer4_out, w2, b2);
        drain_print_buffer<N_FILT_2, layer4_t> (std::string("LAYER_2_OUT"), layer4_out);      
    }
    
    std::cout << "num output pixels " << counter << std::endl;
    exit(0);

}
