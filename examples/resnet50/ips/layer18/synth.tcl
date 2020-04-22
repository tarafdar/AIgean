set arg_0 "-I . -DN_INPUT=N_FILT_14 -DN_CONV=N_FILT_18" 
set arg_1 "-DCONFIG=config18" 
set arg_2 "-DINPUT_T=layer14_t -DCONV_LAYER_T=layer18_t"
set arg_3 "-DWEIGHTS=w18 -DSCALES=s19 -DBIASES=b19"
set args "$arg_0 $arg_1 $arg_2 $arg_3"

source ../common/build.tcl
