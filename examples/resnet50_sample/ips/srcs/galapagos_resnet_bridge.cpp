
#include "_galapagos_resnet_bridge.hpp"


void hls4ml_galapagos_input_bridge_3(galapagos_interface * bridge_in,
                                   hls::stream<resnet50_packet > input[3])
{
#pragma HLS INTERFACE axis register both port=bridge_in
#pragma HLS INTERFACE axis register both port=input
#pragma HLS array_partition variable=input
#pragma HLS INTERFACE ap_ctrl_none port=return
    _hls4ml_galapagos_input_bridge <3> (bridge_in, input);
}
                                   

void hls4ml_galapagos_input_bridge_64(galapagos_interface * bridge_in,
                                   hls::stream<resnet50_packet > input[64])
{

#pragma HLS INTERFACE axis register both port=bridge_in
#pragma HLS array_partition variable=input
#pragma HLS INTERFACE ap_ctrl_none port=return
    _hls4ml_galapagos_input_bridge <64> (bridge_in, input);
}
                                   
void hls4ml_galapagos_input_bridge_128(galapagos_interface * bridge_in,
                                   hls::stream<resnet50_packet > input[128])
{

#pragma HLS INTERFACE axis register both port=bridge_in
#pragma HLS array_partition variable=input
#pragma HLS INTERFACE ap_ctrl_none port=return
    _hls4ml_galapagos_input_bridge <128> (bridge_in, input);
}
                                   

void hls4ml_galapagos_input_bridge_256(galapagos_interface * bridge_in,
                                   hls::stream<resnet50_packet > input[256])
{

#pragma HLS INTERFACE axis register both port=bridge_in
#pragma HLS array_partition variable=input
#pragma HLS INTERFACE ap_ctrl_none port=return
    _hls4ml_galapagos_input_bridge <256> (bridge_in, input);
}
                                   

void hls4ml_galapagos_input_bridge_512(galapagos_interface * bridge_in,
                                   hls::stream<resnet50_packet > input[512])
{

#pragma HLS INTERFACE axis register both port=bridge_in
#pragma HLS array_partition variable=input
#pragma HLS INTERFACE ap_ctrl_none port=return
    _hls4ml_galapagos_input_bridge <512> (bridge_in, input);
}

void hls4ml_galapagos_input_bridge_1024(galapagos_interface * bridge_in,
                                   hls::stream<resnet50_packet > input[1024])
{

#pragma HLS INTERFACE axis register both port=bridge_in
#pragma HLS array_partition variable=input
#pragma HLS INTERFACE ap_ctrl_none port=return
    _hls4ml_galapagos_input_bridge <1024> (bridge_in, input);
}
                                   

void hls4ml_galapagos_input_bridge_2048(galapagos_interface * bridge_in,
                                   hls::stream<resnet50_packet > input[2048])
{
#pragma HLS INTERFACE axis register both port=bridge_in
#pragma HLS array_partition variable=input block factor=2
#pragma HLS INTERFACE ap_ctrl_none port=return
    _hls4ml_galapagos_input_bridge <2048> (bridge_in, input);
}
                                   

                                   

void hls4ml_galapagos_output_bridge_3 (
                                    ap_uint<16> size,
                                    hls::stream<resnet50_packet> output[3],
                                    galapagos_interface * bridge_output,
                                    const ap_uint <8> dest
                    )
{
#pragma HLS INTERFACE axis register both port=bridge_output
#pragma HLS INTERFACE axis register both port=output bundle="output"
//#pragma HLS array_partition variable=output
#pragma HLS INTERFACE ap_ctrl_none port=dest
#pragma HLS INTERFACE ap_ctrl_none port=size
#pragma HLS INTERFACE ap_ctrl_none port=return


    _hls4ml_galapagos_output_bridge <3> (size, output, bridge_output, dest);
}


