<?php
/*
<?xml version="1.0" ?>
<request>
  <client>
    <username>demo</username>
    <password>demo</password>
  </client>
  <request_type>cities</request_type>
  <cities>
    <report_type>short</report_type>
    <city_name></city_name>
  </cities>
</request>
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
      $username_val = $doc->createTextNode('demo');
      $username_val = $username->appendChild($username_val);
      
      $password = $doc -> createElement('password');
      $password = $client->appendChild($password);
      $password_val = $doc->createTextNode('demo');
      $password_val = $password->appendChild($password_val);
      
    $request_type = $doc -> createElement('request_type');
    $request_type = $request->appendChild($request_type);
    $request_type_val = $doc->createTextNode('cities');
    $request_type_val = $request_type->appendChild($request_type_val);
      
    #cities
    $cities = $doc->createElement('cities');
    $cities = $request->appendChild($cities);
    #/cities
    
      $report_type = $doc -> createElement('report_type');
      $report_type = $cities->appendChild($report_type);
      $report_type_val = $doc->createTextNode('short');
      $report_type_val = $report_type->appendChild($report_type_val);
      
      $city_name = $doc -> createElement('city_name');
      $city_name = $cities->appendChild($city_name);
      $city_name_val = $doc->createTextNode('');
      $city_name_val = $city_name->appendChild($city_name_val);
      
#send request
  $xmlStr = $doc->saveXML();