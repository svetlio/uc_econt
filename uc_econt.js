Drupal.behaviors.uc_econt = function (context) {
  $("#edit-panes-delivery-delivery-city").blur(function () {
    
    var pc_url = 'postcode/callback/' + $(this).val();
    if ($(this).val() != '') {
      $.ajax({
        url: pc_url,
        success: function(data){
          var text = '';
          var pcodes = $("span.post_codes");
          var arrValues = data.post_code.split(',');
        
          if (arrValues[1]) {
            $('.post-code').remove();
            //read each element
            $.each( arrValues, function(i, l){
              pcodes.append($('<span class="post-code">' + l + '</span>'));
             });
          }
          else {
            $('.post-code').remove();
            $("#edit-panes-delivery-delivery-postal-code").val(arrValues[0]);
            
            var ordercitypostcode_url = 'ordercitypostcode/' + arrValues[0];
            $.ajax({
              url: ordercitypostcode_url
            });
          }
          $('#edit-panes-delivery-pref-opts-delivery-intercity-express-wrapper').removeClass('hideme');
          $('#edit-panes-delivery-pref-opts-delivery-city-express-wrapper').removeClass('hideme');
          
          var hideme = data.hideme;
          $(hideme).addClass("hideme");

          if (hideme == '#edit-panes-delivery-pref-opts-delivery-intercity-express-wrapper') {
            $('#edit-panes-delivery-pref-opts-delivery-intercity-express-wrapper input[type=checkbox]').removeAttr('checked');
            $('#edit-panes-delivery-pref-opts-delivery-intercity-express-wrapper input[type=checkbox]').val(0);
          }
        },
        dataType: 'json'
        //data: 'js=1' //Pass a key/value pair
      });
      $('#edit-panes-delivery-pref-opts-delivery-intercity-express-wrapper input[type=checkbox]').removeAttr('checked');
      $('#edit-panes-delivery-pref-opts-delivery-intercity-express-wrapper input[type=checkbox]').val(0);
      //return false;
    }
  });
  
  $('.post-code').live('click', function() {
    var pcode = $(this).text();
    $("#edit-panes-delivery-delivery-postal-code").val(pcode);
    
    var ordercitypostcode_url = 'ordercitypostcode/' + pcode;
    $.ajax({
      url: ordercitypostcode_url
    });
    //return false;
  });
  
  //declared value - oc
  if ($('#edit-panes-delivery-pref-opts-delivery-declared-value-wrapper input[type=checkbox]').attr('checked') == '') {
    $('#edit-panes-delivery-pref-opts-delivery-declared-value-wrapper input[type=checkbox]').val(0);
  }
  $('#edit-panes-delivery-pref-opts-delivery-declared-value-wrapper input[type=checkbox]').change( function() {
    var declared_value = $(this).attr('checked');
    if (declared_value == true) {
      $(this).val(1);
    }
    else if (declared_value == false) {
      $(this).val(0);
    }
  });
    
  $('.office').live('click', function() {
    $('.office').removeClass('selected');
    $(this).addClass('selected');
    var office_val = $('.selected').text();
    var selected_office_url = 'selected_office/' + office_val;
    $.ajax({
      url: selected_office_url
    });
    return false;
  });
  
  //intercity express
  if ($('#edit-panes-delivery-pref-opts-delivery-intercity-express-wrapper input[type=checkbox]').attr('checked') == '') {
    $('#edit-panes-delivery-pref-opts-delivery-intercity-express-wrapper input[type=checkbox]').val(0);
  }
  $('#edit-panes-delivery-pref-opts-delivery-intercity-express-wrapper input[type=checkbox]').change( function() {
    var icexpress = $(this).attr('checked');
    if (icexpress == true) {
      $(this).val(1);
    }
    else if (icexpress == false) {
      $(this).val(0);
    }
  });
  
  //show first posible date 
  $("#edit-panes-delivery-pref-opts-prefered-delivery-day").blur(function () {
    var today = $("#edit-panes-delivery-pref-opts-prefered-delivery-day").val();
    //alert (today);
    var pref_date_url = 'prefdeliverydate/' + today;
 
    $.ajax({
      url: pref_date_url,
      success: function(data){
        var dday = '';
        var delivery_days = $(".delivery-days");
        var arrDays = data.split(',');
        
        $('.dday').remove();
        if (arrDays[1]) {
          $.each( arrDays, function(i, l){
            delivery_days.append($('<span class="dday">' + l + '</span>'));
          });
        }
        else {
          $('.dday').remove();
        }
      },
      dataType: 'json'
    });
    //return false;
  });
  
  $('.dday').live('click', function() {
    var dday = $(this).text();
    $("#edit-panes-delivery-pref-opts-prefered-delivery-day").val(dday);
  });
  
  //set gmap url with city and street
  $("#edit-panes-delivery-delivery-street1").blur(function () {
    $('.e-plug').attr('href', '');
    var e_plug_href = 'http://plugins.econt.com/index.php/map_locator/index/F4F4F4/333333/0297D9/FFFFFF/1/900/450/1/999999/1/0297D9/FFFFFF/F4F4F4/FFFFFF/333333/bg';
    
    var delivery_city = $('#edit-panes-delivery-delivery-city').val();
    var delivery_street1 = $('#edit-panes-delivery-delivery-street1').val();
    //var e_plug_href = $('.e-plug').attr('href');
  
    if (delivery_street1 != '') {
      e_plug_href = e_plug_href + '/' + delivery_street1 + '/' + delivery_city;
      $('.e-plug').attr('href', e_plug_href);
    }
  });
  
  //open e-plugin office selector in popup
  $(function(){
    $('a.e-plug').click(function(){
        window.open(this.href, "popup_id", "scrollbars,resizable,width=900,height=450");
        return false;
    });
  });
//////////////////////////////
//aply changes to city, post code, street1 when selected address is changed
  $("#edit-panes-delivery-delivery-address-select").change(function () {
    //ToDo
    //clear office from delivery to office
    
    /////
    $('#edit-panes-delivery-pref-opts-delivery-econt-shipping-to').val(0);
    $('.office').remove();
    var selected_office_clear_url = 'selected_office/clear';
    $.ajax({
      url: selected_office_clear_url
    });
    $('.offices').addClass("hideme");
    
    var pcode = $("#edit-panes-delivery-delivery-postal-code").val();
    var ordercitypostcode_url = 'ordercitypostcode/' + pcode;
    //alert(ordercitypostcode_url);

    $.ajax({
      url: ordercitypostcode_url
    });
    
    //change street city on gmap link
    $('.e-plug').attr('href', '');
    var e_plug_href = 'http://plugins.econt.com/index.php/map_locator/index/F4F4F4/333333/0297D9/FFFFFF/1/900/450/1/999999/1/0297D9/FFFFFF/F4F4F4/FFFFFF/333333/bg';
    
    var delivery_city = $('#edit-panes-delivery-delivery-city').val();
    var delivery_street1 = $('#edit-panes-delivery-delivery-street1').val();
  
    if (delivery_street1 != '') {
      e_plug_href = e_plug_href + '/' + delivery_street1 + '/' + delivery_city;
      $('.e-plug').attr('href', e_plug_href);
    }

  });

}

