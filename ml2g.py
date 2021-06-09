import getopt, sys
import json
import util
import networkx 
import math
#from networkx.drawing.nx_agraph import write_dot
from networkx.drawing.nx_pydot import write_dot
import matplotlib.pyplot as plt
#from asciinet import graph_to_ascii


edges_visited = {}
kerns = []
kerns_rev = {}
kerns_to_node_map = {}
node_to_kern_map = []
kern_predec = {}
kern_succ = {}
metadata =[]
weights_dict = {}
kern_dict_map = {}

ip_hier = []
map_dict = []
kern_dict = []
input_bridges = {} 
output_bridges = []
global_kernels = []
kern_num = 0

node_num = 0
debug = 1 
origin_node = ''
G = networkx.DiGraph()
G_verbose = networkx.DiGraph()




def logical_kernel_element(kern_name, kern_id, bridge=False, bram=False, fifo=False):


    debug = 1 
    kern = kerns[kerns_rev[kern_name]]
    kerns[kerns_rev[kern_name]]["logical"] = True
    #kern_elem = {"clk":"ap_clk", "aresetn":"ap_rst_n", "vendor":"xilinx.com","lib":"hls", "num":kern_id, "rep":1}
    if bram:
        if fifo:
            kern_elem = {"clk":"s_axis_aclk", "aresetn": "s_axis_aresetn",  "vendor":"xilinx.com","lib":"ip", "num":kerns_rev[kern_name], "rep":1, "properties":kerns[kerns_rev[kern_name]]["properties"]}
        else:
            kern_elem = {"clk":["clka","clkb"],  "vendor":"xilinx.com","lib":"ip", "num":kerns_rev[kern_name], "rep":1, "properties":kerns[kerns_rev[kern_name]]["properties"]}
    else:
        kern_elem = {"clk":"ap_clk", "aresetn":"ap_rst_n", "vendor":"xilinx.com","lib":"hls", "num":kerns_rev[kern_name], "rep":1}

    if 'bridge' not in kern and not bram:
        kern_elem["#text"] = kern['inst'] + '_' + kern['kernel']
        kern_elem["note"] = {}
        kern_elem["note"]["inst"] = kern['inst']
    else:
        kern_elem["#text"] = kern['kernel']



    if "s_axis" in kern:
        kern_elem["s_axis"] = kern["s_axis"]
    else:
        kern_elem["s_axis"] = []
    for s_axis in kern['inputs']:
        if 'width' in s_axis:
            if debug:
                loop_bound = 1
            else:
                loop_bound = s_axis['width']
            for i in range(loop_bound):
                if s_axis['global']:
                    kern_elem["s_axis"].append({"name":(s_axis["name"]+"_" + str(i)+ "_V_V"), "scope":"global"})
                    #kern_elem["s_axis"].append({"name":(s_axis["name"]+"_" + str(i)), "scope":"global"})
                else:
                    #master_port = str(kerns[s_axis['local_node']]['outputs'][s_axis['local_port']]['name'])+ "_" +str(i) + "_V_V"
                    #print(kern)
                    #print(s_axis)
                    #master_port = str(s_axis['master']['port'])+ "_" +str(i) + "_V_V"
                    #print("s_axis is: " + str(s_axis))
                    master_port = str(s_axis['master']['port'])+ "_" +str(i) + "_V_V"
                    #master_port = str(s_axis['master']['port'])+ "_" +str(i)
                    kern_elem["s_axis"].append({"name":(s_axis["name"]+"_" + str(i)+ "_V_V"), "scope":"local", "master": {"node": s_axis['master']['node'], "port": master_port}})
                    #kern_elem["s_axis"].append({"name":(s_axis["name"]+"_" + str(i)), "scope":"local", "master": {"node": s_axis['master']['node'], "port": master_port}})
        else:
            kern_elem["s_axis"].append({"name":(s_axis["name"]), "scope":"global"})

    #if(bridge == False):
    #    kern_elem["inst"] = kern["inst"]
    #    kern_elem["kernel"] = kern["kernel"]

    if "m_axis" in kern:
        kern_elem["m_axis"] = kern["m_axis"] 
    else:
        kern_elem["m_axis"] = []
    for m_axis in kern['outputs']:

        if 'width' in m_axis:
            if debug:
                loop_bound = 1
            else:
                loop_bound = m_axis['width']
            for i in range(loop_bound):
                if m_axis['global']:
                    #kern_elem["m_axis"].append({"name":(m_axis["name"]+"_" + str(i)), "scope":"global"})
                    kern_elem["m_axis"].append({"name":(m_axis["name"]+"_" + str(i)+ "_V_V"), "scope":"global"})
                else:
                    #slave_port = str(m_axis['slave']['port'])+ "_" +str(i)
                    #print("kern is " + str(kern))
                    #print("m_axis is " + str(m_axis))
                    slave_port = str(m_axis['slave']['port'])+ "_" +str(i) + "_V_V"
                    #kern_elem["m_axis"].append({"name":(m_axis["name"]+"_" + str(i)), "scope":"local",  "slave": {"node": m_axis['slave']['node'], "port": slave_port}})
                    kern_elem["m_axis"].append({"name":(m_axis["name"]+"_" + str(i)+ "_V_V"), "scope":"local",  "slave": {"node": m_axis['slave']['node'], "port": slave_port}})
        else:
            if m_axis['global']:
                kern_elem["m_axis"].append({"name":m_axis["name"], "scope":"global"})
            else:
                kern_elem["m_axis"].append({"name":m_axis["name"], "scope":"local"})

    if("bram_size" in kern):
        kern_elem["note"]["bram"] =  weights_dict[kern['inst']]
        kerns[kerns_rev[kern_name]].pop("bram_size", None)

    if( "const" in kern):
        kern_elem["const"] = kern["const"]

    if("wire_master" in kern):
        kern_elem["wire_master"] = kern["wire_master"]

    if ("wire_slave" in kern):
        kern_elem["wire_slave"] = kern["wire_slave"]
    
    if("note" in kern):
        kern_elem["note"] = kern["note"]

    if("egress_fifo_depth" in kern):
        kern_elem["note"]["egress_fifo_depth"] = kern["egress_fifo_depth"]


    return kern_elem

def add_logical_ip(ip):

    kerns_rev[ip['inst']] = len(kerns)
    kerns.append(ip)


def clear_graph():
    kerns_to_node_map = {}
    kerns = []
    node_to_kern_map = {}
    kerns_rev = {}

def add_ip(ip, node):

    add_logical_ip(ip)
    kerns_to_node_map[len(kerns) - 1] = node
    node_to_kern_map[node].append(len(kerns) - 1)


