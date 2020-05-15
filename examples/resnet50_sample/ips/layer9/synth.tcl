set arg_0 "-I . -DN_INPUT=N_FILT_6 -DN_OUTPUT=N_FILT_9" 
set arg_1 "-DCONFIG=config9" 
set arg_2 "-DINPUT_T=layer6_t -DLAYER_T=layer9_t"
set arg_3 "-DWEIGHTS=w9 -DSCALES=s10 -DBIASES=b10"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type conv_2d_large_stream_norm_nobias

source ../common/build.tcl
