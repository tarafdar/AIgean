#include "galapagos_packet.h"


void hls4ml_galapagos_input_bridge_one_in_3 (galapagos_interface * bridge_in,
                                           hls::stream<ap_uint<8> > input[3],
                                           volatile ap_uint <1> * iReset_out
                    )
{
#pragma HLS INTERFACE axis both port=bridge_in
#pragma HLS INTERFACE axis both port=input
#pragma HLS INTERFACE ap_none port=iReset_out
#pragma HLS INTERFACE ap_ctrl_none port=return


    static enum dstate{
        IDLE=0,
        TOGGLE_RESET,
        READ
    } state =IDLE;
    
    static ap_uint <1> iReset_internal = 0;

    
    switch(state){
        case IDLE:{
            if(!bridge_in->empty()){
                iReset_internal = 1;
                state = TOGGLE_RESET;
            }
            break;
        }
        case TOGGLE_RESET:{
            iReset_internal = 0;
            state = READ;
            break;
        }
        case READ:{
            iReset_internal = 0;
            galapagos_packet gp_in;
            gp_in = bridge_in->read();
            for(int i=0; i<3; i++){
#pragma HLS pipeline II=1 
                input[i].write(gp_in.data((i+1)*8-1,i*8));
            }
            break;
        }
        default:{
            iReset_internal = 0;
            break;
        }
    }

    *iReset_out = iReset_internal;
}

void hls4ml_galapagos_input_bridge_one_in_64 (galapagos_interface * bridge_in,
                                           hls::stream<ap_uint<8> > input[64],
                                           volatile ap_uint <1> * iReset_out
                    )
{
#pragma HLS INTERFACE axis both port=bridge_in
#pragma HLS INTERFACE axis both port=input
#pragma HLS INTERFACE ap_none port=iReset_out
#pragma HLS INTERFACE ap_ctrl_none port=return


    static enum dstate{
        IDLE=0,
        TOGGLE_RESET,
        READ
    } state =IDLE;
    
    static ap_uint <1> iReset_internal = 0;

    
    switch(state){
        case IDLE:{
            if(!bridge_in->empty()){
                iReset_internal = 1;
                state = TOGGLE_RESET;
            }
            break;
        }
        case TOGGLE_RESET:{
            iReset_internal = 0;
            state = READ;
            break;
        }
        case READ:{
            iReset_internal = 0;
            galapagos_packet gp_in;
            gp_in = bridge_in->read();
            for(int i=0; i<64; i++){
#pragma HLS pipeline II=1 
                input[i].write(gp_in.data((i+1)*8-1,i*8));
            }
            break;
        }
        default:{
            iReset_internal = 0;
            break;
        }
    }

    *iReset_out = iReset_internal;
}

void hls4ml_galapagos_input_bridge_one_in_128 (galapagos_interface * bridge_in,
                                           hls::stream<ap_uint<8> > input[128],
                                           volatile ap_uint <1> * iReset_out
                    )
{
#pragma HLS INTERFACE axis both port=bridge_in
#pragma HLS INTERFACE axis both port=input
#pragma HLS INTERFACE ap_none port=iReset_out
#pragma HLS INTERFACE ap_ctrl_none port=return


    static enum dstate{
        IDLE=0,
        TOGGLE_RESET,
        READ
    } state =IDLE;
    
    static ap_uint <1> iReset_internal = 0;

    
    switch(state){
        case IDLE:{
            if(!bridge_in->empty()){
                iReset_internal = 1;
                state = TOGGLE_RESET;
            }
            break;
        }
        case TOGGLE_RESET:{
            iReset_internal = 0;
            state = READ;
            break;
        }
        case READ:{
            iReset_internal = 0;
            for(int i=0; i<2; i++){
#pragma HLS unroll
                galapagos_packet gp_in;
                gp_in = bridge_in->read();
                for(int j=0; j<64; j++){
#pragma HLS pipeline II=1 
                    input[j+(i*64)].write(gp_in.data((j+1)*8 - 1, j*8));
                }
            }
            break;
        }
        default:{
            iReset_internal = 0;
            break;
        }
    }

    *iReset_out = iReset_internal;
}