def printFPGAGraphs():
    
    #fpga_num = 4
    for fpga_num in range(0, len(map_dict)):
    #if fpga_num == 4:
        _G = networkx.DiGraph()


        for kern_idx, kern in enumerate(kerns):
            #print("kern['inst'] is " + kern['inst'])
#           # print("kern['kernel'] is " + kern['kernel'])
            #print("kerns_rev['inst'] is " + str(kerns_rev[kern['inst']]))
#           # print("kerns_rev['kernel'] is " + str(kerns_rev['kernel']))
            #print("kerns_to_node_map['inst'] is " + str(kerns_to_node_map[kerns_rev[kern['inst']]]))
            if(kerns_to_node_map[kerns_rev[kern['inst']]] == fpga_num):
                _G.add_node(str(kern_idx) + '_' + kern['inst']  , kern=kern['kernel'])

        for kern_idx, kern in enumerate(kerns):
            if kerns_to_node_map[kerns_rev[kern['inst']]] == fpga_num:
                #print("FINAL GRAPH KERN " +  str(kern))
                #print("FINGAL GRAPH KERN OUTPUTS" + str(kern['outputs']))
                #print("FINAL GRAPH KERN NUM OUTPUTS " + str(len(kern['outputs'])))
                for output in kern['outputs']:
                    if 'output_inst' in output:
                        if(kerns_to_node_map[kerns_rev[kern['inst']]] == fpga_num) and (kerns_to_node_map[kerns_rev[output['output_inst']]] == fpga_num):
                            #print("adding edge " + kern['inst'])
                            output_num = kerns_rev[output['output_inst']]
                            _G.add_edge(str(kern_idx) + '_' + kern['inst'], str(output_num) + '_' +  output['output_inst'], source_port=output['name'], sink_port=output['output_port'])


        print("FPGA " + str(fpga_num) + " graph")
        #print("KERNS_TO_NODE_MAP")
        #print(kerns_to_node_map)
        #print("KERNS_REV")
        #print(kerns_rev)
        #print("GRAPH")
        #print(graph_to_ascii(_G))
        #print("Done graph")



def createGraph(test=''):
    global kerns
    global kerns_rev
    global kern_dict
    global G
    global origin_node
    global kern_predec
    global kern_succ

    G = networkx.DiGraph()
    G_verbose = networkx.DiGraph()
    kern_predec = {}
    kern_succ = {}

    for kern in kerns:
        G.add_node(kern['inst'] , kern=kern['kernel'])
        G_verbose.add_node(kern['inst'] + ':' + str(kerns_rev[kern['inst']]) , kern=kern['kernel'])
            
        #if(kern['inst'] == 'layer100' and not(test=='')):
        #print(kerns_to_node_map)
        #print("create graph adding inst " + kern['inst'])
        #if(not(test=='') and (kerns_to_node_map[kerns_rev[kern['inst']]]>1)):
        #    contie
    for kern in kerns:
        #if(test == 'logical_file'):
        if(test == 'before_bridge'):
            print("Making Graph for kern " + kern['inst'] + ' outputs are ' + str(kern['outputs']))
        #print(test + " IN GRAPH CREATION, KERN: " + kern['inst'])
        #if(kern['inst'] == 'layer100' and not(test=='')):
        #print(kerns_to_node_map)
        #if(not(test=='') and (kerns_to_node_map[kerns_rev[kern['inst']]]>1)):
        #    continue
        #if 'note' in kern:
        #    if 'bram' in kern['note']:
        #        continue
        #print(kern)
        for output in kern['outputs']:
            if 'output_inst' in output:
                if kern['inst'] == 'layer118' and output['output_inst'] == 'layer120':
                    print("FINAL KERN " + str(kern))
                if(test == 'logical_file'):
                    print("In Graph Edge formation " + kern['inst'] + " between and " + output['output_inst'])
                #print(test + " IN GRAPH CREATION, EDGE: " + output['output_inst'])
                #print(test + " IN GRAPH CREATION, KERNEL: " + str(kerns[kerns_rev[output['output_inst']]]))
                G.add_edge(kern['inst'], output['output_inst'], source_port=output['name'], sink_port=output['output_port'])
                G_verbose.add_edge(kern['inst'] + ':' + str(kerns_rev[kern['inst']]), output['output_inst'] + ':' + str(kerns_rev[output['output_inst']]), source_port=output['name'], sink_port=output['output_port'])
