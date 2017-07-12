/* TC, 10.07.2017: Programcode for a ESP8266 Module.
The Module opens a Wifi AccessPoint to which you can connect and then use TCP/IP to Port 123 to the Module (Gateway) 
to send and receive serial data. Tools to use are: Putty, Minicom, Screen, picocom
The Module sends all serial data it gets via this TCP Connection.
It also outputs all received data on it's TX Serial Pin.
The baudrate is set to 115200.
The IP is set to 192.168.1.1, the first client gets 192.168.1.100 */
#include <ESP8266WiFi.h>

const char* ssid = "ESP8266_ser_2_wifi";
WiFiServer server(123);
char buffer[256] = "";

void setup() {
	// Start serial
	Serial.begin(115200);
	 
	// Start Wifi AccessPoint
	WiFi.mode(WIFI_AP);
	IPAddress ip(192, 168, 1, 1);
	IPAddress gateway(192, 168, 1, 1);
	IPAddress subnet(255, 255, 255, 0); 	
	WiFi.softAPConfig(ip, gateway, subnet);
	WiFi.softAP(ssid);
	// Start TCP Server
	server.begin();
}

void loop() {
	// Check if a client has connected - we don't need to do anything until then
	WiFiClient client = server.available();
	if (!client) 
	{
		return;
	}	
	
	//Serial.print("Client connected");
	
	// If we're here we have a connected client.
	while (1) {
		// If he sends data simply spit it out on our serial Pin
		if (client.available()) {
			// Clear our buffer
			memset(buffer, 0, sizeof(buffer));
			// Read Bytes (up to 255) in our buffer
			client.readBytes(buffer, 255);
			// Send our Buffer
			Serial.print(buffer);		
			// Simple version
			// Serial.write(client.read());
		}
		
		// Else send all data on the serial port to the client
		if (Serial.available()) {
			// Clear our buffer
			memset(buffer, 0, sizeof(buffer));
			// Read Bytes (up to 255) in our buffer
			Serial.readBytes(buffer, 255);
			// Send our Buffer
			client.print(buffer);
			// Simple -but slow- version
			// client.write(Serial.read());
		}
		
		if (client.connected() == 0) {
			//Serial.print("Client disconnected");
			break;
		}
	}
}