///////////////////
$(document).ready(function(){
  
  //
  $('#edit-panes-delivery-pref-opts-delivery-econt-shipping-to').change( function() { 
    var d_office = $(this).val();
    
    if (d_office == '1') {
      var pcode = $("#edit-panes-delivery-delivery-postal-code").val();
      var ordercitypostcode_url = 'ordercitypostcode/' + pcode;
      //alert(ordercitypostcode_url);
      $.ajax({
        url: ordercitypostcode_url
      });
      
      $('.offices').removeClass("hideme");
      var get_offices_url = 'offices';
        
      $.ajax({
        url: get_offices_url,
        success: function(data){
          var to_office = $('.offices');
          var arrOffices = data.offices.split(',');
          $.each( arrOffices, function(i, text){
            to_office.append($('<span class="office"></span>').val(text).html(text));
          });
        },
        dataType: 'json'
      });
      return false;
    }
    else if (d_office == '0') {
      $('.office').remove();
      var selected_office_clear_url = 'selected_office/clear';
      $.ajax({
        url: selected_office_clear_url
      });
      $('.offices').addClass("hideme");
      return false;
    }
  });
/*
  //aply changes to city, post code, street1 when selected address is changed
  $("#edit-panes-delivery-delivery-address-select").change(function () {
    //ToDo
    //clear office from delivery to office
    
    /////
    $('#edit-panes-delivery-pref-opts-delivery-econt-shipping-to').val(0);
    $('.office').remove();
    var selected_office_clear_url = 'selected_office/clear';
    $.ajax({
      url: selected_office_clear_url
    });
    $('.offices').addClass("hideme");
    
    var pcode = $("#edit-panes-delivery-delivery-postal-code").val();
    var ordercitypostcode_url = 'ordercitypostcode/' + pcode;
    //alert(ordercitypostcode_url);

    $.ajax({
      url: ordercitypostcode_url
    });
    
    //change street city on gmap link
    $('.e-plug').attr('href', '');
    var e_plug_href = 'http://plugins.econt.com/index.php/map_locator/index/F4F4F4/333333/0297D9/FFFFFF/1/900/450/1/999999/1/0297D9/FFFFFF/F4F4F4/FFFFFF/333333/bg';
    
    var delivery_city = $('#edit-panes-delivery-delivery-city').val();
    var delivery_street1 = $('#edit-panes-delivery-delivery-street1').val();
  
    if (delivery_street1 != '') {
      e_plug_href = e_plug_href + '/' + delivery_street1 + '/' + delivery_city;
      $('.e-plug').attr('href', e_plug_href);
    }
  });
*/
});
