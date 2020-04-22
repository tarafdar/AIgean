set arg_0 "-I . -DN_INPUT=N_FILT_132 -DN_OUTPUT=N_FILT_135" 
set arg_1 "-DCONFIG=config135" 
set arg_2 "-DINPUT_T=layer132_t -DLAYER_T=layer135_t"
set arg_3 "-DWEIGHTS=w135 -DSCALES=s136 -DBIASES=b136"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type conv_2d_large_stream_norm_nobias

source ../common/build.tcl
