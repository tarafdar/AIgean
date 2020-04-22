set arg_0 "-I . -DN_INPUT=N_FILT_102 -DN_OUTPUT=N_FILT_105" 
set arg_1 "-DCONFIG=config105" 
set arg_2 "-DINPUT_T=layer102_t -DLAYER_T=layer105_t"
set arg_3 "-DWEIGHTS=w105 -DSCALES=s106 -DBIASES=b106"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type conv_2d_large_stream_norm_nobias

source ../common/build.tcl
