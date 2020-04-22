
set arg_0 "-I . -DN_INPUT=N_FILT_118 -DN_CONV=N_FILT_122" 
set arg_1 "-DCONFIG=config122" 
set arg_2 "-DINPUT_T=layer118_t -DCONV_LAYER_T=layer122_t"
set arg_3 "-DWEIGHTS=w122 -DSCALES=s123 -DBIASES=b123"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type split_one_conv_2d_large_stream_norm_nobias

source ../common/build.tcl


