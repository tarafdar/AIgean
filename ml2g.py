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
debug = 0

def add_ip(ip, node):
    print(ip)
    kerns_rev[ip['inst']] = len(kerns)
    kerns_to_node_map[len(kerns)] = node
    node_to_kern_map[node].append(len(kerns))
    kerns.append(ip)

def create_node(node):

    global kern_num
    global node_num
    node_to_kern_map.append([])
    current_node_map = []
    metadata.append(node['metadata'])


    input_bridge_ip = {
                "inst": node['ips'][0]['inst'] + "_input_bridge",
                "inputs": [{"name":"bridge_in"}],
#                "wire_master" : [{"name":"iReset_out_V", "scope":"local"}],
                #"const" : [],
                "outputs": [],
                "bridge":"input"
            }
    output_bridge_ip = {
                "outputs": [{"name":"bridge_output", "global":1, "bridge":1}],
                "bridge":"output"
    }


    #check first ip in each node to see type of input bridge
    if len(node['ips'][0]['inputs']) == 1:
        width = node['ips'][0]['inputs'][0]['width']
        input_bridge_name = "hls4ml_galapagos_input_bridge_" + str(width)
#        input_bridge_ip["const"].append({"name":"width_V","val":width, "width":16})
        input_bridge_ip["outputs"].append({"name":"input", "width":width, "output_inst":node['ips'][0]["inst"], "output_port":node['ips'][0]["inputs"][0]["name"], "global":0})
    #two inputs
    else:
        input_bridge_name ="hls4ml_galapagos_input_bridge_two_in"
        for in_id, _input in enumerate(node['ips'][0]['inputs']):
            width = node['ips'][0]['inputs'][in_id]['width']
            #input_bridge_ip["const"].append({"name":"width_V","val":width, "width":16})
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
#        ip["wire_slave"] = {"name":"iReset", "master":{"node":kern_num, "port":"iReset_out_V"}, "scope":"local"}
        add_ip(ip, node_num)

    #connect input bridge to first kernel placed
    for in_id, _input in enumerate(kerns[kern_num+1]['inputs']):
        kerns[kern_num+1]['inputs'][in_id]['master'] = {'node':kern_num, 'port':"input_" + str(in_id)}

    #tags input and output ports if its global or local
    for kern_id in range(kern_num, len(kerns)):
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
            if not found and 'bridge' not in kerns[kern_id]:
                kerns[kern_id]['outputs'][m_axis_id]['slave'] = {'node':len(kerns), 'port':"output"}
                kerns[kern_id]['outputs'][m_axis_id]['global'] = 0
                output_bridge_ip["kernel"] = "hls4ml_galapagos_output_bridge_" + str(m_axis['width'])
                output_bridge_ip["inst"] = kerns[kern_id]["inst"] + '_output_bridge'
                output_bridge_ip["inputs"] = [{"name":"output", "width":m_axis['width'], "master":{"node": kern_id, "port":m_axis['name']}, "global":0}]
                if 'output_inst' in m_axis:
                    output_bridge_ip['output_inst'] = m_axis['output_inst']
                else: #dest
                    output_bridge_ip['dest'] = m_axis['dest']

                add_ip(output_bridge_ip, node_num)

            print("m_axis is:" + str(m_axis))


    kern_num=len(kerns) - 1
    node_to_kern_map.extend(current_node_map)
    node_num = node_num + 1

def connect_nodes():

    for kern_id, kern in enumerate(kerns):
        if 'bridge' in kern and kern['bridge'] == "output":
            if 'dest' not in kern:
                dest = kerns_rev[kern['output_inst']] - 1
            else:
                dest = kern['dest']

            kerns[kern_id]["const"] = [{"name":"dest_V","val":dest, "width":16}]

