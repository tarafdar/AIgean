set arg_0 "-I . -DN_INPUT=N_FILT_76 -DN_OUTPUT=N_FILT_80" 
set arg_1 "-DCONFIG=config80" 
set arg_2 "-DINPUT_T=layer77_t -DLAYER_T=layer80_t"
set arg_3 "-DWEIGHTS=w80 -DSCALES=s81 -DBIASES=b81"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type conv_2d_large_stream_norm_nobias

source ../common/build.tcl
