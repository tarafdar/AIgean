set arg_0 "-I . -DN_INPUT=N_FILT_150 -DN_CONV=N_FILT_154" 
set arg_1 "-DCONFIG=config154" 
set arg_2 "-DINPUT_T=layer150_t -DCONV_LAYER_T=layer154_t"
set arg_3 "-DWEIGHTS=w154 -DSCALES=s155 -DBIASES=b155"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type split_one_conv_2d_large_stream_norm_nobias

source ../common/build.tcl