#                G_verbose.add_node(kern['inst'] + ':' + str(kerns_rev[kern['inst']]) , kern=kern['kernel'])
                if kern['inst'] in kern_succ:
                    kern_succ[kern['inst']].append(output['output_inst'])
                else:
                    kern_succ[kern['inst']] = [output['output_inst']]

                if output['output_inst'] in kern_predec:
                    kern_predec[output['output_inst']].append(kern['inst'])
                else:
                    kern_predec[output['output_inst']] = [kern['inst']]
                #for _input in kerns[kerns_rev[output['output_inst']]]['inputs']:
                #    print(" TESTING GRAPH CREAATION WITH " + str(_input) + " and " + str(output))
            elif 'slave' in output:
                if(test == 'logical_file'):
                    print("In Graph Edge formation " + kern['inst'] + " between and " + kerns[output['slave']['node']]['inst'])
                print(kern['inst'])
                print(output)
                G.add_edge(kern['inst'], kerns[output['slave']['node']]['inst'], source_port=output['name'], sink_port=output['slave']['port'])
                G_verbose.add_edge(kern['inst'] + ':' + str(kerns_rev[kern['inst']]), kerns[output['slave']['node']]['inst'] + ':' + str(output['slave']['node']), source_port=output['name'], sink_port=output['slave']['port'])
                
                if kern['inst'] in kern_succ:
                    kern_succ[kern['inst']].append(kerns[output['slave']['node']]['inst'])
                else:
                    kern_succ[kern['inst']] = [kerns[output['slave']['node']]['inst']]
                
                if kerns[output['slave']['node']]['inst'] in kern_predec:
                    kern_predec[kerns[output['slave']['node']]['inst']].append(kern['inst'])
                else:
                    kern_predec[kerns[output['slave']['node']]['inst']] = [kern['inst']]
                #for _input in kerns[kerns_rev[output['output_inst']]]['inputs']:

    #if origin node hasn't been set, set it to the first kernel
    if origin_node == '':
        origin_node = kerns[0]['inst']
    kerns_temp = kerns
    kerns_rev_temp = kerns_rev

    #node_to_kern_map_temp = node_to_kern_map
    kerns_rev_temp = kerns_rev
    kerns_temp = kerns
    kerns_to_node_map_temp = kerns_to_node_map
    clear_graph()
    #kerns = []
    #kerns_rev = {}
    #kern_dict = []

    for edge in networkx.bfs_edges(G, origin_node):
        if not(edge[0] in  kerns_rev_temp):
            add_ip(kerns_temp[kerns_rev_temp[edge[0]]], kerns_to_node_map_temp[kerns_rev[edge[0]]])
            
            #kerns_rev[edge[0]] = len(kerns)
            #kerns.append(kerns_temp[kerns_rev_temp[edge[0]]])
            #kern_elem = logical_kernel_element(edge[0],  len(kerns) - 1 )
            #print("ADDING KERNEL IN GRAPH: " + str(kern_elem))
            #kern_dict.append(kern_elem)
        if not(edge[1] in  kerns_rev):
            add_ip(kerns_temp[kerns_rev_temp[edge[1]]], kerns_to_node_map_temp[kerns_rev[edge[1]]])
            
            #kerns_rev[edge[1]] = len(kerns)
            #kerns.append(kerns_temp[kerns_rev_temp[edge[1]]])
            ##print("edge[1] is " + edge[1])
            #kern_elem = logical_kernel_element(edge[1],  len(kerns) - 1 )
            #print("ADDING KERNEL IN GRAPH: " + str(kern_elem))
            #kern_dict.append(kern_elem)
    #if not(test==''):
    #    for node_idx, node in enumerate(node_to_kern_map):
    #        _G = networkx.DiGraph()
    #        file_ext = test + str(node_idx) + '.dot'
    #        print("writing graph to " + file_ext)
    #        for kern_idx, kern in enumerate(kerns):
    #            if kerns_to_node_map[kern_idx] == node_idx:
    #                _G.add_node(kern['inst'] , kern=kern['kernel'])
    #            for output in kern['outputs']:
    #                if 'output_inst' in output:
    #                    if (kerns_to_node_map[kerns_rev[output['output_inst']]] == node_idx) and (kerns_to_node_map[kern_idx]):
    #                        _G.add_edge(kern['inst'], output['output_inst'], source_port=output['name'], sink_port=output['output_port'])
    #                    print(test + " IN GRAPH CREATION, EDGE: " + output['output_inst'])
    #                    print(test + " IN GRAPH CREATION, KERNEL: " + str(kerns[kerns_rev[output['output_inst']]]))
    #        networkx.nx_pydot.write_dot(_G, file_ext)
    #        #plt.savefig(file_ext)

    #print(graph_to_ascii(G))


def createNode(nodes):
    
    #node_to_kern_map = []

    for node_idx, node in enumerate(nodes):
        node_to_kern_map.append([])
        for kernel in node['kernel']:
            kerns_to_node_map[kernel] = node_idx
            node_to_kern_map[node_idx].append(kernel)




    #tags input and output ports if its global or local
    for kern_id in range(0, len(kerns)):
        for m_axis_id, m_axis in enumerate(kerns[kern_id]['outputs']):
            #if there is a output defined and if on same node, will be already defined if on same node
            found = 0
            if (('dest' not in m_axis) and ('output_inst' in m_axis) and (m_axis['output_inst'] in kerns_rev)):
                for s_axis_id, s_axis in enumerate(kerns[kerns_rev[m_axis['output_inst']]]['inputs']):
                    if(s_axis['name'] == m_axis['output_port']):
                        #same node, local connection
                        if(kerns_to_node_map[kerns_rev[m_axis['output_inst']]] == kerns_to_node_map[kern_id]):
                            kerns[kerns_rev[m_axis['output_inst']]]['inputs'][s_axis_id]['global'] = 0
                            kerns[kerns_rev[m_axis['output_inst']]]['inputs'][s_axis_id]['master'] = {'node':kern_id, 'port':m_axis['name']}
                            kerns[kern_id]['outputs'][m_axis_id]['slave'] = {'node':kerns_rev[m_axis['output_inst']], 'port':s_axis['name']}
                            kerns[kern_id]['outputs'][m_axis_id]['local_node'] = kerns_rev[m_axis['output_inst']]
                            kerns[kern_id]['outputs'][m_axis_id]['local_port'] = s_axis_id
                            kerns[kern_id]['outputs'][m_axis_id]['global'] = 0
                            found = 1
                        break
            #if not found and 'bridge' not in kerns[kern_id]:
            #    kerns[kern_id]['outputs'][m_axis_id]['slave'] = {'node':len(kerns), 'port':"output"}
            #    kerns[kern_id]['outputs'][m_axis_id]['global'] = 0


def get_common_successor(succ_array):

    #print("in get common") 
    _succ_array = succ_array[1:]
    #print("first element in succ_array: ", succ_array[0])
    for i in succ_array[0]:
        found = True
        for succ_list in _succ_array:
            #print("i", i)
            #print("succ_list", succ_list)
            if i not in succ_list:
                #print(i, "not in succ_list")
                found = False
                break
        if found:
            #print("found in succ list")
            return i




def merge1to1Graph():

    cluster_1to1 = False

    G = networkx.DiGraph()
    origin_node = kerns[0]['inst']
    for kern in kerns:
        G.add_node(kern['inst'] , kern=kern['kernel'])

    for kern in kerns:
        for output in kern['outputs']:
            if 'output_inst' in output:
                G.add_edge(kern['inst'], output['output_inst'])

    #print("0:neighbors "  + str(G.neighbors(origin_node)))
    
    
    
    _node = origin_node

    #print("num nodes in graph", len(G.nodes)) 
    for node in G.nodes:
        edges = G.edges(node)
        #print("node " + str(node) +  " " + str(edges))
        
        # split node, figure out next merge node and make subgraph of all intermediate nodes 
        #if(len(edges) > 1):
        if(G.out_degree(node) > 1) and (cluster_1to1 == True):
            succ = {} 

            succ_array = []
            for neighbor in G.neighbors(node):
                succ = networkx.dfs_successors(G, source=neighbor)
                succ_array.append(succ)
            merge = get_common_successor(succ_array)
            #print("merge ", merge) 
            ip_core_list = [node]

            for succ_list in succ_array:
                for succ in succ_list.keys():
                    if succ not in ip_core_list:
                        ip_core_list.append(succ)
                    if (succ == merge):
                        break
            
            #print ("ip core list " + str(ip_core_list))
            ip_num_list = []
            for ip in ip_core_list:
                ip_num_list.append(kerns_rev[ip])
                if([kerns_rev[ip]] in ip_hier):
                    ip_hier.remove([kerns_rev[ip]])

            ip_hier.append(ip_num_list)
            #print(kerns_rev)
            #print("ip_hier_orig", ip_hier)
            #print("ip_num_orig", ip_num_list)
        else:
            ip_hier.append([kerns_rev[node]])
            #print("ip_hier_else", ip_hier)
    

