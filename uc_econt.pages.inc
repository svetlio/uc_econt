<?php

/*
 * generate econt shipping generate query order page
 */
function _econt_shipping_orders() {
  $page_content = t('Orders to generate shipping query on Econt site');
  $page_content .= _econt_shipping_table();
  return $page_content;
}

/*
 * generate econt reports
 */
function _econt_shipping_reports() {
  $page_content = t('Econt shipping Reports with statuses') . '<p>';
  
  $file_cities = drupal_get_path('module', 'uc_econt') . '/data/xml_service_tool.php.cities.xml';
  $file_quarters = drupal_get_path('module', 'uc_econt') . '/data/xml_service_tool.php.quarters.xml';
  $file_streets = drupal_get_path('module', 'uc_econt') . '/data/xml_service_tool.php.streets.xml';
  $file_offices = drupal_get_path('module', 'uc_econt') . '/data/xml_service_tool.php.offices.xml';

  $cities_exist = db_result(db_query("SELECT COUNT(post_code) FROM {uc_econt_cities}"));
  $quarters_exist = db_result(db_query("SELECT COUNT(city_post_code) FROM {uc_econt_quarters}"));
  $streets_exist = db_result(db_query("SELECT COUNT(name) FROM {uc_econt_streets}"));
  $offices_exist = db_result(db_query("SELECT COUNT(id) FROM {uc_econt_offices}"));


  if (file_exists($file_cities) && !$cities_exist) {
    $xml = simplexml_load_file($file_cities, 'SimpleXMLElement', LIBXML_NOCDATA);
    $p_cnt = count($xml->cities->e);
    $data = amstore_xmlobj2array($xml, 3);
    for($i = 0; $i < $p_cnt; $i++) {
      $vals = array();
      foreach ($data['cities']['cities'][$i] as $key => $val) {
        $vals[] = '\'' . $val . '\'';
        $values = implode(', ', $vals);
      }
      db_query("INSERT INTO {uc_econt_cities} (id, post_code, type, id_zone, name, name_en, id_country, id_office) VALUES(" . $values . ")");
    }
  }

  if (file_exists($file_quarters) && !$quarters_exist) {
    $xml = simplexml_load_file($file_quarters, 'SimpleXMLElement', LIBXML_NOCDATA);
    $p_cnt = count($xml->cities_quarters->e);
    $data = amstore_xmlobj2array($xml, 2);
    for($i = 1; $i < $p_cnt; $i++) {
      $vals = array();
      foreach ($data['cities_quarters']['cities_quarters'][$i] as $key => $val) {
        $vals[] = '\'' . $val . '\'';
        $values = implode(', ', $vals);
      }
      db_query("INSERT INTO {uc_econt_quarters} (id, name, name_en, city_post_code, id_city) VALUES(" . $values . ")");
    }
  }
  
  if (file_exists($file_streets) && !$streets_exist) {
    $xml = simplexml_load_file($file_streets, 'SimpleXMLElement', LIBXML_NOCDATA);
    $p_cnt = count($xml->cities_street->e);
    //$page_content .= $p_cnt . ' streets<p>';
    $data = amstore_xmlobj2array($xml, 2);
    for($i = 1; $i < $p_cnt; $i++) {
      $vals = array();
      foreach ($data['cities_street']['cities_street'][$i] as $key => $val) {
        $vals[] = '\'' . $val . '\'';
        $values = implode(', ', $vals);
      }
      db_query("INSERT INTO {uc_econt_streets} (id, name, name_en, city_post_code, id_city) VALUES(" . $values . ")");
    }
  }
  
  if (file_exists($file_offices) && !$offices_exist) {
    $xml = simplexml_load_file($file_offices, 'SimpleXMLElement', LIBXML_NOCDATA);
    $p_cnt = count($xml->offices->e);
    $data = amstore_xmlobj2array($xml, 2);
    for($i = 1; $i < $p_cnt; $i++) {
      $vals = array();
      $key_n = '1';
      foreach ($data['offices']['offices'][$i] as $key => $val) {
        
        //skip en ver
        if (substr($key, -3) == '_en') continue;
        
        $vals[] = '\'' . $val . '\'';
        $values = implode(', ', $vals);
        
        //get only what needed
        if ($key_n == '5') BREAK;
        $key_n++;
      }
      //$page_content .= $values . '<br />';
      db_query("INSERT INTO {uc_econt_offices} (id, name, office_code, address, id_city) VALUES(" . $values . ")");
    }
  }
  
    //$page_content .= 'Failed to open file or data already imported.';
    if ($cities_exist) {
      $page_content .= 'total ' . $cities_exist . ' cities<p>';
    }
    if ($quarters_exist) {
      $page_content .= 'total ' . $quarters_exist . ' quarters<p>';
    }
    if ($streets_exist) {
      $page_content .= 'total ' . $streets_exist . ' streets<p>';
    }
    if ($offices_exist) {
      $page_content .= 'total ' . $offices_exist . ' offices<p>';
    }
    
  
  $page_content .= $p_cnt;

  return $page_content;
}

