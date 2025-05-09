// Libs
#include <Arduino.h>

#pragma region Definitions

// Pin RGB
#define RED_PIN A0
#define GREEN_PIN A1
#define BLUE_PIN A2

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
#define MULTIPLEX_INTERVAL 1000
#define LEDS 12

#pragma endregion

#pragma region Multiplexing Leds

// Pin dei leds sotto forma di vettore
int ledsPins[LEDS] = {
    C_LED_1,
    C_LED_2,
    C_LED_3,
    C_LED_4,
    C_LED_5,
    C_LED_6,
    C_LED_7,
    C_LED_8,
    C_LED_9,
    C_LED_10,
    C_LED_11,
    C_LED_12
};

// Multiplexing dei Led
int currentMultiplexingLed = 0;
unsigned long lastMultiplexUpdate = 0;

// Funzione per il colore
void setColor(const int red, const int green, const int blue) {
    analogWrite(RED_PIN, red);
    analogWrite(GREEN_PIN, green);
    analogWrite(BLUE_PIN, blue);
}

#pragma endregion

#pragma region Profili Leds

// Settings di controllo
int lastLightProfile = 1;
int lightsProfile = 1;

#pragma region Settings dei profili

// Profili
int profiles[5][LEDS][3] = {
    {
        {255, 255, 255},    // Bianco
        {76, 204, 250},     // Azzurro
        {247, 39, 36},      // Rosso
        {246, 122, 252},    // Rosa
        {255, 255, 255},    // Bianco
        {244, 233, 1},      // Giallo
        {246, 165, 29},     // Arancione
        {244, 233, 1},      // Giallo
        {255, 255, 255},    // Bianco
        {76, 204, 250},     // Azzurro
        {247, 39, 36},      // Rosso
        {255, 255, 255},    // Bianco
    },
    {
        {255, 255, 255},    // Bianco
        {246, 165, 29},     // Arancione
        {247, 39, 36},      // Rosso
        {247, 39, 36},      // Rosso
        {255, 255, 255},    // Bianco
        {246, 165, 29},     // Arancione
        {247, 39, 36},      // Rosso
        {246, 165, 29},     // Arancione
        {255, 255, 255},    // Bianco
        {247, 39, 36},      // Rosso
        {247, 39, 36},      // Rosso
        {255, 255, 255},    // Bianco
    },
    {
        {255, 255, 255},    // Bianco
        {144, 25, 236},     // Viola
        {76, 204, 250},     // Azzurro
        {60, 68, 249},      // Blu
        {76, 204, 250},     // Azzurro
        {255, 255, 255},    // Bianco
        {76, 204, 250},     // Azzurro
        {255, 255, 255},    // Bianco
        {76, 204, 250},     // Azzurro
        {60, 68, 249},      // Blu
        {144, 25, 236},     // Viola
        {255, 255, 255},    // Bianco
        },
    {
        {255, 255, 255},    // Bianco
        {32, 182, 39},      // Verde scuro
        {144, 243, 77},     // Verde chiaro
        {76, 204, 250},     // Azzurro
        {32, 182, 39},      // Verde scuro
        {255, 255, 255},    // Bianco
        {144, 243, 77},     // Verde chiaro
        {255, 255, 255},    // Bianco
        {76, 204, 250},     // Azzurro
        {144, 243, 77},     // Verde chiaro
        {32, 182, 39},      // Verde scuro
        {255, 255, 255},    // Bianco
    },
    {
        {255, 0, 0},        // Rosso
        {255, 0, 0},        // Rosso
        {255, 0, 0},        // Rosso
        {255, 0, 0},        // Rosso
        {255, 0, 0},        // Rosso
        {255, 0, 0},        // Rosso
        {255, 0, 0},        // Rosso
        {255, 0, 0},        // Rosso
        {255, 0, 0},        // Rosso
        {255, 0, 0},        // Rosso
        {255, 0, 0},        // Rosso
        {255, 0, 0},        // Rosso
    },
};

#pragma endregion

#pragma endregion

#pragma region Routine

void playLightsProfile() {
    // Millisecondi attuali
    const unsigned long currentMicroseconds = micros();

    // Se da aggiornare, aggiorna
    if (currentMicroseconds - lastMultiplexUpdate > MULTIPLEX_INTERVAL) {
        // Aggiorna l'ultimo aggiornamento
        lastMultiplexUpdate = currentMicroseconds;

        // Spegni il led e cambialo
        digitalWrite(ledsPins[currentMultiplexingLed], HIGH);
        currentMultiplexingLed = (currentMultiplexingLed + 1) % LEDS;

        // Imposta il nuovo colore in base al profilo e accendi
        setColor(profiles[lightsProfile][currentMultiplexingLed][0], profiles[lightsProfile][currentMultiplexingLed][1], profiles[lightsProfile][currentMultiplexingLed][2]);
        digitalWrite(ledsPins[currentMultiplexingLed], LOW);
    }
}

void setup() {
    // Seriale
    Serial.begin(9600);
    Serial1.begin(9600);

    // Imposta i pin RGB
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);

    // Pin LED
    for (const int ledsPin : ledsPins) {
        pinMode(ledsPin, OUTPUT);
        digitalWrite(ledsPin, HIGH);
    }

    // Spegni i pin RGB
    analogWrite(RED_PIN, 0);
    analogWrite(GREEN_PIN, 0);
    analogWrite(BLUE_PIN, 0);
}

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

    // Gestisci i profili luci
    playLightsProfile();
}

#pragma endregion
