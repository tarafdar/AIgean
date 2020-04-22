set arg_0 "-I . -DN_CONV=N_FILT_63 -DN_ADD=N_FILT_56 -DN_CONV_OUT=N_FILT_66 -DN_OUTPUT=N_FILT_66" 
set arg_1 "-DCONFIG=config66" 
set arg_2 "-DCONV_IN_T=layer63_t -DADD_IN_T=layer56_t -DOUTPUT_T=layer66_t"
set arg_3 "-DWEIGHTS=w66 -DSCALES=s67 -DBIASES=b67"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type one_conv_2d_large_stream_norm_nobias_addrelu

source ../common/build.tcl