//store admin oreder sipping econt
/**
 * Build the order admin Econt shipping table.
 */
function _econt_shipping_table() {

  $html = '';

  $header = array(array('data' => t('Order'), 'field' => 'order_id', 'sort' => 'desc'), // sort by name by default, a-z order
  //array('data' => t('Pay delivery'), 'field' => 'pay_delivery_side'),
  t('Delivery date'),
  t('Delivery name'),
  t('Delivery phone'),
  //t('Paymet method'),
  t('Bill of lading'),
  t('Download and print'),
  t('Delivery status'));

  $res = pager_query("SELECT*FROM {uc_econt_shipping}" . tablesort_sql($header), $limit = '20');

  $data = array();
  while ($row = db_fetch_array($res)) {
    $view_order = l($row['order_id'], 'admin/store/orders/' . $row['order_id'], array('attributes' => array('class' => 'view-order', 'title' => t('View order'))));
    $order_res = db_query("SELECT*FROM {uc_orders} WHERE order_id = '%s'", $row['order_id']);
    $order = db_fetch_array($order_res);
    
    //$user = user_load(array('uid' => $order['uid']));

    $pdf_link = l(t('download'), $row['pdf'], array('external' => TRUE, 'attributes' => array ('title' => t('Download application delivery pdf file'))));
    $row['pdf'] ? $pdf_link : $pdf_link = '';
    
    $row['loading_num'] ? $app_delivery = $row['loading_num'] : $app_delivery = drupal_get_form('application_delivery_for_order', $row['order_id']);
    
    $row['loading_num'] ? $delivery_status = drupal_get_form('check_delivery_status', $row['order_id']) : $delivery_status = '';
    
    
    $data[] = array($view_order, /*$row['pay_delivery_side'],*/ $row['delivery_date'], $order['delivery_first_name'], $order['delivery_phone'], /*$order['payment_method'],*/ $app_delivery, $pdf_link, $delivery_status);
  }
  $html .= theme('table', $header, $data);
  $html .= theme('pager');
  
  return $html;
}

//form application delivery
function application_delivery_for_order($form_state, $order_id) {
  
  $form['order_id'] = array(
    '#type' => 'hidden',
    '#title' => t('bar'),
    '#default_value' => $order_id,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Create for order') . ' ' . $order_id,
  );
  
  return $form;
}

//validate form application delivery
function application_delivery_for_order_validate($form, &$form_state) {
  $eurl = variable_get('uc_econt_eecont_url', '');
  //drupal_set_message("$eurl yo", notice);
}

