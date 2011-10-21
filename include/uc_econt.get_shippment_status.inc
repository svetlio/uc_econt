<?php
//calculate only delivery price

  $doc = new DOMDocument('1.0','UTF-8');
  $doc->formatOutput = true;
	
  #requestss
  $requests = $doc->createElement('requests');
  $requests = $doc->appendChild($requests);
    
    #client
    $client = $doc->createElement('client');
    $client = $requests->appendChild($client);
    #/client
    
      $username = $doc -> createElement('username');
      $username = $client->appendChild($username);
      $username_val = $doc->createTextNode(variable_get('uc_econt_e_econt_client_username', 'demo'));
      $username_val = $username->appendChild($username_val);
      
      $password = $doc -> createElement('password');
      $password = $client->appendChild($password);
      $password_val = $doc->createTextNode(variable_get('uc_econt_e_econt_client_passwd', 'demo'));
      $password_val = $password->appendChild($password_val);
  
    
    $request_type = $doc -> createElement('request_type');
    $request_type = $requests->appendChild($request_type);
    $request_type_val = $doc->createTextNode('shipments');
    $request_type_val = $request_type->appendChild($request_type_val);
    
    $shipments = $doc -> createElement('shipments');
    $shipments = $requests->appendChild($shipments);
        //attribute
        $full_tracking = $doc -> createAttribute('full_tracking');
        $full_tracking = $shipments->appendChild($full_tracking);
        $full_tracking_val = $doc->createTextNode('ON');
        $full_tracking_val = $full_tracking->appendChild($full_tracking_val);
    
    $num = $doc -> createElement('num');
    $num = $shipments->appendChild($num);
    $num_val = $doc->createTextNode($loading_num);//1
    $num_val = $num->appendChild($num_val);
    
    //attributes
	$sender_city = $doc -> createAttribute('sender_city');
        $sender_city = $num->appendChild($sender_city);
        $sender_city_val = $doc->createTextNode($store_addr['city']);
        $sender_city_val = $sender_city->appendChild($sender_city_val);
        
        $receiver_city = $doc -> createAttribute('receiver_city');
        $receiver_city = $num->appendChild($receiver_city);
        $receiver_city_val = $doc->createTextNode($delivery_city);
        $receiver_city_val = $receiver_city->appendChild($receiver_city_val);
    
  #send request
  $xmlStr = $doc->saveXML();