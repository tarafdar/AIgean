#ifndef _GALAPAGOS_RESNET_BRIDGE
#define _GALAPAGOS_RESNET_BRIDGE

#include "resnet50.hpp"
#include "packet_size.h"
#ifdef CPU
#include "galapagos_interface.hpp"
#else
#include "galapagos_packet.h"
#endif

void _hls4ml_galapagos_input_bridge_write_words_3(
                                   galapagos_packet gp_in,
                                   int offset,
                                   hls::stream<resnet50_packet >  input[3])

{

    for(int j=0; j<3; j++){
#pragma HLS pipeline II=1 
        resnet50_packet packet;
        if(j == 0)
            packet.id.range() = gp_in.data(0, 0);
        packet.data.range() = gp_in.data((j+1)*8 + offset + 7, (j+1)*8 + offset );
        input[j].write(packet);
    }        
}

template <int width, int total_size, int index_offset>
void _hls4ml_galapagos_input_bridge_write_words(
                                   galapagos_packet gp_in,
                                   hls::stream<resnet50_packet >  input[total_size])

{

    for(int j=0; j<width; j++){
#pragma HLS pipeline II=1 
        resnet50_packet packet;
        if(j == 0)
            packet.id.range() = gp_in.data(0, 0);
        packet.data.range() = gp_in.data((j+1)*8  + 7, (j+1)*8);
        input[j+index_offset].write(packet);
    }        
}

template <int width, int total_size,const int index_offset>
void _hls4ml_galapagos_input_bridge_write_words(
                                   ap_uint<1> packet_reset,
                                   galapagos_packet gp_in,
                                   hls::stream<resnet50_packet >  input[total_size])

{

    for(int j=0; j<width; j++){
#pragma HLS pipeline II=1 
        resnet50_packet packet;
        packet.id.range() = packet_reset.range();
        packet.data.range() = gp_in.data((j)*8 + 7, j*8);
        input[j+index_offset].write(packet);
    }        
}

