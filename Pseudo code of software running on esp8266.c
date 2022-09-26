### Wifi connection
include "user_interface.h" library
include <ESP8266WiFi.h> library

Define  ssid <= "Enter Your SSID”
Define password <= "Enter your WIFI Password”

Create object of WiFiClient <= wificlient:
Void setup:
  Serial.begin(115200) //115200 baud rate
  Print => IOTRFID publish/subscribe Inventory
//Start wifi connection 
  WiFi.begin(ssid, password)
  While (wifi status not connected):
           print=>’’********’’
  print=>"WiFi connection Successful"
  print=>"The IP Address of ESP8266 Module is: "
  Print => WiFi.localIP()

Initialize SPI 
Initialize MFRC522

### Rfid reading

include <SPI.h> library
include <MFRC522.h> library

Assign RST_PIN <------ D3; 
Assign SS_PIN   <-------D4; 
//creating instance of MFRC522
MFRC522 rfid(SS_PIN, RST_PIN)
MFRC522::MIFARE_Key key
In Void loop:
If client is not connected:
   print -> Connecting  client to mqtt Server
While:
    Run the loop till client is not connected to mqtt Server
    Print => ….

If new card is not present:
     Return
Else:
      If ReadCardSerial():
          For loop < 4:
                Tag <= Tag + rfid.uid. uidBytes[i]
Def String Payload:
            payload = "{\"d\":{\"IOTRFID\":\"IR1\",";
    payload += "\"VER\":\"";
    payload += IOTRFIDVERSION;
    payload += "\",\"RFID_ID\":\"";
    payload += String(Tag);
    payload += "\"";
    payload += "}}";
            Measure payload length:
            If payload.length() > 53: 
            print=> sending payload
             If client.publish(topic,payload.c_str()): //true
                 print=>IOT RFID Published
             Else:
                  print=> IOT RFID PUBLISH failed  
                Else:
                       Delay for 500
                       Empty string tag = “ ”
                       HaltA
                       StopCrypto

### Connection with mqtt server

include "PubSubClient.h" library
//Information for Server
define  IOT_RFID_VERSION <= 005  
define  ORG <="RRU"
define  DEVICE_TYPE <= "IOT RFID-01" 
define  DEVICE_ID <="1"
define  TOKEN  <= “xxxxxxxxxxxxxx"

//setup for IOT Raspberry pi
Define IP of  mqttServer(“Server IP address”);
Define topic  <= "IOT RFID";
Define  authMethod <= "use-token-auth";
Assign  token <= TOKEN;  
Assign clientId <= "IOT RFID";

Create Object of PubSubClient <= client:
Client Publish message to server
client(mqttServer,8883,callback,wifiClient);

Def void callback(char  topic,byte payload, unsigned int length)
    Print => "callback invoked from IOT RFID"
