set arg_0 "-I . -DN_INPUT=N_FILT_145 -DN_OUTPUT=N_FILT_148" 
set arg_1 "-DCONFIG=config148" 
set arg_2 "-DINPUT_T=layer145_t -DLAYER_T=layer148_t"
set arg_3 "-DWEIGHTS=w148 -DSCALES=s149 -DBIASES=b149"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type conv_2d_large_stream_norm_nobias

source ../common/build.tcl
