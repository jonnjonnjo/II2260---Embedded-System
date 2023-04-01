#include <WiFi.h>
#include <Arduino.h>
#include <Wire.h>
#include <BMx280I2C.h>

// Replace with your network credentials
const char* ssid = "DESKTOP-FB605Q6 6208";
const char* password = "sinaga123";

// for bmp
#define I2C_SDA 21
#define I2C_SCL 22
#define I2C_ADDRESS 0x76
BMx280I2C bmx280(I2C_ADDRESS);


// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String redState = "off";
String yellowState = "off";
String greenState = "off";

// Assign output variables to GPIO pins
const int redPin = 23;
const int yellowPin = 19;
const int greenPin = 3;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 60000;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs

  pinMode(redPin,OUTPUT);
  pinMode(yellowPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  
  digitalWrite(redPin,LOW);
  digitalWrite(yellowPin,LOW);
  digitalWrite(greenPin,LOW);
  while (!Serial);

  //  Wire.begin();
  Wire.begin(I2C_SDA, I2C_SCL);

  
  //begin() checks the Interface, reads the sensor ID (to differentiate between BMP280 and BME280)
  //and reads compensation parameters.
  //if (!bmx280.begin())
  //{
    //Serial.println("begin() failed. check your BMx280 Interface and I2C Address.");
  // while (1);
 // }

  bmx280.begin();
  if (bmx280.isBME280())
    Serial.println("sensor is a BME280");
  else
    Serial.println("sensor is a BMP280");

  //reset sensor to default parameters.
  bmx280.resetToDefaults();

  //by default sensing is disabled and must be enabled by setting a non-zero
  //oversampling setting.
  //set an oversampling setting for pressure and temperature measurements.
  bmx280.writeOversamplingPressure(BMx280MI::OSRS_P_x16);
  bmx280.writeOversamplingTemperature(BMx280MI::OSRS_T_x16);

  //if sensor is a BME280, set an oversampling setting for humidity measurements.
  if (bmx280.isBME280())
    bmx280.writeOversamplingHumidity(BMx280MI::OSRS_H_x16);

//------------------------------------------------------------------------------------------------------------------

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){


///---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
//----------------
  float temperature = 0;
  float pressure = 0;


  //start a measurement
  if (!bmx280.measure())
  {
    Serial.println("could not start measurement, is a measurement already running?");
    return;
  }

  //wait for the measurement to finish
 // do
 // {
 //   delay(100);
//  } while (!bmx280.hasValue());

  //  Serial.print("Pressure: "); Serial.println(bmx280.getPressure());
  //  Serial.print("Pressure (64 bit): "); Serial.println(bmx280.getPressure64());
  //  Serial.print("Temperature: "); Serial.println(bmx280.getTemperature());

  pressure = bmx280.getPressure();
  temperature = bmx280.getTemperature();
//----------------------------------------------
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /23/on") >= 0) {
              Serial.println("GPIO 23 on");
              redState= "on";
              digitalWrite(redPin, HIGH);
            }else if (header.indexOf("GET /23/off") >= 0) {
              Serial.println("GPIO 23 off");
              redState = "off";
              digitalWrite(redPin,LOW);
            }else if (header.indexOf("GET /1/on") >= 0) {
              Serial.println("GPIO 1 on");
              yellowState ="on";
              digitalWrite(yellowPin, HIGH);
            }else if (header.indexOf("GET /1/off") >= 0) {
              Serial.println("GPIO 1 off");
              yellowState = "off";
              digitalWrite(yellowPin,LOW);
            }else if (header.indexOf("GET /3/on") >= 0) {
              Serial.println("GPIO 3 on");
              greenState ="on";
              digitalWrite(greenPin, HIGH);
            }else if (header.indexOf("GET /3/off") >= 0) {
              Serial.println("GPIO 3 off");
              greenState = "off";
              digitalWrite(greenPin,LOW);
            }

            
            // Display the HTML web page
              client.println(" <!DOCTYPE html><html>");
              client.println(" <head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
              client.println("     <link href='https://fonts.googleapis.com/css?family=Open+Sans' rel='stylesheet'>");
              client.println(" <style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
              client.println(" .button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
              client.println(" text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
              client.println(" .button2 {background-color: #555555;}");
              client.println(" header {");
              client.println("         background-color: #333; /* Set the background color */");
              client.println("         color: white; /* Set the text color */");
              client.println("         padding: 20px; /* Add some padding */");
              client.println("         text-align: center; /* Center the text */");
              client.println("       }");
              client.println("       ");
              client.println("       /* Style for the heading */");
              client.println("       h1 {");
              client.println("         font-size: 36px; /* Set the font size */");
              client.println("         margin: 0; /* Remove margin */");
              client.println("       }");
              client.println("       ");
              client.println("       /* Style for the subheading */");
              client.println("       h2 {");
              client.println("         font-size: 24px; /* Set the font size */");
              client.println("         margin: 0; /* Remove margin */");
              client.println("       }");
              client.println("       body {");
              client.println("         font-family: 'Open Sans', sans-serif;");
              client.println("         font-size: 16px;");
              client.println("         font-weight: 400;");
              client.println("         line-height: 1.5;");
              client.println("       }");
              client.println("       h1, h2, h3, h4, h5, h6 {");
              client.println("         font-weight: 600;");
              client.println("         margin-bottom: 1rem;");
              client.println("       }");
              client.println("       p {");
              client.println("         margin-bottom: 1rem;");
              client.println("       }");
              client.println(" ");
              client.println(" ");
              client.println(" </style></head>");
              client.println(" ");
              client.println(" <body>");
              client.println(" <header>");
              client.println("     <h1>Jon's Weather Station</h1>");
              client.println("     <h2> Temperature - Pressure - Control over LED</h2>");
              client.println(" </header>");

            client.println("<p> Temperature : " + (String)temperature + " °C <p>");
            client.println("<p>Pressure : " + (String)pressure + " Pa <p>");

            // Display current state
            client.println("<p>RED LED - State " +redState + "</p>");
            if(redState == "off")
            {
              client.println("<p><a href=\"/23/on\"><button class=\"button\">ON</button></a></p>");
            }else
            {
              client.println("<p><a href=\"/23/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("<p>Yellow LED - State " +yellowState + "</p>");
            if(yellowState == "off")
            {
              client.println("<p><a href=\"/1/on\"><button class=\"button\">ON</button></a></p>");
            }else
            {
              client.println("<p><a href=\"/1/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("<p>Green LED - State " +greenState + "</p>");
            if(greenState == "off")
            {
              client.println("<p><a href=\"/3/on\"><button class=\"button\">ON</button></a></p>");
            }else
            {
              client.println("<p><a href=\"/3/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}