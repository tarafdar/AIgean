set arg_0 "-I . -DN_INPUT=N_FILT_5 -DN_CONV=N_FILT_6" 
set arg_1 "-DCONFIG=config6" 
set arg_2 "-DINPUT_T=layer5_t -DCONV_LAYER_T=layer6_t"
set arg_3 "-DWEIGHTS=w6 -DSCALES=s7 -DBIASES=b7"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type split_one_conv_2d_large_stream_norm_nobias

source ../common/build.tcl
