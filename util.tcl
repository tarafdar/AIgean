proc connect_bus_V_V {width bus_1 bus_2} {
    
    for {set i 0} {$i < $width} {incr i} {
        
        set str_V_V "_V_V"
        set widthName "_"
        set widthName $widthName$i
        set bus_1_name $bus_1$widthName$str_V_V
        set bus_2_name $bus_2$widthName$str_V_V
        #puts $bus_1_name
        #puts $bus_2_name
        connect_bd_intf_net [get_bd_intf_pins $bus_1_name] [get_bd_intf_pins $bus_2_name]

    }

}

proc hier_connect_bus_V_V {hier width bus_1 bus_2} {
    
    set slash "/"
    set hier $hier$slash
    set bus_1 $hier$bus_1
    set bus_2 $hier$bus_2
    connect_bus_V_V $width $bus_1 $bus_2

}