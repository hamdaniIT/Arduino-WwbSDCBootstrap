#include <Arduino.h>

#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
File myFile;
String readString, pos;

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 1, 177);

int sdpin=4;

byte Rel1=14;
byte Rel2=15;
byte Rel3=16;
byte Rel4=17;
byte Rel5=18;
byte Rel6=19;
byte Rel7=20;
byte Rel8=21;


EthernetServer server(80);

String getNameFile(String link){
	int aw=-1;
	int kurang=5;
	aw=link.indexOf("GET /");
	if(aw==-1){

		aw=link.lastIndexOf("POST /");
		kurang=6;
	}
	int akh= link.lastIndexOf(" HTTP/1");
	return link.substring(aw+kurang,akh);
}
int cek(String in,String cari){
	return in.indexOf("cari");

}

boolean cekPassword(String pasClient, String userSimpan){
  boolean cekPas=false;
  if(pasClient.indexOf(userSimpan.substring(0,userSimpan.length()-1))>=0){
    cekPas=true;
  }else{
    cekPas=false; 
  }
  /*Serial.println("==================================");
  Serial.println(userSimpan.length());
  Serial.println(userSimpan.substring(0,userSimpan.length()-1));
  Serial.println("==================================");
  Serial.print(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
  Serial.print(pasClient);
  Serial.print("***");
  Serial.println(userSimpan);
  Serial.print(">>>>>>>>>>>>>>>>----------------------=");
  Serial.println(cekPas);*/
  return cekPas;
}
void setup(){
    pinMode(sdpin,OUTPUT);
	//Set pin Mode
	pinMode(Rel1,OUTPUT);
	pinMode(Rel2,OUTPUT);
	pinMode(Rel3,OUTPUT);
	pinMode(Rel4,OUTPUT);
    pinMode(Rel5,OUTPUT);
    pinMode(Rel6,OUTPUT);
	pinMode(Rel7,OUTPUT);
    pinMode(Rel8,OUTPUT);



	//Set logika pin 
	digitalWrite(Rel1, LOW);
	digitalWrite(Rel2, LOW);
	digitalWrite(Rel3, LOW);
	digitalWrite(Rel4, LOW);
    digitalWrite(Rel5, LOW);


  // Open serial communications and wait for port to open:
	Serial.begin(9600);
	while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
}


Serial.print("Initializing SD card...");

if (!SD.begin(sdpin)) {
	Serial.println("initialization failed!");
	return;
}
Serial.println("initialization done.");

