
set arg_0 "-I . -DN_INPUT=N_FILT_9 -DN_OUTPUT=N_FILT_12" 
set arg_1 "-DCONFIG=config12" 
set arg_2 "-DINPUT_T=layer9_t -DLAYER_T=layer12_t"
set arg_3 "-DWEIGHTS=w12 -DSCALES=s13 -DBIASES=b13"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type conv_2d_large_stream_norm_nobias


source ../common/build.tcl
