# defines guard-%

SUBDIRS := $(wildcard */.)

.PHONY: all clean

include ../common/include.mk
SYNTH_ROOT = "."

all: input_bridges output_bridges 

input_bridges: input_3 input_64 input_128 input_256 input_512 input_1024 input_2048
output_bridges: output_3 output_64 output_128 output_256 output_512 output_1024 output_2048

input_3:
	mkdir -p ../hls_projects
	vivado_hls synth.tcl -tclargs hls4ml_galapagos_input_bridge_3 $(galapagos_dir)  $(libGalapagos_dir) 

input_64:
	mkdir -p ../hls_projects
	vivado_hls synth.tcl -tclargs hls4ml_galapagos_input_bridge_64 $(galapagos_dir)  $(libGalapagos_dir) 

input_128:
	mkdir -p ../hls_projects
	vivado_hls synth.tcl -tclargs hls4ml_galapagos_input_bridge_128 $(galapagos_dir)  $(libGalapagos_dir) 

input_256:
	mkdir -p ../hls_projects
	vivado_hls synth.tcl -tclargs hls4ml_galapagos_input_bridge_256 $(galapagos_dir)  $(libGalapagos_dir) 

input_512:
	mkdir -p ../hls_projects
	vivado_hls synth.tcl -tclargs hls4ml_galapagos_input_bridge_512 $(galapagos_dir)  $(libGalapagos_dir) 

input_1024:
	mkdir -p ../hls_projects
	vivado_hls synth.tcl -tclargs hls4ml_galapagos_input_bridge_1024 $(galapagos_dir)  $(libGalapagos_dir) 

input_2048:
	mkdir -p ../hls_projects
	vivado_hls synth.tcl -tclargs hls4ml_galapagos_input_bridge_2048 $(galapagos_dir)  $(libGalapagos_dir) 

output_3:
	mkdir -p ../hls_projects
	vivado_hls synth.tcl -tclargs hls4ml_galapagos_output_bridge_3 $(galapagos_dir)  $(libGalapagos_dir) 

output_64:
	mkdir -p ../hls_projects
	vivado_hls synth.tcl -tclargs hls4ml_galapagos_output_bridge_64 $(galapagos_dir)  $(libGalapagos_dir) 

output_128:
	mkdir -p ../hls_projects
	vivado_hls synth.tcl -tclargs hls4ml_galapagos_output_bridge_128 $(galapagos_dir)  $(libGalapagos_dir) 

output_256:
	mkdir -p ../hls_projects
	vivado_hls synth.tcl -tclargs hls4ml_galapagos_output_bridge_256 $(galapagos_dir)  $(libGalapagos_dir) 

output_512:
	mkdir -p ../hls_projects
	vivado_hls synth.tcl -tclargs hls4ml_galapagos_output_bridge_512 $(galapagos_dir)  $(libGalapagos_dir) 

output_1024:
	mkdir -p ../hls_projects
	vivado_hls synth.tcl -tclargs hls4ml_galapagos_output_bridge_1024 $(galapagos_dir)  $(libGalapagos_dir) 

output_2048:
	mkdir -p ../hls_projects
	vivado_hls synth.tcl -tclargs hls4ml_galapagos_output_bridge_2048 $(galapagos_dir)  $(libGalapagos_dir) 

clean:
	rm -rf $(galapagos_dir)/userIP/hls_projects/hls4ml_galapagos_input_bridge_*
	rm -rf $(galapagos_dir)/userIP/hls_projects/hls4ml_galapagos_output_bridge_*
