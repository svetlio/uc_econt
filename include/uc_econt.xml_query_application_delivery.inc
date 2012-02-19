<?php

  $doc = new DOMDocument('1.0','UTF-8');
  $doc->formatOutput = true;
	
  #parcels
  $parcel = $doc->createElement('parcels');
  $parcel = $doc->appendChild($parcel);

    #system
    $system = $doc->createElement('system');
    $system = $parcel->appendChild($system);
    #/system
    
      $validate = $doc -> createElement('validate');
      $validate = $system->appendChild($validate);
      $validate_val = $doc->createTextNode($validate_value);//1 - не се генерира товарителница, 0 - с генериране на товарителница
      $validate_val = $validate->appendChild($validate_val);
      
      $response_type = $doc -> createElement('response_type');
      $response_type = $system->appendChild($response_type);
      $response_type_val = $doc->createTextNode('XML');
      $response_type_val = $response_type->appendChild($response_type_val);
      
    #client
    $client = $doc->createElement('client');
    $client = $parcel->appendChild($client);
     
      $username = $doc -> createElement('username');
      $username = $client->appendChild($username);
      $username_val = $doc->createTextNode(variable_get('uc_econt_e_econt_client_username', 'demo'));
      $username_val = $username->appendChild($username_val);
      
      $password = $doc -> createElement('password');
      $password = $client->appendChild($password);
      $password_val = $doc->createTextNode(variable_get('uc_econt_e_econt_client_passwd', 'demo'));
      $password_val = $password->appendChild($password_val);
    #/client
      
    #loadings
    $loadings = $doc->createElement('loadings');
    $loadings = $parcel->appendChild($loadings);
    #/loadings
      #row
      $row = $doc->createElement('row');
      $row = $loadings->appendChild($row);
      #/row
        #sender
        $sender = $doc->createElement('sender');
        $sender = $row->appendChild($sender);
         
          $city = $doc -> createElement('city');
          $city = $sender->appendChild($city);
          $city_val = $doc->createTextNode($store_addr['city']);//'Варна'
          $city_val = $city->appendChild($city_val);
          
          $post_code = $doc -> createElement('post_code');
          $post_code = $sender->appendChild($post_code);
          $post_code_val = $doc->createTextNode($store_addr['postal_code']);
          $post_code_val = $post_code->appendChild($post_code_val);
          
          $name = $doc -> createElement('name'); //company name
          $name = $sender->appendChild($name);
          $name_val = $doc->createTextNode($store_addr['company'] ? $store_addr['company'] : $store_name_person);
          $name_val = $name->appendChild($name_val);
		  
		  $name_person = $doc -> createElement('name_person'); //name_person
          $name_person = $sender->appendChild($name_person);
          $name_person_val = $doc->createTextNode($store_addr['company'] ? $store_name_person : '');
          $name_person_val = $name_person->appendChild($name_person_val);
		  
		  $quarter = $doc -> createElement('quarter'); //quarter
          $quarter = $sender->appendChild($quarter);
          $quarter_val = $doc->createTextNode($store_addr['store_housing_complex']);
          $quarter_val = $quarter->appendChild($quarter_val);
		  
		  $street = $doc -> createElement('street'); //street
          $street = $sender->appendChild($street);
          $street_val = $doc->createTextNode($store_addr['store_street']);
          $street_val = $street->appendChild($street_val);
		  
		  $street_num = $doc -> createElement('street_num'); //street_num
          $street_num = $sender->appendChild($street_num);
          $street_num_val = $doc->createTextNode($store_addr['store_str_no']);
          $street_num_val = $street_num->appendChild($street_num_val);
		  
		  $street_bl = $doc -> createElement('street_bl'); //street_bl
          $street_bl = $sender->appendChild($street_bl);
          $street_bl_val = $doc->createTextNode($store_addr['store_str_blok']);
          $street_bl_val = $street_bl->appendChild($street_bl_val);
		  
		  $street_vh = $doc -> createElement('street_vh'); //street_vh
          $street_vh = $sender->appendChild($street_vh);
          $street_vh_val = $doc->createTextNode($store_addr['store_str_entry']);
          $street_vh_val = $street_vh->appendChild($street_vh_val);
		  
		  $street_et = $doc -> createElement('street_et'); //street_et
          $street_et = $sender->appendChild($street_et);
          $street_et_val = $doc->createTextNode($store_addr['store_str_floor']);
          $street_et_val = $street_et->appendChild($street_et_val);
		  
		  $street_ap = $doc -> createElement('street_ap'); //street_ap
          $street_ap = $sender->appendChild($street_ap);
          $street_ap_val = $doc->createTextNode($store_adr['store_str_apartment']);
          $street_ap_val = $street_ap->appendChild($street_ap_val);
		  
		  $street_other = $doc -> createElement('street_other'); //street_other
          $street_other = $sender->appendChild($street_other);
          $street_other_val = $doc->createTextNode($store_street_other);
          $street_other_val = $street_other->appendChild($street_other_val);
		  
		  $phone_num = $doc -> createElement('phone_num'); //phone_num
          $phone_num = $sender->appendChild($phone_num);
          $phone_num_val = $doc->createTextNode($store_addr['phone']);
          $phone_num_val = $phone_num->appendChild($phone_num_val);
		#/sender
		
        #receiver
        $receiver = $doc->createElement('receiver');
        $receiver = $row->appendChild($receiver);
         
          $city = $doc -> createElement('city');
          $city = $receiver->appendChild($city);
          $city_val = $doc->createTextNode($receiver_addr['city']);
          $city_val = $city->appendChild($city_val);
          
          $post_code_to = $doc -> createElement('post_code');
          $post_code_to = $receiver->appendChild($post_code_to);
          $post_code_to_val = $doc->createTextNode($receiver_addr['post_code']);
          $post_code_to_val = $post_code_to->appendChild($post_code_to_val);
	  
	  $office_code = $doc -> createElement('office_code');
          $office_code = $receiver->appendChild($office_code);
          $office_code_val = $doc->createTextNode($receiver_addr['selected_office']);
          $office_code_val = $office_code->appendChild($office_code_val);
		  
		  $name = $doc -> createElement('name'); //company name
          $name = $receiver->appendChild($name);
          $name_val = $doc->createTextNode($receiver_addr['name'] ? $receiver_addr['name'] : $receiver_addr['name_person']);
          $name_val = $name->appendChild($name_val);
		  
		  $name_person = $doc -> createElement('name_person'); //name_person
          $name_person = $receiver->appendChild($name_person);
          $name_person_val = $doc->createTextNode($receiver_addr['name'] ? $receiver_addr['name_person'] : '');
          $name_person_val = $name_person->appendChild($name_person_val);
		  
          $receiver_email = $doc -> createElement('receiver_email'); //receiver_email
          $receiver_email = $receiver->appendChild($receiver_email);
          $receiver_email_val = $doc->createTextNode($receiver_addr['email']);
          $receiver_email_val = $receiver_email->appendChild($receiver_email_val);
		  
		  $quarter = $doc -> createElement('quarter'); //quarter
          $quarter = $receiver->appendChild($quarter);
          $quarter_val = $doc->createTextNode($receiver_addr['delivery_housing_complex']);
          $quarter_val = $quarter->appendChild($quarter_val);
		  
		  $street = $doc -> createElement('street'); //street
          $street = $receiver->appendChild($street);
          $street_val = $doc->createTextNode($receiver_addr['delivery_street']);
          $street_val = $street->appendChild($street_val);
		  
		  $street_num = $doc -> createElement('street_num'); //street_num
          $street_num = $receiver->appendChild($street_num);
          $street_num_val = $doc->createTextNode($receiver_addr['delivery_str_no']);
          $street_num_val = $street_num->appendChild($street_num_val);
		  
		  $street_bl = $doc -> createElement('street_bl'); //street_bl
          $street_bl = $receiver->appendChild($street_bl);
          $street_bl_val = $doc->createTextNode($receiver_addr['delivery_str_blok']);
          $street_bl_val = $street_bl->appendChild($street_bl_val);
		  
		  $street_vh = $doc -> createElement('street_vh'); //street_vh
          $street_vh = $receiver->appendChild($street_vh);
          $street_vh_val = $doc->createTextNode($receiver_addr['delivery_str_entry']);
          $street_vh_val = $street_vh->appendChild($street_vh_val);
		  
		  $street_et = $doc -> createElement('street_et'); //street_et
          $street_et = $receiver->appendChild($street_et);
          $street_et_val = $doc->createTextNode($receiver_addr['delivery_str_floor']);
          $street_et_val = $street_et->appendChild($street_et_val);
		  
		  $street_ap = $doc -> createElement('street_ap'); //street_ap
          $street_ap = $receiver->appendChild($street_ap);
          $street_ap_val = $doc->createTextNode($receiver_addr['delivery_str_apartment']);
          $street_ap_val = $street_ap->appendChild($street_ap_val);
		  
		  $street_other = $doc -> createElement('street_other'); //street_other
          $street_other = $receiver->appendChild($street_other);
          $street_other_val = $doc->createTextNode($receiver_addr['delivery_str_other']);
          $street_other_val = $street_other->appendChild($street_other_val);
		  
		  $phone_num = $doc -> createElement('phone_num'); //phone_num
          $phone_num = $receiver->appendChild($phone_num);
          $phone_num_val = $doc->createTextNode($receiver_addr['phone']);
          $phone_num_val = $phone_num->appendChild($phone_num_val);
		  
		  $sms_no = $doc -> createElement('sms_no'); //store sms_no
          $sms_no = $receiver->appendChild($sms_no);
          $sms_no_val = $doc->createTextNode($_SESSION['store_sms_no']);
          $sms_no_val = $sms_no->appendChild($sms_no_val);
		#/receiver
          
        #shipment
        $shipment = $doc->createElement('shipment');
        $shipment = $row->appendChild($shipment);
         
          $shipment_type = $doc -> createElement('shipment_type');
          $shipment_type = $shipment->appendChild($shipment_type);
          $shipment_type_val = $doc->createTextNode('PACK');
          $shipment_type_val = $shipment_type->appendChild($shipment_type_val);
		  
		  $description = $doc -> createElement('description');
          $description = $shipment->appendChild($description);
          $description_val = $doc->createTextNode($_SESSION['order_description']);
          $description_val = $description->appendChild($description_val);
		  
		  $pack_count = $doc -> createElement('pack_count');
          $pack_count = $shipment->appendChild($pack_count);
          $pack_count_val = $doc->createTextNode('1');
          $pack_count_val = $pack_count->appendChild($pack_count_val);
          
          $weight = $doc -> createElement('weight');
          $weight = $shipment->appendChild($weight);
          $weight_val = $doc->createTextNode($delivery_weight);
          $weight_val = $weight->appendChild($weight_val);
          
          $tariff_code = $doc -> createElement('tariff_code');
          $tariff_code = $shipment->appendChild($tariff_code);
          $tariff_code_val = $doc->createTextNode($_SESSION['tariff_code']);//'4'$tariff_codes['0']
          $tariff_code_val = $tariff_code->appendChild($tariff_code_val);
          
          $tariff_sub_code = $doc -> createElement('tariff_sub_code');
          $tariff_sub_code = $shipment->appendChild($tariff_sub_code);
          $tariff_sub_code_val = $doc->createTextNode($_SESSION['tariff_subcode']);//$tariff_codes['1']
          $tariff_sub_code_val = $tariff_sub_code->appendChild($tariff_sub_code_val);
          //
          $invoice_before_pay_CD = $doc -> createElement('invoice_before_pay_CD');
          $invoice_before_pay_CD = $shipment->appendChild($invoice_before_pay_CD);
          $invoice_before_pay_CD_val = $doc->createTextNode(variable_get('uc_econt_invoice_before_pay', '0'));
          $invoice_before_pay_CD_val = $invoice_before_pay_CD->appendChild($invoice_before_pay_CD_val);
          
          $pay_after_accept = $doc -> createElement('pay_after_accept');
          $pay_after_accept = $shipment->appendChild($pay_after_accept);
          $pay_after_accept_val = $doc->createTextNode(variable_get('uc_econt_pay_after_accept', '0'));
          $pay_after_accept_val = $pay_after_accept->appendChild($pay_after_accept_val);
          
          $pay_after_test = $doc -> createElement('pay_after_test');
          $pay_after_test = $shipment->appendChild($pay_after_test);
          $pay_after_test_val = $doc->createTextNode(variable_get('uc_econt_pay_after_test', '0'));
          $pay_after_test_val = $pay_after_test->appendChild($pay_after_test_val);
          
          $instruction_returns = $doc -> createElement('instruction_returns');
          $instruction_returns = $shipment->appendChild($instruction_returns);
          $instruction_returns_val = $doc->createTextNode(variable_get('uc_econt_instruction_returns', 'returns'));
          $instruction_returns_val = $instruction_returns->appendChild($instruction_returns_val);
		  
		  $delivery_day = $doc -> createElement('delivery_day');
          $delivery_day = $shipment->appendChild($delivery_day);
          $delivery_day_val = $doc->createTextNode($delivery_date);//first posible date
          $delivery_day_val = $delivery_day->appendChild($delivery_day_val);
          
		#/shipment
          
        #payment
        $payment = $doc->createElement('payment');
        $payment = $row->appendChild($payment);
        #/payments
        
          $side = $doc -> createElement('side');
          $side = $payment->appendChild($side);
          $side_val = $doc->createTextNode($payment_side['payment_side']);//SENDER, RECEIVER
          $side_val = $side->appendChild($side_val);
		  
		  $method = $doc -> createElement('method');
          $method = $payment->appendChild($method);
          $method_val = $doc->createTextNode($_SESSION['delivery_payment_method']);
          $method_val = $method->appendChild($method_val);
	  //
          $key_word = $doc -> createElement('key_word');
          $key_word = $payment->appendChild($key_word);
          $key_word_val = $doc->createTextNode(variable_get('uc_econt_credit_customer_number', ''));
          $key_word_val = $key_word->appendChild($key_word_val);
          
          $receiver_share_sum = $doc -> createElement('receiver_share_sum');
          $receiver_share_sum = $payment->appendChild($receiver_share_sum);
          $receiver_share_sum_val = $doc->createTextNode($payment_side['share_sum']);
          $receiver_share_sum_val = $receiver_share_sum->appendChild($receiver_share_sum_val);
         
        #services
        $services = $doc->createElement('services');
	    $services = $row->appendChild($services);
          
	      $p = $doc -> createElement('p');
          $p = $services->appendChild($p);
          $p_val = $doc->createTextNode($_SESSION['time_value']);
          $p_val = $p->appendChild($p_val);
	        //attribute
	        $p_type = $doc -> createAttribute('type');
            $p_type = $p->appendChild($p_type);
            $p_type_val = $doc->createTextNode($_SESSION['time_type']);
            $p_type_val = $p_type->appendChild($p_type_val);
	   
	      $e = $doc -> createElement('e');
          $e = $services->appendChild($e);
          $e_val = $doc->createTextNode($_SESSION['service_e']);
          $e_val = $e->appendChild($e_val);
	  
	      $e1 = $doc -> createElement('e1');
          $e1 = $services->appendChild($e1);
          $e1_val = $doc->createTextNode($_SESSION['service_e1']);
          $e1_val = $e1->appendChild($e1_val);
	    
	      $e2 = $doc -> createElement('e2');
          $e2 = $services->appendChild($e2);
          $e2_val = $doc->createTextNode($_SESSION['service_e2']);
          $e2_val = $e2->appendChild($e2_val);
	  
	      $e3 = $doc -> createElement('e3');
          $e3 = $services->appendChild($e3);
          $e3_val = $doc->createTextNode($_SESSION['service_e3']);
          $e3_val = $e3->appendChild($e3_val);
	      
	  $dc = $doc -> createElement('dc');
          $dc = $services->appendChild($dc);
          $dc_val = $doc->createTextNode($_SESSION['dc']);
          $dc_val = $dc->appendChild($dc_val);
		  
	  $dc_cp = $doc -> createElement('dc_cp');
          $dc_cp = $services->appendChild($dc_cp);
          $dc_cp_val = $doc->createTextNode($_SESSION['dc_cp']);
          $dc_cp_val = $dc_cp->appendChild($dc_cp_val);
		  
	  $dp = $doc -> createElement('dp');
          $dp = $services->appendChild($dp);
          $dp_val = $doc->createTextNode($_SESSION['dp']);
          $dp_val = $dp->appendChild($dp_val);
		  
          $oc = $doc -> createElement('oc');
          $oc = $services->appendChild($oc);
          $oc_val = $doc->createTextNode($_SESSION['oc']);
          $oc_val = $oc->appendChild($oc_val);
		  
		  $cd = $doc -> createElement('cd');
          $cd = $services->appendChild($cd);
          $cd_val = $doc->createTextNode($_SESSION['order_total']);//наложен платеж стойност
          $cd_val = $cd->appendChild($cd_val);
	        //attribute
	        $cd_type = $doc -> createAttribute('type');
            $cd_type = $cd->appendChild($cd_type);
            $cd_type_val = $doc->createTextNode('GET');
            $cd_type_val = $cd_type->appendChild($cd_type_val);
			
		  $cd_agreement_num = $doc -> createElement('cd_agreement_num');
          $cd_agreement_num = $services->appendChild($cd_agreement_num);
          $cd_agreement_num_val = $doc->createTextNode(variable_get('uc_econt_cod_agreement_number', ''));//наложен платеж споразумение
          $cd_agreement_num_val = $cd_agreement_num->appendChild($cd_agreement_num_val);
        #/services

  #send request
  $xmlStr = $doc->saveXML();