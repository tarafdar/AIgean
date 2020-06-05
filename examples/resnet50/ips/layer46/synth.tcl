set arg_0 "-I . -DN_INPUT=N_FILT_34 -DN_OUTPUT=N_FILT_46" 
set arg_1 "-DCONFIG=config46" 
set arg_2 "-DINPUT_T=layer170_t -DLAYER_T=layer47_t"
set arg_3 "-DWEIGHTS=w46  -DBIASES=b46"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type conv_2d_large_cl_1x1

source ../common/build.tcl
