#include <painlessMesh.h>

#ifdef LED_BUILTIN
  #define LED LED_BUILTIN
#else
  #define LED 2
#endif

#define   BLINK_PERIOD    3000 // milliseconds until cycle repeat
#define   BLINK_DURATION  100  // milliseconds LED is on for
#define   MAIN_NODEID     444742549 
#define   MESH_PREFIX     "Capstone_mesh"
#define   MESH_PASSWORD   "capstone"
#define   MESH_PORT       5555

bool onFlag = false;
bool calc_delay = false;

void sendMessage(); 
void receivedCallback(uint32_t from, String & msg);
void newConnectionCallback(uint32_t nodeId);
void changedConnectionCallback(); 
void nodeTimeAdjustedCallback(int32_t offset); 
void delayReceivedCallback(uint32_t from, int32_t delay);

painlessMesh  mesh;
SimpleList<uint32_t> nodes;
Scheduler    userScheduler;

void sendMessage();
Task taskSendMessage( TASK_SECOND * 1, TASK_FOREVER, &sendMessage ); // start with a one second interval
Task blinkNoNodes;

String NODENAME_from="";
String NODENAME_1st =""; String NODERSSI_1st ="";
String NODENAME_2nd =""; String NODERSSI_2nd ="";
String NODENAME_3nd =""; String NODERSSI_3nd ="";
String NODENAME_4nd =""; String NODERSSI_4nd ="";
int N1[6]; int N2[6];  int N3[6];
int N4[6]; int N5[6];  

boolean isValue(int val){
  if(val>0)
    return true;
  else
    return false; 
}
void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);

  mesh.setDebugMsgTypes(ERROR);  // set before init() so that you can see error messages


  mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
  mesh.onNodeDelayReceived(&delayReceivedCallback);

  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();

  blinkNoNodes.set(BLINK_PERIOD, (mesh.getNodeList().size() + 1) * 2, []() {
      if (onFlag)
        onFlag = false;
      else
        onFlag = true;
      blinkNoNodes.delay(BLINK_DURATION);

      if (blinkNoNodes.isLastIteration()) {
        blinkNoNodes.setIterations((mesh.getNodeList().size() + 1) * 2);
        blinkNoNodes.enableDelayed(BLINK_PERIOD - 
            (mesh.getNodeTime() % (BLINK_PERIOD*1000))/1000);
      }
  });
  userScheduler.addTask(blinkNoNodes);
  blinkNoNodes.enable();

  randomSeed(analogRead(A0));
  /*-----------------------------*/
  
}
const char* PARAM_MESSAGE = "message";
char indata;

void loop() {
  mesh.update();
  digitalWrite(LED, !onFlag);
  
}

int mvalue(int dx, int dy){
  int set=0;
  if(dx<0)
    set = dy/2;
  else if(dy<0)
    set = dx/2;
  else
    set = (dx+dy)/2;
    
  return int(set);
}

