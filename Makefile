
model_dir=../hls4ml/example-models/resnet50-hls-full_brainwave/firmware
#model_dir=examples/resnet50

galapagosPythonDir=../galapagos/middleware/python
netFile=$(model_dir)/model.json
logicalFile=$(model_dir)/logical.json
mapFile_floating=$(model_dir)/map.json
mapFile=$(model_dir)/map_partitioned.json
#ipDir=/home/tarafdar/Downloads/hls_projects
#ipDir=../galapagos/userIP/hls_projects
#ipDir=../galapagos/userIP/hls_projects_orig
ipDir=../galapagos/userIP/hls_projects4
mapFile_output=$(model_dir)/map_partitioned_output.json
logicalFile_output=$(model_dir)/logical_output.json
projectName=full_test
#projectName=part_test



all: net partition bridge

net: $(netFile)
	python3.7 ml2g.py --mode=net --netFile=$(netFile) --logicalFile=$(logicalFile) --mapFile=$(mapFile_floating) --ipDir=$(ipDir)

partition: $(logicalFile) $(mapFile_floating)
	python3.7 $(galapagosPythonDir)/map_s2s.py --fpgaFile=$(galapagosPythonDir)/fpga.json --ipDir=$(ipDir) --logicalFile=$(logicalFile) --mapFile=$(mapFile_floating)

bridge: $(mapFile)
	python3.7 ml2g.py --mode=bridge --netFile=$(netFile) --logicalFile=$(logicalFile) --mapFile=$(mapFile) --ipDir=$(ipDir)

galapagos: $(mapFile_output) $(logicalFile_output)
	python3.7 $(galapagosPythonDir)/globalFPGAParser.py --logicalFile=$(logicalFile_output) --mapFile=$(mapFile_output) --projectName=$(projectName)

