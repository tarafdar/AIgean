set arg_0 "-I . -DN_INPUT=N_FILT_34 -DN_CONV=N_FILT_38" 
set arg_1 "-DCONFIG=config38" 
set arg_2 "-DINPUT_T=layer34_t -DCONV_LAYER_T=layer38_t"
set arg_3 "-DWEIGHTS=w38 -DSCALES=s39 -DBIASES=b39"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type split_one_conv_2d_large_stream_norm_nobias

source ../common/build.tcl
