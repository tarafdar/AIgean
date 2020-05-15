#ifndef RESNET50_FULL_H_
#define RESNET50_FULL_H_

#include <complex>
#include "ap_int.h"
#include "ap_fixed.h"



struct resnet50_packet{
    ap_uint<8> data;
    ap_int <1> id;
};



#endif