def get_bram_size(ipDir, ip):
    fileName = ipDir + "/" + "resnet_" + ip['inst']  + "/solution1/syn/verilog/" + ip['inst'] + '_' + ip['kernel'] + '.v'
    file = open(fileName, "r")
    bram_dict = {}
    found_addr = False
    found_data = False
    for line in file:
        line_array = line.split()
        if(len(line_array) == 3):
            if(line_array[0] == "output" and line_array[2].endswith("_V_address0;")):
                addr_array = line_array[1].split(':')
                bram_dict['addr'] = int(addr_array[0][1:])
                found_addr = True
            if(line_array[0] == "output" and line_array[2].endswith("_V_d1;")):
                data_array = line_array[1].split(':')
                bram_dict['data'] = int(data_array[0][1:])
                found_data = True
        if(found_addr and found_data):
            break
    
    weights_dict[ip['inst']] = bram_dict


def createIPList(ipDict):
    global kerns_rev
    global kerns_to_node_map
    global kerns
    global node_num


    for ip in ipDict:
        kerns_rev[ip['inst']] = len(kerns)
        kerns_to_node_map[len(kerns)] = node_num
        if "bram_size" in ip: 
            get_bram_size(ipDir, ip)
            #if(((ip["bram_size"]/64)%64) == 0):
            #    weights_dict[ip['inst']] = int(((ip["bram_size"]/64)/8)*8)
            #else:
            #    weights_dict[ip['inst']] = int(math.ceil((ip["bram_size"]/64)/64)*64)

        for _id, _input in enumerate(ip['inputs']):
            ip['inputs'][_id]['global'] = 1
            ip['inputs'][_id]['local_node'] = 0
            ip['inputs'][_id]['local_port'] = 0

        for _id, _output in enumerate(ip['outputs']):
            ip['outputs'][_id]['global'] = 1
            ip['outputs'][_id]['local_node'] = 0
            ip['outputs'][_id]['local_port'] = 0
        
        add_logical_ip(ip)



def connect_nodes():

    for kern_id, kern in enumerate(kerns):
        if 'bridge' in kern and kern['bridge'] == "output":
            if 'dest' not in kern:
                dest = kerns_rev[kern['output_inst']] - 1
            else:
                dest = kern['dest']

            kerns[kern_id]["const"] = [{"name":"dest_V","val":dest, "width":16}]



def create_map_file(map_file_name, map_input=[], bridge=False):

    cluster_dict = {}
    createGraph()

    if bridge==True:
        for idx, node in enumerate(node_to_kern_map):
            map_element = {"board": "sidewinder", "comm":"udp", "type":"hw"}
            map_element["mac"] = map_input[idx]["mac"]
            map_element["ip"] = map_input[idx]["ip"]
            map_element["kernel"] = node
            map_dict.append(map_element)

        cluster_dict = {'cluster':{'node':map_dict}}
    else:
        cluster_dict = {'cluster':{'node':map_dict}}
        origin_node = kerns[0]['inst']
        floating_kernels = []
        _kerns_rev = {}
        for edge in networkx.bfs_edges(G, origin_node):
            if not(edge[0] in _kerns_rev):
                _kerns_rev[edge[0]] = kerns_rev[edge[0]]
                floating_kernels.append(kerns_rev[edge[0]])
            
            if not(edge[1] in _kerns_rev):
                _kerns_rev[edge[1]] = kerns_rev[edge[1]]
                floating_kernels.append(kerns_rev[edge[1]])
            
        #floating_kernels= list(kerns_rev.values())
        #floating_kernels.sort()
        #for i in ip_hier:
        #    floating_kernels.append(i)
        #print(floating_kernels)
        #cluster_dict = {'cluster':{'floating':ip_hier, 'comm':'udp', 'subnet':'10.1.3.0', 'starting_ip':'10.1.3.212'}}
        cluster_dict = {'cluster':{'floating': floating_kernels, 'comm':'udp', 'subnet':'10.1.3.0', 'starting_ip':'10.1.3.212'}}



    r = json.dumps(cluster_dict, indent=4, separators=(',', ': '), sort_keys=True)
    f = open(map_file_name, "w")
    f.write(str(r))
    f.close()


def add_kernel_to_dict(kernel_name, kern_id, bram=False):
    
    if 'bridge' in kerns[kerns_rev[kernel_name]]:
        if kerns[kerns_rev[kernel_name]]['bridge'] == 'input':
            for _input_idx, _input in enumerate(kerns[kerns_rev[kernel_name]]['inputs']):
                kerns[kerns_rev[kernel_name]]['inputs'][_input_idx]['global'] = 1 
                if 'slave' in  kerns[kerns_rev[kernel_name]]['inputs'][_input_idx]:
                    del kerns[kerns_rev[kernel_name]]['inputs'][_input_idx]['slave']

        elif kerns[kerns_rev[kernel_name]]['bridge'] == 'output':
            for _output_idx, _input in enumerate(kerns[kerns_rev[kernel_name]]['outputs']):
                kerns[kerns_rev[kernel_name]]['outputs'][_output_idx]['global'] = 1 
                if 'master' in  kerns[kerns_rev[kernel_name]]['outputs'][_output_idx]:
                    del kerns[kerns_rev[kernel_name]]['outputs'][_output_idx]['master']



    kerns[kerns_rev[kernel_name]]['logical'] = True
    kern_elem = logical_kernel_element(kerns[kerns_rev[kernel_name]]['inst'],  kern_id, False, bram, False)
    kern_id = kern_id + 1
    kern_dict_map[kerns_rev[kernel_name]] = len(kern_dict)
    kern_dict.append(kern_elem)
    return kern_id


def create_logical_file(logical_file_name, bridge=False):

    createGraph(test='logical_file')


    kern_id = 0
    for edge in networkx.bfs_edges(G, origin_node):
        #print( "edge " + str(edge) + " data " + (str(G.get_edge_data(edge[0], edge[1]))))
        if not('logical' in  kerns[kerns_rev[edge[0]]]):
            
            kern_id = add_kernel_to_dict(edge[0], kern_id)
            #kerns[kerns_rev[edge[0]]]['logical'] = True
            #kern_elem = logical_kernel_element(kerns[kerns_rev[edge[0]]]['inst'],  kern_id)
            #kern_id = kern_id + 1
            #kern_dict.append(kern_elem)
        if not('logical' in  kerns[kerns_rev[edge[1]]]):
            kern_id = add_kernel_to_dict(edge[1], kern_id)
            #kerns[kerns_rev[edge[1]]]['logical'] = True
            #kern_elem = logical_kernel_element(kerns[kerns_rev[edge[1]]]['inst'],  kern_id)
            #kern_id = kern_id + 1
            #kern_dict.append(kern_elem)


    #adding weights
    for kern_idx, kern in enumerate(kerns):
        if kern['outputs'] == []:
            print(kern)
            kern_id = add_kernel_to_dict(kern['inst'], kern_id, bram=True)

    #print(graph_to_ascii(G))

    cluster_dict = {'cluster':{'kernel':kern_dict}}
    #r = json.dumps(kern_dict)
    r = json.dumps(cluster_dict, indent=4, separators=(',', ': '), sort_keys=True)
    f = open(logical_file_name, "w")
    f.write(str(r))
    f.close()

