void setup()
{
  pinMode(PinButtons, INPUT_PULLUP);
  pinMode(PinRelay, OUTPUT);
  pinMode(PinLed, OUTPUT);
  Wire.begin();
  Serial.begin(115200);
  Serial.println(""); Serial.println("");
  setup_out_init ( "Start FS" );          FS_init();
  setup_out_init ("Loading 'Setup.json'");  SetupMode = readFile("SetupMode.json", 4096);  Serial.println(SetupMode);
  setup_out_init ("Loading 'Names.json'");  Names = readFile("Names.json", 4096);  Serial.println(Names);
  setup_out_init ("Loading 'Autorisation.json'");  Autorisation = readFile("Autorisation.json", 4096);  Serial.println(Autorisation);
  setup_out_init ("Loading 'Variables.json'");  Variables = readFile("Variables.json", 4096);  Serial.println(Variables);
  setup_out_init ("Loading 'IPadresses.json'");  IPadresses = readFile("IPadresses.json", 4096);  Serial.println(IPadresses); Serial.println(); Serial.println();
  LoadVariable ();
  setup_out_init ("Start WIFI");        WIFIinit();
  setup_out_init ("Start begin Time");  Time_init(); 
  setup_out_init ("Start SSDP");        SSDP_init();
  setup_out_init ("Start WebServer");   HTTP_init();
  setup_out_init ("Load Mode Work");    HTTP_init();
}

void LoadVariable ()
{
  _MQTTip = jsonRead ( IPadresses, "MQTTip" );                                       Serial.print ( "Loading from SPIFFS MQTTip = ");    Serial.println ( _MQTTip );
  SSDP_Name = jsonRead ( Names, "ssdp" );                                            Serial.print ( "Loading from SPIFFS SSDP_Name = "); Serial.println ( SSDP_Name );
  pubtopic = jsonRead ( Names, "pubtopic" );                                         Serial.print ( "Loading from SPIFFS pubtopic = ");  Serial.println ( pubtopic );
  StatusDeviceTopic = jsonRead ( Names, "StatusDeviceTopic" );                       Serial.print ( "Loading from SPIFFS StatusDeviceTopic = ");  Serial.println ( StatusDeviceTopic );
  Mode = jsonReadtoInt ( SetupMode, "Mode" );                                        Serial.print ( "Loading from SPIFFS Mode = ");      Serial.println ( Mode );
  ssid = jsonRead ( Autorisation, "ssid" );                                          Serial.print ( "Loading from SPIFFS ssid = ");      Serial.println ( ssid );
  password = jsonRead ( Autorisation, "password" );                                  Serial.print ( "Loading from SPIFFS password = ");  Serial.println ( password );
  NumberOfHomeSystemController = jsonRead ( Names, "NumberOfHomeSystemController" ); Serial.print ( "Loading from SPIFFS NumberOfHomeSystemController = "); Serial.println ( NumberOfHomeSystemController );
  NumberDevice[0][0] = jsonReadtoInt ( Names, "NumberDevice1_1" );                   Serial.print ( "Loading from SPIFFS NumberDevice1_1 = "); Serial.println ( NumberDevice[0][0] );
  NumberDevice[0][1] = jsonReadtoInt ( Names, "NumberDevice1_2" );                   Serial.print ( "Loading from SPIFFS NumberDevice1_2 = "); Serial.println ( NumberDevice[0][1] );
  NumberDevice[1][0] = jsonReadtoInt ( Names, "NumberDevice2_1" );                   Serial.print ( "Loading from SPIFFS NumberDevice2_1 = "); Serial.println ( NumberDevice[1][0] );
  NumberDevice[1][1] = jsonReadtoInt ( Names, "NumberDevice2_2" );                   Serial.print ( "Loading from SPIFFS NumberDevice2_2 = "); Serial.println ( NumberDevice[1][1] );
  NumberDevice[2][0] = jsonReadtoInt ( Names, "NumberDevice3_1" );                   Serial.print ( "Loading from SPIFFS NumberDevice3_1 = "); Serial.println ( NumberDevice[2][0] );
  NumberDevice[2][1] = jsonReadtoInt ( Names, "NumberDevice3_2" );                   Serial.print ( "Loading from SPIFFS NumberDevice3_2 = "); Serial.println ( NumberDevice[2][1] );
  NumberDevice[3][0] = jsonReadtoInt ( Names, "NumberDevice4_1" );                   Serial.print ( "Loading from SPIFFS NumberDevice4_1 = "); Serial.println ( NumberDevice[3][0] );
  NumberDevice[3][1] = jsonReadtoInt ( Names, "NumberDevice4_2" );                   Serial.print ( "Loading from SPIFFS NumberDevice4_2 = "); Serial.println ( NumberDevice[3][1] );
  NumberDevice[4][0] = jsonReadtoInt ( Names, "NumberDevice5_1" );                   Serial.print ( "Loading from SPIFFS NumberDevice5_1 = "); Serial.println ( NumberDevice[4][0] );
  NumberDevice[4][1] = jsonReadtoInt ( Names, "NumberDevice5_2" );                   Serial.print ( "Loading from SPIFFS NumberDevice5_2 = "); Serial.println ( NumberDevice[4][1] );
  NumberDevice[5][0] = jsonReadtoInt ( Names, "NumberDevice6_1" );                   Serial.print ( "Loading from SPIFFS NumberDevice6_1 = "); Serial.println ( NumberDevice[5][0] );
  NumberDevice[5][1] = jsonReadtoInt ( Names, "NumberDevice6_2" );                   Serial.print ( "Loading from SPIFFS NumberDevice6_2 = "); Serial.println ( NumberDevice[5][1] );
  flagActivURLcontrols = jsonReadtoInt ( Variables, "flagActivURLcontrols" );        Serial.print ( "Loading from SPIFFS flagActivURLcontrols = "); Serial.println ( flagActivURLcontrols );
  ComandON = jsonRead ( Names, "ComandON" ); Serial.print ("Loading from SPIFFS ComandON = "); Serial.println( ComandON );
  ComandOFF = jsonRead ( Names, "ComandOFF" ); Serial.print ("Loading from SPIFFS ComandOFF = "); Serial.println( ComandOFF );
  String ip = _MQTTip; 
  int i = ip.indexOf( "." );                                                                    String _ip = ip.substring( 0, i ); MQTTip [ 0 ] = _ip.toInt();
      i = ip.indexOf( "." ); _ip = ip.substring( 1, i+1 ); ip.replace(_ip, ""); i = ip.indexOf( "." ); _ip = ip.substring( 1, i ); MQTTip [ 1 ] = _ip.toInt();
      i = ip.indexOf( "." ); _ip = ip.substring( 1, i+1 ); ip.replace(_ip, ""); i = ip.indexOf( "." ); _ip = ip.substring( 1, i ); MQTTip [ 2 ] = _ip.toInt();
      i = ip.indexOf( "." ); _ip = ip.substring( 1, i+1 ); ip.replace(_ip, ""); i = ip.indexOf( "." ); _ip = ip.substring( 1, i ); MQTTip [ 3 ] = _ip.toInt();
  IPAddress ip_MQTTip ( MQTTip[0], MQTTip[1], MQTTip[2], MQTTip[3] ); 
  Serial.print ( MQTTip[0] ); Serial.print ( "," ); Serial.print ( MQTTip[1] ); Serial.print ( "," ); Serial.print ( MQTTip[2] ); Serial.print ( "," ); Serial.println ( MQTTip[3] );
}

void setup_out_init ( String text )
{
  Serial.println ( text );
  delay(500);
}
