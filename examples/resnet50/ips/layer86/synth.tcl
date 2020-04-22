set arg_0 "-I . -DN_INPUT=N_FILT_83 -DN_OUTPUT=N_FILT_86" 
set arg_1 "-DCONFIG=config86" 
set arg_2 "-DINPUT_T=layer83_t -DLAYER_T=layer86_t"
set arg_3 "-DWEIGHTS=w86 -DSCALES=s87 -DBIASES=b87"
set args "$arg_0 $arg_1 $arg_2 $arg_3"
set layer_type conv_2d_large_stream_norm_nobias

source ../common/build.tcl