void hls4ml_galapagos_input_bridge_one_in_256 (galapagos_interface * bridge_in,
                                           hls::stream<ap_uint<8> > input[256],
                                           volatile ap_uint <1> * iReset_out
                    )
{
#pragma HLS INTERFACE axis both port=bridge_in
#pragma HLS INTERFACE axis both port=input
#pragma HLS INTERFACE ap_none port=iReset_out
#pragma HLS INTERFACE ap_ctrl_none port=return


    static enum dstate{
        IDLE=0,
        TOGGLE_RESET,
        READ
    } state =IDLE;
    
    static ap_uint <1> iReset_internal = 0;

    
    switch(state){
        case IDLE:{
            if(!bridge_in->empty()){
                iReset_internal = 1;
                state = TOGGLE_RESET;
            }
            break;
        }
        case TOGGLE_RESET:{
            iReset_internal = 0;
            state = READ;
            break;
        }
        case READ:{
            iReset_internal = 0;
            for(int i=0; i<4; i++){
#pragma HLS unroll
                galapagos_packet gp_in;
                gp_in = bridge_in->read();
                for(int j=0; j<64; j++){
#pragma HLS pipeline II=1 
                    input[j+(i*64)].write(gp_in.data((j+1)*8 - 1, j*8));
                }
            }
            break;
        }
        default:{
            iReset_internal = 0;
            break;
        }
    }

    *iReset_out = iReset_internal;
}

void hls4ml_galapagos_input_bridge_one_in_512 (galapagos_interface * bridge_in,
                                           hls::stream<ap_uint<8> > input[512],
                                           volatile ap_uint <1> * iReset_out
                    )
{
#pragma HLS INTERFACE axis both port=bridge_in
#pragma HLS INTERFACE axis both port=input
#pragma HLS INTERFACE ap_none port=iReset_out
#pragma HLS INTERFACE ap_ctrl_none port=return


    static enum dstate{
        IDLE=0,
        TOGGLE_RESET,
        READ
    } state =IDLE;
    
    static ap_uint <1> iReset_internal = 0;

    
    switch(state){
        case IDLE:{
            if(!bridge_in->empty()){
                iReset_internal = 1;
                state = TOGGLE_RESET;
            }
            break;
        }
        case TOGGLE_RESET:{
            iReset_internal = 0;
            state = READ;
            break;
        }
        case READ:{
            iReset_internal = 0;
            for(int i=0; i<8; i++){
#pragma HLS unroll
                galapagos_packet gp_in;
                gp_in = bridge_in->read();
                for(int j=0; j<64; j++){
#pragma HLS pipeline II=1 
                    input[j+(i*64)].write(gp_in.data((j+1)*8 - 1, j*8));
                }
            }
            break;
        }
        default:{
            iReset_internal = 0;
            break;
        }
    }

    *iReset_out = iReset_internal;
}

void hls4ml_galapagos_input_bridge_one_in_1024 (galapagos_interface * bridge_in,
                                           hls::stream<ap_uint<8> > input[1024],
                                           volatile ap_uint <1> * iReset_out
                    )
{
#pragma HLS INTERFACE axis both port=bridge_in
#pragma HLS INTERFACE axis both port=input
#pragma HLS INTERFACE ap_none port=iReset_out
#pragma HLS INTERFACE ap_ctrl_none port=return


    static enum dstate{
        IDLE=0,
        TOGGLE_RESET,
        READ
    } state =IDLE;
    
    static ap_uint <1> iReset_internal = 0;

    
    switch(state){
        case IDLE:{
            if(!bridge_in->empty()){
                iReset_internal = 1;
                state = TOGGLE_RESET;
            }
            break;
        }
        case TOGGLE_RESET:{
            iReset_internal = 0;
            state = READ;
            break;
        }
        case READ:{

            iReset_internal = 0;
            for(int i=0; i<16; i++){
#pragma HLS unroll
                galapagos_packet gp_in;
                gp_in = bridge_in->read();
                for(int j=0; j<64; j++){
#pragma HLS pipeline II=1 
                    input[j+(i*64)].write(gp_in.data((j+1)*8 - 1, j*8));
                }
            }
            break;
        }
        default:{
            iReset_internal = 0;
            break;
        }
    }

    *iReset_out = iReset_internal;
}

