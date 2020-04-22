set arg_0 "-I . -DN_INPUT=N_FILT_128 -DN_CONV=N_FILT_132" 
set arg_1 "-DCONFIG=config132" 
set arg_2 "-DINPUT_T=layer128_t -DCONV_LAYER_T=layer132_t"
set arg_3 "-DWEIGHTS=w132 -DSCALES=s133 -DBIASES=b133"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type split_one_conv_2d_large_stream_norm_nobias

source ../common/build.tcl
