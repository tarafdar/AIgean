set arg_0 "-I . -DN_CONV=N_FILT_34 -DN_ADD=N_FILT_44 -DN_CONV_OUT=N_FILT_46 -DN_OUTPUT=N_FILT_46" 
set arg_1 "-DCONFIG=config46" 
set arg_2 "-DCONV_IN_T=layer34_t -DADD_IN_T=layer44_t -DOUTPUT_T=layer46_t"
set arg_3 "-DWEIGHTS=w46 -DSCALES=s47 -DBIASES=b47"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type one_conv_2d_large_stream_norm_resnet_addrelu

source ../common/build.tcl
