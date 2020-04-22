set arg_0 "-I . -DN_CONV=N_FILT_95 -DN_ADD=N_FILT_88 -DN_CONV_OUT=N_FILT_98 -DN_OUTPUT=N_FILT_98" 
set arg_1 "-DCONFIG=config98" 
set arg_2 "-DCONV_IN_T=layer96_t -DADD_IN_T=layer98_t -DOUTPUT_T=layer98_t"
set arg_3 "-DWEIGHTS=w98 -DSCALES=s99 -DBIASES=b99"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type one_conv_2d_large_stream_norm_resnet_addrelu

source ../common/build.tcl
