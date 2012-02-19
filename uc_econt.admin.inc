<?php

/**
 * ECONT shipping settings form
 */
function uc_econt_admin_settings() {
  $form = array();
  $pickup_addr_uc = (array) variable_get('uc_quote_store_default_address', new stdClass());
//  $pickup_addr_econt = _uc_econt_get_address($pickup_addr_uc);
  $url_options = array(t('Demo mode'), t('Live mode'));
  $instruction_returns = array(0 => t('Disabled'), 'shipping_returns' => t('Shipping and returns'), 'returns' => t('Returns'));
  $receipt = array('none' => t('Disabled'), 'dc' => t('Acknowledgment - DC'), 'dc_cp' => t('Acknowledgment + stock receipt - DC-CP'));
  $extra_declared_value = array(0 => t('Disabled'), 1 => t('Always On'), 2 => t('Users choose'));
  
  $country_name = db_result(db_query("SELECT country_name FROM {uc_countries} WHERE country_id = '%s'", $pickup_addr_uc['country']));
  
  $form['econt'] = array(
    '#type' => 'fieldset',
    '#title' => t('Econt shipping options'),
//    '#description' => 'fieldset description',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#weight' => '-1',
  );
  $form['econt']['pickup'] = array(
    '#type' => 'item',
    '#title' => t('Pickup address status'),
    '#value' => _econt_check_default_store_address(),
    '#description' => t('Econt shipping will be active only if default pickup address
      was filled on <a href="@url">Shipping quote settings</a> page and it is located in Bulgaria, !!! Current country is @country',
      array('@url' => url('admin/store/settings/quotes/edit'), '@country' => $country_name)),
    '#weight' => '1',
  );
  
  $form['econt']['uc_econt_eecont_url'] = array(
    '#type' => 'select',
    '#title' => t('Calculate delivery mode'),
    '#options' => $url_options,
    '#default_value' =>  variable_get('uc_econt_eecont_url', 'Demo mode'),
    '#description' => t("To test calculating delivery use Demo mode."),
  );
  /*
  $form['econt']['uc_econt_insurance'] = array(
    '#type' => 'checkbox',
    '#title' => t('Insurance'),
    '#default_value' => variable_get('uc_econt_insurance', '1'),
    '#description' => t('Insurance consignment'),
    '#weight' => '2',
  );*/
  $form['econt']['uc_econt_send_delivery_from'] = array(
    '#type' => 'radios',
    '#title' => t('Send delivery from'),
    '#default_value' => variable_get('uc_econt_send_delivery_from', '0'),
    '#options' => array(t('door'), t('Econt office')),
    '#description' => t('Send a consignment of Еcont office, or from your store door.'),
    '#weight' => '3',
  );
  $form['econt']['uc_econt_shop_pay_delivery'] = array(
    '#type' => 'textfield',
    '#title' => t('The Delivery is on behalf of the shop'),
    '#default_value' => variable_get('uc_econt_shop_pay_delivery', ''),
    '#description' => t('Delivery is charged to the store when the contract value is greater than this value, where less is paid by the customer. Value zero /0/ = always at the expense of Store. Blank field = always on behalf of Client.'),
    '#size' => 5,
    '#field_suffix' => variable_get('uc_currency_sign', ''),
    '#weight' => '4',
  );
  $form['econt']['uc_econt_fixed_price'] = array(
    '#type' => 'textfield',
    '#title' => t('Fixed delivery price'),
    '#default_value' => variable_get('uc_econt_fixed_price', '0'),
    '#description' => t('If ECONT website is unreachable to generate the price of delivery, this price is used as a ECONT delivery price.'),
    '#size' => 5,
    '#field_suffix' => variable_get('uc_currency_sign', ''),
    '#weight' => '5',
  );
  $form['econt']['uc_econt_sms_notification'] = array(
    '#type' => 'checkbox',
    '#title' => t('Sms notification of shipment'),
    '#default_value' => variable_get('uc_econt_sms_notification', '1'),
    '#description' => t('Sms notification of the store for a shipment.'),
    '#weight' => '6',
  );
  
  $form['econt']['uc_econt_invoice_before_pay'] = array(
    '#type' => 'checkbox',
    '#title' => t('Invoice before pay CD'),
    '#default_value' => variable_get('uc_econt_invoice_before_pay', '1'),
    '#description' => t('Enable uc_econt_invoice_before_pay.'),
    '#weight' => '7',
  );
  $form['econt']['uc_econt_pay_after_accept'] = array(
    '#type' => 'checkbox',
    '#title' => t('Pay after accept'),
    '#default_value' => variable_get('uc_econt_pay_after_accept', '1'),
    '#description' => t('Orders consignment to be inspected by the recipient and pay cash on delivery only if you ACCEPT my product.'),
    '#weight' => '8',
  );
  $form['econt']['uc_econt_pay_after_test'] = array(
    '#type' => 'checkbox',
    '#title' => t('Pay after test'),
    '#default_value' => variable_get('uc_econt_pay_after_test', '1'),
    '#description' => t('Orders consignment to be Inspected and Tested by recipient and to pay cash on delivery only if
I accept the goods.'),
    '#weight' => '9',
  );
  
  $form['econt']['uc_econt_instruction_returns'] = array(
    '#type' => 'select',
    '#title' => t('Pay for a canceled item'),
    '#options' => $instruction_returns,
    '#default_value' => variable_get('uc_econt_instruction_returns', 'returns'),
    '#description' => t('When refused shipment on account of the sender is the cost of selected activities. When Disabled, all expenses are charged to the customer.'),
    '#weight' => '10',
  );
  $form['econt']['uc_econt_receipt'] = array(
    '#type' => 'select',
    '#title' => t('Receipts'),
    '#options' => $receipt,
    '#default_value' => variable_get('uc_econt_receipt', '0'),
    '#description' => t('Acknowledgment DC / Acknowledgment + stock receipt DC-CP for shipping product.'),
    '#weight' => '10',
  );
  $form['econt']['uc_econt_dp'] = array(
    '#type' => 'checkbox',
    '#title' => t('Two-way shipment - DP'),
    '#default_value' => variable_get('uc_econt_dp', '1'),
    '#description' => t('Two-way shipment.'),
    '#weight' => '13',
  );
  
  $form['econt']['uc_econt_credit_customer_number'] = array(
    '#type' => 'textfield',
    '#title' => t('Econt customer number of credit payment'),
    '#default_value' => variable_get('uc_econt_credit_customer_number', ''),
    '#description' => t('Customer number for payment of the supply of credit by the sender. <a href="@url">Agreement.</a>', array('@url' => url('http://www.econt.com/dogovoreni_usloviq/'))),
    '#size' => 10,
    //'#field_suffix' => variable_get('uc_currency_sign', ''),
    '#weight' => '14',
  );
  $form['econt']['uc_econt_cod_agreement_number'] = array(
    '#type' => 'textfield',
    '#title' => t('Agreement number for COD'),
    '#default_value' => variable_get('uc_econt_cod_agreement_number', ''),
    '#description' => t('Number of payment for COD.'),
    '#size' => 10,
    //'#field_suffix' => variable_get('uc_currency_sign', ''),
    '#weight' => '15',
  );
  //Econt shipping Extra customer fields
  $form['customer_extra'] = array(
    '#type' => 'fieldset',
    '#title' => t('Econt Extra customer options'),
    '#description' => t('On the next fields, if enabled here customer will choose or set these options on checkout pane.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['customer_extra']['uc_econt_extra_date_priority'] = array(
    '#type' => 'checkbox',
    '#title' => t('Date priority'),
    '#default_value' => variable_get('uc_econt_extra_date_priority', '1'),
    '#description' => t('Enable the date priority.'),
    '#weight' => '1',
  );
  $form['customer_extra']['uc_econt_extra_time_priority'] = array(
    '#type' => 'checkbox',
    '#title' => t('Time priority'),
    '#default_value' => variable_get('uc_econt_extra_time_priority', '1'),
    '#description' => t('Enable the time priority.'),
    '#weight' => '2',
  );
  $form['customer_extra']['uc_econt_extra_declared_value'] = array(
    '#type' => 'select',
    '#title' => t('Declared value'),
    '#options' => $extra_declared_value,
    '#default_value' => variable_get('uc_econt_extra_declared_value', '0'),
    '#description' => t('Enable the field for declared value.'),
    '#weight' => '3',
  );
  $form['customer_extra']['uc_econt_auto_declared_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Auto declared value'),
    '#default_value' => variable_get('uc_econt_auto_declared_value', '0'),
    '#description' => t('Automatically enable option "declared value" for orders over that amount.'),
    '#size' => 5,
    '#field_suffix' => variable_get('uc_currency_sign', ''),
    '#weight' => '4',
  );
  $form['customer_extra']['uc_econt_extra_city_express'] = array(
    '#type' => 'checkbox',
    '#title' => t('Express services'),
    '#default_value' => variable_get('uc_econt_extra_city_express', '1'),
    '#description' => t('Enable city express / intercity express courier.'),
    '#weight' => '5',
  );
  //eEcont profile user
  $form['e_econt_client'] = array(
    '#type' => 'fieldset',
    '#title' => t('e-Econt client login data'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['e_econt_client']['uc_econt_e_econt_client_username'] = array(
    '#type' => 'textfield',
    '#title' => t('e-Econt username'),
    '#default_value' => variable_get('uc_econt_e_econt_client_username', 'demo'),
    '#description' => t('Client username on e-Econt profile'),
    '#size' => 15,
  );
  $form['e_econt_client']['uc_econt_e_econt_client_passwd'] = array(
    '#type' => 'password',
    '#title' => t('e-Econt password'),
    '#default_value' => variable_get('uc_econt_e_econt_client_passwd', 'demo'),
    '#description' => t('Client password on e-Econt profile, leave blank to not change current if it has been introduced.'),
    '#size' => 15,
  );
  
  $form['#submit'][] = 'uc_econt_admin_settings_form_submit';
  
  return system_settings_form($form);
}

//validate
function uc_econt_admin_settings_validate($form, &$form_state) {
  if ($form_state['values']['uc_econt_e_econt_client_passwd'] == '') {
//    drupal_set_message('validate ok', status);
    $form_state['values']['uc_econt_e_econt_client_passwd'] = variable_get('uc_econt_e_econt_client_passwd', 'demo');
  }
}

function uc_econt_admin_settings_form_submit($form, &$form_state) {
//  drupal_set_message('submit handler ok', status);
  //get cities from econt site and save in table uc_econt_cities
}


//
function _econt_check_default_store_address() {
  $pickup_addr_uc = (array) variable_get('uc_quote_store_default_address', new stdClass());
  $pickup_addr_econt = $pickup_addr_uc['country'];
  if ($pickup_addr_econt && $pickup_addr_uc['country'] == '100') {
    $output = '<span style="color:green; font-weight:bold">'. t('Completed') .':</span> ' . t('store address is available');
  }
  else {
    $output = '<span style="color:red; font-weight:bold">'. t('Not completed!') .'</span>';
  }
  return $output;
}

function _econt_import_cities() {
//  $cities_exist = db_result(db_query(""))

  include_once('uc_econt.xml_get_cities.inc');
  
  $sTmpFileName = '/tmp/get_cities_query.xml';
  //create file
  file_put_contents($sTmpFileName,$xmlStr);
    
    $eecont_service_url = 'http://demo.econt.com/e-econt/xml_service_tool.php';
    
    $ch = curl_init($eecont_service_url_); //!!!!! add _ of the end for test
    curl_setopt($ch, CURLOPT_POSTFIELDS, array('file' => "@$sTmpFileName"));
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_HTTPHEADER, array("Content-Type: text/xml; charset=utf-8", 'Expect: 100-continue'));
    curl_setopt($ch, CURLOPT_TIMEOUT, 3);
//    curl_setopt($ch, CURLOPT_HTTPHEADER, array ("Accept: application/json"));
    $responseResult = curl_exec($ch);
    $info = curl_getinfo($ch);
    $curl_error = curl_error($ch);
    curl_close($ch);
    
    
//    $sTmpFileCities = '/tmp/econt_cities.xml';
//    file_put_contents($sTmpFileCities,$responseResult);
    
//    if (file_exists($sTmpFileName)) {
//      unlink($sTmpFileName);
//    }
    
//    foreach($info as $key => $val) {
//      $info .= $key . ' ' . $val . ' : ';
//    }
    
    //parse the xml response
//    $dom_obj = new xml2array_parser($responseResult);
//    $data_arr = $dom_obj->array;
    
//    $cities = $data_arr['response']['cities']['e']['name'];
//    foreach($cities as $key => $val) {
//      $cities .= $val . ', ';
//    }
    
//    watchdog('uc_econt', '@info // @cities', array('@info' => $info['http_code'], '@cities' => $responseResult), WATCHDOG_NOTICE);
    
    
}

