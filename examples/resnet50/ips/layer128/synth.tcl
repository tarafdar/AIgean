set arg_0 "-I . -DN_CONV=N_FILT_125 -DN_ADD=N_FILT_118 -DN_CONV_OUT=N_FILT_128 -DN_OUTPUT=N_FILT_128" 
set arg_1 "-DCONFIG=config128" 
set arg_2 "-DCONV_IN_T=layer125_t -DADD_IN_T=layer128_t -DOUTPUT_T=layer128_t"
set arg_3 "-DWEIGHTS=w128 -DSCALES=s129 -DBIASES=b129"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type conv_2d_large_stream_norm_nobias

source ../common/build.tcl
