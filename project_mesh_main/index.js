var express = require('express');
var http = require('http');
var app = express();
var path = require('path');
var bodyParaser = require('body-parser');
var server = http.createServer(app);
const {ReadlineParser} = require('@serialport/parser-readline');

server.listen(3000);

var serialport  = require('serialport');
var serialPort  = serialport.SerialPort;


var avgStr = "";
var divStr = "NODEDATA::";
var nodeStat = new Array(0, 0, 0, 0, 0);
var node1 = new Array(0,0,0,0,0);
var node2 = new Array(0,0,0,0,0);
var node3 = new Array(0,0,0,0,0);
var node4 = new Array(0,0,0,0,0);
var node5 = new Array(0,0,0,0,0);

var node1_dist = new Array(5);
var node2_dist = new Array(5);
var node3_dist = new Array(5);
var node4_dist = new Array(5);
var node5_dist = new Array(5);

var node11=00; var node12=00; var node13=00; var node14=00; var node15=00;
var node21=00; var node22=00; var node23=00; var node24=00; var node25=00;
var node31=00; var node32=00; var node33=00; var node34=00; var node35=00;
var node41=00; var node42=00; var node43=00; var node44=00; var node45=00;
var node51=00; var node52=00; var node53=00; var node54=00; var node55=00;

var avgDist12;var avgDist13;var avgDist14;var avgDist15;var avgDist23;var avgDist24;
var avgDist25;var avgDist34;var avgDist35;var avgDist45;var avgDist;

var port = new serialPort({
    path:'COM21',
    baudRate : 115200,
    dataBits : 8,
    parity : 'none',
    stopBits: 1,
    flowControl: false
})

var parser = port.pipe(new ReadlineParser({delimiter: '\n'}));