#def connect_nodes():
#    output_bridges = []
#
#
#    for kern_id, kern in enumerate(kerns):
#        output_bridge_ip = {
#                            "inst": kern["inst"] + '_output_bridge',
#                            "outputs": [{"name":"bridge_output", "global":1, "bridge":1}],
#                            "bridge":1
#
#                }
#
#
#
#        found = 0
#        #print(kern)
#        for output_id, output in enumerate(kern['outputs']):
#            # this output exists on another node
#            if output['global'] == 1 and 'bridge' not in output:
#                print("output is " + str(output))
#                if 'output_inst' in output:
#                    dest = kerns_rev[output['output_inst']] - 1
#                    kerns[output['master']]['outputs'][0]['dest'] = dest
#                    kerns[output['master']]['inst'] = kern["inst"] + '_output_bridge_' + output['output_inst']  + '_' + str(dest)
#                    kerns[output['master']]["const"] = [{"name":"dest_V","val":dest, "width":16}]
#                    kerns[output['master']]["inputs"] = [{"name":"output", "width":output['width']}]
#                    kerns[output['master']]['inputs'][0]['global'] = 0
#                    kerns[output['master']]['inputs'][0]['master'] = {'node':kern_id, 'port':output['name']}
#                    kerns[output['master']]["kernel"] = "hls4ml_galapagos_output_bridge_" + str(output['width'])
#                    kerns[kern_id]['outputs'][output_id]['output_inst'] = kern["inst"] + '_bridge'
#                    kerns[kern_id]['outputs'][output_id]['global'] = 0
#                    kerns[kern_id]['outputs'][output_id]['output_port'] = 'output'
#                    kerns[kern_id]['outputs'][output_id]['slave'] = {"node":(len(kerns)), "port":"output"}
#                    found = 1
#                elif 'dest' in output:
#                    dest = output['dest']
#                    kerns[output['master']]['outputs'][0]['dest'] = dest
#                    kerns[output['master']]['inst'] = kern["inst"] + '_output_bridge_dir_' + str(dest)
#                    kerns[output['master']]["const"] = [{"name":"dest_V","val":dest, "width":16}]
#                    kerns[output['master']]["inputs"] = [{"name":"output", "width":output['width']}]
#                    kerns[output['master']]['inputs'][0]['global'] = 0
#                    kerns[output['master']]['inputs'][0]['master'] = {'node':kern_id, 'port':output['name']}
#                    kerns[output['master']]["kernel"] = "hls4ml_galapagos_output_bridge_" + str(output['width'])
#                    kerns[kern_id]['outputs'][output_id]['output_inst'] = kern["inst"] + '_bridge'
#                    kerns[kern_id]['outputs'][output_id]['global'] = 0
#                    kerns[kern_id]['outputs'][output_id]['output_port'] = 'output'
#                    kerns[kern_id]['outputs'][output_id].pop('dest')
#                    kerns[kern_id]['outputs'][output_id]['slave'] = {"node":(len(kerns)), "port":"output"}
#                    found = 1
#                #if found:
#                #    add_ip(output_bridge_ip, kerns_to_node_map[kern_id])
#                #    break
#
#
#        #if found:
#        #    output_bridges.append([output_bridge_ip, kerns_to_node_map[kern_id]])
#
#        #for bridge in output_bridges:
#        #    add_ip(bridge[0], bridge[1])


def create_map_file(map_file_name):

    for idx, node in enumerate(node_to_kern_map):
        map_element = {"board": "sidewinder", "comm":"udp", "type":"hw"}
        map_element["mac"] = metadata[idx]["mac"]
        map_element["ip"] = metadata[idx]["ip"]
        map_element["kernel"] = node
        map_dict.append(map_element)

    cluster_dict = {'cluster':{'node':map_dict}}
    r = json.dumps(cluster_dict, indent=4, separators=(',', ': '), sort_keys=True)
    f = open(map_file_name, "w")
    f.write(str(r))

