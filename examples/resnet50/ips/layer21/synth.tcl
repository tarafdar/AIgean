set arg_0 "-I . -DN_INPUT=N_FILT_18 -DN_OUTPUT=N_FILT_21" 
set arg_1 "-DCONFIG=config21" 
set arg_2 "-DINPUT_T=layer18_t -DLAYER_T=layer21_t"
set arg_3 "-DWEIGHTS=w21 -DSCALES=s22 -DBIASES=b22"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type conv_2d_large_stream_norm_nobias

source ../common/build.tcl