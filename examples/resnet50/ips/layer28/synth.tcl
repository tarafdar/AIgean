set arg_0 "-I . -DN_INPUT=N_FILT_24 -DN_CONV=N_FILT_28" 
set arg_1 "-DCONFIG=config28" 
set arg_2 "-DINPUT_T=layer24_t -DCONV_LAYER_T=layer28_t"
set arg_3 "-DWEIGHTS=w28 -DSCALES=s29 -DBIASES=b29"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type split_one_conv_2d_large_stream_norm_nobias

source ../common/build.tcl
