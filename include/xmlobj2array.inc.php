<?php
function amstore_xmlobj2array($obj, $level=0) {
   
    $items = array();
   
    if(!is_object($obj)) return $items;
       
    $child = (array)$obj;
   
    if(sizeof($child)>1) {
        foreach($child as $aa=>$bb) {
            if(is_array($bb)) {
                foreach($bb as $ee=>$ff) {
                    if(!is_object($ff)) {
                        $items[$aa][$ee] = $ff;
                    } else
                    if(get_class($ff)=='SimpleXMLElement') {
                        $items[$aa][$ee] = amstore_xmlobj2array($ff,$level+1);
                    }
                }
            } else
            if(!is_object($bb)) {
                $items[$aa] = $bb;
            } else
            if(get_class($bb)=='SimpleXMLElement') {
                $items[$aa] = amstore_xmlobj2array($bb,$level+1);
            }
        }
    } else
    if(sizeof($child)>0) {
        foreach($child as $aa=>$bb) {
            if(!is_array($bb)&&!is_object($bb)) {
                $items[$aa] = $bb;
            } else
            if(is_object($bb)) {
                $items[$aa] = amstore_xmlobj2array($bb,$level+1);
            } else {
                foreach($bb as $cc=>$dd) {
                    if(!is_object($dd)) {
                        $items[$obj->getName()][$cc] = $dd;
                    } else
                    if(get_class($dd)=='SimpleXMLElement') {
                        $items[$obj->getName()][$cc] = amstore_xmlobj2array($dd,$level+1);
                    }
                }
            }
        }
    }

    return $items;
}