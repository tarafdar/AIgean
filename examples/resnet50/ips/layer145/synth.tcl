set arg_0 "-I . -DN_INPUT=N_FILT_142 -DN_OUTPUT=N_FILT_145" 
set arg_1 "-DCONFIG=config145" 
set arg_2 "-DINPUT_T=layer142_t -DLAYER_T=layer145_t"
set arg_3 "-DWEIGHTS=w145 -DSCALES=s146 -DBIASES=b146"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type conv_2d_large_stream_norm_nobias

source ../common/build.tcl
