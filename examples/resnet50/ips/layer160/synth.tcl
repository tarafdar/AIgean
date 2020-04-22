set arg_0 "-I . -DN_CONV=N_FILT_157 -DN_ADD=N_FILT_154 -DN_CONV_OUT=N_FILT_160 -DN_OUTPUT=N_FILT_160" 
set arg_1 "-DCONFIG=config160" 
set arg_2 "-DCONV_IN_T=layer157_t -DADD_IN_T=layer154_t -DOUTPUT_T=layer160_t"
set arg_3 "-DWEIGHTS=w160 -DSCALES=s161 -DBIASES=b161"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type one_conv_2d_large_stream_norm_nobias_addrelu

source ../common/build.tcl
