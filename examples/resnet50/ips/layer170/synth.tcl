set arg_0 "-I . -DN_CONV=N_FILT_167 -DN_ADD=N_FILT_164 -DN_CONV_OUT=N_FILT_170 -DN_OUTPUT=N_FILT_170" 
set arg_1 "-DCONFIG=config170" 
set arg_2 "-DCONV_IN_T=layer167_t -DADD_IN_T=layer164_t -DOUTPUT_T=layer170_t"
set arg_3 "-DWEIGHTS=w170 -DSCALES=s171 -DBIASES=b171"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type one_conv_2d_large_stream_norm_nobias_addrelu

source ../common/build.tcl
