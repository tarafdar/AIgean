#ifndef GALAPAGOS_RESNET_BRIDGE
#define GALAPAGOS_RESNET_BRIDGE

#include "_galapagos_resnet_bridge.hpp"


template <int width>
void hls4ml_galapagos_input_bridge(galapagos_interface * bridge_in,
                                   hls::stream<resnet50_packet > input[width])
{


    _hls4ml_galapagos_input_bridge<width>(bridge_in, input);


}
                                   


template<int width>
void hls4ml_galapagos_output_bridge (
                                    ap_uint<16> size,
                                    hls::stream<resnet50_packet> output[width],
                                    galapagos_interface * bridge_output,
                                    const ap_uint <8> dest
                    )
{


    _hls4ml_galapagos_output_bridge<width>(size, output, bridge_output, dest);

}

template<int width>
void hls4ml_galapagos_output_bridge (
                                    hls::stream<resnet50_packet> output[width],
                                    galapagos_interface * bridge_output,
                                    const ap_uint <8> dest
                    )
{


    _hls4ml_galapagos_output_bridge<width>(output, bridge_output, dest);

}

#endif
