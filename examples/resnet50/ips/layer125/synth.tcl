
set arg_0 "-I . -DN_INPUT=N_FILT_122 -DN_OUTPUT=N_FILT_125" 
set arg_1 "-DCONFIG=config125" 
set arg_2 "-DINPUT_T=layer122_t -DLAYER_T=layer125_t"
set arg_3 "-DWEIGHTS=w125 -DSCALES=s126 -DBIASES=b126"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type conv_2d_large_stream_norm_nobias

source ../common/build.tcl
