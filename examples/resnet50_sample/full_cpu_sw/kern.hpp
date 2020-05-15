#ifndef KERN_HPP
#define KERN_HPP

#include "resnet50.hpp"
#include "packet_size.h"
typedef ap_uint<PACKET_DATA_LENGTH> T;


void kern_send(short id, galapagos_interface * in, galapagos_interface  * out);
//void kern_loopback(short id, galapagos_interface * in, galapagos_interface  * out);
void kern_aigean(short id, galapagos_interface * in, galapagos_interface  * out);



#endif
