String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";

String html_1 = R"=====(
<!DOCTYPE html>
<html>
 <head>
 <meta name='viewport' content='width=device-width, initial-scale=1.0'/>
 <meta charset='utf-8'>
 <style>
  body {font-size:140%;} 
  #main {display: table; margin: auto;  padding: 0 10px 0 10px; } 
  h2 {text-align:center; } 
  #LED_button { padding:10px 10px 10px 10px; width:100%;  background-color: #50FF50; font-size: 120%;}
  #clock{text-align: center; color: darkslateblue; font-size: 75px; padding: 5px 5px 5px 5px;}
 </style>

<script type="text/javascript">
    function switchLED() {
       var button_text = document.getElementById("LED_button").value;
     if (button_text=="Syncronize"){
       document.getElementById("LED_button").value = "Syncronize";
       ajaxLoad('SYNC'); 
     }
    }
var ajaxRequest = null;
if (window.XMLHttpRequest)  { ajaxRequest =new XMLHttpRequest(); }
else{ ajaxRequest =new ActiveXObject("Microsoft.XMLHTTP"); }

function ajaxLoad(ajaxURL){
  var times = new Date();
  var HH = times.getHours()+ "";
  var MM = times.getMinutes()+ "";
  var SS = times.getSeconds()+ "";
  var DAY= times.getDay()+ "";
  var DD = times.getDate()+ "";
  var BB = times.getMonth()+ "";
  var YY = times.getFullYear()+ "";

  var bulan = ("Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec");
  bulan = bulan.split(" ");
 
  var jam = (HH.length==1?"0"+HH:HH) + ":" + (MM.length==1?"0"+MM:MM) + ":" + (SS.length==1?"0"+SS:SS);
  var tanggal = bulan[BB] + " " + (DD.length==1?"0"+DD:DD) + " " + YY;
 
  if(!ajaxRequest){ alert("AJAX is not supported."); return;}
  
  ajaxRequest.open("GET",ajaxURL + tanggal + jam ,true);
  ajaxRequest.onreadystatechange = function(){
    if(ajaxRequest.readyState == 4 && ajaxRequest.status==200) {
      var ajaxResult = ajaxRequest.responseText;
      if( ajaxResult == "Syncron" )   { 
        document.getElementById("LED_button").value = "Syncron";}
      document.getElementById("reply").innerHTML = ajaxResult;
    }
  }
  ajaxRequest.send();
}

</script>
<script type="text/javascript">        
    function tampilkanwaktu(){         //fungsi ini akan dipanggil di bodyOnLoad dieksekusi tiap 1000ms = 1detik    
    var waktu = new Date();            //membuat object date berdasarkan waktu saat 
    var sh = waktu.getHours() + "";    //memunculkan nilai jam, //tambahan script + "" supaya variable sh bertipe string sehingga bisa dihitung panjangnya : sh.length    //ambil nilai menit
    var sm = waktu.getMinutes() + "";  //memunculkan nilai detik    
    var ss = waktu.getSeconds() + "";  //memunculkan jam:menit:detik dengan menambahkan angka 0 jika angkanya cuma satu digit (0-9)
    document.getElementById("clock").innerHTML = (sh.length==1?"0"+sh:sh) + ":" + (sm.length==1?"0"+sm:sm) + ":" + (ss.length==1?"0"+ss:ss);
    }
/*Menampilkan Waktu*/
</script>
 <title>Jadwal Sholat</title>
</head>

<body onload="tampilkanwaktu();setInterval('tampilkanwaktu()', 100);"> 
 <div id='main'>
  <h2>Setting Jam</h2>
  <p id="clock"></p> 
  <input type="button" id = "LED_button" onclick="switchLED()" value="Syncronize"  /> 
  <p id = "reply">Reply appears here</p>
 </div>  
</body>

</html>

)=====";
