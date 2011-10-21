<?php
define('EECONT_DEMO_MODE_URL', 'http://demo.econt.com/e-econt/xml_parcel_import.php');
define('EECONT_DEMO_SERVICE_URL', 'http://demo.econt.com/e-econt/xml_service_tool.php');
define('EECONT_LIFE_MODE_URL', 'http://www.econt.com/e-econt/xml_parcel_import.php');
define('EECONT_LIFE_SERVICE_URL', 'http://www.econt.com/e-econt/xml_service_tool.php');

//eecont url
function _eecont_url() {
  switch (variable_get('uc_econt_eecont_url', '')) {
    case 0:
      $eecont_url = EECONT_DEMO_MODE_URL;
      $eecont_tool_url = EECONT_DEMO_SERVICE_URL;
      break;
    case 1:
      $eecont_url = EECONT_LIFE_MODE_URL;
      $eecont_tool_url = EECONT_LIFE_SERVICE_URL;
      break;
  }
  
  return array($eecont_url, $eecont_tool_url);
}

//explode addres elements
function _street_and_opts($arg1, $arg2) {//street string
  switch($arg1) {
    case 'store':
      $point = 'store';
      break;
    case 'receiver':
      $point = 'delivery';
      break;
  }

  $street = explode(', ', $arg2);
  $opts_addr = array();
  
  if (is_array($street) == FALSE && strpos($street, '.') == FALSE && strlen($street) <= '3') {
    if ($arg1 == 'receiver' && strpos($street, ',') == FALSE) {
      $opts_addr['delivery_str_no'] = trim($arg2);
    }
  }
  
  foreach ($street AS $opt) {
    $s_avenue = '(^бул.|ул.)';
    $s_no = '(^№|No.|No|N)';
    $h_complex = '(^кв.|ж.к.)';
    
    $addr_string = '(^бул.|ул.|№|No.|No|N|кв.|ж.к.|бл.|вх.|ет.|ап.)';
    
    //ул. бул.
    if (preg_match($s_avenue, $opt, $matches)) {
      $avenue = substr($opt, strlen($matches['0']), strlen($opt));
      $opts_addr[$point . '_street'] = trim($matches['0']) . ' ' . trim($avenue);
    }
    //№
    if (preg_match($s_no, $opt, $matches)) {
      $str_no = substr($opt, strlen($matches['0']), strlen($opt));
      $opts_addr[$point . '_str_no'] = trim($str_no);
    }
    if (preg_match($addr_string, $opt, $matches) == '0') {
      $opts_addr['delivery_str_no'] = trim($arg2);
    }
    //кв. ж.к.
    if (preg_match($h_complex, $opt, $matches)) {
      $complex = substr($opt, strlen($matches['0']), strlen($opt));
      $opts_addr[$point . '_housing_complex'] = trim($matches['0']) . ' ' . trim($complex);//$complex;
    }
    
    //бл.
    if (strpos($opt, 'бл.') !== FALSE) {
      $data = explode('.', $opt);
      $opts_addr[$point . '_str_blok'] = trim($data['1']);
    }
    //вх.
    if (strpos($opt, 'вх.') !== FALSE) {
      $data = explode('.', $opt);
      $opts_addr[$point . '_str_entry'] = trim($data['1']);
    }
    //ет.
    if (strpos($opt, 'ет.') !== FALSE) {
      $data = explode('.', $opt);
      $opts_addr[$point . '_str_floor'] = trim($data['1']);
    }
    //ап.
    if (strpos($opt, 'ап.') !== FALSE) {
      $data = explode('.', $opt);
      $opts_addr[$point . '_str_apartment'] = trim($data['1']);
    }
    
  }

  return $opts_addr;
}