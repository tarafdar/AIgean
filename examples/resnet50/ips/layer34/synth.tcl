set arg_0 "-I . -DN_CONV=N_FILT_31 -DN_ADD=N_FILT_24 -DN_CONV_OUT=N_FILT_34 -DN_OUTPUT=N_FILT_34" 
set arg_1 "-DCONFIG=config34" 
set arg_2 "-DCONV_IN_T=layer31_t -DADD_IN_T=layer24_t -DOUTPUT_T=layer34_t"
set arg_3 "-DWEIGHTS=w34 -DSCALES=s35 -DBIASES=b35"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type one_conv_2d_large_stream_norm_nobias_addrelu

source ../common/build.tcl
