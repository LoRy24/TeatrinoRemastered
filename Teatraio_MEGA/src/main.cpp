#include <Arduino.h>

int lightsProfile = 1;
int lastLightProfile = 1;

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);

    pinMode(22, OUTPUT);
    pinMode(23, OUTPUT);
    pinMode(24, OUTPUT);
    pinMode(25, OUTPUT);
    pinMode(26, OUTPUT);
}

void playLightsProfile() {
    if (lightsProfile == 1) {
        digitalWrite(22, HIGH);
        digitalWrite(23, LOW);
        digitalWrite(24, HIGH);
        digitalWrite(25, LOW);
        digitalWrite(26, HIGH);
    }
    else if (lightsProfile == 2) {
        digitalWrite(22, LOW);
        digitalWrite(23, HIGH);
        digitalWrite(24, LOW);
        digitalWrite(25, HIGH);
        digitalWrite(26, LOW);
    }
}

void loop() {
    lastLightProfile = lightsProfile;

    if (Serial1.available() > 0) {
        const int newLightsProfile = Serial1.parseInt(); // NOLINT(*-narrowing-conversions)
        lightsProfile = newLightsProfile;
    }

    if (lastLightProfile != lightsProfile) {
        Serial.print("[!] Lights profile changed to ");
        Serial.print(lightsProfile);
        Serial.print("\n\r");
    }

    playLightsProfile();
}