def create_hierarchy(file_name, logicalFile_name, mapFile_name, ipDir):
    """ Given a json file creates the objects representing the cluster (globals defined at the top) """

    #layers = util.getDict("layers.json")
    top = util.getDict(file_name)
    global kern_num

    createIPList(top['ips'])
    #createGraph()
    kern_num = 0

    create_map_file(mapFile_name)
    create_logical_file(logicalFile_name)
    print(weights_dict)





def _add_output_bridge(output_kernel, dest, port_dest=None, source=None, slave_exists=True):
    
    if source == "output" or source == "output_1":
        output_idx = 0
    else:
        output_idx = 1

    output_bridge_ip = {
                #"outputs": [{"name":"bridge_output", "global":1, "bridge":"output"}],
                #"outputs": [{"name":"bridge_output", "global":0, "bridge":"output", "slave":{'node':len(kerns) + 1, 'port': 'input'}}],
                "const":{"name":"dest_V","val":int(dest), "width":16},
                "bridge":"output"
    }

    if slave_exists:
        output_bridge_ip["outputs"] = [{"name":"bridge_output", "global":0, "bridge":"output", "slave":{'node':len(kerns) + 1, 'port': 'input'}}]
    else:
        output_bridge_ip["outputs"] = [{"name":"bridge_output", "global":1, "bridge":"output"}]

    ext_kernel = kerns[kerns_rev[output_kernel]]
    ext_port = ext_kernel['outputs'][output_idx]
    
    #ext_port = ext_kernel['outputs'][0]
    output_bridge_ip["kernel"] = "output_" + str(ext_port['width']) +  "hls4ml_galapagos_output_bridge_" + str(ext_port['width'])
    output_bridge_ip["inst"] = 'hls4ml_output_bridge_' + str(output_kernel) + '_' + source
    #output_bridge_ip["inputs"] = [{"name":"output", "width":ext_port['width'], "master":{"node": kerns_rev[output_kernel], "port":ext_port['name']}, "global":0}]
    #output_bridge_ip["inputs"] = [{"name":"output", "width":ext_port['width'], "global":0}]
    node_idx = kerns_to_node_map[kerns_rev[output_kernel]]

    
    kerns[kerns_rev[output_kernel]]['outputs'][output_idx]['global'] = 0
    kerns[kerns_rev[output_kernel]]['outputs'][output_idx]['width'] = ext_port["width"]
    kerns[kerns_rev[output_kernel]]['outputs'][output_idx]['slave'] =  {'node':(len(kerns) ), 'port':'output'} 
    kerns[kerns_rev[output_kernel]]['outputs'][output_idx]['name'] = source 

    _kern_output = kerns[kerns_rev[output_kernel]]
    _kerns_kerns_rev_output_kernel =  kerns[kerns_rev[output_kernel]]['inst']
    if port_dest == None:
        output_bridge_ip["inputs"] = [{"name":"output", "width":ext_port['width'], "master":{"node": kerns_rev[output_kernel], "port":ext_port['name']}, "global":0}]
        output_bridge_ip["inputs"][0]['master'] = {"node":kerns_rev[output_kernel], "port":'output'}
        kerns[kerns_rev[output_kernel]]['outputs'][output_idx]['output_inst'] = 'hls4ml_output_bridge_' + output_kernel + '_' + source 
        kerns[kerns_rev[output_kernel]]['outputs'][output_idx]['output_port'] = "output"
    else:
        dest_encap_ip = {
            "outputs": [{"name":"output_r", "global": 0, "slave":{'node':len(kerns) + 1, 'port':'output'}, "output_inst": 'hls4ml_output_bridge_' + str(output_kernel) + '_' + source, "output_port": "output" }],
            "kernel":"header_const_encap",
            #"inst":'hls4ml_const_encap_port_' + str(dest[-1]) + '_kernel_' + str(output_kernel),
            "inst":'hls4ml_const_encap_port_' + str(dest) + '_kernel_' + str(output_kernel),
            "inputs":[{"name":"input_r", "global":0, "master":{"node":kerns_rev[output_kernel], "port":'output'}}],
            #"const":{"name":"header","val":int(dest[-1]), "width":16}
            "const":{"name":"header","val":int(port_dest), "width":16}
        }
        #kerns[kerns_rev[output_kernel]]['outputs'][output_idx]['output_inst'] =  'hls4ml_const_encap_port_' + str(dest[-1]) + '_kernel_' + str(output_kernel)
        kerns[kerns_rev[output_kernel]]['outputs'][output_idx]['output_inst'] =  'hls4ml_const_encap_port_' + str(dest) + '_kernel_' + str(output_kernel)
        kerns[kerns_rev[output_kernel]]['outputs'][output_idx]['output_port'] = "input_r"
        output_bridge_ip["inputs"] = [{"name":"output", "width":ext_port['width'], "master":{"node": len(kerns), "port":ext_port['name']}, "global":0}]
        add_ip(dest_encap_ip, node_idx)
    if 'dest' in ext_port:
        output_bridge_ip['dest'] = ext_port['dest']
    else:
        output_bridge_ip['output_inst'] = ext_port['output_inst']


    add_ip(output_bridge_ip, node_idx)


