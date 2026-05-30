/*
 * =========================================================================
 * PROJET : Cible Lumineuse Autonome à Impact (Gong Réactif)
 * AUTEUR : Taka Tech Lab (Binôme Ingénieur & Designer)
 * URL    : https://github.com/TakaTechLab/cible-lumineuse-neopixel
 * VIDÉO  : https://youtube.com/shorts/t4cpQ6EM9uQ
 * LICENCE: MIT (Libre d'utilisation avec obligation de crédit)
 * =========================================================================
 * Description : Gestion par machine à états (sans delay) d'un cycle de 
 * clignotement dynamique (Vert/Rouge) avec accélération 
 * temporelle après détection d'impact sur broche D2.
 */

#include <Adafruit_NeoPixel.h>

#define SHOCK_SENSOR_PIN 2
#define NEOPIXEL_DATA_PIN 6
#define NUM_PIXELS 5

Adafruit_NeoPixel pixels(NUM_PIXELS, NEOPIXEL_DATA_PIN, NEO_GRB + NEO_KHZ800);

// --------------------
// MACHINE A ETATS
// --------------------
enum State {
  IDLE,
  BLINKING,
  DONE
};

State state = IDLE;

// --------------------
// PARAMÈTRES
// --------------------
const int TOTAL_CYCLES = 4;     // 3 répétitions
const int PHASES = 4;            // vert / off / rouge / off

unsigned long shockStartTime = 0;
unsigned long lastBlinkTime = 0;

int stepIndex = 0;
int cycleCount = 0;

// vitesse dynamique
unsigned long blinkInterval = 100;
const unsigned long MIN_INTERVAL = 20;
const unsigned long ACCEL_STEP = 20;

// --------------------
void setAllPixels(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUM_PIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
  pixels.show();
}

// --------------------
void setup() {
  Serial.begin(9600);

  pinMode(SHOCK_SENSOR_PIN, INPUT_PULLUP);

  pixels.begin();
  pixels.setBrightness(255);
  pixels.clear();
  pixels.show();

  Serial.println("Système prêt");
}

// --------------------
void loop() {
  unsigned long currentTime = millis();
  int shockValue = digitalRead(SHOCK_SENSOR_PIN);

  // --------------------
  // 1. Déclenchement
  // --------------------
  if (state == IDLE) {
    if (shockValue == LOW) {
      Serial.println("Choc détecté !");
      state = BLINKING;

      shockStartTime = currentTime;
      lastBlinkTime = currentTime;

      stepIndex = 0;
      cycleCount = 0;
      blinkInterval = 80; // reset vitesse
    }
  }

  // --------------------
  // 2. CLIGNOTEMENT
  // --------------------
  if (state == BLINKING) {

    if (currentTime - lastBlinkTime >= blinkInterval) {
      lastBlinkTime = currentTime;

      int phase = stepIndex % PHASES;

      switch (phase) {
        case 0: setAllPixels(0, 255, 0); break; // vert
        case 1: pixels.clear(); pixels.show(); break;
        case 2: setAllPixels(255, 0, 0); break; // rouge
        case 3: pixels.clear(); pixels.show(); break;
      }

      stepIndex++;

      // fin d'un cycle complet (4 phases)
      if (stepIndex % PHASES == 0) {
        cycleCount++;

        // accélération
        if (blinkInterval > MIN_INTERVAL) {
          blinkInterval -= ACCEL_STEP;
        }
      }

      // fin des 3 cycles
      if (cycleCount >= TOTAL_CYCLES) {
        state = DONE;
        pixels.clear();
        pixels.show();
        Serial.println("Séquence terminée");
      }
    }
  }

  // --------------------
  // 3. FIN
  // --------------------
  if (state == DONE) {
    // retour automatique à l'état initial si plus de choc
    if (shockValue == HIGH) {
      state = IDLE;
    }
  }
}
