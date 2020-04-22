set arg_0 "-I . -DN_CONV=N_FILT_5 -DN_ADD=N_FILT_12 -DN_CONV_OUT=N_FILT_14 -DN_OUTPUT=N_FILT_14" 
set arg_1 "-DCONFIG=config14" 
set arg_2 "-DCONV_IN_T=layer5_t -DADD_IN_T=layer12_t -DOUTPUT_T=layer14_t"
set arg_3 "-DWEIGHTS=w14 -DSCALES=s15 -DBIASES=b15"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type one_conv_2d_large_stream_norm_nobias_addrelu

source ../common/build.tcl
