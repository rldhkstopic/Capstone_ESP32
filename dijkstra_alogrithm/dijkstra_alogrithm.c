import processing.serial.*;
Serial port;

//boolean isValue(int val);
String NODENAME_from="";
String NODENAME_1st =""; String NODERSSI_1st ="";
String NODENAME_2nd =""; String NODERSSI_2nd ="";
String NODENAME_3nd =""; String NODERSSI_3nd ="";
String NODENAME_4nd =""; String NODERSSI_4nd ="";


float wpos1 = width/random(1,4);     float hpos1 = height/random(1,4);
float wpos2 = width/random(1,4);     float hpos2 = height/random(1,4);  
float wpos3 = width/random(1,4);     float hpos3 = height/random(1,4);
float wpos4 = width/random(1,4);     float hpos4 = height/random(1,4);
float wpos5 = width/random(1,4);     float hpos5 = height/random(1,4);

int NODECNT = 5;
int[] N1 = new int[6]; int[] N2 = new int[6];
int[] N3 = new int[6]; int[] N4 = new int[6]; int[] N5 = new int[6];

boolean isValue(int val){
  if(val>0)
    return true;
  else
    return false; 
}

void setup() {  
 size(640, 640);
 port = new Serial(this, "COM21", 115200);  
}

void draw() {
  
  if(port.available()>0){
   String nodeMsg = port.readString();
   int received = "RECEIVED::".length();
   
   if(nodeMsg.indexOf("ECEIVED::")>0){
      int NODE_from = nodeMsg.indexOf(",");
      String NODENAME_from = nodeMsg.substring(received, received+2);
      
      int NODE_1st = nodeMsg.indexOf(",", NODE_from+1);
      int RSSI_1st = nodeMsg.indexOf(",", NODE_1st+1);
      if(isValue(NODE_1st)){
       if(NODE_1st > received+2)
         NODENAME_1st = nodeMsg.substring(NODE_from+1, NODE_1st);
       if(RSSI_1st > NODE_1st)  
         NODERSSI_1st = nodeMsg.substring(NODE_1st+1, RSSI_1st);
      } else{
       NODENAME_1st = "";
       NODERSSI_1st = "";
      }
      int NODE_2nd = nodeMsg.indexOf(",", RSSI_1st+1);
      int RSSI_2nd = nodeMsg.indexOf(",", NODE_2nd+1);
      if(isValue(NODE_2nd)){
       if(NODE_2nd>NODE_1st)
         NODENAME_2nd = nodeMsg.substring(RSSI_1st+1, NODE_2nd);
       if(RSSI_2nd>NODE_2nd) 
         NODERSSI_2nd = nodeMsg.substring(NODE_2nd+1, RSSI_2nd);
      } else{
       NODENAME_2nd = "";
       NODERSSI_2nd = "";
      }
      int NODE_3nd = nodeMsg.indexOf(",", RSSI_2nd+1);
      int RSSI_3nd = nodeMsg.indexOf(",", NODE_3nd+1);
      if(isValue(NODE_3nd)){
        if(NODE_3nd>NODE_2nd)
         NODENAME_3nd = nodeMsg.substring(RSSI_2nd+1, NODE_3nd);
        if(RSSI_3nd>NODE_3nd)
         NODERSSI_3nd = nodeMsg.substring(NODE_3nd+1, RSSI_3nd);
      } else{
       NODENAME_3nd = "";
       NODERSSI_3nd = "";
      }
      int NODE_4nd = nodeMsg.indexOf(",", RSSI_3nd+1);
      int RSSI_4nd = nodeMsg.indexOf(",", NODE_4nd+1);
      if(isValue(NODE_4nd)){
        if(NODE_4nd>NODE_3nd)
         NODENAME_4nd = nodeMsg.substring(RSSI_3nd+1, NODE_4nd);
        if(RSSI_4nd>NODE_4nd)
         NODERSSI_4nd = nodeMsg.substring(NODE_4nd+1, RSSI_4nd);
      } else{
       NODENAME_4nd = "";
       NODERSSI_4nd = "";
      }
    //print(NOD!ENAME_from);print(" ");
    //print(NODENAME_1st);print(" "); print(NODERSSI_1st);print(" ");    
    //print(NODENAME_2nd);print(" "); print(NODERSSI_2nd);print(" ");    
    //print(NODENAME_3nd);print(" "); print(NODERSSI_3nd);print(" ");    
    //print(NODENAME_4nd);print(" "); print(NODERSSI_4nd);print(" \n");
    
    N1[0] = 1;    N2[0] = 2;    N3[0] = 3;    N4[0] = 4;    N5[0] = 5;
    
    switch(int(NODENAME_from.substring(1))){
      case 1: // N1
          N1[0] = 0;
          if(NODENAME_1st!="")
            if(int(NODENAME_1st.substring(1))<NODECNT+1) 
              N1[int(NODENAME_1st.substring(1))] = int(NODERSSI_1st)*-1;
          if(NODENAME_2nd!="")
            if(int(NODENAME_2nd.substring(1))<NODECNT+1) 
              N1[int(NODENAME_2nd.substring(1))] = int(NODERSSI_2nd)*-1;
          if(NODENAME_3nd!="")
            if(int(NODENAME_3nd.substring(1))<NODECNT+1) 
              N1[int(NODENAME_3nd.substring(1))] = int(NODERSSI_3nd)*-1;
          if(NODENAME_4nd!="")
            if(int(NODENAME_4nd.substring(1))<NODECNT+1) 
              N1[int(NODENAME_4nd.substring(1))] = int(NODERSSI_4nd)*-1;
        break;
      case 2: // N2
          N2[2] = 0;
          if(NODENAME_1st!="")
            if(int(NODENAME_1st.substring(1))<NODECNT+1) 
              N2[int(NODENAME_1st.substring(1))] = int(NODERSSI_1st)*-1;
          if(NODENAME_2nd!="")
            if(int(NODENAME_2nd.substring(1))<NODECNT+1) 
              N2[int(NODENAME_2nd.substring(1))] = int(NODERSSI_2nd)*-1; 
          if(NODENAME_3nd!="")
            if(int(NODENAME_3nd.substring(1))<NODECNT+1) 
              N2[int(NODENAME_3nd.substring(1))] = int(NODERSSI_3nd)*-1;
          if(NODENAME_4nd!="")
            if(int(NODENAME_4nd.substring(1))<NODECNT+1) 
              N2[int(NODENAME_4nd.substring(1))] = int(NODERSSI_4nd)*-1;
        break;
      case 3: // N3
          N3[3] = 0;
          if(NODENAME_1st!="")
            if(int(NODENAME_1st.substring(1))<NODECNT+1) 
              N3[int(NODENAME_1st.substring(1))] = int(NODERSSI_1st)*-1;
          if(NODENAME_2nd!="")
            if(int(NODENAME_2nd.substring(1))<NODECNT+1) 
              N3[int(NODENAME_2nd.substring(1))] = int(NODERSSI_2nd)*-1;
          if(NODENAME_3nd!="")
            if(int(NODENAME_3nd.substring(1))<NODECNT+1) 
              N3[int(NODENAME_3nd.substring(1))] = int(NODERSSI_3nd)*-1;
          if(NODENAME_4nd!="")
            if(int(NODENAME_4nd.substring(1))<NODECNT+1) 
              N3[int(NODENAME_4nd.substring(1))] = int(NODERSSI_4nd)*-1;
        break;
      case 4: // N4
          N4[4] = 0;
          if(NODENAME_1st!="")
            if(int(NODENAME_1st.substring(1))<NODECNT+1) 
              N4[int(NODENAME_1st.substring(1))] = int(NODERSSI_1st)*-1;
          if(NODENAME_1st!="")
            if(int(NODENAME_2nd.substring(1))<NODECNT+1) 
              N4[int(NODENAME_2nd.substring(1))] = int(NODERSSI_2nd)*-1;
          if(NODENAME_3nd!="")
            if(int(NODENAME_3nd.substring(1))<NODECNT+1) 
              N4[int(NODENAME_3nd.substring(1))] = int(NODERSSI_3nd)*-1;
          if(NODENAME_4nd!="")
            if(int(NODENAME_4nd.substring(1))<NODECNT+1) 
              N4[int(NODENAME_4nd.substring(1))] = int(NODERSSI_4nd)*-1;
          if(NODENAME_1st!="")
        break;
      case 5: // N5
          N5[5] = 0;
          if(NODENAME_1st!="")
            if(int(NODENAME_1st.substring(1))<NODECNT+1) 
              N5[int(NODENAME_1st.substring(1))] = int(NODERSSI_1st)*-1;
          if(NODENAME_2nd!="")
            if(int(NODENAME_2nd.substring(1))<NODECNT+1)  
              N5[int(NODENAME_2nd.substring(1))] = int(NODERSSI_2nd)*-1;
          if(NODENAME_3nd!="")
            if(int(NODENAME_3nd.substring(1))<NODECNT+1) 
              N5[int(NODENAME_3nd.substring(1))] = int(NODERSSI_3nd)*-1;
          if(NODENAME_4nd!="")
            if(int(NODENAME_4nd.substring(1))<NODECNT+1)  
              N5[int(NODENAME_4nd.substring(1))] = int(NODERSSI_4nd)*-1;
        break;
      }  
      print("--------\n");
      print("N1 :");print(N1[1]); print("|");print(N1[2]);print("|"); print(N1[3]);print("|"); print(N1[4]);print("|"); print(N1[5]);print("|"); print("\n");
      print("N2 :");print(N2[1]); print("|");print(N2[2]);print("|"); print(N2[3]);print("|"); print(N2[4]);print("|"); print(N2[5]);print("|"); print("\n");
      print("N3 :");print(N3[1]); print("|");print(N3[2]);print("|"); print(N3[3]);print("|"); print(N3[4]);print("|"); print(N3[5]);print("|"); print("\n");
      print("N4 :");print(N4[1]); print("|");print(N4[2]);print("|"); print(N4[3]);print("|"); print(N4[4]);print("|"); print(N4[5]);print("|"); print("\n"); 
      print("N5 :");print(N5[1]); print("|");print(N5[2]);print("|"); print(N5[3]);print("|"); print(N5[4]);print("|"); print(N5[5]);print("|"); print("\n");
      print("--------\n");
      
      wpos1 = width * 0.7;
      hpos1 = height * 0.5;
      if(NODERSSI_1st.length()>0){
         NODERSSI_1st = NODERSSI_1st.substring(1);
         wpos2 = width * 0.32;
         hpos2 = height * 0.8;
      }if(NODERSSI_2nd.length()>0){
         NODERSSI_2nd = NODERSSI_2nd.substring(1);
         wpos3 = width * 0.75;
         hpos3 = height * 0.7;
      }if(NODERSSI_3nd.length()>0){
         NODERSSI_3nd = NODERSSI_3nd.substring(1);
         wpos4 = width * 0.25;
         hpos4 = height * 0.4 ;
      }if(NODERSSI_4nd.length()>0){
         NODERSSI_4nd = NODERSSI_4nd.substring(1);
         wpos5 = width * 0.8;
         hpos5 = height * 0.2;
      }
      
      textSize(30);
      background(125);      
      float gap = 40;
      
      /*----------------------------------------------------*/     
       line(wpos1, hpos1, wpos2, hpos2);
       line(wpos1, hpos1, wpos3, hpos3);           
       line(wpos1, hpos1, wpos4, hpos4);
       line(wpos1, hpos1, wpos5, hpos5);
      /*-----------------------------------------------------*/
       line(wpos2, hpos2, wpos3, hpos3);       
       line(wpos2, hpos2, wpos4, hpos4);       
       line(wpos2, hpos2, wpos5, hpos5);
      /*-----------------------------------------------------*/ 
       line(wpos3, hpos3, wpos4, hpos4);       
       line(wpos3, hpos3, wpos5, hpos5);     
      /*-----------------------------------------------------*/
       line(wpos4, hpos4, wpos5, hpos5);       
      /*-----------------------------------------------------*/
        fill(255, 255, 255);
        ellipse(wpos1, hpos1, 40, 40); // Standard NODE
        
        fill(50, 50, 50);
        ellipse(wpos2, hpos2, 40, 40);     
        
        fill(115, 54, 234);        
        ellipse(wpos3, hpos3, 40, 40);
        
        fill(247, 72, 142);
        ellipse(wpos4, hpos4, 40, 40);  
        
        fill(255, 226, 99);
        ellipse(wpos5, hpos5, 40, 40);     
      /*-----------------------------------------------------*/
       int mgap = 65;
       
       fill(255, 255, 255);
       text("N1 ", 0, 20);
         text("X", gap*3-mgap, 20);
       text(N1[2], gap*4-mgap, 20);
       text(N1[3], gap*5-mgap, 20);
       text(N1[4], gap*6-mgap, 20);
       text(N1[5], gap*7-mgap, 20);
       
       fill(50, 50, 50);
       text("N2 ", 0, 50);
       text(N2[1], gap*3-mgap, 50);
         text("X", gap*4-mgap, 50);
       text(N2[3], gap*5-mgap, 50);
       text(N2[4], gap*6-mgap, 50);
       text(N2[5], gap*7-mgap, 50);       
       
       fill(115, 54, 234);       
       text("N3 ", 0, 80);
       text(N3[1], gap*3-mgap, 80);
       text(N3[2], gap*4-mgap, 80);
         text("X", gap*5-mgap, 80);
       text(N3[4], gap*6-mgap, 80);
       text(N3[5], gap*7-mgap, 80);
       
       
       fill(247, 72, 142);   
       text("N4 ", 0, 110);
       text(N4[1], gap*3-mgap, 110);
       text(N4[2], gap*4-mgap, 110);
       text(N4[3], gap*5-mgap, 110);
         text("X", gap*6-mgap, 110);
       text(N4[5], gap*7-mgap, 110);
       
       fill(255, 226, 99);   
       text("N4 ", 0, 140);
       text(N4[1], gap*3-mgap, 140);
       text(N4[2], gap*4-mgap, 140);
       text(N4[3], gap*5-mgap, 140);
       text(N4[5], gap*6-mgap, 140);
         text("X", gap*7-mgap, 140);
       
     
      

     
    }
  }
}
