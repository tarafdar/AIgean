set arg_0 "-I . -DN_INPUT=N_FILT_50 -DN_OUTPUT=N_FILT_53" 
set arg_1 "-DCONFIG=config53" 
set arg_2 "-DINPUT_T=layer50_t -DLAYER_T=layer53_t"
set arg_3 "-DWEIGHTS=w53 -DSCALES=s54 -DBIASES=b54"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type conv_2d_large_stream_norm_nobias

source ../common/build.tcl