void hls4ml_galapagos_input_bridge_one_in_2048 (galapagos_interface * bridge_in,
                                           hls::stream<ap_uint<8> > input[2048],
                                           volatile ap_uint <1> * iReset_out
                    )
{
#pragma HLS INTERFACE axis both port=bridge_in
#pragma HLS INTERFACE axis both port=input
#pragma HLS array_partition variable=input block factor=1024 dim=0
#pragma HLS INTERFACE ap_none port=iReset_out
#pragma HLS INTERFACE ap_ctrl_none port=return


    static enum dstate{
        IDLE=0,
        TOGGLE_RESET,
        READ
    } state =IDLE;
    
    static ap_uint <1> iReset_internal = 0;

    
    switch(state){
        case IDLE:{
            if(!bridge_in->empty()){
                iReset_internal = 1;
                state = TOGGLE_RESET;
            }
            break;
        }
        case TOGGLE_RESET:{
            iReset_internal = 0;
            state = READ;
            break;
        }
        case READ:{
            iReset_internal = 0;
            for(int i=0; i<32; i++){
#pragma HLS unroll
                galapagos_packet gp_in;
                gp_in = bridge_in->read();
                for(int j=0; j<64; j++){
#pragma HLS pipeline II=1 
                    input[j+(i*64)].write(gp_in.data((j+1)*8 - 1, j*8));
                }
            }
            break;
        }
        default:
            iReset_internal = 0;
            break;
    }

    *iReset_out = iReset_internal;
}




