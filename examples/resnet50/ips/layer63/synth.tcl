set arg_0 "-I . -DN_INPUT=N_FILT_60 -DN_OUTPUT=N_FILT_63" 
set arg_1 "-DCONFIG=config63" 
set arg_2 "-DINPUT_T=layer60_t -DLAYER_T=layer63_t"
set arg_3 "-DWEIGHTS=w63 -DSCALES=s64 -DBIASES=b64"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type conv_2d_large_stream_norm_nobias

source ../common/build.tcl