// submit form application delivery
function application_delivery_for_order_submit($form, &$form_state) {
  global $user;
  
  $validate_value = '0';
  
  $order_id = $form_state['values']['order_id'];

  $store_addr = (array) variable_get('uc_quote_store_default_address', new stdClass());
  
  $store_addr_street1 = _street_and_opts('store', $store_addr['street1']);
  $store_addr_street2 = _street_and_opts('store', $store_addr['street2']);
  $store_addr = array_merge($store_addr, $store_addr_street1, $store_addr_street2);
  $store_addr['store_name_person'] = $store_addr['first_name'] . ' ' . $store_addr['last_name'];

  $store_sms_no = $store_addr['phone'];
  _store_sms_notify($store_sms_no);

  $store_street_other = variable_get('uc_econt_store_addr_str_other', '');
  
  //receiver and order info  
  $receiver_addr = _receiver_address($order_id);
  $receiver_addr['selected_office'] = db_result(db_query("SELECT selected_office FROM {uc_econt_shipping} WHERE order_id = '%s'", $order_id));

  //drupal_set_message($output);
  
  _econt_cod_cd_type($order_id);// $payment_method);
  
  _receiver_share_sum($order_id);

//  delivery_weight
  $delivery_weight = _delivery_weight($order_id);
  
  //payment side
  $payment_side = _payment_side($order_id);//get from tbl uc_econt_sipping
  //$delivery_payment_method = 'CASH'; //CASH, CREDIT
  
  //tariff_code
  _tariff_code($order_id);
  
  //services
  $services = _parcel_services($order_id);//get from tbl uc_econt_sipping
  
  //end of colect info for application delivery
  
  //create xml, file, send it, receive response
  include_once('include/uc_econt.xml_query_application_delivery.inc');
  
  //drupal_set_message($xmlStr);
  
  watchdog('uc_econt', 'application delivery: @xmlStr', array('@xmlStr' => $xmlStr), WATCHDOG_NOTICE);
  
  //filepath
  $sTmpFileName = file_directory_temp() . '/application_delivery_' . $receiver_addr['uid'] . '_' . $order_id . '.xml';
  //create file
  file_put_contents($sTmpFileName, $xmlStr);
  
  $eecont_url = _eecont_url();
    
  $ch = curl_init($eecont_url[0]); //!!!!! _
  curl_setopt($ch, CURLOPT_POSTFIELDS, array('file' => "@$sTmpFileName"));
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_TIMEOUT, 3);
  $responseResult = curl_exec($ch);
  $info = curl_getinfo($ch);
  $curl_error = curl_error($ch);
  curl_close($ch);
  
  //watchdog('uc_econt', '@xmlStr', array('@xmlStr' => $responseResult), WATCHDOG_NOTICE);
  //drupal_set_message($xmlStr);
  
  if (file_exists($sTmpFileName)) {
    //unlink($sTmpFileName);
  }
  
  //processing response - save in table, set message to wachdog, set message to user
    
  //parse xml response
  $dom_obj = new xml2array_parser($responseResult);
  $data_arr = $dom_obj->array;
    
  $loading_id = $data_arr['response']['result']['e']['loading_id'];// id на товарителница
  $loading_num = $data_arr['response']['result']['e']['loading_num'];//номер на товарителница
  $delivery_date = $data_arr['response']['result']['e']['delivery_date'];
//  $c = $data_arr['response']['result']['loading_price']['total'];
  $total_delivery_price = $data_arr['response']['result']['e']['loading_price']['total'];
  $sender_total = $data_arr['response']['result']['e']['loading_price']['sender_total'];
  $receiver_total = $data_arr['response']['result']['e']['loading_price']['receiver_total'];
  $other_total = $data_arr['response']['result']['e']['loading_price']['other_total'];
  $currency = $data_arr['response']['result']['e']['loading_price']['currency'];
  $error = $data_arr['response']['result']['e']['error'];
  $error_code = $data_arr['response']['result']['e']['error_code'];
  $pdf = $data_arr['response']['pdf']['blank_no'];
  $blank = $data_arr['response']['pdf']['blank_yes'];
  
  if ($info['http_code'] == 200) {
    if ($loading_num) {
      //update uc_econt_shipping loading_id loading_num pdf
      db_query("UPDATE {uc_econt_shipping} SET loading_id = '%d', loading_num = '%d', pdf = '%s', blank = '%s' WHERE order_id = '%d'", $loading_id, $loading_num, $pdf, $blank, $order_id);
    
      $message = "Генерирана е товарителница $loading_num за поръчка $order_id.";
      drupal_set_message("$message");
      watchdog('uc_econt', '@message', array('@message' => $message), WATCHDOG_NOTICE);
    }
    elseif ($error) {
      watchdog('uc_econt', '@error', array('@error' => $error), WATCHDOG_WARNING);
      drupal_set_message($error, 'error');
    }
    else {
      $message = $responseResult;
      drupal_set_message($message, 'error');
      watchdog('uc_econt', '@message', array('@message' => $message), WATCHDOG_ERROR);
    }
  }
  else {
    $message = $responseResult;
    drupal_set_message($message, 'error');
    watchdog('uc_econt', '@message', array('@message' => $message), WATCHDOG_ERROR);
  }
 
}

