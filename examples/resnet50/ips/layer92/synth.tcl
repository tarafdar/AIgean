set arg_0 "-I . -DN_INPUT=N_FILT_76 -DN_CONV=N_FILT_88" 
set arg_1 "-DCONFIG=config92" 
set arg_2 "-DINPUT_T=layer92_t -DCONV_LAYER_T=layer92_t"
set arg_3 "-DWEIGHTS=w92 -DSCALES=s93 -DBIASES=b93"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type split_one_conv_2d_large_stream_norm_nobias

source ../common/build.tcl
