set arg_0 "-I . -DN_INPUT=N_FILT_28 -DN_OUTPUT=N_FILT_31" 
set arg_1 "-DCONFIG=config31" 
set arg_2 "-DINPUT_T=layer28_t -DLAYER_T=layer31_t"
set arg_3 "-DWEIGHTS=w31 -DSCALES=s32 -DBIASES=b32"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type conv_2d_large_stream_norm_nobias

source ../common/build.tcl
