set arg_0 "-I . -DN_CONV=N_FILT_105 -DN_ADD=N_FILT_98 -DN_CONV_OUT=N_FILT_108 -DN_OUTPUT=N_FILT_108" 
set arg_1 "-DCONFIG=config108" 
set arg_2 "-DCONV_IN_T=layer105_t -DADD_IN_T=layer108_t -DOUTPUT_T=layer108_t"
set arg_3 "-DWEIGHTS=w108 -DSCALES=s109 -DBIASES=b109"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type one_conv_2d_large_stream_norm_resnet_addrelu

source ../common/build.tcl
