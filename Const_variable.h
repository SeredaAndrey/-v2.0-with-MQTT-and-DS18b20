////////////////////////////// SSID & password //////////////////////////////
String ssid       = "Pushkina15_2.4GHz"; 
String password   = "Sereda19792004"; 
////////////////////////////// SSIDAP & passwordIP //////////////////////////////
String ssidAP     = "WiFi_ESP_for_Config";   
String passwordAP = "Sereda19792004";
////////////////////////////// IPs //////////////////////////////
String _MQTTip  = "192.168.10.100";
int    myip   [4] = { 192, 168, 10,  99 };         
int    mask   [4] = { 255, 255, 255, 0  };
int    gate   [4] = { 192, 168, 10,  1  }; 
int    MQTTip [4] = { 192, 168, 10, 100 };
////////////////////////////// HTTP, MQTT & UDP //////////////////////////////
int    port = 80;
int    timeZone = 3;  
String pubtopic = "/Boller-Controller";             //топик контроллера боллера
String StatusDeviceTopic = "/Boller-Controller/Devices-Status"; //топик состояний устройств
String flagActivURLcontrols = "1";                  //Флаг активации режима при котором при отсутсвии подключения к MQTT упарвление через URL запросы
bool   flagFailMQTTconnect = 0;
String NumberOfHomeSystemController = "110";
String ComandON = "DeviceON!";
String ComandOFF = "DeviceOFF!";
////////////////////////////// Names //////////////////////////////
String SSDP_Name   = "Boller-Controller"; 
int    NumberDevice [6][2];
////////////////////////////// FS //////////////////////////////
String IPadresses = "{}";                           // "{"MQTTip":"192.168.10.100"}"
String Names = "{}";                                // "{"SSDP_Name":"Boller-Controller","StatusDeviceTopic":"/Boller-Controller/Devices-Status"}";
String SetupMode = "{}";                            // Запись состояний MODE 
String Variables = "{}";                            // Запись состояний TimeZone & Temperature
String Autorisation = "{}";                         // "{"ssid":"Pushkina15_2.4GHz","password":"Sereda19792004","ssidAP":"WiFi_ESP_for_Config","passwordAP":"Sereda19792004"}";
////////////////////////////// Modes //////////////////////////////
double Tnow;                                        // Реальная температура теплоносителя в доубле
String _Tnow;                                       // Реальная температура теплоносителя в стринге
int    Mode = 1;                                    // Режим работы устройства 1-автоматический (работа с зависимостью от состояний потребителей тепла), 2-всегда вкдючен, 0-всегда выключен
bool   ResetFlag = 0;                               // флаг активирующий таймер перезагрузки контроллера
bool   BollerOnOff = 0;                             // флаг активации котла
bool   StatusDevice[6][2];
////////////////////////////// TIMERS //////////////////////////////
unsigned long currentMillis;                        // переменная для записи таймера
#define ds18b20interval 10000                       // опрос датчика температуры каждую минуту (60 000мс) 
#define ResetESPInterval 300000                     // перезагрузка ESP через 5 минут после загрузки в АР режиме (300000мс) - должно хватить для настройки в режим клиента 
#define ActivateRefresh 5000                        // проверка сотояния котла через каждые 5 секунд
#define SendDataInterval 30000                      // отправка состояния котла на сайт каждые 30 секунд
const int TimerTopic [6][2] = {{ 180000, 180000 }, 
                               { 180000, 180000 }, 
                               { 180000, 180000 }, 
                               { 180000, 180000 }, 
                               { 180000, 180000 }, 
                               { 180000, 180000 }}; // обнуление состояния устройств в случае не обновленияния топиков, для каждого топика 3 минуты
long    SendDataMillis = 0;                         // счетчик отправки стостояния котла 
long    ActivateRefreshMillis = 0;                  // счетчик проверка сотояния котла 
long    ResetESPMillis = 0;                         // счетчик перезагрузки ESP
long    ds18b20readMillis = 0;                      // счетчик прошедшего времени для интервала чтения с датчика температуры
long    TopicMillis [6][2];                         // счетчик для проверки обновления топиков
////////////////////////////// GPIO //////////////////////////////
#define PinButtons 0                                // кнопка на пине 0
#define PinLed LED_BUILTIN                          // светодиод на програмном пине LED_BUILTIN для SONOFF pin13
#define PinRelay 12                                 // реле активации котла на пине 12
bool    button_state      = false;
bool    button_auto_state = false;
uint32_t ms_button         = 0;
uint32_t ms_auto_click     = 0;
////////////////////////////// LED //////////////////////////////
byte modes[] = 
{
   0B00000000,                       // Светодиод выключен
   0B11111111,                       // Горит постоянно
   0B00001111,                       // Мигание по 0.5 сек
   0B00000001,                       // Короткая вспышка раз в секунду
   0B00000101,                       // Две короткие вспышки раз в секунду
   0B00010101,                       // Три короткие вспышки раз в секунду
   0B01010101                        // Частые короткие вспышки (4 раза в секунду)
};
