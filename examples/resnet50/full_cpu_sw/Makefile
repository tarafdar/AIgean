#===============================
# AUTHOR     : Naif Tarafdar
# CREATE DATE     : April 20, 2019
#===============================

LIBGALAPAGOS_DIR=../../../../libGalapagos
XILINX_INCLUDE=$(LIBGALAPAGOS_DIR)/xil_include
FIRMWARE_DIR=../../../../hls4ml/example-models/resnet50-hls-full_v2/firmware

DEBUG_FLAGS = -g -DLOG_LEVEL=5
PRODUCTION_FLAGS = -O3 -DLOG_LEVEL=0
BOOST_LDFLAGS=-lboost_thread -lboost_system -lpthread -lboost_log -lboost_log_setup -lboost_program_options
FLAGS=-DCPU  -std=c++17 -isystem $(XILINX_INCLUDE) -D FIRMWARE_DIR=\"$(FIRMWARE_DIR)\" -I../../../../spdlog/include -I srcs -I ../../../../galapagos/middleware/include -I $(FIRMWARE_DIR) -I $(LIBGALAPAGOS_DIR)  -I ../kernel_headers -DINTERFACE_100G  

release: CXXFLAGS = $(FLAGS)  ${PRODUCTION_FLAGS}
release: hello_world.exe
debug: CXXFLAGS = $(FLAGS) ${DEBUG_FLAGS}
debug: hello_world.exe

all: debug 

hello_world.exe: cpu_node.cpp kern.cpp $(LIBGALAPAGOS_DIR)/common.cpp  
	g++ $(CXXFLAGS) $^ -o $@ $(BOOST_LDFLAGS)	

clean:
	rm -rf *.exe
