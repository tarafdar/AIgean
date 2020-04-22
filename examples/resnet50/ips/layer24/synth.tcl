set arg_0 "-I . -DN_CONV=N_FILT_21 -DN_ADD=N_FILT_14 -DN_CONV_OUT=N_FILT_24 -DN_OUTPUT=N_FILT_24" 
set arg_1 "-DCONFIG=config24" 
set arg_2 "-DCONV_IN_T=layer21_t -DADD_IN_T=layer14_t -DOUTPUT_T=layer24_t"
set arg_3 "-DWEIGHTS=w24 -DSCALES=s25 -DBIASES=b25"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type one_conv_2d_large_stream_norm_nobias_addrelu

source ../common/build.tcl