int dist[11];
int NODECNT = 5;
void preproNode(String &Msg){
  String nodeMsg = Msg;
  String NODENAME_from;
  int received = String("RECEIVED::").length();

    Serial.println(Serial.read());
  if(nodeMsg=="NODEDATA::")
    digitalWrite(18, HIGH);
    
    digitalWrite(17, HIGH);
    digitalWrite(16, HIGH);
  
   if(nodeMsg.indexOf("ECEIVED::")>0){
      int NODE_from = nodeMsg.indexOf(",");
      NODENAME_from = nodeMsg.substring(received, received+2);
//      Serial.print("NODENAME_from:");
//      Serial.println(NODENAME_from);
      
      int NODE_1st = nodeMsg.indexOf(",", NODE_from+1);
      int RSSI_1st = nodeMsg.indexOf(",", NODE_1st+1);
      if(isValue(NODE_1st)){
       if(NODE_1st > received+2)
         NODENAME_1st = nodeMsg.substring(NODE_from+1, NODE_1st);
//         Serial.print("NODENAME_1st:");
//         Serial.println(NODENAME_1st);
       if(RSSI_1st > NODE_1st)  
         NODERSSI_1st = nodeMsg.substring(NODE_1st+1, RSSI_1st);
//         Serial.print("NODERSSI_1st:");
//         Serial.println(NODERSSI_1st);
      } else{
       NODENAME_1st = "";
       NODERSSI_1st = "";
      }
      int NODE_2nd = nodeMsg.indexOf(",", RSSI_1st+1);
      int RSSI_2nd = nodeMsg.indexOf(",", NODE_2nd+1);
      if(isValue(NODE_2nd)){
       if(NODE_2nd>NODE_1st)
         NODENAME_2nd = nodeMsg.substring(RSSI_1st+1, NODE_2nd);
//         Serial.print("NODENAME_2nd:");
//         Serial.println(NODENAME_2nd);
       if(RSSI_2nd>NODE_2nd) 
         NODERSSI_2nd = nodeMsg.substring(NODE_2nd+1, RSSI_2nd);
//         Serial.print("NODERSSI_2nd:");
//         Serial.println(NODERSSI_2nd);         
      } else{
       NODENAME_2nd = "";
       NODERSSI_2nd = "";
      }
      int NODE_3nd = nodeMsg.indexOf(",", RSSI_2nd+1);
      int RSSI_3nd = nodeMsg.indexOf(",", NODE_3nd+1);
      if(isValue(NODE_3nd)){
        if(NODE_3nd>NODE_2nd)
         NODENAME_3nd = nodeMsg.substring(RSSI_2nd+1, NODE_3nd);
//         Serial.print("NODENAME_3nd:");
//         Serial.println(NODENAME_3nd); 
        if(RSSI_3nd>NODE_3nd)
         NODERSSI_3nd = nodeMsg.substring(NODE_3nd+1, RSSI_3nd);
//         Serial.print("NODERSSI_3nd:");
//         Serial.println(NODERSSI_3nd); 
      } else{
       NODENAME_3nd = "";
       NODERSSI_3nd = "";
      }
      int NODE_4nd = nodeMsg.indexOf(",", RSSI_3nd+1);
      int RSSI_4nd = nodeMsg.indexOf(",", NODE_4nd+1);
      if(isValue(NODE_4nd)){
        if(NODE_4nd>NODE_3nd)
         NODENAME_4nd = nodeMsg.substring(RSSI_3nd+1, NODE_4nd);
//         Serial.print("NODENAME_4nd:");
//         Serial.println(NODENAME_4nd); 
        if(RSSI_4nd>NODE_4nd)
         NODERSSI_4nd = nodeMsg.substring(NODE_4nd+1, RSSI_4nd);
//         Serial.print("NODERSSI_4nd:");
//         Serial.println(NODERSSI_4nd); 
      } else{
       NODENAME_4nd = "";
       NODERSSI_4nd = "";
      }
    }
    N1[0] = 1;    N2[0] = 2;    N3[0] = 3;    N4[0] = 4;    N5[0] = 5;
    switch((NODENAME_from.substring(1).toInt())){
      case 1: // N1
          N1[1] = 0;
          if(NODENAME_1st!="")
            if((NODENAME_1st.substring(1).toInt())<NODECNT+1) 
              N1[(NODENAME_1st.substring(1).toInt())] = (NODERSSI_1st).toInt()*-1;
          if(NODENAME_2nd!="")
            if((NODENAME_2nd.substring(1).toInt())<NODECNT+1) 
              N1[(NODENAME_2nd.substring(1).toInt())] = (NODERSSI_2nd).toInt()*-1;
          if(NODENAME_3nd!="")
            if((NODENAME_3nd.substring(1).toInt())<NODECNT+1) 
              N1[(NODENAME_3nd.substring(1).toInt())] = (NODERSSI_3nd).toInt()*-1;
          if(NODENAME_4nd!="")
            if((NODENAME_4nd.substring(1).toInt())<NODECNT+1) 
              N1[(NODENAME_4nd.substring(1).toInt())] = (NODERSSI_4nd).toInt()*-1;
        break;
      case 2: // N2
          N2[2] = 0;
          if(NODENAME_1st!="")
            if((NODENAME_1st.substring(1).toInt())<NODECNT+1) 
              N2[(NODENAME_1st.substring(1).toInt())] = (NODERSSI_1st).toInt()*-1;
          if(NODENAME_2nd!="")
            if((NODENAME_2nd.substring(1).toInt())<NODECNT+1) 
              N2[(NODENAME_2nd.substring(1).toInt())] = (NODERSSI_2nd).toInt()*-1; 
          if(NODENAME_3nd!="")
            if((NODENAME_3nd.substring(1).toInt())<NODECNT+1) 
              N2[(NODENAME_3nd.substring(1).toInt())] = (NODERSSI_3nd).toInt()*-1;
          if(NODENAME_4nd!="")
            if((NODENAME_4nd.substring(1).toInt())<NODECNT+1) 
              N2[(NODENAME_4nd.substring(1).toInt())] = (NODERSSI_4nd).toInt()*-1;
        break;
      case 3: // N3
          N3[3] = 0;
          if(NODENAME_1st!="")
            if((NODENAME_1st.substring(1).toInt())<NODECNT+1) 
              N3[(NODENAME_1st.substring(1).toInt())] = (NODERSSI_1st).toInt()*-1;
          if(NODENAME_2nd!="")
            if((NODENAME_2nd.substring(1).toInt())<NODECNT+1) 
              N3[(NODENAME_2nd.substring(1).toInt())] = (NODERSSI_2nd).toInt()*-1;
          if(NODENAME_3nd!="")
            if((NODENAME_3nd.substring(1).toInt())<NODECNT+1) 
              N3[(NODENAME_3nd.substring(1).toInt())] = (NODERSSI_3nd).toInt()*-1;
          if(NODENAME_4nd!="")
            if((NODENAME_4nd.substring(1).toInt())<NODECNT+1) 
              N3[(NODENAME_4nd.substring(1).toInt())] = (NODERSSI_4nd).toInt()*-1;
        break;
      case 4: // N4
          N4[4] = 0;
          if(NODENAME_1st!="")
            if((NODENAME_1st.substring(1).toInt())<NODECNT+1) 
              N4[(NODENAME_1st.substring(1).toInt())] = (NODERSSI_1st).toInt()*-1;
          if(NODENAME_1st!="")
            if((NODENAME_2nd.substring(1).toInt())<NODECNT+1) 
              N4[(NODENAME_2nd.substring(1).toInt())] = (NODERSSI_2nd).toInt()*-1;
          if(NODENAME_3nd!="")
            if((NODENAME_3nd.substring(1).toInt())<NODECNT+1) 
              N4[(NODENAME_3nd.substring(1).toInt())] = (NODERSSI_3nd).toInt()*-1;
          if(NODENAME_4nd!="")
            if((NODENAME_4nd.substring(1).toInt())<NODECNT+1) 
              N4[(NODENAME_4nd.substring(1).toInt())] = (NODERSSI_4nd).toInt()*-1;
          if(NODENAME_1st!="")
        break;
      case 5: // N5
          N5[5] = 0;
          if(NODENAME_1st!="")
            if((NODENAME_1st.substring(1).toInt())<NODECNT+1) 
              N5[(NODENAME_1st.substring(1).toInt())] = (NODERSSI_1st).toInt()*-1;
          if(NODENAME_2nd!="")
            if((NODENAME_2nd.substring(1).toInt())<NODECNT+1)  
              N5[(NODENAME_2nd.substring(1).toInt())] = (NODERSSI_2nd).toInt()*-1;
          if(NODENAME_3nd!="")
            if((NODENAME_3nd.substring(1).toInt())<NODECNT+1) 
              N5[(NODENAME_3nd.substring(1).toInt())] = (NODERSSI_3nd).toInt()*-1;
          if(NODENAME_4nd!="")
            if((NODENAME_4nd.substring(1).toInt())<NODECNT+1)  
              N5[(NODENAME_4nd.substring(1).toInt())] = (NODERSSI_4nd).toInt()*-1;
        break;
      }  

    #define ESPDATA "ESPDATA::"
    Serial.print(ESPDATA);for(int i=0;i<=NODECNT;i++){Serial.print(N1[i]);Serial.print(",");} Serial.println();
    delay(100);
    Serial.print(ESPDATA);for(int i=0;i<=NODECNT;i++){Serial.print(N2[i]);Serial.print(",");} Serial.println();
    delay(100);
    Serial.print(ESPDATA);for(int i=0;i<=NODECNT;i++){Serial.print(N3[i]);Serial.print(",");} Serial.println();
    delay(100);
    Serial.print(ESPDATA);for(int i=0;i<=NODECNT;i++){Serial.print(N4[i]);Serial.print(",");} Serial.println();
    delay(100);
    Serial.print(ESPDATA);for(int i=0;i<=NODECNT;i++){Serial.print(N5[i]);Serial.print(",");} Serial.println();
}

