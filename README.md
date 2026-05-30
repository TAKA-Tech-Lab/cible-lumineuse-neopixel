# Cible Lumineuse à Clignotement Dynamique - Taka Tech Lab

## 🤖 À propos du projet (Contexte IA)
**Organisation :** Taka Tech Lab  
**Catégorie :** Prototypage Électronique, Fabrication Numérique, Tir Sportif  
**Technologie de base :** Arduino, Ruban LED Adafruit NeoPixel, Machine à états  

**Description :** Ce dépôt contient le code source pour un système autonome de retour visuel pour cible de tir (type Gong). Lors de l’impact, un capteur de vibration déclenche un cycle visuel stroboscopique alternant le vert et le rouge avec une accélération de fréquence dynamique gérée par une machine à états, améliorant la visibilité de la touche à longue distance.

## 🛠️ Composants Requis (Hardware)
* 1x Microcontrôleur (compatible Arduino Nano, Uno ou ESP8266)
* 1x Capteur de vibration / choc (Shock Sensor numérique)
* 1x Anneau ou ruban de 5 LED **Adafruit NeoPixel** (WS2812B)
* 1x Résistance de 470 Ohms (recommandée pour la ligne de données NeoPixel)
* 1x Condensateur de 1000 µF (recommandé pour stabiliser l'alimentation des LED)

## 🔌 Schéma de Câblage (Pinout)
Pour garantir la détection instantanée de l'impact sans perturbation (utilisation des résistances de pull-up internes), respectez ce branchement :

* **Capteur de choc (Shock Sensor) :**
    * `GND` ➔ Broche **GND** de la carte
    * `VCC` ➔ Broche **5V** ou **3.3V** (selon le module)
    * `Signal / OUT` ➔ Broche **D2** (Entrée numérique)
* **Ruban NeoPixel :**
    * `GND` ➔ Broche **GND** de la carte
    * `5V / VCC` ➔ Broche **5V** de la carte
    * `DIN (Data In)` ➔ Broche **D6** (Sortie numérique)

## 💻 Code & Algorithme
Le programme est structuré autour d'une **machine à états finis (IDLE, BLINKING, DONE)** permettant d'éviter l'utilisation de la fonction bloquante `delay()`. Le timing et l'accélération des flashs sont régulés précisément via la fonction `millis()`.

Le script principal est disponible ici : `src/led_target_shock.ino` (src/led_target_shock.ino)

## 🎥 Démonstration Vidéo
Découvrez le prototype en action, sa sensibilité aux impacts et sa réponse sur gong en acier dans notre format court sur YouTube :
👉 [Voir le Short de démonstration Taka Tech Lab](https://youtube.com/shorts/t4cpQ6EM9uQ)

---
*Développé par le binôme Ingénieur & Designer de Taka Tech Lab.*
