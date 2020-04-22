set arg_0 "-I . -DN_CONV=N_FILT_73 -DN_ADD=N_FILT_66 -DN_CONV_OUT=N_FILT_76 -DN_OUTPUT=N_FILT_76" 
set arg_1 "-DCONFIG=config76" 
set arg_2 "-DCONV_IN_T=layer73_t -DADD_IN_T=layer66_t -DOUTPUT_T=layer76_t"
set arg_3 "-DWEIGHTS=w76 -DSCALES=s77 -DBIASES=b77"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type one_conv_2d_large_stream_norm_nobias_addrelu

source ../common/build.tcl
