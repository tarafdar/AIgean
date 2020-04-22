set arg_0 "-I . -DN_INPUT=N_INPUT_3_1 -DN_CONV_OUTPUT=N_FILT_2 -DN_OUTPUT=N_FILT_5" 
set arg_1 "-DCONFIG_CONV=config2 -DCONFIG_POOL=config5" 
set arg_2 "-DINPUT_T=input_t -DCONV_LAYER_T=layer2_t -DPOOL_LAYER_T=layer5_t"
set arg_3 "-DWEIGHTS=w2 -DSCALES=s3 -DBIASES=b3"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type conv_2d_large_stream_norm_nobias_pool

source ../common/build.tcl