template <int width>
void _hls4ml_galapagos_input_bridge(galapagos_interface * bridge_in,
                                   hls::stream<resnet50_packet > input[width])
{
//cases 64 - 2048, loop explicitly rolled out to help hls, else non constant loop index gives poor result
    if (width == 3){
        galapagos_packet gp_in;
        gp_in = bridge_in->read();
        resnet50_packet packet;
        ap_uint<16> size;
        size.range() = gp_in.data.range(15,0);
        for(int i=0;i<size;i++){
            int offset = 16 + i * 4 * 8;
            _hls4ml_galapagos_input_bridge_write_words_3(gp_in, offset, input);
        }
    }
    else if(width == 64){
        galapagos_packet gp_in;
        gp_in = bridge_in->read();
        ap_uint <1> reset = gp_in.data.range(0,0);
        _hls4ml_galapagos_input_bridge_write_words<63, width, 0>(gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<1, width, 63>(reset, gp_in, input);
    }
    else if(width == 128){
        galapagos_packet gp_in;
        gp_in = bridge_in->read();
        ap_uint <1> reset = gp_in.data.range(0,0);
        _hls4ml_galapagos_input_bridge_write_words<63, width, 0>(gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 63>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<1, width, 127>(reset, gp_in, input);
    }
    else if(width == 256){
        galapagos_packet gp_in;
        gp_in = bridge_in->read();
        ap_uint <1> reset = gp_in.data.range(0,0);
        _hls4ml_galapagos_input_bridge_write_words<63, width, 0>(gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 63>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 127>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 191>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<1, width, 255>(reset, gp_in, input);
    }
    else if(width == 512){
        galapagos_packet gp_in;
        gp_in = bridge_in->read();
        ap_uint <1> reset = gp_in.data.range(0,0);
        _hls4ml_galapagos_input_bridge_write_words<63, width, 0>(gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 63>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 127>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 191>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 255>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 319>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 383>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 447>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<1, width, 511>(reset, gp_in, input);
    }
    else if(width == 1024){
        galapagos_packet gp_in;
        gp_in = bridge_in->read();
        ap_uint <1> reset = gp_in.data.range(0,0);
        _hls4ml_galapagos_input_bridge_write_words<63, width, 0>(gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 63>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 127>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 191>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 255>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 319>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 383>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 447>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 511>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 575>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 639>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 703>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 767>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 831>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 895>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 895>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 959>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<1, width, 1023>(reset, gp_in, input);
    }
    else if(width == 2048){
        galapagos_packet gp_in;
        gp_in = bridge_in->read();
        ap_uint <1> reset = gp_in.data.range(0,0);
        _hls4ml_galapagos_input_bridge_write_words<63, width, 0>(gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 63>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 127>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 191>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 255>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 319>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 383>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 447>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 511>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 575>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 639>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 703>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 767>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 831>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 895>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 895>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 959>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 1023>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 1087>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 1151>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 1215>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 1279>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 1343>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 1407>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 1471>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 1535>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 1599>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 1663>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 1727>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 1791>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 1855>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 1919>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<64, width, 1983>(reset, gp_in, input);
        gp_in = bridge_in->read();
        _hls4ml_galapagos_input_bridge_write_words<1, width, 2047>(reset, gp_in, input);
    }




//    else{
//        for(int i=0; i<=width/64; i++){
//            galapagos_packet gp_in;
//            gp_in = bridge_in->read();
//            int offset = 0;
//            ap_uint<1> packet_reset;
//            if(i==0){
//                _hls4ml_galapagos_input_bridge_write_words<63, width>(gp_in, 0,  offset, input);
//                packet_reset = gp_in.data.range(0,0);
//            }
//            else if(i == (width/64))
//                _hls4ml_galapagos_input_bridge_write_words<1, width>(packet_reset, gp_in, width - 1, offset, input);
//            else
//                _hls4ml_galapagos_input_bridge_write_words<64, width>(packet_reset, gp_in, (i*64) - 1,  offset, input);
//
//        }
//
//    }



}
                                   

template <int width, int total_size>
void _hls4ml_galapagos_output_bridge_read_words_3(
                                   bool reset,
                                   //int index_offset,
                                   galapagos_packet  & gp_out,
                                   int offset,
                                   hls::stream<resnet50_packet >  output[total_size])
{

    for(int j=0; j<width; j++){
#pragma HLS pipeline II=1 
        if(!output[j].empty()){
            resnet50_packet packet;
            packet = output[j].read();
            if(reset){
                if(j == 0)
                    gp_out.data(offset, offset) = packet.id.range();
                gp_out.data.range((j+1)*8 + offset + 7, (j+1)*8 + offset) = packet.data.range();
            }
            else
                gp_out.data.range((j)*8 + offset + 7, (j)*8 + offset) = packet.data.range();
        }
    }
}


template <int width, int total_size, int index_offset>
void _hls4ml_galapagos_output_bridge_read_words(
                                   bool reset,
                                   //int index_offset,
                                   galapagos_packet  & gp_out,
                                   hls::stream<resnet50_packet >  output[total_size])
{

    for(int j=0; j<width; j++){
#pragma HLS pipeline II=1 
        if(!output[j + index_offset].empty()){
            resnet50_packet packet;
            packet = output[j+index_offset].read();
            if(reset){
                if(j == 0)
                    gp_out.data(0, 0) = packet.id.range();
                gp_out.data.range((j+1)*8 + 7, (j+1)*8 ) = packet.data.range();
            }
            else
                gp_out.data.range((j)*8 + 7, (j)*8) = packet.data.range();
        }
    }
}

template<int width>
void _hls4ml_galapagos_output_bridge (
                                    ap_uint<16> size,
                                    hls::stream<resnet50_packet> output[width],
                                    galapagos_interface * bridge_output,
                                    const ap_uint <8> dest
                    )
{

    if(width == 3){
        galapagos_packet gp_out;
        gp_out.data.range(15,0) = size;
        gp_out.data = gp_out.data & 0x0ffff;
        for(int i=0; i<size; i++){
#pragma HLS pipeline II=1 
            int offset = 16 + i*4*8;
            _hls4ml_galapagos_output_bridge_read_words_3<3,3>(true, gp_out, offset, output);
        }
        gp_out.dest = dest;
        gp_out.last = 1;
        bridge_output->write(gp_out);
    }
    else if(width == 64){
        galapagos_packet gp_out;
        gp_out.last = 0;
        gp_out.dest = dest;
        _hls4ml_galapagos_output_bridge_read_words<63, 64, 0>(true, gp_out, output);
        bridge_output->write(gp_out);
        gp_out.last = 1;
        _hls4ml_galapagos_output_bridge_read_words<1, 64, 63>(false, gp_out, output);
        bridge_output->write(gp_out);
    }
    else if(width == 128){
        galapagos_packet gp_out;
        gp_out.last = 0;
        gp_out.dest = dest;
        _hls4ml_galapagos_output_bridge_read_words<63, width, 0>(true, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 63>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 63>(false, gp_out, output);
        gp_out.last = 1;
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<1, width, 127>(false, gp_out, output);
        bridge_output->write(gp_out);
    }
    else if(width == 256){
        galapagos_packet gp_out;
        gp_out.last = 0;
        gp_out.dest = dest;
        _hls4ml_galapagos_output_bridge_read_words<63, width, 0>(true, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 63>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 63>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 127>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 191>(false, gp_out, output);
        bridge_output->write(gp_out);
        gp_out.last = 1;
        _hls4ml_galapagos_output_bridge_read_words<1, width, 255>(false, gp_out, output);
        bridge_output->write(gp_out);
    }
    else if(width == 512){
        galapagos_packet gp_out;
        gp_out.last = 0;
        gp_out.dest = dest;
        _hls4ml_galapagos_output_bridge_read_words<63, width, 0>(true, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 63>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 63>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 127>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 191>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 255>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 319>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 383>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 447>(false, gp_out, output);
        bridge_output->write(gp_out);
        gp_out.last = 1;
        _hls4ml_galapagos_output_bridge_read_words<1, width, 511>(false, gp_out, output);
        bridge_output->write(gp_out);
    }
    else if(width == 1024){
        galapagos_packet gp_out;
        gp_out.last = 0;
        gp_out.dest = dest;
        _hls4ml_galapagos_output_bridge_read_words<63, width, 0>(true, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 63>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 63>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 127>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 191>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 255>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 319>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 383>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 447>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 511>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 511>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 575>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 639>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 703>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 767>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 831>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 895>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 895>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 959>(false, gp_out, output);
        bridge_output->write(gp_out);
        gp_out.last = 1;
        _hls4ml_galapagos_output_bridge_read_words<1, width, 1023>(false, gp_out, output);
        bridge_output->write(gp_out);
    }
    else if(width == 2048){
        galapagos_packet gp_out;
        gp_out.last = 0;
        gp_out.dest = dest;
        _hls4ml_galapagos_output_bridge_read_words<63, width, 0>(true, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 63>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 63>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 127>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 191>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 255>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 319>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 383>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 447>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 511>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 511>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 575>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 639>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 703>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 767>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 831>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 895>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 895>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 959>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 1023>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 1087>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 1151>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 1215>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 1279>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 1343>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 1407>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 1471>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 1535>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 1599>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 1663>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 1727>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 1791>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 1855>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 1919>(false, gp_out, output);
        bridge_output->write(gp_out);
        _hls4ml_galapagos_output_bridge_read_words<64, width, 1983>(false, gp_out, output);
        bridge_output->write(gp_out);
        gp_out.last = 1;
        _hls4ml_galapagos_output_bridge_read_words<1, width, 2047>(false, gp_out, output);
        bridge_output->write(gp_out);
    }
     
    
    
    
    
     
    
    
    
    
    //else{
    //    for(int i=0; i<=width/64; i++){
    //        galapagos_packet gp_out;
    //        gp_out.last = 0;
    //        gp_out.dest = dest;
    //        bool packet_reset;
    //        if(i==0){
    //            _hls4ml_galapagos_output_bridge_read_words<63, width>(true, 0, gp_out, 0, output);
    //        }
    //        else if(i == (width/64)){
    //            _hls4ml_galapagos_output_bridge_read_words<1, width>(false, width - 1, gp_out, 0, output);
    //            gp_out.last = 1;
    //        }
    //        else{
    //            _hls4ml_galapagos_output_bridge_read_words<64, width>(false, (i*64)- 1, gp_out, 0, output);
    //        }
    //        bridge_output->write(gp_out);

    //    }
    //}
}

template<int width>
void _hls4ml_galapagos_output_bridge (
                                    hls::stream<resnet50_packet> output[width],
                                    galapagos_interface * bridge_output,
                                    const ap_uint <8> dest
                    )
{

    _hls4ml_galapagos_output_bridge <256> (1, output, bridge_output, dest);
}
#endif
