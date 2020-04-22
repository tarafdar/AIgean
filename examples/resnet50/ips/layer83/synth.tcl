set arg_0 "-I . -DN_INPUT=N_FILT_80 -DN_OUTPUT=N_FILT_83" 
set arg_1 "-DCONFIG=config83" 
set arg_2 "-DINPUT_T=layer80_t -DLAYER_T=layer83_t"
set arg_3 "-DWEIGHTS=w83 -DSCALES=s84 -DBIASES=b84"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type conv_2d_large_stream_norm_nobias

source ../common/build.tcl