def _add_input_bridge(input_kernel, dest=None, sink=None, first=False):
    

    input_bridge_ip = {
            "inputs": [{"name":"bridge_in"}],
            "outputs": [],
            "bridge":"input"
        }
    
    if not first:
        input_bridge_ip["global"] = 0
        input_bridge_ip["slave"] = {"node": len(kerns) -1, "port": "output"}
    else:
        input_bridge_ip["global"] = 1 

            
            

    #ext_kernel is the kernel to add the bridge to, dereferenced by name
    ext_kernel = kerns[kerns_rev[input_kernel]]
    
    if sink == "input" or sink == "input_1":
        input_idx = 0
    else:
        input_idx = 1

    # ext_port is the input port to add a bridge to
    # TODO , currently adding it to first port, use cases happen to be single input port on external interface of cut
    # However will need to be updatec if the first kernel is a split kernel
    ext_port = ext_kernel['inputs'][input_idx]
    node_idx = kerns_to_node_map[kerns_rev[input_kernel]]

    input_bridge_name = "input_" + str(ext_port['width']) + "hls4ml_galapagos_input_bridge_" + str(ext_port['width'])
    input_bridge_ip['kernel'] = input_bridge_name
    input_bridge_ip["inst"] = 'hls4ml_input_bridge_' + str(input_kernel)
    input_bridge_ip["outputs"].append({"name":"input", "width":ext_port['width'], "output_inst": input_kernel, "output_port": sink, "global": 0, 
                "slave": {"node": kerns_rev[input_kernel], "port":"input"}, "bridge": 1, "note": ["ml2g", input_kernel, "input_bridge"]

                })

    kerns[kerns_rev[input_kernel]]['inputs'][input_idx]['global'] = 0
    kerns[kerns_rev[input_kernel]]['inputs'][input_idx]['name'] = "input"
   # kerns[kerns_rev[input_kernel]]['outputs'][input_idx]['width'] = ext_port["width"]

    #if input kernel does not have one input then we need to handle hierarchical routing
    if not(dest == None):
        #input bridge no longer connected to global switch
        input_bridge_ip["inputs"][0]["global"] = 0
        
        if dest == 'input1':
            port = "M00_AXIS"
        else:
            port = "M01_AXIS"

        
        if input_kernel not in input_bridges:
            input_bridge_ip["inputs"][0]['master'] = {"node":len(kerns) + 1, "port":port}
            input_bridges[input_kernel] = {"bridge":len(kerns) + 2, "port_switch":len(kerns) + 1, "decap":len(kerns)}

            #route output bridge to point to decap (output bridge is the last kernel added)

            #connect port input to decapsulatator
            port_switch_ip = {
                    "inputs": [{"name":"S00_AXIS", 'master':{'node':len(kerns), "port":"output_r"}, "global":0}],
                    "outputs": [{"name":"M00_AXIS", "global":0},{"name":"M01_AXIS", "global":0}],
                    "clk" : ["aclk"],
                    "aresetn": ["aresetn"],
                    "kernel" : "axis_switch",
                    "inst" : "port_switch_" + input_kernel,
                    "properties": [["CONFIG.HAS_TLAST.VALUE_SRC USER"],["CONFIG.NUM_SI {1}", "CONFIG.NUM_MI {2}", "CONFIG.HAS_TLAST {1}", "CONFIG.DECODER_REG {1}"]],
                    "note": ["ml2g", input_kernel, "port_switch"]
                }

            if dest == 'input1':
                port_switch_ip["outputs"][0]["master"] = {"node":len(kerns) + 2, "port":"bridge_input"}
                port_switch_ip["outputs"][0]["output_inst"] = input_bridge_ip["inst"] 
                port_switch_ip["outputs"][0]["output_port"] = "bridge_input"
            else:
                port_switch_ip["outputs"][1]["master"] = {"node":len(kerns) + 2, "port":"bridge_input"}
                port_switch_ip["outputs"][1]["output_inst"] = input_bridge_ip["inst"] 
                port_switch_ip["outputs"][1]["output_port"] = "bridge_input"

            decap_ip = {
                "kernel" : "decap_ip",
                "inst" : "decap_ip_" + input_kernel, 
                "inputs": [{"name": "input_r", "global":1}],
                #"outputs": [{"name":"output_r", "slave": {"node": len(kerns) + 1, "port":"S00_AXIS"}, "global":0, "output_inst": "port_switch_" + input_kernel, "output_port": "S00_AXIS"}]
                "outputs": [{"name":"output_r", "global":0, "output_inst": "port_switch_" + input_kernel, "output_port": "S00_AXIS"}],
                "note": ["ml2g", input_kernel, "port_switch"]
            }
            kerns[kerns_rev[input_kernel]]['inputs'][0]['master'] = {"node":len(kerns) + 2, "port":"input"}
#            kerns[kerns_rev[input_kernel]]['note'] =  ["ml2g", input_kernel, "input"]
            kerns[len(kerns) - 1]["outputs"][0]["output_inst"] = decap_ip["inst"]
            kerns[len(kerns) - 1]["outputs"][0]["output_port"] = "input_r" 
            add_ip(decap_ip, node_idx)
            add_ip(port_switch_ip, node_idx)
            add_ip(input_bridge_ip, node_idx)
        else:
            kerns[len(kerns) - 1]["outputs"][0]["output_inst"] = "decap_ip_" + input_kernel
            kerns[len(kerns) - 1]["outputs"][0]["output_port"] = "input_r" 
            input_bridge_ip["inputs"][0]['master'] = {"node":input_bridges[input_kernel], "port":port}
            add_ip(input_bridge_ip, node_idx)            
    else:
        input_bridge_index = len(kerns) 
        add_ip(input_bridge_ip, node_idx)
        _updating_kern = kerns[input_bridge_index]['inst']
        kerns[input_bridge_index]["outputs"][0]["slave"] = {"node":kerns_rev[input_kernel], "port":sink}
        kerns[input_bridge_index]["outputs"][0]["output_inst"] = input_kernel 
        kerns[input_bridge_index]["outputs"][0]["output_port"] = sink 
        kerns[input_bridge_index]['outputs'][0]['width'] = ext_port["width"]
        #kerns[input_bridge_index]["const"] = {"name":"dest","val":len(kerns), "width":16}
        kerns[kerns_rev[input_kernel]]['inputs'][input_idx]['master'] = {"node":input_bridge_index, "port":"input"}


def hierRoutingNeeded(source_ports, sink_ports, edge):

    sink_port = sink_ports[edge]



    num_external_predec = 0 

    if len(kern_predec[edge[1]]) > 1:
        for predec in kern_predec[edge[1]]:
            if not(kerns_to_node_map[kerns_rev[predec]] == kerns_to_node_map[kerns_rev[edge[1]]]):
                num_external_predec = num_external_predec + 1
            
    if num_external_predec > 1:
        return True
    else:
        return False


    #TODO currently cases where hierarchical routing is actually needed not in resnet50 due to partitioning, not verified, might need to add logic for TCL in extra switch 

