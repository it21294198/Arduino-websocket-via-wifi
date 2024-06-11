const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 WebSocket Control</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      text-align: center;
      margin-top: 50px;
    }
    button {
      padding: 15px 30px;
      font-size: 16px;
      margin: 10px;
      cursor: pointer;
    }
  </style>
</head>
<body>
  <h1>ESP32 WebSocket Control</h1>
  <button id="on" onclick="sendMessage('ON')">Turn On</button>
  <button id="off" onclick="sendMessage('OFF')">Turn Off</button>

  <script>
    var gateway = `ws://${window.location.hostname}:81/`;
    var websocket;

    window.addEventListener('load', onLoad);

    function onLoad(event) {
      initWebSocket();
    }

    function initWebSocket() {
      console.log('Trying to open a WebSocket connection...');
      websocket = new WebSocket(gateway);
      websocket.onopen = onOpen;
      websocket.onclose = onClose;
      websocket.onmessage = onMessage;
    }

    function onOpen(event) {
      console.log('Connection opened');
    }

    function onClose(event) {
      console.log('Connection closed');
      setTimeout(initWebSocket, 2000);
    }

    function onMessage(event) {
      console.log('Message from server ', event.data);
    }

    function sendMessage(message) {
      console.log('Sending: ', message);
      websocket.send(message);
    }
  </script>
</body>
</html>
)rawliteral";
