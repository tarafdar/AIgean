#ifndef _STREAM_RESNET50_HPP
#define _STREAM_RESNET50_HPP

#include "resnet50.hpp"

template <class _INPUT_T, int _N_INPUT>
bool _stream_to_input(
        hls::stream<resnet50_packet> stream_input[_N_INPUT],
        hls::stream<_INPUT_T> input[_N_INPUT]
        ){

    bool reset;
    for(int i = 0; i<_N_INPUT;i++){
        resnet50_packet temp;
#ifdef CPU
        if(!stream_input[i].empty()){
#endif
            temp = stream_input[i].read();
#ifdef CPU
            std::cout << "IN[" << i << "]=" << temp.data << std::endl;
#endif
            input[i].write(temp.data);
            if(i==0){
                if(temp.id == 1)
                    reset = true;
                else
                {
                    reset = false;
                }
            }
#ifdef CPU
        }
#endif
    }

    return reset;
}


template <class _OUTPUT_T, int _N_OUTPUT>
bool _output_to_stream(
        bool reset,
        hls::stream<_OUTPUT_T> output[_N_OUTPUT],
        hls::stream<resnet50_packet> stream_output[_N_OUTPUT]
        )
{


    for(int i = 0; i<_N_OUTPUT;i++){
#ifdef CPU
        if(!output[i].empty()){
#endif
            _OUTPUT_T temp;
            temp = output[i].read();
            resnet50_packet temp2; 
            temp2.data = temp;
#ifdef CPU
            std::cout << "OUT[" << i << "]=" << temp << std::endl;
#endif
            temp2.id = reset;
            stream_output[i].write(temp2);
#ifdef CPU
        }
#endif
    }



}

#endif