#TODO currently no coe file, weights are 0, need to add COE file in HLS4ML and then import into weight
def addWeights(ipDir):
    
    for kern_idx, kern in enumerate(kerns):
        if "bram_size" in kern:
            weight_port_name = 'w' + str(kern['inst'][5:])
            get_bram_size(ipDir, kern)
            layer_name = kern['inst']
            master_node = kerns_rev[layer_name]
            bram_dict = weights_dict[layer_name]
            weight_mem = {
                    "clk" : ["clka", "clkb"],
                    "kernel" : "blk_mem_gen",
                    "inst" : "weight_mem_" + layer_name,
                    "outputs": [],
                    "inputs": [],
                    "properties": ["CONFIG.Memory_Type {Dual_Port_ROM}",
                                  "CONFIG.Enable_32bit_Address {false}", 
                                  "CONFIG.Use_Byte_Write_Enable {false}", 
                                  "CONFIG.Byte_Size {9}", 
                                  "CONFIG.Write_Width_A {" + str(bram_dict["data"]+1) + "}",
                                  "CONFIG.Write_Depth_A {" + str(int(pow(2,bram_dict["addr"]+1))) + "}", 
                                  "CONFIG.Read_Width_A {" + str(bram_dict["data"] + 1) +"}",
                                  "CONFIG.Operating_Mode_A {NO_CHANGE}",
                                  "CONFIG.Write_Width_B {" + str(bram_dict["data"] + 1) + "}",
                                  "CONFIG.Read_Width_B {" + str(bram_dict["data"] + 1) + "}",
                                  "CONFIG.use_bram_block {Stand_Alone}",
                                  "CONFIG.Enable_B {Use_ENB_Pin}",
                                  "CONFIG.Register_PortA_Output_of_Memory_Primitives {true}",
                                  "CONFIG.Register_PortB_Output_of_Memory_Primitives {true}"],
                    "wire_master": [
                                    {'name':'douta',
                                    'scope': 'local', 
                                    'slave':
                                        {'kernel_inst':
                                        {'inst': kern['inst'], 'kernel': kern['kernel'], 'node':kern_idx}, 
                                        'port': weight_port_name  + '_V_q0', 'node': kern_idx}},
                                    {'name':'doutb',
                                    'scope': 'local', 
                                    'slave':
                                        {'kernel_inst':
                                        {'inst': kern['inst'], 'kernel': kern['kernel'], 'node':kern_idx}, 
                                        'port': weight_port_name  + '_V_q1', 'node': kern_idx}}
                                        ],
                    "wire_slave": [
                                    {'name':'addra',
                                    'scope': 'local', 
                                    'master':
                                        {'kernel_inst':
                                        {'inst': kern['inst'], 'kernel': kern['kernel'], 'node':kern_idx}, 
                                        'port': weight_port_name  + '_V_address0', 'node': kern_idx}},
                                    {'name':'addrb',
                                    'scope': 'local', 
                                    'master':
                                        {'kernel_inst':
                                        {'inst': kern['inst'], 'kernel': kern['kernel'], 'node':kern_idx}, 
                                        'port': weight_port_name  + '_V_address1', 'node': kern_idx}}
                                        ]
            }
            kerns[kern_idx]["wire_slave"] = [
                                            {'name': weight_port_name +  '_V_q0',
                                               'scope': 'local', 
                                               'master': 
                                                {'kernel_inst':
                                                    {'inst': "weight_mem_" + layer_name, 'kernel': "blk_mem_gen", 'node':len(kerns)},
                                                'port': 'douta',
                                                'node': len(kerns)
                                                }},
                                            {'name': weight_port_name +  '_V_q1',
                                               'scope': 'local', 
                                               'master': 
                                                {'kernel_inst':
                                                    {'inst': "weight_mem_" + layer_name, 'kernel': "blk_mem_gen", 'node':len(kerns)},
                                                'port': 'doutb',
                                                'node': len(kerns)
                                                }}
                                                ]
            kerns[kern_idx]["wire_master"] = [
                                               {'name': weight_port_name +  '_V_address0',
                                               'scope': 'local', 
                                               'master': 
                                                {'kernel_inst':
                                                    {'inst': "weight_mem_" + layer_name, 'kernel': "blk_mem_gen", 'node':len(kerns)},
                                                'port': 'addra',
                                                'node': len(kerns)
                                                }},
                                               {'name': weight_port_name +  '_V_address1',
                                               'scope': 'local', 
                                               'master': 
                                                {'kernel_inst':
                                                    {'inst': "weight_mem_" + layer_name, 'kernel': "blk_mem_gen", 'node':len(kerns)},
                                                'port': 'addrb',
                                                'node': len(kerns)
                                                }}
                                                
                                                ]
            add_ip(weight_mem, kerns_to_node_map[kerns_rev[kern['inst']]])



def addBridges():
    global origin_node



    #print(graph_to_ascii(G))
    
    _add_input_bridge(origin_node, dest=None, sink='input')
    origin_node = kerns[len(kerns) - 1]['inst']
    
    #remake graph with new input bridge
    createGraph(test='before_bridge')

    #
    source_ports = networkx.get_edge_attributes(G,'source_port')
    sink_ports = networkx.get_edge_attributes(G,'sink_port')
    succ = networkx.dfs_successors(G, origin_node)[origin_node]


    last_edge = None
    edges_visted = {}
    for edge in networkx.bfs_edges(G, origin_node):
        edges_visited[edge] = 1
        source_port = source_ports[edge]
        sink_port = sink_ports[edge]
        sourceEdgeNode = kerns_to_node_map[kerns_rev[edge[0]]]
        sinkEdgeNode = kerns_to_node_map[kerns_rev[edge[1]]]

        if not(sourceEdgeNode == sinkEdgeNode):
            output_bridge_id = -1 
            input_port_name = ''
            for output_id, _output in enumerate(kerns[kerns_rev[edge[0]]]['outputs']):
                
                #destination is a single port
                
                if _output['name'] == source_port:
                    #RESNET 50 use case shouldn't trigger this
                    if hierRoutingNeeded(source_ports, sink_ports, edge):
                        _add_output_bridge(edge[0], kerns_rev[edge[1]], port_dest=kerns_rev[edge[0]], source=source_port)
                        _add_input_bridge(edge[1], dest=kerns_rev[edge[0]])
                    else:
                        _add_output_bridge(edge[0], kerns_rev[edge[1]], port_dest=None, source=source_port)
                        _add_input_bridge(edge[1], dest=None, sink=sink_port)

        last_edge = edge
    
    iterEdges = []
    for edge in networkx.bfs_edges(G, last_edge[1]):
        iterEdges.append(edge)
        last_edge = edge
    

    for edge in G.edges():
        if not (edge in edges_visited):
            edges_visited[edge] = 1
            source_port = source_ports[edge]
            sink_port = sink_ports[edge]
            sourceEdgeNode = kerns_to_node_map[kerns_rev[edge[0]]]
            sinkEdgeNode = kerns_to_node_map[kerns_rev[edge[1]]]
            print("CHECKING EDGE " +  str(edge))

            if not(sourceEdgeNode == sinkEdgeNode):
                output_bridge_id = -1 
                input_port_name = ''
                for output_id, _output in enumerate(kerns[kerns_rev[edge[0]]]['outputs']):
                    
                    #destination is a single port
                    if _output['name'] == source_port:
                        #RESNET 50 use case shouldn't trigger this
                        if hierRoutingNeeded(source_ports, sink_ports, edge):
                            _add_output_bridge(edge[0], kerns_rev[edge[1]], port_dest=kerns_rev[edge[0]], source=source_port)
                            _add_input_bridge(edge[1], dest=kerns_rev[edge[0]])
                        else:
                            _add_output_bridge(edge[0], kerns_rev[edge[1]], port_dest=None, source=source_port)
                            _add_input_bridge(edge[1], dest=None, sink=sink_port)



    while(len(iterEdges) > 0):
        iterEdges = []
        for edge in networkx.bfs_edges(G, last_edge[1]):
            iterEdges.append(edge)
            last_edge = edge


    if not (last_edge == None):
        _add_output_bridge(last_edge[1], 0, port_dest=None,  source='output', slave_exists=False)