void hls4ml_galapagos_input_bridge_one_in (galapagos_interface * bridge_in,
                                           hls::stream<ap_uint<8> > input[1024],
                                           const ap_uint <16> width,
                                           volatile ap_uint <1> * iReset_out
                    )
{
#pragma HLS INTERFACE axis both port=bridge_in
#pragma HLS INTERFACE axis both port=input
#pragma HLS INTERFACE ap_none port=iReset_out
#pragma HLS INTERFACE ap_ctrl_none port=width
#pragma HLS INTERFACE ap_ctrl_none port=return


    static enum dstate{
            IDLE=0,
            TOGGLE_RESET,
            READ_3,
            READ_64,
            READ_128,
            READ_256,
            READ_512,
            READ_1024//,
//            READ_2048
    }   state = IDLE;


    
    static ap_uint <1> iReset_internal = 0;
    *iReset_out = iReset_internal;

    switch(state){
        case IDLE:{
            if(!bridge_in->empty()){
                iReset_internal = 1;
                state = TOGGLE_RESET;
            }
            break;
        }
        case TOGGLE_RESET:{
            iReset_internal = 0;
            if(width == 64){
                state = READ_64;
            }
            else if(width == 128){
                state = READ_128;
            }
            else if(width == 256){
                state = READ_256;
            }
            else if(width == 512){
                state = READ_512;
            }
            else if(width == 3){
                state = READ_3;
            }
            break;
        }
        case READ_3:{
            iReset_internal = 0;
            galapagos_packet gp_in;
            gp_in = bridge_in->read();
            for(int i=0; i<3; i++){
#pragma HLS pipeline II=1 
                input[i].write(gp_in.data((i+1)*8-1,i*8));
            }
            state = IDLE;
            break;
        }
        case READ_64:{
            iReset_internal = 0;
            galapagos_packet gp_in;
            gp_in = bridge_in->read();
            for(int i=0; i<64; i++){
#pragma HLS pipeline II=1 
                input[i].write(gp_in.data((i+1)*8-1,i*8));
            }
            state = IDLE;
            break;
        }
        case READ_128:{
            iReset_internal = 0;
            for(int i=0; i<2; i++){
#pragma HLS unroll
                galapagos_packet gp_in;
                gp_in = bridge_in->read();
                for(int j=0; j<64; j++){
#pragma HLS pipeline II=1 
                    input[j+(i*64)].write(gp_in.data((j+1)*8 - 1, j*8));
                }
            }
            state = IDLE;
            break;

        }

        case READ_256:{
            iReset_internal = 0;
            for(int i=0; i<4; i++){
#pragma HLS unroll
                galapagos_packet gp_in;
                gp_in = bridge_in->read();
                for(int j=0; j<64; j++){
#pragma HLS pipeline II=1 
                    input[j+(i*64)].write(gp_in.data((j+1)*8 - 1, j*8));
                }
            }
            state = IDLE;
            break;

        }
        case READ_512:{
            iReset_internal = 0;
            for(int i=0; i<8; i++){
#pragma HLS unroll
                galapagos_packet gp_in;
                gp_in = bridge_in->read();
                for(int j=0; j<64; j++){
#pragma HLS pipeline II=1 
                    input[j+(i*64)].write(gp_in.data((j+1)*8 - 1, j*8));
                }
            }
            state = IDLE;
            break;
        }
        case READ_1024:{
            iReset_internal = 0;
            for(int i=0; i<16; i++){
#pragma HLS unroll
                galapagos_packet gp_in;
                gp_in = bridge_in->read();
                for(int j=0; j<64; j++){
#pragma HLS pipeline II=1 
                    input[j+(i*64)].write(gp_in.data((j+1)*8 - 1, j*8));
                }
            }
            state = IDLE;
            break;
        }
//        case READ_2048:{
//            iReset_internal = 0;
//            for(int i=0; i<32; i++){
//#pragma HLS unroll
//                galapagos_packet gp_in;
//                gp_in = bridge_in->read();
//                for(int j=0; j<64; j++){
//#pragma HLS pipeline II=1 
//                    input[j+(i*64)].write(gp_in.data((j+1)*8 - 1, j*8));
//                }
//            }
//            state = IDLE;
//            break;
//        }
        default:
            iReset_internal = 0;
            break;

    }

    *iReset_out = iReset_internal;


}

void hls4ml_galapagos_output_bridge_64 (
                                    hls::stream<ap_uint<8> > output[64],
                                    galapagos_interface * bridge_output,
                                    const ap_uint <8> dest
                    )
{

#pragma HLS INTERFACE axis both port=bridge_out
#pragma HLS INTERFACE axis both port=output
#pragma HLS INTERFACE ap_ctrl_none port=dest
#pragma HLS INTERFACE ap_ctrl_none port=return

    galapagos_packet gp_out;
    for(int j=0; j<64; j++){
#pragma HLS pipeline II=1 
        gp_out.data((j+1)*8-1, j*8) = output[j].read();
    }
    gp_out.dest = dest;
    bridge_output->write(gp_out);
}

void hls4ml_galapagos_output_bridge_128 (
                                    hls::stream<ap_uint<8> > output[128],
                                    galapagos_interface * bridge_output,
                                    const ap_uint <8> dest
                    )
{

#pragma HLS INTERFACE axis both port=bridge_out
#pragma HLS INTERFACE axis both port=output
#pragma HLS INTERFACE ap_ctrl_none port=dest
#pragma HLS INTERFACE ap_ctrl_none port=return

    for(int i=0; i<2; i++){
        galapagos_packet gp_out;
        for(int j=0; j<64; j++){
#pragma HLS pipeline II=1 
            gp_out.data((j+1)*8-1, j*8) = output[j+(i*64)].read();
        }
        gp_out.dest = dest;
        bridge_output->write(gp_out);
    }

}

