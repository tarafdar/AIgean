set arg_0 "-I . -DN_INPUT=N_FILT_108 -DN_CONV=N_FILT_112" 
set arg_1 "-DCONFIG=config112" 
set arg_2 "-DINPUT_T=layer108_t -DCONV_LAYER_T=layer112_t"
set arg_3 "-DWEIGHTS=w112 -DSCALES=s113 -DBIASES=b113"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type split_one_conv_2d_large_stream_norm_nobias

source ../common/build.tcl