def printKernelPlacements():
    for kern_idx, _kern in enumerate(kerns):
        print("kern " + str(kern_idx) + " " + _kern['inst'] + " on FPGA: " +  str(kerns_to_node_map[kern_idx]))


def addBuffers(logical_file_name, map_file_name):

    fifo_ip = {
        "ip":"fifo",
        "kernel": "axis_data_fifo",
        "properties": [],
        "inputs": [],
        "outputs": []
    }


    valid_fifo_depths = [16, 32, 64, 128, 512, 1024, 2048, 4096, 8192, 16384, 32768]
    
    for kern_idx, kern in enumerate(kern_dict):
        if "note" in kern:
            if "egress_fifo_depth" in kern['note']:
                for output_idx, output in enumerate(kern["m_axis"]):
                    if not(kern["note"]["egress_fifo_depth"] in valid_fifo_depths):
                        for _depth in valid_fifo_depths:
                            if(_depth> kern["note"]["egress_fifo_depth"]):
                                kern["note"]["egress_fifo_depth"] = _depth
                                break
                    fifo_ip["properties"] = ["CONFIG.FIFO_DEPTH {" + str(kern["note"]["egress_fifo_depth"]) + "}"]
                    fifo_ip["s_axis"] = {"name": "S_AXIS", "master": {"node": kern["num"], "port": output["name"]}, 'scope': 'local'}
                    print(kern)
                    print(output)
                    fifo_ip["m_axis"] = {"name": "M_AXIS", "slave": {"node": output["slave"]["node"], "port": output["slave"]["port"]}, 'scope': 'local'}
                    print(kern["note"])
                    fifo_ip["inst"] = "fifo_" + kern["note"]["inst"] + "_" + output["name"]
                    fifo_ip["depth"] = kern["note"]["egress_fifo_depth"]
                    kern_dict[kern_idx]["m_axis"][output_idx]["slave"]["node"] = len(kerns)
                    kern_dict[kern_idx]["m_axis"][output_idx]["slave"]["port"] = "S_AXIS"
                    print(kern_dict[kern_dict_map[fifo_ip["s_axis"]["master"]["node"]]])
                    kern_dict[kern_dict_map[fifo_ip["s_axis"]["master"]["node"]]]["s_axis"][output_idx]["master"]["node"] = len(kerns)
                    kern_dict[kern_dict_map[fifo_ip["s_axis"]["master"]["node"]]]["s_axis"][output_idx]["master"]["port"] = "M_AXIS" 
                    node_idx = kerns_to_node_map[kerns_rev[kern["note"]["inst"]]]
                    add_ip(fifo_ip, node_idx)
                    fifo_logical_element = logical_kernel_element(fifo_ip["inst"], 0, bridge=False, bram=True, fifo=True)
                    kern_dict.append(fifo_logical_element)

                    #map_dict[node_idx]["kernel"].append(len(kerns) - 1)
                #get_logical_element of fifo


    cluster_dict = {'cluster':{'kernel':kern_dict}}
    #r = json.dumps(kern_dict)
    r = json.dumps(cluster_dict, indent=4, separators=(',', ': '), sort_keys=True)
    f = open(logical_file_name, "w")
    f.write(str(r))
    f.close()

    cluster_dict = {'cluster':{'node':map_dict}}
    r = json.dumps(cluster_dict, indent=4, separators=(',', ': '), sort_keys=True)
    f = open(map_file_name, "w")
    f.write(str(r))
    f.close()
#    for kern_idx, kern in enumerate(kerns):
#        if "egress_fifo_depth" in kern:
#            for output_idx, output in enumerate(kern['outputs']):
#                kerns[kern_idx]['outputs'][output_idx]['output_inst'] = fifo_ip['inst'] 
#                kerns[kern_idx]['outputs'][output_idx]['output_port'] = "S_AXIS"
#                add_ip(fifo_ip, kerns_to_node_map[kern['inst']])
#            print("EGRESS " + kern['inst'] + " fifo depth is "  + str(kern["egress_fifo_depth"]))

def addBridgesAndWeights(netFile_name, logicalFile_name, mapFile_name, ipDir):

    net = util.getDict(netFile_name)
    mapFile = util.getDict(mapFile_name)


    #now can reference via layer name and kernel num


    createIPList(net['ips'])
    createNode(mapFile['cluster']['node'])
    createGraph()    
    addBridges()
    addWeights(ipDir)
    output_map = mapFile_name.split('.json')[0] + '_output.json'
    output_logical = logicalFile_name.split('.json')[0] + '_output.json'
    map_input = util.getDict(mapFile_name)['cluster']['node']
    create_map_file(output_map,map_input, True)
    create_logical_file(output_logical, True)
    addBuffers(output_logical, output_map)
    createGraph() 
    printFPGAGraphs()
#    print(graph_to_ascii(G))

if __name__=='__main__':

    try:
        opts, args = getopt.getopt(sys.argv[1:],"", ["mode=","netFile=", "mapFile=", "logicalFile=", "ipDir="])
    except:
        usage()
        sys.exit(2)

    netFile = None
    mapFile = None
    logicalFile = None
    mode = 'net'
    ipDir = None

    for o, a in opts:
        if o in ("--mode"):
            mode = a
        elif o in ("--netFile"):
            netFile = a
        elif o in ("--mapFile"):
            mapFile = a
        elif o in ("--logicalFile"):
            logicalFile = a
        elif o in ("--ipDir"):
            ipDir = a

    if (mode == 'net'):
        create_hierarchy(netFile, logicalFile, mapFile, ipDir)
    else:
        addBridgesAndWeights(netFile, logicalFile, mapFile, ipDir)



