# IOTRFID
Aim: Build an IOT device for Reading RFID cards i.e IOTRFID along with Inventory System and implementing security features in it.


# Hardware requirement
ESP8266 Nodemcu <br/>
125KHz RFID Reader RC522 <br/>
Raspberry pi <br/>
Jumper wires <br/>
125KHz RFID Tags <br/>

# Tools required
Arduino IDE <br/>
Openssl <br/>
MQTT Broker <br/>
MySql <br/>

# Workflow of Project
RFID Tag reader in our case it is MFRC522  whose range  is 125KHz has RFID Antenna on it whenever 125kHz RFID Tag wave on the Reader it will fetch its Tag ID.
The Tag ID is passed over to WIFI Module which is ESP8266 NodeMCU.
The C code is flashed to NodeMCU which instruct it how to read Tag ID , connect to which wifi, how to make connection pipeline with server and forward the data.  

![Screenshot from 2022-09-26 15-12-01](https://user-images.githubusercontent.com/55538188/192245567-90cda218-da2f-408b-b45f-a477ad119a65.png)

When ESP8266 NodeMCU is powered on ,there is a loop always running which makes a payload of data collected from the RFID Tag Reader.
Then send the connection request to MQTT Broker which resides on our server , when the broker receive connection request it will check authentication and send acknowledgement to MQTT Client i.e IOTRFID.
When a client receives CONACK it will subscribe to MQTT broker using Topic and MQTT broker send back SUBACK.
At the last  MQTT Client publishes the actual payload to MQTT Broker which is on the server.
On the server side there is python code running which manages all the connections on the server.
This python code receives a payload in json format which it convert into dictionary format that stores IOTRFID version,TAG ID and reader device name.

![Screenshot from 2022-09-26 15-12-25](https://user-images.githubusercontent.com/55538188/192245599-46082312-2ab9-4bac-bdaa-6cad21073dda.png)<br/>
The two layers of encryption applied to the payload received on the server. First, the tag data is encoded into base64 format and second aes256 encryption is applied on the encoded data.
Before storing the data base64 encoded data is compared with the prestored database if it will match with the database then only it will be forwarded.
Now the encrypted data is stored on the MySQL database with date and time stamps.   

![Screenshot from 2022-09-26 15-13-23](https://user-images.githubusercontent.com/55538188/192245614-a7668362-a10e-468a-9135-522dfcd47d13.png)<br/>
When login successful it will fetch the encrypted data from the sql database with the id and password of the database.
The fetched data is decrypted from aes256 and again decoded from base64 format.
The tag data in normal text along with a time stamp is displayed on the GUI window in table format.   

# Establishing MQTT server on Raspberry pi
All commands are mentioned in "Establishing MQTT server on Raspberry pi" file.
# Pseudo code of software running on esp8266 based on each requirement
To generate code for wifimodule that establish connection between rfid reader and server using  MQTT broker open this "Pseudo code of software running on esp8266" file.

# software running on Raspberry pi server
Open "software running on Raspberry pi server.py" for code running on raspberry pi.

# Security implementation


##### Security in this device is implemented in three ways
##### 1) Implement security in your wifi such as WPA2 PSK security. So an outsider will not be able to take over your network.<br/>
##### 2) Securing the data stored in the database by applying encryption on base64 encoded  Tag ID . So whenever data leaks happen due to cyber attack the chances of receiving true data to the attacker will be reduced.<br/>
##### 3) Implementing Encryption such TLS/SSL on payload that comes from  IOTRFID reader to MQTT server . So the chances of MITM is negligible. 
open "Pseudo code for implementing encryption" file for code of TLS/SSL encryption using CA certificate.

# All screenshots of Outputs

Output to serial monitor while flashing to ESP8266 NodeMCU
![Screenshot from 2022-09-26 14-54-22](https://user-images.githubusercontent.com/55538188/192242713-fafa21ea-2907-413f-bb88-72b7ec8fa647.png)


Output on Subscribers code <br/>
![Screenshot from 2022-09-26 14-52-03](https://user-images.githubusercontent.com/55538188/192242827-8bc49931-5ceb-4742-a1d9-a000bdde912b.png)


Encrypted Data on MySQL Database
![Screenshot from 2022-09-26 14-52-28](https://user-images.githubusercontent.com/55538188/192242899-3c2497f1-30b3-4e5a-965a-269732dfe1d0.png)


Login Form Window for authentication. 

![Screenshot from 2022-09-26 14-52-51](https://user-images.githubusercontent.com/55538188/192242950-22a52967-27cf-48dc-8d8f-8e2b182fe99d.png)

GUI based visuals of Database for authenticated users such as admin.
![Screenshot from 2022-09-26 14-53-18](https://user-images.githubusercontent.com/55538188/192243041-8b5db235-a37d-4294-854d-5b52d28b1815.png)






