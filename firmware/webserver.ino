#include <WiFi.h>
#include <WebServer.h>
#include <Stepper.h>

const char *ssid = "TNCAP6BA69B";
const char *password = "FEB41BCBE7";
const char *esp32_cam_ip = "http://192.168.1.30:81/stream"; //link can change


WebServer server(80);


#define steps_per_rev 300 
#define ENA  4  // Enable Motor A
#define IN1  17 // Motor A forward
#define IN2  21 // Motor A backward
#define ENB  18 // Enable Motor B
#define IN3  19 // Motor B forward
#define IN4  16 // Motor B backward
#define led 15

#define SIN1 25
#define SIN2 26
#define SIN3 22
#define SIN4 23
Stepper stepper(steps_per_rev, SIN1, SIN2, SIN3, SIN4);

void setup() {
    Serial.begin(115200);
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(led, OUTPUT);
    pinMode(SIN1, OUTPUT);
    pinMode(SIN1, OUTPUT);
    pinMode(SIN1, OUTPUT);
    pinMode(SIN1, OUTPUT);
    stepper.setSpeed(10);
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB,HIGH);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
        digitalWrite(led, HIGH);
        delay(1000);
        digitalWrite(led, LOW);
        delay(1000);
    }
    Serial.println("\nWiFi connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    digitalWrite(led, HIGH);

    server.on("/", handle_OnConnect);
    server.on("/forward", moveForward);
    server.on("/reverse", moveReverse);
    server.on("/left", turnLeft);
    server.on("/right", turnRight);
    server.on("/stop", stopMotors);
    server.on("/panright", panright);
    server.on("/panleft", panleft);
    server.onNotFound(handle_NotFound);
    
    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
}

void stopMotors() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    Serial.println("Motors Stopped");
    server.send(200, "text/html", SendHTML("Stopped"));
}

void moveForward() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    Serial.println("Moving Forward");
    server.send(200, "text/html", SendHTML("Forward"));
}

void moveReverse() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    Serial.println("Moving Reverse");
    server.send(200, "text/html", SendHTML("Reverse"));
}

void turnRight() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    Serial.println("Turning Right");
    server.send(200, "text/html", SendHTML("Right"));
}

void turnLeft() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    Serial.println("Turning Left");
    server.send(200, "text/html", SendHTML("Left"));
}

void panright() {
    Serial.println("Panning Right");
    stepper.step(steps_per_rev);
    server.send(200, "text/html", SendHTML("Panning Right"));
}

void panleft() {
    Serial.println("Panning Left");
    stepper.step(-steps_per_rev);
    server.send(200, "text/html", SendHTML("Panning Left"));
}

void handle_OnConnect() {
    Serial.println("Client Connected");
    server.send(200, "text/html", SendHTML("Welcome"));
}

void handle_NotFound() {
    server.send(404, "text/plain", "Not Found");
}

String SendHTML(String status) {
    String ptr = "<!DOCTYPE html> <html>\n";
    ptr += "<head><title>ESP32 Motor Control</title></head>\n";
    ptr += "<body><h1>ESP32 Web Motor Control</h1>\n";
    ptr += "<p>Status: " + status + "</p>\n";

    // ESP32-CAM Stream
    ptr += "<h2>ESP32-CAM Stream</h2>\n";
    ptr += "<img src='" + String(esp32_cam_ip) + "' width='320' height='240'>\n";

    // Motor Control Buttons
    ptr += "<h2>Motor Controls</h2>\n";
    ptr += "<a href='/forward'><button>Forward</button></a>\n";
    ptr += "<a href='/reverse'><button>Reverse</button></a>\n";
    ptr += "<a href='/left'><button>Left</button></a>\n";
    ptr += "<a href='/right'><button>Right</button></a>\n";
    ptr += "<a href='/stop'><button>Stop</button></a>\n";

    // Stepper Motor Pan Controls
    ptr += "<h2>Camera Panning</h2>\n";
    ptr += "<a href='/panright'><button>Pan Right</button></a>\n";
    ptr += "<a href='/panleft'><button>Pan Left</button></a>\n";

    ptr += "</body></html>\n";
    return ptr;
}