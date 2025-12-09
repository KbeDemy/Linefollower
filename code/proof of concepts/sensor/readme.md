# 📊 Sensoren Proof of Concept: Onafhankelijke ADC-Uitlezing (ESP32)

Dit project toont de basisfunctionaliteit van een ESP32 om **8 analoge sensoren** onafhankelijk uit te lezen, waarbij het volledige 12-bit bereik van de Analoog-naar-Digitaal Converter (ADC) wordt benut.

---

## 1. 🎯 Doelstelling

* Aantonen dat minimaal 6 (in dit geval 8) analoge ingangen onafhankelijk kunnen worden uitgelezen.
* Benutten van het volledige ADC-bereik (0-4095).
* Basisimplementatie zonder complexe verwerking (calibratie/normalisatie).

## 2. ⚙️ Hardware Vereisten

| Component | Beschrijving |
| :--- | :--- |
| **Microcontroller** | ESP32-compatibel bord |
| **Analoge Sensoren** | Minimaal 8 sensoren die variabele spanning leveren (0V - 3.3V). |

## 3. 📌 Pinconfiguratie

De code leest de waarden van **8 verschillende GPIO-pinnen** die zijn geconfigureerd als Analoge Ingangen (ADC).

| Sensor ID | ESP32 GPIO Pin | ADC-bereik |
| :---: | :---: | :---: |
| **S1** | 33 | 0-4095 |
| **S2** | 32 | 0-4095 |
| **S3** | 27 | 0-4095 |
| **S4** | 14 | 0-4095 |
| **S5** | 39 | 0-4095 |
| **S6** | 36 | 0-4095 |
| **S7** | 34 | 0-4095 |
| **S8** | 35 | 0-4095 |

---

## 4. 💻 Code Functionele Analyse

### Functie: Getimede Uitlezing

De `loop()`-functie zorgt ervoor dat de 8 analoge waarden slechts **één keer per seconde** worden uitgelezen en afgedrukt.

```cpp
void loop() {
  if (millis() - vorigeMillis >= 1000){
    // Lees 8 pinnen uit en formatteer de data...
    // ...
  }
}
```
Uitlezing en Formattering

De kern van de uitlezing is: $$ \text{Outputwaarde} = \text{analogRead}(\text{GPIO}) $$ Deze output is een integer tussen 0 en 4095 (12-bit resolutie).

De sprintf()-functie verzamelt de 8 onafhankelijke meetwaarden in één overzichtelijke string voor de Seriële Monitor:

S1: [Waarde] , S2: [Waarde] , S3: [Waarde] , ...

## 5. ▶️ Ingebruikname

    Sluit de 8 sensoren aan op de overeenkomstige GPIO-pinnen (32, 33, 27, 14, 39, 36, 34, 35).

    Upload de code naar de ESP32.

    Open de Seriële Monitor (115200 baud) om de onafhankelijke uitlezingen te observeren.
