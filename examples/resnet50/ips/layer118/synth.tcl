
set arg_0 "-I . -DN_CONV=N_FILT_115 -DN_ADD=N_FILT_108 -DN_CONV_OUT=N_FILT_118 -DN_OUTPUT=N_FILT_118" 
set arg_1 "-DCONFIG=config118" 
set arg_2 "-DCONV_IN_T=layer115_t -DADD_IN_T=layer118_t -DOUTPUT_T=layer118_t"
set arg_3 "-DWEIGHTS=w118 -DSCALES=s119 -DBIASES=b119"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type one_conv_2d_large_stream_norm_resnet_addrelu

source ../common/build.tcl

