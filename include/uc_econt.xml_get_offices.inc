<?php
/*
<?xml version="1.0" encoding="UTF-8"?>
<requests>
  <client>
    <username>svetlios</username>
    <password>123456</password>
  </client>
  <request_type>offices</request_type>
</requests>

*/


  $doc = new DOMDocument('1.0','UTF-8');
  $doc->formatOutput = true;
	
  #requests
  $request = $doc->createElement('requests');
  $request = $doc->appendChild($request);

    #client
    $client = $doc->createElement('client');
    $client = $request->appendChild($client);
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
    $request_type = $request->appendChild($request_type);
    $request_type_val = $doc->createTextNode('offices');
    $request_type_val = $request_type->appendChild($request_type_val);
      
#send request
  $xmlStr = $doc->saveXML();