import json
import util

kerns = []
kerns_rev = {}
kerns_to_node_map = {}
node_to_kern_map = []
metadata =[]

map_dict = []
kern_dict = []
input_bridges = []
output_bridges = []
global_kernels = []
kern_num = 0

node_num = 0


def add_ip(ip, node):
    print(ip)
    kerns_rev[ip['inst']] = len(kerns)
    kerns_to_node_map[len(kerns)] = node
    node_to_kern_map[node].append(len(kerns))
    kerns.append(ip)

def create_node(layers, node):

    global kern_num 
    global node_num
    node_to_kern_map.append([])
    current_node_map = []
    metadata.append(node['metadata'])
        
        
    input_bridge_ip = {
                "inst": node['ips'][0]['inst'] + "_input_bridge", 
                "inputs": [{"name":"bridge_in"}], 
                "wire_master" : ["iReset_out"],
                "const" : [],
                "outputs": []
            }



    #check first ip in each node to see type of input bridge
    if len(node['ips'][0]['inputs']) == 1:
        input_bridge_name = "hls4ml_galapagos_input_bridge_one_in"
        width = node['ips'][0]['inputs'][0]['width']
        input_bridge_ip["const"].append({"name":"width","val":width, "width":8})
        input_bridge_ip["outputs"].append({"name":"input", "width":width, "output_inst":node['ips'][0]["inst"], "output_port":node['ips'][0]["inputs"][0]["name"], "global":0})
    #two inputs
    else:
        input_bridge_name ="hls4ml_galapagos_input_bridge_two_in"
        for in_id, _input in enumerate(node['ips'][0]['inputs']):
            width = node['ips'][0]['inputs'][in_id]['width']
            input_bridge_ip["const"].append({"name":"width","val":width, "width":8})
            input_bridge_ip["outputs"].append({"name":"input_" + str(in_id) , "width":width, "output_inst":node['ips'][0]["inst"], "output_port":node['ips'][0]["inputs"][in_id]["name"], "global":0})

    input_bridge_ip["kernel"] = input_bridge_name
    add_ip(input_bridge_ip, node_num)     

    for ip in node['ips']:
        kerns_rev[ip['inst']] = len(kerns)
        kerns_to_node_map[len(kerns)] = node_num
        for _id, _input in enumerate(ip['inputs']):
            ip['inputs'][_id]['global'] = 1 
            ip['inputs'][_id]['local_node'] = 0 
            ip['inputs'][_id]['local_port'] = 0 
        
        for _id, _output in enumerate(ip['outputs']):
            ip['outputs'][_id]['global'] = 1 
            ip['outputs'][_id]['local_node'] = 0 
            ip['outputs'][_id]['local_port'] = 0
        ip["wire_slave"] = {"name":"iReset", "master":{"node":kern_num, "port":"iReset_out"}}
        add_ip(ip, node_num)
    
    #tags input and output ports if its global or local
    for kern_id in range(kern_num, len(kerns)):
        for m_axis_id, m_axis in enumerate(kerns[kern_id]['outputs']):
            #if there is a output defined and if on same node, will be already defined if on same node
            if (('dest' not in m_axis) and (m_axis['output_inst'] in kerns_rev)):
                for s_axis_id, s_axis in enumerate(kerns[kerns_rev[m_axis['output_inst']]]['inputs']):
                    if(s_axis['name'] == m_axis['output_port']):
                        #same node, local connection
                        if(kerns_to_node_map[kerns_rev[m_axis['output_inst']]] == kerns_to_node_map[kern_id]):
                            kerns[kerns_rev[m_axis['output_inst']]]['inputs'][s_axis_id]['global'] = 0
                            kerns[kerns_rev[m_axis['output_inst']]]['inputs'][s_axis_id]['local_node'] = kern_id
                            kerns[kerns_rev[m_axis['output_inst']]]['inputs'][s_axis_id]['local_port'] = m_axis_id
                            kerns[kern_id]['outputs'][m_axis_id]['local_node'] = kerns_rev[m_axis['output_inst']] 
                            kerns[kern_id]['outputs'][m_axis_id]['local_port'] = s_axis_id
                            kerns[kern_id]['outputs'][m_axis_id]['global'] = 0
                        else:
                            print("failing m_axis is:" + str(m_axis))
                        break
            print("m_axis is:" + str(m_axis))


    kern_num=len(kerns) - 1     
    node_to_kern_map.extend(current_node_map)
    node_num = node_num + 1

