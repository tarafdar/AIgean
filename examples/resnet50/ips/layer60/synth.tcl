set arg_0 "-I . -DN_INPUT=N_FILT_56 -DN_CONV=N_FILT_60" 
set arg_1 "-DCONFIG=config60" 
set arg_2 "-DINPUT_T=layer56_t -DCONV_LAYER_T=layer60_t"
set arg_3 "-DWEIGHTS=w60 -DSCALES=s61 -DBIASES=b61"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type split_one_conv_2d_large_stream_norm_nobias

source ../common/build.tcl
