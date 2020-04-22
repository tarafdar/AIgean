set arg_0 "-I . -DN_INPUT=N_FILT_70 -DN_OUTPUT=N_FILT_73" 
set arg_1 "-DCONFIG=config73" 
set arg_2 "-DINPUT_T=layer70_t -DLAYER_T=layer73_t"
set arg_3 "-DWEIGHTS=w73 -DSCALES=s74 -DBIASES=b74"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type conv_2d_large_stream_norm_nobias

source ../common/build.tcl