def create_logical_file(logical_file_name):


    for kern_id, kern in enumerate(kerns):
        kern_elem = {"clk":"ap_clk", "aresetn":"ap_rst_n", "vendor":"xilinx.com","lib":"hls"}
        if 'bridge' not in kern:
            kern_elem["#text"] = kern['inst'] + '_' + kern['kernel']
        else:
            kern_elem["#text"] = kern['kernel']

        kern_elem["s_axis"] = []
        for s_axis in kern['inputs']:
            if 'width' in s_axis:
                if debug:
                    loop_bound = 1
                else:
                    if(s_axis['width'] < 2048):
                        loop_bound = s_axis['width']
                    else:
                        loop_bound = 1024

                for i in range(loop_bound):
                    if s_axis['global']:
                        #kern_elem["s_axis"].append({"name":(s_axis["name"]+"_" + str(i)+ "_V_V"), "scope":"global"})
                        kern_elem["s_axis"].append({"name":(s_axis["name"]+"_" + str(i)), "scope":"global"})
                    else:
                        #master_port = str(kerns[s_axis['local_node']]['outputs'][s_axis['local_port']]['name'])+ "_" +str(i) + "_V_V"
                        print(kern)
                        print(s_axis)
                        #master_port = str(s_axis['master']['port'])+ "_" +str(i) + "_V_V"
                        master_port = str(s_axis['master']['port'])+ "_" +str(i)
                        #kern_elem["s_axis"].append({"name":(s_axis["name"]+"_" + str(i)+ "_V_V"), "scope":"local", "master": {"node": s_axis['master']['node'], "port": master_port}})
                        kern_elem["s_axis"].append({"name":(s_axis["name"]+"_" + str(i)), "scope":"local", "master": {"node": s_axis['master']['node'], "port": master_port}})
            else:
                kern_elem["s_axis"].append({"name":(s_axis["name"]), "scope":"global"})

        kern_elem["m_axis"] = []
        for m_axis in kern['outputs']:

            if 'width' in m_axis:
                if debug:
                    loop_bound = 1
                else:
                    if(m_axis['width'] < 2048):
                        loop_bound = m_axis['width']
                    else:
                        loop_bound = 1024

                for i in range(loop_bound):
                    if m_axis['global']:
                        kern_elem["m_axis"].append({"name":(m_axis["name"]+"_" + str(i)), "scope":"global"})
                        #kern_elem["m_axis"].append({"name":(m_axis["name"]+"_" + str(i)+ "_V_V"), "scope":"global"})
                    else:
                        print(m_axis)
                        slave_port = str(m_axis['slave']['port'])+ "_" +str(i) 
                        #slave_port = str(m_axis['slave']['port'])+ "_" +str(i) + "_V_V"
                        kern_elem["m_axis"].append({"name":(m_axis["name"]+"_" + str(i)), "scope":"local",  "slave": {"node": m_axis['slave']['node'], "port": slave_port}})
                        #kern_elem["m_axis"].append({"name":(m_axis["name"]+"_" + str(i)+ "_V_V"), "scope":"local",  "slave": {"node": m_axis['slave']['node'], "port": slave_port}})
            else:
                if m_axis['global']:
                    kern_elem["m_axis"].append({"name":m_axis["name"], "scope":"global"})
                else:
                    kern_elem["m_axis"].append({"name":m_axis["name"], "scope":"local"})

        if( "const" in kern):
            kern_elem["const"] = kern["const"]

        if("wire_master" in kern):
            kern_elem["wire_master"] = kern["wire_master"]

        if ("wire_slave" in kern):
            kern_elem["wire_slave"] = kern["wire_slave"]
        kern_elem["num"] = kern_id
        kern_elem["rep"] = 1
        kern_dict.append(kern_elem)

    cluster_dict = {'cluster':{'kernel':kern_dict}}
    #r = json.dumps(kern_dict)
    r = json.dumps(cluster_dict, indent=4, separators=(',', ': '), sort_keys=True)
    f = open(logical_file_name, "w")
    f.write(str(r))

def create_hierarchy(file_name):
    """ Given a json file creates the objects representing the cluster (globals defined at the top) """

    #layers = util.getDict("layers.json")
    top = util.getDict(file_name)
    global kern_num
    global node_num

    for node in top:
        create_node(node)

    kern_num = 0
    node_num = 0

    connect_nodes()

    local_kerns = kerns
    create_map_file("examples/resnet50_sample/map_aegean.json")
    create_logical_file("examples/resnet50_sample/logical_aegean.json",)

if __name__=='__main__':
    create_hierarchy("examples/resnet50_sample/resnet50.json")