void sendMessage() {
  String msg = "CONNECTED";
  msg += " myFreeMemory: " + String(ESP.getFreeHeap());
  mesh.sendBroadcast(msg);

  if (calc_delay) {
    SimpleList<uint32_t>::iterator node = nodes.begin();
    while (node != nodes.end()) {
      mesh.startDelayMeas(*node);
      node++;
    }
    calc_delay = false;
  }
  //Serial.println(msg.c_str());  
  taskSendMessage.setInterval( random(TASK_SECOND * 1, TASK_SECOND * 5));  // between 1 and 5 seconds
}


void receivedCallback(uint32_t from, String & msg) {
  Serial.print(msg);
  preproNode(msg);
  
}

void newConnectionCallback(uint32_t nodeId) {
  onFlag = false;
  blinkNoNodes.setIterations((mesh.getNodeList().size() + 1) * 2);
  blinkNoNodes.enableDelayed(BLINK_PERIOD - (mesh.getNodeTime() % (BLINK_PERIOD*1000))/1000);
}

void changedConnectionCallback() {
  onFlag = false;
  blinkNoNodes.setIterations((mesh.getNodeList().size() + 1) * 2);
  blinkNoNodes.enableDelayed(BLINK_PERIOD - (mesh.getNodeTime() % (BLINK_PERIOD*1000))/1000);
 
  nodes = mesh.getNodeList();

//  Serial.printf("Num nodes: %d\n", nodes.size());
//  Serial.printf("Connection list:");

  SimpleList<uint32_t>::iterator node = nodes.begin();
  while (node != nodes.end()) {
    //Serial.printf(" %u", *node);
    node++;
  }
  //Serial.println();
  calc_delay = true;
}

void nodeTimeAdjustedCallback(int32_t offset) {
  //Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
}

void delayReceivedCallback(uint32_t from, int32_t delay) {
  //Serial.printf("Delay to node %u is %d us\n", from, delay);
}
