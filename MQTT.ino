// mosquitto_pub -h localhost -t "SmartHome/Living-Rooms/Room-Controller/Temperature" -m 21.0 сделать публикацию в топике
// mosquitto_sub -h localhost -t "SmartHome/Living-Rooms/Room-Controller/Activate"            подписаться на топик              

void handleMQTT ()
{
  IPAddress ip_MQTTip ( MQTTip[0], MQTTip[1], MQTTip[2], MQTTip[3] ); 
  String _topic = "/SmartHome"; 
  _topic += pubtopic; 
//  _topic += subtopic1;
  String _topicActiv = _topic + "/Activate";
  if ( WiFi.status () == WL_CONNECTED )
  {
    client.set_server ( ip_MQTTip );
    //Serial.println ( "Connect to WiFi - ACCEPT" );
    if ( !client.connected () )
    {
      //Serial.println ( "Connect to MQTT - ACCEPT" );
      if ( client.connect ( SSDP_Name ) )
      {
        client.set_callback ( callback );
        client.subscribe ( _topicActiv );
      }
    }
    else flagFailMQTTconnect = 1;
    if ( client.connected () )
    {
      client.loop ();
    }
    SendData ();
  }
}

void MQTTcall ()
{
  String _Mode; String _Activate;
  String _topic = "/SmartHome"; 
  String _statusTopic = _topic; 
  _statusTopic += StatusDeviceTopic;
  _topic += pubtopic;
  String _topicTemp = _topic + "/temperature";
  String _topicMode = _topic + "/Mode"; 
  String _topicActivate = _topic + "/Activate"; 
        if      ( Mode == 1 )           _Mode     = "Automatic mode"; 
        else if ( Mode == 2 )           _Mode     = "Always on"; 
        else if ( Mode == 0 )           _Mode     = "Always off"; 
        else                            _Mode     = "Wrong status mode";
        if      ( BollerOnOff == 0 )    _Activate = "Boller is OFF";
        else if ( BollerOnOff == 1 )    _Activate = "Boller is ON";
        else                            _Activate = "Wrong status activate";
  //Serial.print ( "Connect to MQTT with SSDP_Name " ); Serial.print ( SSDP_Name ); Serial.println ( " - ACCEPT" ); 
  flagFailMQTTconnect = 0;
  client.publish ( _topicTemp,     _Tnow      ); Serial.print ( "Publish " ); Serial.print ( _topicTemp     ); Serial.print ( " " ); Serial.println ( _Tnow      ); 
  client.publish ( _topicMode,     _Mode      ); Serial.print ( "Publish " ); Serial.print ( _topicMode     ); Serial.print ( " " ); Serial.println ( _Mode      ); 
  client.publish ( _topicActivate, _Activate  ); Serial.print ( "Publish " ); Serial.print ( _topicActivate ); Serial.print ( " " ); Serial.println ( _Activate  ); 
  client.set_callback ( callback );
  client.subscribe ( _statusTopic );
//  Serial.println ( client.subscribe ( _topicActiv ) );
  flagFailMQTTconnect = 0;
}

void callback(const MQTT::Publish& pub) 
{
  String _topic = "/SmartHome"; _topic += StatusDeviceTopic;  
  String payload = pub.payload_string();
  if ( String ( pub.topic () ) == _topic ) 
  { 
    String Variable = payload; Serial.print ( "Incoming mesage " ); Serial.println ( Variable ); 
    ParsingSubscribeMQTT ( Variable );
  }
}

void ParsingSubscribeMQTT ( String Variable )
{
  String _pars = "";
  _pars += Variable;
  int i = _pars.indexOf ( "-" );
  String pars1 = _pars.substring ( 0, i );
  String pars2 = _pars.substring ( i+1, _pars.length() );
  for ( int s = 0; s <= 5; s++ )
  {
    for ( int p = 0; p <= 1; p++ )
    {
      if ( NumberDevice [s][p] == pars1.toInt() ) 
      {
        if      ( pars2 == ComandON  ) 
        { 
          StatusDevice [s][p] = 1; Serial.print ( "StatusDevice " ); Serial.print ( s+1 ); Serial.print ( "_" ); Serial.print ( p+1 ); Serial.print ( "-" ); Serial.println ( "Device ON "  );
          TopicMillis [s][p] = currentMillis;
        }
        else if ( pars2 == ComandOFF ) 
        { 
          StatusDevice [s][p] = 0; Serial.print ( "StatusDevice " ); Serial.print ( s+1 ); Serial.print ( "_" ); Serial.print ( p+1 ); Serial.print ( "-" ); Serial.println ( "Device OFF " );
          TopicMillis [s][p] = currentMillis;
        }
      }
    }
  }
}
