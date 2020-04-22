set arg_0 "-I . -DN_INPUT=N_FILT_138 -DN_CONV=N_FILT_142" 
set arg_1 "-DCONFIG=config142" 
set arg_2 "-DINPUT_T=layer138_t -DCONV_LAYER_T=layer142_t"
set arg_3 "-DWEIGHTS=w142 -DSCALES=s143 -DBIASES=b143"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type split_one_conv_2d_large_stream_norm_nobias

source ../common/build.tcl