def connect_nodes(layers):
    output_bridges = []

    
    for kern_id, kern in enumerate(kerns):
        output_bridge_ip = {
                            "inst": kern["inst"] + '_output_bridge', 
                            "kernel": "hls4ml_galapagos_output_bridge", 
                            "inputs": [{"name":"output"}] 
                }



        found = 0
        #print(kern)
        for output_id, output in enumerate(kern['outputs']):
            # this output exists on another node
            if output['global'] == 1 and 'bridge' not in output:
                print("output is " + str(output))
                if 'output_inst' in output:
                    dest = kerns_rev[output['output_inst']]
                    output_bridge_ip['inst'] = kern["inst"] + '_output_bridge_' + output['output_inst']  + '_' + str(dest)
                    output_bridge_ip["const"] = [{"name":"dest","val":dest, "width":8}],
                    output_bridge_ip["outputs"] = [{"name":"output", "width":output['width'], "dest":dest, "global":1, "bridge":1}]
                    kerns[kern_id]['outputs'][output_id]['output_inst'] = kern["inst"] + '_bridge'
                    kerns[kern_id]['outputs'][output_id]['global'] = 0
                    kerns[kern_id]['outputs'][output_id]['output_port'] = 'output'
                    found = 1
                elif 'dest' in output:
                    dest = output['dest']
                    output_bridge_ip['inst'] = kern["inst"] + '_output_bridge_dir_' + str(dest)
                    output_bridge_ip["const"] = [{"name":"dest","val":dest, "width":8}],
                    output_bridge_ip["outputs"] = [{"name":"output", "width":output['width'], "dest":dest, "global":1, "bridge":1}]
                    kerns[kern_id]['outputs'][output_id]['output_inst'] = kern["inst"] + '_bridge'
                    kerns[kern_id]['outputs'][output_id]['global'] = 0
                    kerns[kern_id]['outputs'][output_id]['output_port'] = 'output'
                    kerns[kern_id]['outputs'][output_id].pop('dest')
                    found = 1
                if found:
                    break
        
        
        if found:
            output_bridges.append([output_bridge_ip, kerns_to_node_map[kern_id]])
    
    for bridge in output_bridges:
       add_ip(bridge[0], bridge[1]) 


def create_map_file(map_file_name):

    map_element = {"board": "sidewinder", "comm":"udp", "type":"hw"}
    for idx, node in enumerate(node_to_kern_map):
        map_element["mac"] = metadata[idx]["mac"]
        map_element["ip"] = metadata[idx]["ip"]
        map_element["kernel"] = node
        map_dict.append(map_element)
    r = json.dumps(map_dict, indent=4, separators=(',', ': '), sort_keys=True)
    f = open(map_file_name, "w")
    f.write(str(r))

def create_logical_file(layers, logical_file_name):


    for kern_id, kern in enumerate(kerns):
        kern_elem = {"clk":"ap_clk", "aresetn":"ap_rst_n"}
        
        kern_elem["#text"] = kern['inst'] + '_' + kern['kernel']
        for s_axis in kern['inputs']:
            kern_elem["s_axis"] = []
            if 'width' in s_axis: 
                for i in range(s_axis['width']):
                    if s_axis['global']:
                        kern_elem["s_axis"].append({"name":(s_axis["name"]+"_" + str(i)+ "_V_V"), "scope":"global"})
                    else:
                        master_port = str(kerns[s_axis['local_node']]['outputs'][s_axis['local_port']]['name'])+ "_" +str(i) + "_V_V"
                        kern_elem["s_axis"].append({"name":(s_axis["name"]+"_" + str(i)+ "_V_V"), "scope":"local", "master": {"node": s_axis['local_node'], "port": master_port}})
            else:
                kern_elem["s_axis"].append({"name":(s_axis["name"]), "scope":"global"})

        kern_elem["m_axis"] = []
        for m_axis in kern['outputs']:

            for i in range(m_axis['width']):
                if m_axis['global']:
                    kern_elem["m_axis"].append({"name":(m_axis["name"]+"_" + str(i)+ "_V_V"), "scope":"global"})
                else:
                    kern_elem["m_axis"].append({"name":(m_axis["name"]+"_" + str(i)+ "_V_V"), "scope":"local"})
        if( "const" in kern):
            kern_elem["const"] = kern["const"]
        
        if("wire_master" in kern):
            kern_elem["wire_master"] = kern["wire_master"]

        if ("wire_slave" in kern):
            kern_elem["wire_slave"] = kern["wire_slave"]
        kern_elem["node"] = kerns_to_node_map[kern_id]
        kern_elem["num"] = kern_id
        kern_dict.append(kern_elem)
    
    #r = json.dumps(kern_dict)
    r = json.dumps(kern_dict, indent=4, separators=(',', ': '), sort_keys=True)
    f = open(logical_file_name, "w")
    f.write(str(r))

def create_hierarchy(file_name):
    """ Given a json file creates the objects representing the cluster (globals defined at the top) """

    layers = util.getDict("layers.json")
    top = util.getDict(file_name)
    global kern_num
    global node_num 
    
    for node in top:
        create_node(layers, node)
    
    kern_num = 0
    node_num = 0
    
    connect_nodes(layers)

    create_map_file("map_aegean.json")
    create_logical_file(layers,"logical_aegean.json",)

if __name__=='__main__':
    create_hierarchy("aegean_test.json")
 


