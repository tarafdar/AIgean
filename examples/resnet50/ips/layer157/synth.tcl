set arg_0 "-I . -DN_INPUT=N_FILT_154 -DN_OUTPUT=N_FILT_157" 
set arg_1 "-DCONFIG=config157" 
set arg_2 "-DINPUT_T=layer154_t -DLAYER_T=layer157_t"
set arg_3 "-DWEIGHTS=w157 -DSCALES=s158 -DBIASES=b158"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type conv_2d_large_stream_norm_nobias

source ../common/build.tcl