port.on('data', function(data){
  var espData = data.toString('utf-8');
  port.write('NODEDATA::');
  switch (espData.substring(0,9)) {
    case "ESPDATA::":
        // console.log(Number(espData.substr(9,1)));
        var sepFirst = espData.indexOf(","); // console.log(sepFirst);
        var sepSecond = espData.indexOf(",", sepFirst+1);  //console.log(sepSecond);
        var sepThird = espData.indexOf(",",  sepSecond+1); // console.log(sepThird);
        var sepFourth = espData.indexOf(",", sepThird+1);  //console.log(sepFourth);
        var sepFifth = espData.indexOf(",", sepFourth+1);  //console.log(sepFifth);
        var sepSixth =  espData.indexOf(",", sepFifth+1);


          switch (Number(espData.substr(9,1))) {
            case 1:
                nodeStat[0]=true;
                node1[0] = Number(espData.substr(9,1));
                node1[1] = Number(espData.substring(sepFirst+1, sepSecond));
                node11 = node1[1];
                node1[2] = Number(espData.substring(sepSecond+1, sepThird));
                node12 = node1[2];
                node1[3] = Number(espData.substring(sepThird+1, sepFourth));
                node13 = node1[3];
                node1[4] = Number(espData.substring(sepFourth+1,sepFifth));
                node14 = node1[4];
                node1[5] = Number(espData.substring(sepFifth+1,sepSixth));
                node15 = node1[5];
                if((node1[1]+node1[2]+node1[3]+node1[4]+node1[5])==0) nodeStat[0]=false;
              break;
            case 2:
                nodeStat[1]=true;
                node2[0] = Number(espData.substr(9,1));
                node2[1] = Number(espData.substring(sepFirst+1, sepSecond));
                node21 = node2[1];
                node2[2] = Number(espData.substring(sepSecond+1, sepThird));
                node22 = node2[2];
                node2[3] = Number(espData.substring(sepThird+1,sepFourth));
                node23 = node2[3];
                node2[4] = Number(espData.substring(sepFourth+1,sepFifth));
                node24 = node2[4];
                node2[5] = Number(espData.substring(sepFifth+1,sepSixth));
                node25 = node2[5];
                if((node2[1]+node2[2]+node2[3]+node2[4]+node2[5])==0) nodeStat[1]=false;
              break;
            case 3:
                nodeStat[2]=true;
                node3[0] = Number(espData.substr(9,1));
                node3[1] = Number(espData.substring(sepFirst+1,sepSecond));
                node31 = node3[1];
                node3[2] = Number(espData.substring(sepSecond+1,sepThird));
                node32 = node3[2];
                node3[3] = Number(espData.substring(sepThird+1,sepFourth));
                node33 = node3[3];
                node3[4] = Number(espData.substring(sepFourth+1,sepFifth));
                node34 = node3[4];
                node3[5] = Number(espData.substring(sepFifth+1,sepSixth));
                node35 = node3[5];
                if((node3[1]+node3[2]+node3[3]+node3[4]+node3[5])==0) nodeStat[2]=false;
              break;
            case 4:
                nodeStat[3]=true;
                node4[0] = Number(espData.substr(9,1));
                node4[1] = Number(espData.substring(sepFirst+1,sepSecond));
                node41 = node4[1];
                node4[2] = Number(espData.substring(sepSecond+1,sepThird));
                node42 = node4[2];
                node4[3] = Number(espData.substring(sepThird+1,sepFourth));
                node43 = node4[3];
                node4[4] = Number(espData.substring(sepFourth+1,sepFifth));
                node44 = node4[4];
                node4[5] = Number(espData.substring(sepFifth+1,sepSixth));
                node45 = node4[5];
                if((node4[1]+node4[2]+node4[3]+node4[4]+node4[5])==0) nodeStat[3]=false;
              break;
            case 5:
                nodeStat[4]=true;
                node5[0] = Number(espData.substr(9,1));
                node5[1] = Number(espData.substring(sepFirst+1, sepSecond));
                node51 = node5[1];
                node5[2] = Number(espData.substring(sepSecond+1, sepThird));
                node52 = node5[2];
                node5[3] = Number(espData.substring(sepThird+1, sepFourth));
                node53 = node5[3];
                node5[4] =  Number(espData.substring(sepFourth+1,sepFifth));
                node54 = node5[4];
                node5[5] = Number(espData.substring(sepFifth+1,sepSixth));
                node55 = node5[5];
                if((node5[1]+node5[2]+node5[3]+node5[4]+node5[5])==0) nodeStat[4]=false;
              break;
            default:
              break;
          }

          console.log(espData);
          console.log(node1);
          console.log(node2);
          console.log(node3);
          console.log(node4);
          console.log(node5);
        break;
    case "ESPSTATUS::":

      break;
  }
  var minDist = 20;

if(node12 && node21)
    avgDist12 = (node12 + node21) / 2;//console.log(avgDist12);
if(node13 && node31)
  avgDist13 = (node13 + node31) / 2;//console.log(avgDist13);
if(node14 && node41)
  avgDist14 = (node14 + node41) / 2;//console.log(avgDist14);
if(node15 && node51)
  avgDist15 = (node15 + node51) / 2;//console.log(avgDist15);
if(node23 && node32)
  avgDist23 = (node23 + node32) / 2;//console.log(avgDist23);
if(node24 && node43)
  avgDist24 = (node24 + node42) / 2;//console.log(avgDist24);
if(node25 && node52)
  avgDist25 = (node25 + node52) / 2;//console.log(avgDist25);
if(node34 && node43)
  avgDist34 = (node34 + node43) / 2;//console.log(avgDist34);
if(node35 && node53)
  avgDist35 = (node35 + node53) / 2;//console.log(avgDist35);
if(node45 && node54)
  avgDist45 = (node45 + node54) / 2;//console.log(avgDist45);

  avgStr = "";
  avgInfo = new Array("Node1-Node2", "Node1-Node3", "Node1-Node4", "Node1-Node5", "Node2-Node3", "Node2-Node4", "Node2-Node5", "Node3-Node4", "Node3-Node5", "Node4-Node5");
  avgDist = new Array(avgDist12, avgDist13, avgDist14, avgDist15, avgDist23, avgDist24, avgDist25, avgDist34, avgDist35, avgDist45);
  avgDist.forEach((item, i) => {
    if(item<minDist &&  item>0){
      avgStr +="[";
      avgStr += item;
      avgStr += " dBm] ";
      avgStr += avgInfo[i];
      avgStr += "..........";
    }
  });


  for(var i=0;i<6;i++){
      if(node1[i]<minDist&&i>0&&node1[i]>0){
        node1_dist[i-1] = true;
      } else {
        node1_dist[i-1] = false;
      }
  }
    for(var i=0;i<6;i++){
    if(node2[i]<minDist&&i>0&&node2[i]>0){
      node2_dist[i-1] = true;
    } else {
      node2_dist[i-1] = false;
    }
  }
    for(var i=0;i<6;i++){
    if(node3[i]<minDist&&i>0&&node3[i]>0){
      node3_dist[i-1] = true;
    } else {
      node3_dist[i-1] = false;
    }
  }
    for(var i=0;i<6;i++){
    if(node4[i]<minDist&&i>0&&node4[i]>0){
      node4_dist[i-1] = true;
    } else {
      node4_dist[i-1] = false;
    }
  }
    for(var i=0;i<6;i++){
    if(node5[i]<minDist&&i>0&&node5[i]>0){
      node5_dist[i-1] = true;
    } else {
      node5_dist[i-1] = false;
    }
  }
})
port.on('open', function() {
  console.log('open serial communication');

});

