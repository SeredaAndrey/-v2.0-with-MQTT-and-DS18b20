void Mode_init()
{
  { 
    if      ( Mode == 0 ) { BollerOnOff = 0; Activate ( false ); }                                                                // режим "ВСЕГДА ВЫКЛЮЧЕН" 
    else if ( Mode == 1 ) { BollerOnOffInit(); }                                                                                  // режим "АВТО"          
    else if ( Mode == 2 ) { BollerOnOff = 1; Activate ( true );  }                                                                // режим "ВСЕГДА ВКЛЮЧЕН"  
  }
}

void Led_init()
{
  int StatusLed;
  if      ( Mode == 0                     ) StatusLed = 0;
  else if ( Mode == 1 && BollerOnOff == 0 ) StatusLed = 3;
  else if ( Mode == 1 && BollerOnOff == 1 ) StatusLed = 4;
  else if ( Mode == 2                     ) StatusLed = 6;
  
  if      ( StatusLed !=0 ) 
  {
    static unsigned long prevTime;
    static int blink_loop; 
    byte blink_mode = modes [ StatusLed ];
    if ( millis () - prevTime > 125 )
    {
      prevTime = millis();
      if ( blink_mode & 1 << ( blink_loop&0x07 ) ) digitalWrite ( PinLed, LOW ); // Режим светодиода ищем по битовой маске
      else  digitalWrite ( PinLed, HIGH );
      blink_loop++; 
      if ( blink_loop > 8 ) 
      {
        blink_loop = 0;
        StatusLed = 0;
        digitalWrite( PinLed, HIGH );  
      }
    }
  } 
}

void BollerOnOffInit ()
{
  if ( StatusDevice[0][0] == 1 || StatusDevice[0][1] == 1 ||      // зона 1 контроллеры 1 и 2
       StatusDevice[1][0] == 1 || StatusDevice[1][1] == 1 ||      // зона 2 контроллеры 1 и 2 
       StatusDevice[2][0] == 1 || StatusDevice[2][1] == 1 ||      // ..
       StatusDevice[3][0] == 1 || StatusDevice[3][1] == 1 ||      // ..
       StatusDevice[4][0] == 1 || StatusDevice[4][1] == 1 ||      // ..
       StatusDevice[5][0] == 1 || StatusDevice[5][1] == 1 )       // зона 6 контроллеры 1 и 2
  { 
    BollerOnOff = 1;
    Activate ( true ); 
    //Serial.println ( "Boller is ON"  ); 
  }
  else                                                
  { 
    BollerOnOff = 0; 
    Activate ( false );  
    //Serial.println ( "Boller is OFF" ); 
  }
}
void Activate ( bool variable )
{
  if      ( variable == true  ) digitalWrite ( PinRelay, HIGH ); 
  else if ( variable == false ) digitalWrite ( PinRelay, LOW  ); 
}
void RefreshStatusDevice ()
{
  for ( int s = 0; s <= 5; s++ )
  {
    for ( int p = 0; p <= 1; p++ )
    {
      if ( currentMillis - TopicMillis [s][p] > TimerTopic [s][p] )
      {
        TopicMillis [s][p] = currentMillis;
        StatusDevice [s][p] = 0;
        Serial.print ( "Automatic disable device - " ); Serial.print ( s+1 ); Serial.print ( "_" ); Serial.println ( p+1 );
      }
    }
  }
}
