#ifndef credpage_h
#define credpage_h

const char CRED_page[] PROGMEM = R"=====(

<!DOCTYPE html>    
<html>
  <head>
    <meta charset="utf-8"
          name="viewport" 
          content="initial-scale=1.0, maximum-scale=1.0, user-scalable=0">
  </head>
  <style>
    body  
    {  
        background-color: #000000;
        font-family: 'Georgia';
        font-size: 30px;
    }
    p
    {
        text-align: center;
        color: #FFFFFF;
    }
    label
    {
      color: #FFFFFF;
      font-size: 20px;
    }
    #ID
    {
      width: 300px;
      height: 30px;
      border: none;
      border-radius: 3px;
      font-family: Georgia;
      font-size: 20px;
    }
    #Pass
    {
      width: 300px;
      height: 30px;
      border: none;
      border-radius: 3px;
      font-family: Georgia;
      font-size: 20px;
    }
    #Connect
    {
      width: 100px;
      height: 30px;
      border: none;
      border-radius: 20px;
      color: black;
      font-family: 'Georgia';
    }
    #Standalone
    {
      width: 200px;
      height: 30px;
      border: none;
      border-radius: 20px;
      color: black;
      font-family: 'Georgia';
    }
  </style>
  <body>
    <p style="font-size: 40px; padding-top: 45px;">Smart LED Setup</p>
    <div style="display: inline-block; text-align: center; margin: auto; width: 100%">
      <label><b>WiFi ID</b></label>
      <br>
      <input type="WiFi ID" name="ID" id="ID">
      <br>
      <label><b>Password</b></label>
      <br>
      <input type="Password" name="Pass" id="Pass">
      <br><br>
      <button onclick="sendPass()" id="Connect">Connect</button>
      <br><br>
      <label><b>IP Address</b></label>
      <br>
      <label id="IPaddr">Waiting</label>
    <div>
  </body>
  <script>
    var connection;
    var webSocketConnected = false;
    var serverData = null;
    
    initWebSocket();
    var init = setInterval(initWebSocket, 2000);
    
    function initWebSocket()
    {
      if (webSocketConnected == false)
      {
        try
        {
          connection = new WebSocket('ws://' + window.location.hostname + ':81/');
          connection.onmessage = function(event)
          {
            console.log('Server says: ', event.data);
            serverData = event.data.split('#');
            // Disregard all serverData except the IP address.
            document.getElementById('IPaddr').innerHTML = serverData[13];
          }
          connection.onclose = function(event)
          {
            console.log('Websocket connection closed.');
            webSocketConnected = false;
            serverData = null;
          };
          webSocketConnected = true;
        }
        catch(e)
        {
          console.log('Could not open websocket.');
          webSocketConnected = false;
          serverData = null;
        }
      }
    }
    function sendPass()
    {
      var idString       = document.getElementById('ID').value;
      var passwordString = document.getElementById('Pass').value;
      connection.send('$S' + '#' + idString + '#' + passwordString);
    }
  </script>
</html>

)=====";

#endif