//form check delivery status
function check_delivery_status($form_state, $order_id) {
  
  $form['order_id'] = array(
    '#type' => 'hidden',
    '#title' => t('orderid'),
    '#default_value' => $order_id,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Check status') . ' ' . $order_id,
  );
  
  return $form;
}

function check_delivery_status_submit($form, &$form_state) {  
  $order_id = $form_state['values']['order_id'];
  
  $loading_num = db_result(db_query("SELECT loading_num FROM {uc_econt_shipping} WHERE order_id = '%s'", $order_id));
  $store_addr = (array) variable_get('uc_quote_store_default_address', new stdClass());
  $delivery_city = db_result(db_query("SELECT delivery_city FROM {uc_orders} WHERE order_id = '%d'", $order_id));
  
  include_once('include/uc_econt.get_shippment_status.inc');
  
  //watchdog('uc_econt', 'delivery status: @xmlStr', array('@xmlStr' => $xmlStr), WATCHDOG_NOTICE);
  
  //filepath
  $sTmpFileName = file_directory_temp() . '/shippment_status_' . $loading_num . '.xml';
  //create file
  file_put_contents($sTmpFileName, $xmlStr);
  
  $eecont_tool_url = _eecont_url();
  
  //drupal_set_message($eecont_tool_url[1]);
    
  $ch = curl_init($eecont_tool_url[1]); //!!!!! _
  curl_setopt($ch, CURLOPT_POSTFIELDS, array('file' => "@$sTmpFileName"));
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_TIMEOUT, 3);
  $responseResult = curl_exec($ch);
  $info = curl_getinfo($ch);
  $curl_error = curl_error($ch);
  curl_close($ch);
  
  //watchdog('uc_econt', '@xmlStr', array('@xmlStr' => $responseResult), WATCHDOG_NOTICE);
  //drupal_set_message($responseResult);
  
  if (file_exists($sTmpFileName)) {
    //unlink($sTmpFileName);
  }
  
  //parse xml response
  $dom_obj = new xml2array_parser($responseResult);
  $data_arr = $dom_obj->array;
    
  //$loading_num = $data_arr['response']['result']['e']['loading_num'];// num на товарителница
  $is_imported = $data_arr['response']['result']['e']['is_imported'];//1,0
  $receiver_person = $data_arr['response']['result']['e']['receiver_person'];
  $receiver_phone = $data_arr['response']['result']['e']['receiver_phone'];
  $receiver_time = $data_arr['response']['result']['e']['receiver_time'];
  $receiver_courier = $data_arr['response']['result']['e']['receiver_courier'];
  $receiver_courier_phone = $data_arr['response']['result']['e']['receiver_courier_phone'];
  $cd_get_sum = $data_arr['response']['result']['e']['CD_get_sum'];
  $cd_get_time = $data_arr['response']['result']['e']['CD_get_time'];
  $cd_send_sum = $data_arr['response']['result']['e']['CD_send_sum'];
  $cd_send_time = $data_arr['response']['result']['e']['CD_send_time'];
  
  $is_imported ? $shipment = t('Bill is triggered:') : $shipment = t('Bill is not triggered:');
  
  $titles = array(0 => 0, t('Date of delivery:'), t('Receiver:'), t('Receiver phone:'), t('Courier:'), t('Courier phone:'), t('Total CD:'), t('Date get CD:'), t('Date send CD:'), );
  
  $output = '';
  $output .= $shipment . $loading_num . '<br>';
  $output .= $titles['1'] . $receiver_time . '<br>';
  $output .= $titles['2'] . $receiver_person . '<br>';
  $output .= $titles['3'] . $receiver_phone . '<br>';
  $output .= $titles['4'] . $receiver_courier . '<br>';
  $output .= $titles['5'] . $receiver_courier_phone . '<br>';
  $output .= $titles['6'] . $cd_get_sum . '<br>';
  $output .= $titles['7'] . $cd_get_time . '<br>';
  $output .= $titles['8'] . $cd_send_time;
  
  drupal_set_message($output);
}

