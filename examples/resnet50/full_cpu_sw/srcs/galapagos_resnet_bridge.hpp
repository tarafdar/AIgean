#ifndef GALAPAGOS_RESNET_BRIDGE
#define GALAPAGOS_RESNET_BRIDGE

#include "_galapagos_resnet_bridge.hpp"


template <int width, class INPUT_T>
void hls4ml_galapagos_input_bridge(galapagos_interface * bridge_in,
                                   hls::stream<INPUT_T > input[width])
{


    _hls4ml_galapagos_input_bridge<width, INPUT_T>(bridge_in, input);


}
                                   


template<int width, class OUTPUT_T>
void hls4ml_galapagos_output_bridge (
                                    ap_uint<16> size,
                                    hls::stream<OUTPUT_T > output[width],
                                    galapagos_interface * bridge_output,
                                    const ap_uint <8> dest
                    )
{


    _hls4ml_galapagos_output_bridge<width, OUTPUT_T>(size, output, bridge_output, dest);

}

#define BITS_PER_BYTE 8 
#define BYTES_PER_PIXEL 4
#define BITS_FOR_SIZE 32

template<class OUTPUT_T>
void hls4ml_galapagos_output_bridge_4 (
                                    ap_uint<16> size_per_flit,
                                    OUTPUT_T data_in[N_INPUT_3_1][N_INPUT_2_1][N_INPUT_1_1],
                                    std::vector<std::vector<int> > output,
                                    galapagos_interface * bridge_output,
                                    const ap_uint <8> dest


                    )
{
    std::vector<ap_uint<PACKET_DATA_LENGTH> > vec;
    ap_uint<PACKET_DATA_LENGTH> data_out;
    int pixel_index = 0;
    for(int i=0; i<output.size() ; i+=size_per_flit){
        data_out.range(BITS_FOR_SIZE-1,0) = size_per_flit;
        data_out.range() = data_out.range() & 0x0ffffffff;
        for(int j=0; j<size_per_flit; j++){
            OUTPUT_T pixel[N_INPUT_1_1] = data_in[output[pixel_index][0]][output[pixel_index][1]];
            //std::cout << "OUTPUT PIXEL INDEX: " << output[pixel_index][0] << " , " << output[pixel_index][1] << std::endl;
            //std::cout << "OUTPUT BRIDGE PIXEL: " << std::hex << pixel[3] << " " << pixel[2] << " " << pixel[1] << " " << pixel[0] << std::endl;

            for(int k=0; k<BYTES_PER_PIXEL; k++){
                OUTPUT_T data = pixel[k];
                //std::cout << "hi range: " << j*BYTES_PER_PIXEL*BITS_PER_BYTE +  k*BITS_PER_BYTE   + BITS_FOR_SIZE + BITS_PER_BYTE - 1 << 
                //             "low range " <<  j*BYTES_PER_PIXEL*BITS_PER_BYTE +  k*BITS_PER_BYTE   + BITS_FOR_SIZE;
                data_out.range(j*BYTES_PER_PIXEL*BITS_PER_BYTE +  k*BITS_PER_BYTE   + BITS_FOR_SIZE + BITS_PER_BYTE - 1, 
                               j*BYTES_PER_PIXEL*BITS_PER_BYTE +  k*BITS_PER_BYTE   + BITS_FOR_SIZE) = data.range();
            }
            pixel_index++;
        }
        //std::cout << std::hex << "data_out " << data_out.range() << std::dec << std::endl;
        vec.push_back(data_out);
    }
    bridge_output->packet_write((char *)vec.data(), vec.size(), dest, 0);
}

#endif