void hls4ml_galapagos_output_bridge_256 (
                                    hls::stream<ap_uint<8> > output[256],
                                    galapagos_interface * bridge_output,
                                    const ap_uint <8> dest
                    )
{

#pragma HLS INTERFACE axis both port=bridge_out
#pragma HLS INTERFACE axis both port=output
#pragma HLS INTERFACE ap_ctrl_none port=dest
#pragma HLS INTERFACE ap_ctrl_none port=return

    for(int i=0; i<4; i++){
        galapagos_packet gp_out;
        for(int j=0; j<64; j++){
#pragma HLS pipeline II=1 
            gp_out.data((j+1)*8-1, j*8) = output[j+(i*64)].read();
        }
        gp_out.dest = dest;
        bridge_output->write(gp_out);
    }

}

void hls4ml_galapagos_output_bridge_512 (
                                    hls::stream<ap_uint<8> > output[512],
                                    galapagos_interface * bridge_output,
                                    const ap_uint <8> dest
                    )
{

#pragma HLS INTERFACE axis both port=bridge_out
#pragma HLS INTERFACE axis both port=output
#pragma HLS INTERFACE ap_ctrl_none port=dest
#pragma HLS INTERFACE ap_ctrl_none port=return

    for(int i=0; i<8; i++){
        galapagos_packet gp_out;
        for(int j=0; j<64; j++){
#pragma HLS pipeline II=1 
            gp_out.data((j+1)*8-1, j*8) = output[j+(i*64)].read();
        }
        gp_out.dest = dest;
        bridge_output->write(gp_out);
    }

}

void hls4ml_galapagos_output_bridge_1024 (
                                    hls::stream<ap_uint<8> > output[1024],
                                    galapagos_interface * bridge_output,
                                    const ap_uint <8> dest
                    )
{

#pragma HLS INTERFACE axis both port=bridge_out
#pragma HLS INTERFACE axis both port=output
#pragma HLS INTERFACE ap_ctrl_none port=dest
#pragma HLS INTERFACE ap_ctrl_none port=return

    for(int i=0; i<16; i++){
        galapagos_packet gp_out;
        for(int j=0; j<64; j++){
#pragma HLS pipeline II=1 
            gp_out.data((j+1)*8-1, j*8) = output[j+(i*64)].read();
        }
        gp_out.dest = dest;
        bridge_output->write(gp_out);
    }

}

void hls4ml_galapagos_output_bridge_2048 (
                                    hls::stream<ap_uint<8> > output[2048],
                                    galapagos_interface * bridge_output,
                                    const ap_uint <8> dest
                    )
{

#pragma HLS INTERFACE axis both port=bridge_out
#pragma HLS INTERFACE axis both port=output
#pragma HLS array_partition variable=output block factor=1024 dim=0
#pragma HLS INTERFACE ap_ctrl_none port=dest
#pragma HLS INTERFACE ap_ctrl_none port=return

    for(int i=0; i<32; i++){
        galapagos_packet gp_out;
        for(int j=0; j<64; j++){
#pragma HLS pipeline II=1 
            gp_out.data((j+1)*8-1, j*8) = output[j+(i*64)].read();
        }
        gp_out.dest = dest;
        bridge_output->write(gp_out);
    }

}