Ethernet.begin(mac, ip);
server.begin();
Serial.print("server is at ");
Serial.println(Ethernet.localIP());
Serial.println("////////////////////////////////////");

}
void loop(){
EthernetClient client = server.available();
	if (client) {
		Serial.println("??????????????????????????????????????????????????????");
		Serial.println("new client");

		boolean currentLineIsBlank = true;
		while (client.connected()) {
			if (client.available()) {
				char c = client.read();
				Serial.write(c);
				if (readString.length() < 100) {

					readString += c;
				} 

				if (c == '\n' && currentLineIsBlank) {
					// Serial.print("url lllllllllllllll = ");
					// Serial.println(getNameFile(readString));
					client.println("HTTP/1.1 200 OK");
					// client.println("Content-Type: text/html");
					client.println("Content-Type: */*");
					client.println("Connection: close");
					client.println();
					String url=getNameFile(readString);
					 Serial.println("==================ooooooooo========================");
					 Serial.println(url.indexOf(".txt"));
					 Serial.println("==================000000000========================");
				    
					int cek =url.indexOf(".txt")  ;
				    if(cek>=0){


				    	//Control lampu 1
					 	if(url.indexOf("Lam1Off.txt")>=0){
					    digitalWrite(Rel1, HIGH);
					    client.println("Lampu Mati");
					    client.stop();
						}else if(url.indexOf("Lam1On.txt")>=0){
					    digitalWrite(Rel1, LOW);
					    client.println("Lampu Hidup");
					    client.stop();
						}
						//Control lampu 2
					 	if(url.indexOf("Lam2Off.txt")>=0){
					    digitalWrite(Rel2, HIGH);
					    client.println("Lampu Mati");
					    client.stop();
						}else if(url.indexOf("Lam2On.txt")>=0){
					    digitalWrite(Rel2, LOW);
					    client.println("Lampu Hidup");
					    client.stop();
						}
						//Control lampu 3
					 	if(url.indexOf("Lam3Off.txt")>=0){
					    digitalWrite(Rel3, HIGH);
					    client.println("Lampu Mati");
					    client.stop();
						}else if(url.indexOf("Lam3On.txt")>=0){
					    digitalWrite(Rel3, LOW);
					    client.println("Lampu Hidup");
					    client.stop();
						}
						//Control lampu 4
					 	if(url.indexOf("Lam4Off.txt")>=0){
					    digitalWrite(Rel4, HIGH);
					    client.println("Lampu Mati");
					    client.stop();
						}else if(url.indexOf("Lam4On.txt")>=0){
					    digitalWrite(Rel4, LOW);
					    client.println("Lampu Hidup");
					    client.stop();
						}
						//Control swim kipas angin
					 	if(url.indexOf("swmOff.txt")>=0){
					    digitalWrite(Rel8, HIGH);
					    client.println("Diam");
					    client.stop();
						}else if(url.indexOf("swmOn.txt")>=0){
					    digitalWrite(Rel8, LOW);
					    client.println("Berputar");
					    client.stop();
						}
						//Control Kipas angin
					 	if(url.indexOf("KipasOff.txt")>=0){
					    	digitalWrite(Rel5, HIGH);
					    	digitalWrite(Rel6, HIGH);
					    	digitalWrite(Rel7, HIGH);
					    	client.println("Kipas Mati");
					    	client.stop();
						}else if(url.indexOf("KOnSp1.txt")>=0){
					    	digitalWrite(Rel5, LOW);
					    	digitalWrite(Rel6, HIGH);
					    	digitalWrite(Rel7, HIGH);
					    	client.println("Spead 1");
					    	client.stop();
						}else if(url.indexOf("KOnSp2.txt")>=0){
					    	digitalWrite(Rel5, HIGH);
					    	digitalWrite(Rel6, LOW);
					    	digitalWrite(Rel7, HIGH);
					    	client.println("Spead 2");
					    	client.stop();
						}else if(url.indexOf("KOnSp3.txt")>=0){
							digitalWrite(Rel5, HIGH);
					    	digitalWrite(Rel6, HIGH);
					    	digitalWrite(Rel7, LOW);
					    	client.println("Spead 3");
					    	client.stop();
						}
					}else { 
						if( url.indexOf("index.htm?")>=0){
						boolean cekLog=false;
						 ///////////////chack user name and password///////////////////
							SD.begin(sdpin);
							myFile = SD.open("user.txt");
							if (myFile) {
							  while (myFile.available()) {
							  	// String baba="userName=Hamdani&password=12345";
							  	 String baba=myFile.readStringUntil('\n');
							    cekLog = cekLog || cekPassword(getNameFile(readString),baba);							
							  	// Serial.print("==========================gfsg===fgsdf===");
							  	// Serial.println(cekLog);
							  }					
								myFile.close();
							} 

							if(cekLog){
								Serial.println("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ok");
								SD.begin(sdpin);
								myFile = SD.open("indexii.htm");
								if (myFile) {
							  	while (myFile.available()) {
								  client.println(myFile.readStringUntil('\n'));
							  	}
									client.println(); 
									myFile.close();
									client.stop();
								} 
							    
							}else{
								goto jaum;
							}
              
              			//////////////////////////////////

						}else{
jaum:						SD.begin(sdpin);
							// myFile = SD.open(getNameFile( readString));
							myFile = SD.open("login.htm");
							if (myFile) {
							while (myFile.available()) {
								client.println(myFile.readStringUntil('\n'));
							}
								client.println(); 
								myFile.close();
								client.stop();
							} else {
								Serial.println("error opening file");
							} 
						} 
					}
					break;
				}
				if (c == '\n') {

					currentLineIsBlank = true;
				} else if (c != '\r') {
					currentLineIsBlank = false;
				}
			}

		}
		readString="";


		delay(1);
		client.stop();

		Serial.println("client disconnected");
	}
}