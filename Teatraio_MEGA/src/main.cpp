#include <Arduino.h>

// Pin RGB
#define RED_PIN 2
#define GREEN_PIN 3
#define BLUE_PIN 4

// Pin Controllo
#define C_LED_1 22
#define C_LED_2 23
#define C_LED_3 24
#define C_LED_4 25
#define C_LED_5 26
#define C_LED_6 27
#define C_LED_7 28
#define C_LED_8 29
#define C_LED_9 30
#define C_LED_10 31
#define C_LED_11 32
#define C_LED_12 33

// Settings
#define LED_LIGHT_DELAY 1

// Valori set
int lastLightProfile = 1;
int lightsProfile = 1;

void setup() {
    // Seriale
    Serial.begin(9600);
    Serial1.begin(9600);

    // Imposta tutti i pin definiti come OUTPUT
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);

    // Pin LED
    pinMode(C_LED_1, OUTPUT);
    pinMode(C_LED_2, OUTPUT);
    pinMode(C_LED_3, OUTPUT);
    pinMode(C_LED_4, OUTPUT);
    pinMode(C_LED_5, OUTPUT);
    pinMode(C_LED_6, OUTPUT);
    pinMode(C_LED_7, OUTPUT);
    pinMode(C_LED_8, OUTPUT);
    pinMode(C_LED_9, OUTPUT);
    pinMode(C_LED_10, OUTPUT);
    pinMode(C_LED_11, OUTPUT);
    pinMode(C_LED_12, OUTPUT);
}

void setColor(const int red, const int green, const int blue) {
    analogWrite(RED_PIN, red);
    analogWrite(GREEN_PIN, green);
    analogWrite(BLUE_PIN, blue);
}

void playLedColor(const int led, const int red, const int green, const int blue) {
    setColor(red, green, blue);
    digitalWrite(led, LOW);
    delay(LED_LIGHT_DELAY);
    digitalWrite(led, HIGH);
}

/*
 * Profili Luci
 */

void playProfile1() {
    playLedColor(C_LED_1, 255, 255, 255); // Bianco
    playLedColor(C_LED_2, 76, 204, 250); // Azzurro
    playLedColor(C_LED_3, 247, 39, 36); // Rosso
    playLedColor(C_LED_4, 246, 122, 252); // Rosa
    playLedColor(C_LED_5, 255, 255, 255); // Bianco
    playLedColor(C_LED_6, 244, 233, 1); // Giallo
    playLedColor(C_LED_7, 246, 165, 29); // Arancione
    playLedColor(C_LED_8, 244, 233, 1); // Giallo
    playLedColor(C_LED_9, 255, 255, 255); // Bianco
    playLedColor(C_LED_10, 76, 204, 250); // Azzurro
    playLedColor(C_LED_3, 247, 39, 36); // Rosso
    playLedColor(C_LED_12, 255, 255, 255); // Bianco
}

void playProfile2() {
    playLedColor(C_LED_1, 255, 255, 255); // Bianco
    playLedColor(C_LED_2, 246, 165, 29); // Arancione
    playLedColor(C_LED_3, 247, 39, 36); // Rosso
    playLedColor(C_LED_4, 247, 39, 36); // Rosso
    playLedColor(C_LED_5, 255, 255, 255); // Bianco
    playLedColor(C_LED_6, 246, 165, 29); // Arancione
    playLedColor(C_LED_7, 247, 39, 36); // Rosso
    playLedColor(C_LED_8, 246, 165, 29); // Arancione
    playLedColor(C_LED_9, 255, 255, 255); // Bianco
    playLedColor(C_LED_10, 247, 39, 36); // Rosso
    playLedColor(C_LED_11, 247, 39, 36); // Rosso
    playLedColor(C_LED_1, 255, 255, 255); // Bianco
}

