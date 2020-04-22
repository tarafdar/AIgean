set arg_0 "-I . -DN_INPUT=N_FILT_160 -DN_CONV=N_FILT_164" 
set arg_1 "-DCONFIG=config164" 
set arg_2 "-DINPUT_T=layer160_t -DCONV_LAYER_T=layer164_t"
set arg_3 "-DWEIGHTS=w164 -DSCALES=s165 -DBIASES=b165"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type split_one_conv_2d_large_stream_norm_nobias

source ../common/build.tcl
