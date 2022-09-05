var gateway = `ws://${window.location.hostname}/ws`;
var websocket;

window.addEventListener('load', onload);

var message;
setInterval(tampilkanwaktu, 200);


function onload(event) {
  initWebsocket();
}

function initWebsocket() {
  console.log('trying to open a websocket connection....');
  websocket = new WebSocket(gateway);
  websocket.onopen = onOpen;
  websocket.onclose = onClose;
  websocket.onmessage = onMessage;
}

function onOpen(event) {
  console.log('Conection opened');
}

function onClose(event) {
  console.log('Conection close');
  setTimeout(initWebsocket, 2000);
}

function onMessage(event) {
  console.log(event.data);
  message = event.data;
  if (message == "jamOK") {
    document.getElementById("jam_reply").innerHTML = "OK";
  }
  else if (message == "almOK") {
     document.getElementById("alm_reply").innerHTML = "OK";
  }
}

function sendAlm() {
  document.getElementById("alm_reply").innerHTML = "Sending...";
  var alarmDt = document.getElementById("dalarm").value;
  alarmDt = alarmDt.split(":");
  var alarmSnd = alarmDt[0] + alarmDt[1]
  console.log(alarmSnd);
  websocket.send(`ALRM${alarmSnd}`);
}

function sendTime() {
  time();
  document.getElementById("jam_reply").innerHTML = "Sending...";
  var bulan = ("Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec");
  bulan = bulan.split(" ");

  var jam = (HH.length==1?"0"+HH:HH) + ":" + (MM.length==1?"0"+MM:MM) + ":" + (SS.length==1?"0"+SS:SS);
  var tanggal = bulan[BB] + " " + (DD.length==1?"0"+DD:DD) + " " + YY;
  websocket.send(`ALRM${jam}${tanggal}`);
}



// var HH ;    //memunculkan nilai jam
// var MM ; //ambil nilai menit    
// var SS ; //memunculkan nilai detik 
// var DAY;
// var DD ;
// var BB ;  
// var YY ;
// function sendBottom() {
//   var button_text = document.getElementById("Send_button").value;
//     if (button_text=="Syncronize"){
//       document.getElementById("Send_button").value = "Syncronize";
//       sendTime();
//     }
//   }

// function sendAlm(){
//   var data_alarm = document.getElementById("dalarm").value;
//   data_alarm = data_alarm.split(":");
//   // console.log(data_alarm);
//   var dAlarm = data_alarm[0] + data_alarm[1];
//   ajaxLoad('ALRM',dAlarm);

// } 
// function sendTime(){
//   time();
//   var bulan = ("Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec");
//   bulan = bulan.split(" ");

//   var jam = (HH.length==1?"0"+HH:HH) + ":" + (MM.length==1?"0"+MM:MM) + ":" + (SS.length==1?"0"+SS:SS);
//   var tanggal = bulan[BB] + " " + (DD.length==1?"0"+DD:DD) + " " + YY;
//   ajaxLoad('SYNC',tanggal + jam ); 
// }

// var ajaxRequest = null;
// if (window.XMLHttpRequest)  { ajaxRequest =new XMLHttpRequest(); }
// else{ ajaxRequest =new ActiveXObject("Microsoft.XMLHTTP"); }
// var str;

// function ajaxLoad(ajaxURL, str){
//   if(!ajaxRequest){ 
//     alert("AJAX is not supported."); 
//     return;
//   }
  
//   ajaxRequest.open("GET",ajaxURL + str,true);
//   ajaxRequest.onreadystatechange = function(){
//     if(ajaxRequest.readyState == 4 && ajaxRequest.status==200) {
//       var ajaxResult = ajaxRequest.responseText;
//       if( ajaxResult == "Syncron" )   { 
//       document.getElementById("jam_reply").innerHTML = ajaxResult;
//       }
//       else if(ajaxResult == "AlmOK"){
//           document.getElementById("alm_reply").innerHTML = ajaxResult;
//       }
//       // document.getElementById("reply").innerHTML = ajaxResult;
//     }
//   }
//   ajaxRequest.send();
// }       
function tampilkanwaktu(){         //fungsi ini akan dipanggil di bodyOnLoad dieksekusi tiap 1000ms = 1detik    
  time();
  var DAYStr = ("Minggu Senin Selasa Rabu Kamis Jum'at Sabtu"); 
  DAYStr = DAYStr.split(" ");
  var MonStr = ("Januari Februari Maret April Mei Juni Juli Agustus September Oktober November Desember");
  MonStr = MonStr.split(" ");
  document.getElementById("clock").innerHTML = (HH.length==1?"0"+HH:HH) + ":" + (MM.length==1?"0"+MM:MM) + ":" + (SS.length==1?"0"+SS:SS);
  document.getElementById("Date").innerHTML = `${(DD.length==1?"0"+DD:DD)} / ${MonStr[BB]} / ${YY}`;  
  document.getElementById("DAY").innerHTML = DAYStr[DAY] ;
}

function time(){
  var waktu = new Date();
  HH = waktu.getHours() + "";    //memunculkan nilai jam
  MM = waktu.getMinutes() + ""; //ambil nilai menit    
  SS = waktu.getSeconds() + ""; //memunculkan nilai detik 
  DAY= waktu.getDay();
  DD = waktu.getDate()+ "";
  BB = waktu.getMonth()+ "";  
  YY = waktu.getFullYear()+ "";
}

