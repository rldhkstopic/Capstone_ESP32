/* 졸업하자!!! */
String NODE_NAME    =  "N5";

#include <Wire.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "painlessMesh.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define DELAY_CNT_MAX   50
#define DELAY_TIME_MAX 50000

#ifdef LED_BUILTIN
#define LED LED_BUILTIN
#else
#define LED 2
#endif


int delayTime = 0;
int delayCnt = 0;
bool onFlag = false;
bool delayFlag = false;


#define   MAIN_NODEID     444742549
#define   MESH_PREFIX     "Capstone_mesh"
#define   MESH_PASSWORD   "capstone"
#define   MESH_PORT       5555

char nodeList[][5][20] = {
  {"1", "E8:9F:6D:E8:CD:29"}, // node 1
  {"2", "B8:D6:1A:82:2E:8D"}, // node 2
  {"3", "10:97:BD:34:60:71"}, // node 3
  {"4", "B8:D6:1A:82:2D:BD"}, // node 4
  {"5", "24:D7:EB:0C:8D:51"}, // node 5 3943468369
  //"6", "B8:D6:1A:82:3B:95"}, // node Main

  };
  
//typedef enum {
//    WL_NO_SHIELD        = 255,   // for compatibility with WiFi Shield library
//    WL_IDLE_STATUS      = 0,
//    WL_NO_SSID_AVAIL    = 1,
//    WL_SCAN_COMPLETED   = 2,
//    WL_CONNECTED        = 3,
//    WL_CONNECT_FAILED   = 4,
//    WL_CONNECTION_LOST  = 5,
//    WL_DISCONNECTED     = 6
//} wl_status_t;

int8_t nodeEA = sizeof(nodeList) / sizeof(nodeList[0]);

Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void sendMessage(); // Prototype so PlatformIO doesn't complain
void displayOLED(String message);
Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );


void sendMessage() {
  display.clearDisplay();

  String noti = "";
  String msg = "RECEIVED::";
  msg+=NODE_NAME;
  msg+=",";

  boolean sended;
  
  int scanCnt = 0;
  int scanNet = WiFi.scanNetworks();
  if(scanNet<0){Serial.println("CONNECTION::WIFI_SCAN_ERROR");
    delayFlag = false;
    delayCnt++;
    scanNet=10;
    if(delayCnt>20)ESP.restart();
  } else {delayCnt =0;}
  
  Serial.printf("ScanNetworks : %d , delayCnt : %d, delayFlag : %d, delayTime : %d, WiFi status : %d , BSSDI : ", scanNet, delayCnt, delayFlag, delayTime, WiFi.status());
  Serial.println(WiFi.BSSIDstr());
  int node_num=0;
  for(int i=0;i<scanNet;i++){ 
      if(String(WiFi.SSID(i))==MESH_PREFIX){   //Serial.println("MESH_PREFIX is detected");
         for(int ea=0;ea<nodeEA;ea++){
           if(String(nodeList[ea][1]) == WiFi.BSSIDstr(i)){scanCnt++;
             String rssi = String(WiFi.RSSI(i));
             Serial.print("NODE : ");
             Serial.print(String(nodeList[ea][0]));
             Serial.print(" | BSSID : ");
             Serial.print(String(nodeList[ea][1]));
             Serial.print(" | RSSI : ");
             Serial.print(rssi);
             Serial.println(" dBm");
             noti = String("N"+String(nodeList[ea][0])+","+rssi+",");
             if((WiFi.RSSI(i)*-1)<15)node_num++;
              Serial.println(node_num);
              if(node_num>0) ledcWrite(0,255);
              else ledcWrite(0, 0);
             msg += noti;
             displayOLED(noti,10*String(nodeList[ea][0]).toInt());
           }
         }
      }
  }
  msg+="\n";
  sended = mesh.sendSingle( MAIN_NODEID, msg );
  if(sended){
      displayOLED("[Server Connected]---", 0);
      delayFlag = true;
      
      if(onFlag)onFlag = false;
      else onFlag = true;
  } else {
      delayFlag = false;
      displayOLED(String("Stand-By..."+String(delayTime/1000)+"/"+String(DELAY_TIME_MAX/1000))+"s", 0);
    
  }
//  if(delayCnt>DELAY_CNT_MAX)ESP.restart();
  taskSendMessage.setInterval( TASK_SECOND * 1 );
  display.clearDisplay();
}

void receivedCallback( uint32_t from, String &msg ){
  if(msg){
    Serial.printf("Msg : %s \n",msg.c_str());
  }
}

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("--> startHere: New Connection, nodeId : %u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
  Serial.printf("Adjusted time %u. Offset : %d\n", mesh.getNodeTime(), offset);
}

void displayOLED(String message, int pos) {
//  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, pos);  // Display static text
  display.println(message);
  display.display();
}

unsigned long previous_time = 0;
void setup() {
  ledcSetup(0, 5000, 8);
  ledcAttachPin(23, 0);
  Serial.begin(115200);
  Serial.println(NODE_NAME);
  pinMode(LED, OUTPUT);
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }  delay(1000); display.clearDisplay(); displayOLED(NODE_NAME,0);

  mesh.setDebugMsgTypes( ERROR | STARTUP);  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();
}
int cnt = 0;
void loop() {
  unsigned long current_time = millis();  
  
  if((WiFi.status() != WL_CONNECTED)){
    delayTime = current_time - previous_time;
    if((delayFlag==false) && (current_time - previous_time>=DELAY_TIME_MAX)){
      Serial.println("Try to Reconnect to Server");
      WiFi.disconnect();
      WiFi.reconnect();
      previous_time = current_time;
      delayTime=0;
    }
  }
  mesh.update();
  digitalWrite(LED, !onFlag);
}
