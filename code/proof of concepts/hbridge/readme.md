#  H-Brug Proof-of-Concept met de TB6612FNG Dual DC Motor Driver

Deze proof of concept demonstreert het principe van de **H-Brug** voor de onafhankelijke en traploze regeling van twee DC-motoren (snelheid en draairichting) met behulp van de TB6612FNG dual motor driver en een ESP32-microcontroller.

---

## 1.  Hardware Vereisten

| Component | Beschrijving | Opmerkingen |
| :--- | :--- | :--- |
| **Microcontroller** | ESP32-compatibel bord | Nodig voor geavanceerde PWM (LEDC) en snelle GPIO-schakeling. |
| **Motor Driver** | TB6612FNG Dual DC Motor Driver | Bevat de twee noodzakelijke H-bruggen. |
| **DC Motoren** | 2 x DC Motoren | De belasting die wordt aangestuurd. |
| **Voeding** | Externe voeding (5-12V) | **Belangrijk:** Voor de motoren (VM/VCC), gescheiden van de logica. |

> 

## 2.  Software Vereisten

* Arduino IDE (of PlatformIO).
* De meegeleverde `TB6612.h` en `TB6612.cpp` bibliotheekbestanden, verpakt als de `MotorDriver` klasse.

---

## 3.  Pinconfiguratie (ESP32)

De TB6612FNG wordt als volgt aangesloten op de ESP32:

| TB6612 Pin | ESP32 Pin | Functie | Mechanisme |
| :--- | :--- | :--- | :--- |
| **AIN1** | 17 | Richting Motor A | H-Brug Input 1 (IN) |
| **AIN2** | 16 | Richting Motor A | H-Brug Input 2 (IN) |
| **PWMA** | 25 | Snelheid Motor A | PWM (Enable) |
| **BIN1** | 18 | Richting Motor B | H-Brug Input 1 (IN) |
| **BIN2** | 19 | Richting Motor B | H-Brug Input 2 (IN) |
| **PWMB** | 26 | Snelheid Motor B | PWM (Enable) |

> **Opmerking:** Zorg ervoor dat de **STBY**-pin van de TB6612 permanent op **HIGH** is aangesloten om de driver in te schakelen.

---

## 4.  Stappenplan (Ingebruikname)

1.  **Aansluiten Hardware:** Verbind alle componenten volgens de pinconfiguratie. Sluit de DC-motoren aan op de **AOUT1/AOUT2** en **BOUT1/BOUT2** uitgangen en zorg voor de juiste stroomaansluitingen (VM/VCC/GND).
2.  **Code voorbereiden:** Plaats de meegeleverde bronbestanden in een map `TB6612` in de bibliotheekmap van je schets.
3.  **Uploaden:** Upload de hoofdcode (met de `loop()`) naar de ESP32.
4.  **Testen:** Open de Seriële Monitor (`115200` baud). De motoren starten de testcyclus.

---

## 5. Code Analyse (Werking & H-Brug Logica)

### 5.1. De `loop()` functie: Onafhankelijke & Traploze Regeling

De `loop()` demonstreert het Proof-of-Concept door beide motoren tegelijkertijd, maar onafhankelijk, door een volledige snelheidscyclus te sturen.

```cpp
void loop() {
  for(int i = -255; i < 255; i++){
    motors.set_speed(i,-i);
  }
}
```

Motor A (Snelheid i): Variëert van −255 (Max. Achteruit) →0 (Stilstand) →+255 (Max. Vooruit).

    Motor B (Snelheid -i): Variëert tegenovergesteld, van +255 (Max. Vooruit) →0 (Stilstand) →−255 (Max. Achteruit).

### 5.2. De set_speed(int16_t motor_a, int16_t motor_b) Functie

Deze functie vertaalt de invoersnelheid (bereik: [−255,255]) naar de fysieke sturing van de motor.
### 5.3 Richtingbepaling (H-Brug Logica)

De draairichting van de motor wordt bepaald door de logische toestand van de twee IN-pinnen van de H-brug (AIN1/AIN2 of BIN1/BIN2). Dit verandert de polariteit over de motor.

| Invoer Snelheid ($\text{motor}$) | IN1 ($\text{AIN1}$ of $\text{BIN1}$) | IN2 ($\text{AIN2}$ of $\text{BIN2}$) | Resultaat (Draairichting) |
| :---: | :---: | :---: | :--- |
| **Positief** $(>0)$ | $\text{Hoog} \text{ (Set)}$ | $\text{Laag} \text{ (Clear)}$ | **Voorwaarts** |
| **Negatief** $(<0)$ | $\text{Laag} \text{ (Clear)}$ | $\text{Hoog} \text{ (Set)}$ | **Achterwaarts** |
| **Nul** $(0)$ | $\text{Laag} \text{ (Clear)}$ | $\text{Laag} \text{ (Clear)}$ | **Stilstand** (Rem of Freewheel) |