void hls4ml_galapagos_output_bridge (
                                    hls::stream<ap_uint<8> > output[1024],
                                    galapagos_interface * bridge_output,
                                    const ap_uint <8> dest,
                                    const ap_uint <16> width
                    )
{
#pragma HLS INTERFACE axis both port=bridge_out
#pragma HLS INTERFACE axis both port=output
#pragma HLS INTERFACE ap_ctrl_none port=width
#pragma HLS INTERFACE ap_ctrl_none port=dest
#pragma HLS INTERFACE ap_ctrl_none port=return

    if(width == 64){
        galapagos_packet gp_out;
        for(int j=0; j<64; j++){
#pragma HLS pipeline II=1 
            gp_out.data((j+1)*8-1, j*8) = output[j].read();
        }
        gp_out.dest = dest;
        bridge_output->write(gp_out);
    }
    else if (width == 128){
        for(int i=0; i<2; i++){
            galapagos_packet gp_out;
            for(int j=0; j<64; j++){
#pragma HLS pipeline II=1 
                gp_out.data((j+1)*8-1, j*8) = output[j+(i*64)].read();
            }
            gp_out.dest = dest;
            bridge_output->write(gp_out);
        }
    }
    else if (width == 256){
        for(int i=0; i<4; i++){
            galapagos_packet gp_out;
            for(int j=0; j<64; j++){
#pragma HLS pipeline II=1 
                gp_out.data((j+1)*8-1, j*8) = output[j+(i*64)].read();
            }
            gp_out.dest = dest;
            bridge_output->write(gp_out);
        }


    }
    else if (width == 512){
        for(int i=0; i<8; i++){
            galapagos_packet gp_out;
            for(int j=0; j<64; j++){
#pragma HLS pipeline II=1 
                gp_out.data((j+1)*8-1, j*8) = output[j+(i*64)].read();
            }
            gp_out.dest = dest;
            bridge_output->write(gp_out);
        }
    }
    else if (width == 1024){
        for(int i=0; i<16; i++){
            galapagos_packet gp_out;
            for(int j=0; j<64; j++){
#pragma HLS pipeline II=1 
                gp_out.data((j+1)*8-1, j*8) = output[j+(i*64)].read();
            }
            gp_out.dest = dest;
            bridge_output->write(gp_out);
        }
    }
//    else if (width == 2048){
//        for(int i=0; i<32; i++){
//            galapagos_packet gp_out;
//            for(int j=0; j<64; j++){
//#pragma HLS pipeline II=1 
//                gp_out.data((j+1)*8-1, j*8) = output[j+(i*64)].read();
//            }
//            gp_out.dest = dest;
//            bridge_output->write(gp_out);
//        }
//    }
}


//void galapagos_bridge_64_in(galapagos_interface * bridge_in,
//                        hls::stream<ap_uint<8> >  input[64]
//        )
//{
//#pragma HLS INTERFACE axis both port=bridge_in
//#pragma HLS INTERFACE axis both port=input
//
//    galapagos_packet gp_in;
//    gp_in = bridge_in->read();
//    for(int i=0; i<64; i++){
//#pragma HLS pipeline II=1 
//        input[i].write(gp_in.data((i+1)*8-1,i*8));
//    }
//
//
//}
//
//void galapagos_bridge_64_out(ap_uint<8> dest,
//                    hls::stream<ap_uint<8> > output[64],
//                    galapagos_interface * bridge_out
//        )
//{
//#pragma HLS INTERFACE axis both port=bridge_out
//#pragma HLS INTERFACE axis both port=output
//
//        galapagos_packet gp_out;
//        for(int j=0; j<64; j++){
//#pragma HLS pipeline II=1 
//            gp_out.data((j+1)*8-1, j*8) = output[j].read();
//        }
//        gp_out.dest = dest;
//        bridge_out->write(gp_out);
//
//        
//}
//
//void galapagos_bridge_256_in(galapagos_interface * bridge_in,
//                        hls::stream<ap_uint<8> >  input[256]
//        )
//{
//#pragma HLS INTERFACE axis both port=bridge_in
//#pragma HLS INTERFACE axis both port=input
//
//    
//    for(int i=0; i<4; i++){
//        galapagos_packet gp_in;
//        gp_in = bridge_in->read();
//        for(int j=0; j<64; j++){
//#pragma HLS pipeline II=1 
//            input[j+(i*64)].write(gp_in.data((j+1)*8 - 1, j*8));
//       }
//    }
//}

//void galapagos_bridge_256_out(ap_uint<8> dest,
//                    hls::stream<ap_uint<8> > output[256],
//                    galapagos_interface * bridge_out
//        )
//{
//#pragma HLS INTERFACE axis both port=bridge_out
//#pragma HLS INTERFACE axis both port=output
//    
//    for(int i=0; i<4; i++){
//        galapagos_packet gp_out;
//        for(int j=0; j<64; j++){
//#pragma HLS pipeline II=1 
//            gp_out.data((j+1)*8-1, j*8) = output[j+(i*64)].read();
//        }
//        gp_out.dest = dest;
//        bridge_out->write(gp_out);
//    }
//}
//