//payment side
function _payment_side($arg1) {
  if (variable_get('uc_econt_cod_tax', 0)) {
    $payment_side['payment_side'] = 'SENDER';
    //$payment_side['payment_side'] = strtoupper(db_result(db_query("SELECT pay_delivery_side FROM {uc_econt_shipping} WHERE order_id = '%s'", $arg1)));
    $payment_side['share_sum'] = db_result(db_query("SELECT delivery_price FROM {uc_econt_shipping} WHERE order_id = '%s'", $arg1));
    //$payment_side['share_sum'] = db_result(db_query("SELECT cod_tax FROM {uc_econt_shipping} WHERE order_id = '%s'", $arg1));
  }
  else {
    $payment_side['payment_side'] = strtoupper(db_result(db_query("SELECT pay_delivery_side FROM {uc_econt_shipping} WHERE order_id = '%s'", $arg1)));
    $payment_side['share_sum'] = 0;
  }
  return $payment_side;
}

//tariff_code
function _tariff_code($arg1) {
  $result = db_query("SELECT tariff_code, tariff_subcode FROM {uc_econt_shipping} WHERE order_id = '%s'", $arg1);
  $tariff_codes = db_fetch_object($result);
  
  $_SESSION['tariff_code'] = $tariff_codes -> tariff_code;
  $_SESSION['tariff_subcode'] = $tariff_codes -> tariff_subcode;
}

//shipping services - extras
function _parcel_services($arg1) {
  $order_pref_opts = db_query("SELECT*FROM {uc_econt_shipping} WHERE order_id = '%s'", $arg1);
  $pref_opts_fields = db_fetch_object($order_pref_opts);
  
  $_SESSION['delivery_payment_method'] = $pref_opts_fields -> delivery_payment_method;
  
  $time_type = array('BEFORE', 'IN', 'AFTER');
  
  $pref_opts_fields -> prefered_time_type ? $_SESSION['time_type'] = $time_type[$pref_opts_fields -> prefered_time_type - '1'] : $_SESSION['time_type'] = '';
  $pref_opts_fields -> prefered_time_value ? $_SESSION['time_value'] = $pref_opts_fields -> prefered_time_value : $_SESSION['time_value'] = '';

//  $result['city_express'] = $pref_opts_fields -> city_express;
  $result['declared_value'] = $pref_opts_fields -> declared_value;
  
  $pref_opts_fields -> service_e ? $_SESSION['service_e'] = $pref_opts_fields -> service_e : $_SESSION['service_e'] = '';
  $pref_opts_fields -> service_e1 ? $_SESSION['service_e1'] = $pref_opts_fields -> service_e1 : $_SESSION['service_e1'] = '';
  $pref_opts_fields -> service_e2 ? $_SESSION['service_e2'] = $pref_opts_fields -> service_e2 : $_SESSION['service_e2'] = '';
  $pref_opts_fields -> service_e3 ? $_SESSION['service_e3'] = $pref_opts_fields -> service_e3 : $_SESSION['service_e3'] = '';
  //dc / dc_cp
  switch (variable_get('uc_econt_receipt', 'dc')) {
    case 'dc':
      $_SESSION['dc'] = 'ON';
      $_SESSION['dc_cp'] = '';
      break;
    case 'dc_cp':
      $_SESSION['dc'] = '';
      $_SESSION['dc_cp'] = 'ON';
      break;
    case 'none':
      $_SESSION['dc'] = '';
      $_SESSION['dc_cp'] = '';
      break;
  }
  /*variable_get('uc_econt_dc', '') ? $_SESSION['dc'] = 'ON' : $_SESSION['dc'] = '';
  variable_get('uc_econt_dc_cp', '') ? $_SESSION['dc_cp'] = 'ON' : $_SESSION['dc_cp'] = '';
  variable_get('uc_econt_dp', '') ? $_SESSION['dp'] = 'ON' : $_SESSION['dp'] = '';
  */
  $order = db_query("SELECT*FROM {uc_order_products} WHERE order_id = '%s'", $arg1);
  while ($row = db_fetch_array($order)) {
    $order_total += $row['price'] * $row['qty'];
  }
  $_SESSION['order_total'] = $order_total;
    
  if ($result['declared_value'] > 0) {
    $_SESSION['oc'] = $order_total;
  }
  
  $result['delivery_price'] = db_result(db_query("SELECT rate FROM {uc_order_quotes} WHERE order_id = '%s'", $arg1));
  
  return $result;
}