app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');
app.use(express.static(path.join(__dirname, 'public')));

app.get('/',function(req,res) {
    res.status(200).render('controller.ejs',{
      node11 : node11,
      node12 : node12,
      node13 : node13,
      node14 : node14,
      node15 : node15,

      node21 : node21,
      node22 : node22,
      node23 : node23,
      node24 : node24,
      node25 : node25,

      node31 : node31,
      node32 : node32,
      node33 : node33,
      node34 : node34,
      node35 : node35,

      node41 : node41,
      node42 : node42,
      node43 : node43,
      node44 : node44,
      node45 : node45,

      node51 : node51,
      node52 : node52,
      node53 : node53,
      node54 : node54,
      node55 : node55,

      node1Stat : nodeStat[0],
      node2Stat : nodeStat[1],
      node3Stat : nodeStat[2],
      node4Stat : nodeStat[3],
      node5Stat : nodeStat[4],

      node1_dist1 : node1_dist[0],
      node1_dist2 : node1_dist[1],
      node1_dist3 : node1_dist[2],
      node1_dist4 : node1_dist[3],
      node1_dist5 : node1_dist[4],

      node2_dist1 : node2_dist[0],
      node2_dist2 : node2_dist[1],
      node2_dist3 : node2_dist[2],
      node2_dist4 : node2_dist[3],
      node2_dist5 : node2_dist[4],

      node3_dist1 : node3_dist[0],
      node3_dist2 : node3_dist[1],
      node3_dist3 : node3_dist[2],
      node3_dist4 : node3_dist[3],
      node3_dist5 : node3_dist[4],

      node4_dist1 : node4_dist[0],
      node4_dist2 : node4_dist[1],
      node4_dist3 : node4_dist[2],
      node4_dist4 : node4_dist[3],
      node4_dist5 : node4_dist[4],

      node5_dist1 : node5_dist[0],
      node5_dist2 : node5_dist[1],
      node5_dist3 : node5_dist[2],
      node5_dist4 : node5_dist[3],
      node5_dist5 : node5_dist[4],

      avgDist12 : avgDist12,
      avgDist13 : avgDist13,
      avgDist14 : avgDist14,
      avgDist15 : avgDist15,
      avgDist23 : avgDist23,
      avgDist24 : avgDist24,
      avgDist25 : avgDist25,
      avgDist34 : avgDist34,
      avgDist35 : avgDist35,
      avgDist45 : avgDist45,

      avgInfo : avgStr,

    });
})

app.get('/controller/:id', function(req,res){
    console.log(req.params.id);
    port.write(req.params.id);
    res.status(200).send('LED Controll OK!!');
})
