set arg_0 "-I . -DN_INPUT=N_FILT_41 -DN_OUTPUT=N_FILT_44" 
set arg_1 "-DCONFIG=config44" 
set arg_2 "-DINPUT_T=layer41_t -DLAYER_T=layer44_t"
set arg_3 "-DWEIGHTS=w44 -DSCALES=s45 -DBIASES=b45"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type conv_2d_large_stream_norm_nobias

source ../common/build.tcl
