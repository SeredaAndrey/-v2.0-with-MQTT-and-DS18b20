void SendData ()
{
  if ( currentMillis - SendDataMillis > SendDataInterval )
  {
    SendDataMillis = currentMillis;
    Serial.println ( "attempt to send to MQTT" );
    MQTTcall ();
  }
}

String getURL (String urls)
{
  String answer = "";
  HTTPClient http;
  http.begin ( urls );
  int httpCode = http.GET ();
  if ( httpCode == HTTP_CODE_OK )
  {
    answer = http.getString ();
  }
  http.end ();
  return answer;
}


 