void hls4ml_galapagos_output_bridge_64 (
                                    ap_uint<16> size,
                                    hls::stream<resnet50_packet> output[64],
                                    galapagos_interface * bridge_output,
                                    const ap_uint <8> dest
                    )
{

#pragma HLS INTERFACE axis register both port=bridge_output
#pragma HLS INTERFACE axis register both port=output bundle="output"
#pragma HLS INTERFACE ap_ctrl_none port=dest
#pragma HLS INTERFACE ap_ctrl_none port=size
#pragma HLS INTERFACE ap_ctrl_none port=return

    _hls4ml_galapagos_output_bridge <64> (size, output, bridge_output, dest);
}

void hls4ml_galapagos_output_bridge_128 (
                                    ap_uint<16> size,
                                    hls::stream<resnet50_packet> output[128],
                                    galapagos_interface * bridge_output,
                                    const ap_uint <8> dest
                    )
{

#pragma HLS INTERFACE axis register both port=bridge_output
#pragma HLS INTERFACE axis register both port=output bundle="output"
//#pragma HLS array_partition variable=output bundle="output"
#pragma HLS INTERFACE ap_ctrl_none port=dest
#pragma HLS INTERFACE ap_ctrl_none port=size
#pragma HLS INTERFACE ap_ctrl_none port=return

    _hls4ml_galapagos_output_bridge <128> (size, output, bridge_output, dest);
}

void hls4ml_galapagos_output_bridge_256 (
                                    ap_uint<16> size,
                                    hls::stream<resnet50_packet> output[256],
                                    galapagos_interface * bridge_output,
                                    const ap_uint <8> dest
                    )
{

#pragma HLS INTERFACE axis register both port=bridge_output
#pragma HLS INTERFACE axis register both port=output bundle="output"
//#pragma HLS array_partition variable=output bundle="output"
#pragma HLS INTERFACE ap_ctrl_none port=dest
#pragma HLS INTERFACE ap_ctrl_none port=size
#pragma HLS INTERFACE ap_ctrl_none port=return

    _hls4ml_galapagos_output_bridge <256> (size, output, bridge_output, dest);
}


void hls4ml_galapagos_output_bridge_512 (
                                    ap_uint<16> size,
                                    hls::stream<resnet50_packet> output[512],
                                    galapagos_interface * bridge_output,
                                    const ap_uint <8> dest
                    )
{

#pragma HLS INTERFACE axis register both port=bridge_output
#pragma HLS array_partition variable=output
#pragma HLS INTERFACE ap_ctrl_none port=dest
#pragma HLS INTERFACE ap_ctrl_none port=size
#pragma HLS INTERFACE ap_ctrl_none port=return

    _hls4ml_galapagos_output_bridge <512> (size, output, bridge_output, dest);
}


void hls4ml_galapagos_output_bridge_1024 (
                                    ap_uint<16> size,
                                    hls::stream<resnet50_packet> output[1024],
                                    galapagos_interface * bridge_output,
                                    const ap_uint <8> dest
                    )
{

#pragma HLS INTERFACE axis register both port=bridge_output
#pragma HLS array_partition variable=output
#pragma HLS INTERFACE ap_ctrl_none port=dest
#pragma HLS INTERFACE ap_ctrl_none port=size
#pragma HLS INTERFACE ap_ctrl_none port=return

    _hls4ml_galapagos_output_bridge <1024> (size, output, bridge_output, dest);
}


void hls4ml_galapagos_output_bridge_2048 (
                                    ap_uint<16> size,
                                    hls::stream<resnet50_packet> output[2048],
                                    galapagos_interface * bridge_output,
                                    const ap_uint <8> dest
                    )
{
#pragma HLS INTERFACE axis register both port=bridge_output
#pragma HLS array_partition variable=output block factor=2
#pragma HLS INTERFACE ap_ctrl_none port=dest
#pragma HLS INTERFACE ap_ctrl_none port=size
#pragma HLS INTERFACE ap_ctrl_none port=return


    _hls4ml_galapagos_output_bridge <2048> (size, output, bridge_output, dest);
}