function _store_sms_notify($arg1) {
  if (variable_get('uc_econt_sms_notification', '1')) {
    if (strpos($arg1, ','|'.')) {
      $nums = explode($arg1, ',');
    }
    else {
      $nums[] = $arg1;
    }
    
    foreach ($nums as $num) {
      $num = str_replace(' ', '', $num);
      if(strlen($num) == '10' && mb_substr($num, '0', '2') == '08') {
        $_SESSION['store_sms_no'] = $num;
        break;
      }
      else {
        $_SESSION['store_sms_no'] = '';
      }
    }
  }
}

//if payment method is econt cod, get value from receiver
function _econt_cod_cd_type ($arg1) {//, $arg2) {
  $order = uc_order_load($arg1);
  if ($order -> payment_method == 'uc_econt_cod') {
    $_SESSION['econt_cod_get'] = 'GET';   
    $_SESSION['econt_cod_get_value'] = $order -> order_total;
  }
  else {
    $_SESSION['econt_cod_get'] = '';
    $_SESSION['econt_cod_get_value'] = '';
  }
}

//receiver address
function _receiver_address($arg1) {
  $order = uc_order_load($arg1);//load order address
  $receiver_addr_street1 = array();
  $receiver_addr_street2 = array();
  if ($order -> delivery_street1) {
    $receiver_addr_street1 = _street_and_opts('receiver', $order -> delivery_street1);
  }
  
  if ($order -> delivery_street2) {
    $receiver_addr_street2 = _street_and_opts('receiver', $order -> delivery_street2);
  }
  $receiver_addr = array();
  $receiver_addr = array_merge($receiver_addr, $receiver_addr_street1, $receiver_addr_street2);
  $receiver_addr['post_code'] = $order -> delivery_postal_code;
  $receiver_addr['name'] = $order -> delivery_company;
  $receiver_addr['name_person'] = $order -> delivery_first_name . ' ' . $order -> delivery_last_name;
  $receiver_addr['city'] = $order -> delivery_city;
  $receiver_addr['phone'] = $order -> delivery_phone;
  $receiver_addr['email'] = $order -> primary_email;
  $receiver_addr['uid'] = $order -> uid;
  
  return $receiver_addr;
}

/**
 * set session cod_tax string if store pay cod tax is enabled
 */
function _receiver_share_sum($order_id) {
  
  if(variable_get('uc_econt_cod_tax', 0)) {
    $cod_tax = db_result(db_query("SELECT cod_tax FROM {uc_econt_shipping} WHERE order_id = '%s'", $order_id));
    $_SESSION['cod_tax'] = $cod_tax;
  }
}

//order weight
function _delivery_weight($arg1) {
  $result = db_query("SELECT*FROM {uc_order_products} WHERE order_id = '%s'", $arg1);
  while ($row = db_fetch_array($result)) {
    $delivery_weight = $delivery_weight + $row['weight'];
    $description[] = $row['title'] . '-' . $row['qty']; 
  }
  $_SESSION['order_description'] = implode(', ', $description);
  return $delivery_weight;
}

//download remote data for cities, streets,quarters, offices in separated files
function _econt_data_download() {
  $output = '';
  
  $output = 'download remote data for cities, streets,quarters, offices in separated files';
  
  //include_once('include/uc_econt.xml_query_application_delivery.inc');
  
  $file_to_send = drupal_get_path('module', 'uc_econt') . '/include/get_cities_query.xml';
  $eecont_tool_url = _eecont_url();
  
  $ch = curl_init($eecont_url[1]); //!!!!! _ 
  curl_setopt($ch, CURLOPT_POSTFIELDS, array('file' => "@$file_to_send"));
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_TIMEOUT, 3);
  $responseResult = curl_exec($ch);
  $info = curl_getinfo($ch);
  $curl_error = curl_error($ch);
  curl_close($ch);
  
  //watchdog('uc_econt', '@xmlStr', array('@xmlStr' => $responseResult), WATCHDOG_NOTICE);
  //drupal_set_message($xmlStr);
  
  if ($responseResult) {
    //filepath
    $sTmpFileName =  file_directory_path() . '/data/offices.xml';
    //create file
    file_put_contents($sTmpFileName, $responseResult);
    
    $output .= $responseResult;
  }
  
  return $output;
}

include_once('include/funcs.inc.php');
include_once('include/xml2array.inc.php');
include_once('include/xmlobj2array.inc.php');
