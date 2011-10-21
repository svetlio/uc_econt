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
      $password_val = $doc->createTextNode(variable_get('uc_econt_e_econt_client_username', 'demo'));
      $password_val = $password->appendChild($password_val);
  
    
    $request_type = $doc -> createElement('request_type');
    $request_type = $requests->appendChild($request_type);
    $request_type_val = $doc->createTextNode('delivery_days');//1
    $request_type_val = $request_type->appendChild($request_type_val);
    
    $delivery_days = $doc -> createElement('delivery_days');
    $delivery_days = $requests->appendChild($delivery_days);
    $delivery_days_val = $doc->createTextNode($date);//1
    $delivery_days_val = $delivery_days->appendChild($delivery_days_val);
    
  #send request
  $xmlStr = $doc->saveXML();