set arg_0 "-I . -DN_INPUT=N_FILT_46 -DN_CONV=N_FILT_50" 
set arg_1 "-DCONFIG=config50" 
set arg_2 "-DINPUT_T=layer46_t -DCONV_LAYER_T=layer50_t"
set arg_3 "-DWEIGHTS=w50 -DSCALES=s51 -DBIASES=b51"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type split_one_conv_2d_large_stream_norm_nobias

source ../common/build.tcl
