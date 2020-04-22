set arg_0 "-I . -DN_INPUT=N_FILT_66 -DN_CONV=N_FILT_70" 
set arg_1 "-DCONFIG=config70" 
set arg_2 "-DINPUT_T=layer66_t -DCONV_LAYER_T=layer70_t"
set arg_3 "-DWEIGHTS=w70 -DSCALES=s71 -DBIASES=b71"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type split_one_conv_2d_large_stream_norm_nobias

source ../common/build.tcl
