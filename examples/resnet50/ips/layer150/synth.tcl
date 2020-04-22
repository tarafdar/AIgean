set arg_0 "-I . -DN_CONV=N_FILT_138 -DN_ADD=N_FILT_148 -DN_CONV_OUT=N_FILT_150 -DN_OUTPUT=N_FILT_150" 
set arg_1 "-DCONFIG=config150" 
set arg_2 "-DCONV_IN_T=layer138_t -DADD_IN_T=layer148_t -DOUTPUT_T=layer150_t"
set arg_3 "-DWEIGHTS=w150 -DSCALES=s151 -DBIASES=b151"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type one_conv_2d_large_stream_norm_resnet_addrelu

source ../common/build.tcl