void playProfile3() {
    playLedColor(C_LED_1, 255, 255, 255); // Bianco
    playLedColor(C_LED_2, 144, 25, 236); // Viola
    playLedColor(C_LED_3, 76, 204, 250); // Azzurro
    playLedColor(C_LED_4, 60, 68, 249); // Blu
    playLedColor(C_LED_5, 76, 204, 250); // Azzurro
    playLedColor(C_LED_6, 255, 255, 255); // Bianco
    playLedColor(C_LED_7, 76, 204, 250); // Azzurro
    playLedColor(C_LED_8, 255, 255, 255); // Bianco
    playLedColor(C_LED_9, 76, 204, 250); // Azzurro
    playLedColor(C_LED_10, 60, 68, 249); // Blu
    playLedColor(C_LED_11, 144, 25, 236); // Viola
    playLedColor(C_LED_12, 255, 255, 255); // Bianco
}

void playProfile4() {
    playLedColor(C_LED_1, 255, 255, 255); // Bianco
    playLedColor(C_LED_2, 32, 182, 39); // Verde Scuro
    playLedColor(C_LED_3, 144, 243, 77); // Verde Chiaro
    playLedColor(C_LED_4, 76, 204, 250); // Azzurro
    playLedColor(C_LED_5, 32, 182, 39); // Verde Scuro
    playLedColor(C_LED_6, 255, 255, 255); // Bianco
    playLedColor(C_LED_7, 144, 243, 77); // Verde Chiaro
    playLedColor(C_LED_8, 255, 255, 255); // Bianco
    playLedColor(C_LED_9, 76, 204, 250); // Azzurro
    playLedColor(C_LED_10, 144, 243, 77); // Verde Chiaro
    playLedColor(C_LED_11, 32, 182, 39); // Verde Scuro
    playLedColor(C_LED_12, 255, 255, 255); // Bianco
}

void playErrorProfile() {
    playLedColor(C_LED_1, 255, 255, 255);
    playLedColor(C_LED_2, 255, 255, 255);
    playLedColor(C_LED_3, 255, 255, 255);
    playLedColor(C_LED_4, 255, 255, 255);
    playLedColor(C_LED_5, 255, 255, 255);
    playLedColor(C_LED_6, 255, 255, 255);
    playLedColor(C_LED_7, 255, 255, 255);
    playLedColor(C_LED_8, 255, 255, 255);
    playLedColor(C_LED_9, 255, 255, 255);
    playLedColor(C_LED_10, 255, 255, 255);
    playLedColor(C_LED_11, 255, 255, 255);
    playLedColor(C_LED_12, 255, 255, 255);
    delay(500);
    playLedColor(C_LED_1, 0, 0, 0);
    playLedColor(C_LED_2, 0, 0, 0);
    playLedColor(C_LED_3, 0, 0, 0);
    playLedColor(C_LED_4, 0, 0, 0);
    playLedColor(C_LED_5, 0, 0, 0);
    playLedColor(C_LED_6, 0, 0, 0);
    playLedColor(C_LED_7, 0, 0, 0);
    playLedColor(C_LED_8, 0, 0, 0);
    playLedColor(C_LED_9, 0, 0, 0);
    playLedColor(C_LED_10, 0, 0, 0);
    playLedColor(C_LED_11, 0, 0, 0);
    playLedColor(C_LED_12, 0, 0, 0);
    delay(500);
}

void playLightsProfile() {
    // Switch in base al profilo luci
    switch (lightsProfile) {
        case 1: {
            playProfile1();
            break;
        }

        case 2: {
            playProfile2();
            break;
        }

        case 3: {
            playProfile3();
            break;
        }

        case 4: {
            playProfile4();
            break;
        }

        default: {
            playErrorProfile();
            break;
        }
    }
}

// Routine

void loop() {
    // Aggiorna l'ultimo profilo
    lastLightProfile = lightsProfile;

    // Leggi il nuovo profilo quando inviato
    if (Serial1.available() > 0) {
        const int newLightsProfile = Serial1.parseInt(); // NOLINT(*-narrowing-conversions)
        lightsProfile = newLightsProfile;
    }

    // Notifica il cambio in seriale
    if (lastLightProfile != lightsProfile) {
        Serial.print("[!] Lights profile changed to ");
        Serial.print(lightsProfile);
        Serial.print("\n\r");
    }

    // Avvia il profilo luci
    playLightsProfile();
}