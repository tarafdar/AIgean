set arg_0 "-I . -DN_INPUT=N_FILT_98 -DN_CONV=N_FILT_102" 
set arg_1 "-DCONFIG=config102" 
set arg_2 "-DINPUT_T=layer98_t -DCONV_LAYER_T=layer102_t"
set arg_3 "-DWEIGHTS=w102 -DSCALES=s103 -DBIASES=b103"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type split_one_conv_2d_large_stream_norm_nobias

source ../common/build.tcl
