void WIFIinit() 
{
   HTTP.on ( "/Activate", HTTP_GET, []() 
  {
    HTTP.send ( 200, "text/plain", "OK" ); 
    String ActivateS = HTTP.arg ( "Activate" ); BollerOnOff = ActivateS.toInt ();
  }); 
  HTTP.on ( "/Commands", HTTP_GET, []()                 // --------------------Получаем ComandON & ComandOFF со страницы
  {
    jsonWrite ( Names, "ComandON", HTTP.arg ( "ComandON" ) );
    jsonWrite ( Names, "ComandOFF", HTTP.arg ( "ComandOFF" ) );
    ComandON = HTTP.arg ( "ComandON" );
    ComandOFF = HTTP.arg ( "ComandOFF" ); 
    saveNames ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/ssid", HTTP_GET, []()                        // --------------------Получаем SSDP со страницы
  {
    jsonWrite ( Autorisation, "ssid", HTTP.arg ( "ssid" ) );
    jsonWrite ( Autorisation, "password", HTTP.arg ( "password" ) );
    ssid = HTTP.arg ( "ssid" ); password = HTTP.arg ( "password" );
    saveAutorisation ();                 
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/ssidap", HTTP_GET, []()                      // --------------------Получаем SSDP со страницы  
  {
    jsonWrite ( Autorisation, "ssidAP", HTTP.arg ( "ssidAP"   ));
    jsonWrite ( Autorisation, "passwordAP", HTTP.arg ( "passwordAP" ) );
    ssidAP = HTTP.arg ( "ssidAP" ); passwordAP = HTTP.arg ( "passwordAP" );
    saveAutorisation ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/topic", HTTP_GET, []()                  // --------------------Получаем pubtopic, subtopic1 & subtopic2 со страницы
  {
    jsonWrite ( Names, "pubtopic", HTTP.arg ( "pubtopic" ) );
    pubtopic = HTTP.arg ( "pubtopic" ); 
    jsonWrite ( Names, "StatusDeviceTopic", HTTP.arg ( "StatusDeviceTopic" ) );
    StatusDeviceTopic = HTTP.arg ( "StatusDeviceTopic" );
    saveNames ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/ssdp", HTTP_GET, []()                   // --------------------Получаем SSDP со страницы
  {
    jsonWrite ( Names, "ssdp", HTTP.arg ( "ssdp" ) );
    SSDP_Name = HTTP.arg ( "ssdp" ); 
    saveNames ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/Mode", HTTP_GET, []() 
  {
    jsonWrite ( SetupMode, "Mode", HTTP.arg ( "Mode" ) );
    saveSetupMode ();                 
    HTTP.send ( 200, "text/plain", "OK" ); 
    String ModeS = HTTP.arg ( "Mode" ); Mode = ModeS.toInt ();
  });
  HTTP.on ( "/flagActivURLcontrols", HTTP_GET, []()   // --------------------Получаем flagActivURLcontrols со страницы
  {
    jsonWrite ( Variables, "flagActivURLcontrols", HTTP.arg ( "flagActivURLcontrols" ) );
    flagActivURLcontrols = HTTP.arg ( "flagActivURLcontrols" ); 
    saveVariables ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/NumberOfHomeSystem", HTTP_GET, []()   // --------------------Получаем flagActivURLcontrols со страницы
  {
    String variable;
    jsonWrite ( Names, "NumberOfHomeSystemController", HTTP.arg ( "NumberOfHomeSystemController" ) );
    variable = HTTP.arg ( "NumberOfHomeSystemController" ); NumberOfHomeSystemController = variable.toInt();
    jsonWrite ( Names, "NumberDevice1_1", HTTP.arg ( "NumberDevice1_1" ) );
    variable = HTTP.arg ( "NumberDevice1_1" ); NumberDevice[0][0] = variable.toInt();
    jsonWrite ( Names, "NumberDevice1_2", HTTP.arg ( "NumberDevice1_2" ) );
    variable = HTTP.arg ( "NumberDevice1_2" ); NumberDevice[0][1] = variable.toInt();
    jsonWrite ( Names, "NumberDevice2_1", HTTP.arg ( "NumberDevice2_1" ) );
    variable = HTTP.arg ( "NumberDevice2_1" ); NumberDevice[1][0] = variable.toInt();
    jsonWrite ( Names, "NumberDevice2_2", HTTP.arg ( "NumberDevice2_2" ) );
    variable = HTTP.arg ( "NumberDevice2_3" ); NumberDevice[1][1] = variable.toInt();
    jsonWrite ( Names, "NumberDevice3_1", HTTP.arg ( "NumberDevice3_1" ) );
    variable = HTTP.arg ( "NumberDevice3_1" ); NumberDevice[2][0] = variable.toInt();
    jsonWrite ( Names, "NumberDevice3_2", HTTP.arg ( "NumberDevice3_2" ) );
    variable = HTTP.arg ( "NumberDevice3_2" ); NumberDevice[2][1] = variable.toInt();
    jsonWrite ( Names, "NumberDevice4_1", HTTP.arg ( "NumberDevice4_1" ) );
    variable = HTTP.arg ( "NumberDevice4_1" ); NumberDevice[3][0] = variable.toInt();
    jsonWrite ( Names, "NumberDevice4_2", HTTP.arg ( "NumberDevice4_2" ) );
    variable = HTTP.arg ( "NumberDevice4_2" ); NumberDevice[3][1] = variable.toInt();
    jsonWrite ( Names, "NumberDevice5_1", HTTP.arg ( "NumberDevice5_1" ) );
    variable = HTTP.arg ( "NumberDevice5_1" ); NumberDevice[4][0] = variable.toInt();
    jsonWrite ( Names, "NumberDevice5_2", HTTP.arg ( "NumberDevice5_2" ) );
    variable = HTTP.arg ( "NumberDevice5_2" ); NumberDevice[4][1] = variable.toInt();
    jsonWrite ( Names, "NumberDevice6_1", HTTP.arg ( "NumberDevice6_1" ) );
    variable = HTTP.arg ( "NumberDevice6_1" ); NumberDevice[5][0] = variable.toInt();
    jsonWrite ( Names, "NumberDevice6_2", HTTP.arg ( "NumberDevice6_2" ) );
    variable = HTTP.arg ( "NumberDevice6_2" ); NumberDevice[5][1] = variable.toInt();
    saveNames ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/MQTTip", HTTP_GET, []()                 // --------------------Получаем MQTTip со страницы
  {
    jsonWrite ( IPadresses, "MQTTip", HTTP.arg ( "MQTTip" ) );
    _MQTTip = HTTP.arg ( "MQTTip" ); 
    saveIPs ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
 
  
  
  
  // Попытка подключения к точке доступа
  WiFi.mode(WIFI_STA);
  byte tries = 11;
  if (ssid == "" && password == "" ) 
  {
    WiFi.begin();
  }
  else 
  {   
    WiFi.begin(ssid.c_str(), password.c_str());
  }
  while (--tries && WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("");
    Serial.println("WiFi up AP");
    StartAPMode();
  }
  else 
  {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

bool StartAPMode() 
{
  IPAddress apIP(192, 168, 4, 1);
  IPAddress staticGateway(192, 168, 4, 1);
  IPAddress staticSubnet(255, 255, 255, 0);
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, staticGateway, staticSubnet);
  ssidAP = jsonRead ( Autorisation, "ssidAP" ); Serial.print ("Loading from SPIFFS ssidAP = "); Serial.println( ssidAP );
  passwordAP = jsonRead ( Autorisation, "passwordAP" ); Serial.print ("Loading from SPIFFS passwordAP = "); Serial.println( passwordAP );
  WiFi.softAP ( ssidAP.c_str(), passwordAP.c_str() );
  Mode = 2;
  ResetFlag = 1;
  ResetESPMillis = currentMillis;
  return true;
}

void ResetESP ()
{
  if ( ResetFlag == 1 )
  {
    if ( currentMillis - ResetESPMillis > ResetESPInterval)
    {
       ESP.restart();
    }
  }
}
