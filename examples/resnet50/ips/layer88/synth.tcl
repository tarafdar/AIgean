set arg_0 "-I . -DN_CONV=N_FILT_76 -DN_ADD=N_FILT_86 -DN_CONV_OUT=N_FILT_88 -DN_OUTPUT=N_FILT_76" 
set arg_1 "-DCONFIG=config88" 
set arg_2 "-DCONV_IN_T=layer86_t -DADD_IN_T=layer86_t -DOUTPUT_T=layer88_t"
set arg_3 "-DWEIGHTS=w88 -DSCALES=s89 -DBIASES=b89"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type one_conv_2d_large_stream_norm_resnet_addrelu

source ../common/build.tcl
