set arg_0 "-I . -DN_CONV=N_FILT_53 -DN_ADD=N_FILT_46 -DN_CONV_OUT=N_FILT_56 -DN_OUTPUT=N_FILT_56" 
set arg_1 "-DCONFIG=config56" 
set arg_2 "-DCONV_IN_T=layer53_t -DADD_IN_T=layer46_t -DOUTPUT_T=layer56_t"
set arg_3 "-DWEIGHTS=w56 -DSCALES=s57 -DBIASES=b57"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type one_conv_2d_large_stream_norm_nobias_addrelu

source ../common/build.tcl
