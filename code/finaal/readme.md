#  LineFollow_V2 - Geavanceerde Lijnvolgrobot (ESP32 / PID)

Dit project is de firmware voor een lijnvolgrobot op basis van een **ESP32** microcontroller. Het maakt gebruik van een reeks analoge lijnsensoren, een TB6612FNG motorstuurprogramma en een Bluetooth-verbinding voor runtime configuratie en telemetrie via een externe GUI.

##  Belangrijkste Functies

* **PID-Controle:** Implementatie van een Proportioneel-Integraal-Derivatief (PID) algoritme om de robot nauwkeurig op de lijn te houden.
* **8-Sensor Array:** Gebruik van 8 analoge sensoren om de positie van de lijn te bepalen met kwadratische interpolatie.
* **Bluetooth Configuratie:** Volledige draadloze configuratie (PID-parameters, snelheid, contrast) en monitoring via de `BluetoothSerial` bibliotheek.
* **Permanente Opslag (EEPROM):** Opslag van configuratieparameters en sensorcalibratiewaarden in het EEPROM-geheugen van de ESP32.
* **Line Lost Detection:** Automatische stop bij het verliezen van de lijn (drempelwaarde gebaseerd op contrast).

---

##  Hardware Vereisten

Dit project is geschreven voor een **ESP32** microcontroller en vereist de volgende hardwarecomponenten:

* **Microcontroller:** ESP32-board
* **Motor Driver:** TB6612FNG (of compatibele) motorstuurprogramma.
* **Motoren:** Twee DC-motoren.
* **Lijnsensoren:** Een array van 8 analoge reflectiesensoren (aangesloten op de gedefinieerde GPIO-pinnen).

### Pin Configuratie

| Component | Pin Functie | GPIO-Pin(s) |
| :--- | :--- | :--- |
| **Motoren** | Linker Motor PWM/IN1/IN2 | `25`, `17`, `16` |
| | Rechter Motor PWM/IN1/IN2 | `26`, `18`, `19` |
| **Sensoren** | Analoge Ingangen | `33`, `32`, `27`, `14`, `39`, `36`, `34`, `35` |
| **Bluetooth**| Interne ESP32 Bluetooth | N/A |

---

##  Software Setup (Arduino IDE)

### 1. Bibliotheken Installeren

Dit project vereist de volgende externe bibliotheken die u in de Arduino IDE (of via `platformio.ini`) moet installeren:

1.  **`BluetoothSerial`**: Standaard ESP32-bibliotheek voor Bluetooth Classic Serial.
2.  **`TB6612`**: Een bibliotheek voor de TB6612FNG Dual Motor Driver (Zorg ervoor dat u de compatibele versie voor uw driver heeft).
3.  **`EEPROM`**: Standaard ESP32-bibliotheek voor EEPROM-emulatie.

### 2. Eerste Flash en EEPROM Initialisatie

Bij de **eerste keer** uploaden naar de ESP32 zal de code de EEPROM controleren op een 'magic number' (`0xBEEDCAFE`).

* Als dit nummer niet wordt gevonden, initialiseert de `setup()` functie de EEPROM automatisch met **veilige standaardwaarden** (Default ConfigParams).
* **LET OP:** Als u de configuratie volledig wilt resetten, moet u de EEPROM handmatig wissen of de checkwaarde in het geheugen wijzigen.

---

##  Gebruik en Configuratie

### 1. Bluetooth Verbinding

De robot zendt zichzelf uit als **`LineFollow_V2`** via Bluetooth Classic.

* Een externe GUI moet verbinding maken met dit apparaat.
* De communicatie werkt via **JSON-berichten** (als string-lijnen afgesloten met `\n`).

### 2. Essentiële Commando's (via BT/GUI)

| Commando | Beschrijving |
| :--- | :--- |
| **`"PING"`** | Handshake om de verbinding te controleren. De robot antwoordt met `"PONG"` en reset de verbindingstimer. |
| **`{"run": "true/false"}`** | Start (`true`) of stopt (`false`) de lijnvolgroutine. Bij `false` worden de motoren onmiddellijk stilgezet. |
| **`{"telem": "true/false"}`** | Schakelt het verzenden van telemetrie-data (sensorwaarden, positie, PID-output) aan/uit. |

### 3. Configuratie Commando's (alleen bij `robot.run = false`)

De PID-parameters, snelheid en drempels kunnen alleen worden gewijzigd wanneer de robot **stilstaat**. Wijzigingen worden in RAM opgeslagen en na 2 seconden inactiviteit naar EEPROM geschreven (**debounced commit**).

* **PID:** `{"pid": {"kp": 1.0, "ki": 0.0, "kd": 0.0}}`
* **Snelheid (Power):** `{"speed": 50}` (Basissnelheid, 0-255)
* **Interval (Regelcyclus):** `{"interval": 2000}` (Interval van de PID-berekening in microseconden)
* **Calibratie:** `{"calib": "white"}` of `{"calib": "black"}`
* **Manuele Motorcontrole:** `{"motor": 1, "value": 150}` (Motor 1, snelheid 150)

### 4. PID-Loop Logica (`updatePID` functie)

1.  **Foutberekening (`pid.error`):** De error is gebaseerd op de `filterPosition` (de laagdoorlaatgefilterde positie van de lijn, geschaald van -60.0 tot 60.0).
2.  **Output:** De PID-output wordt berekend op basis van $\text{PID Output} = \text{Kp} \cdot \text{Error} + \text{Ki} \cdot \text{Integral} + \text{Kd} \cdot \text{Derivative}$.
3.  **Motorbesturing:** De output wordt gebruikt om de basissnelheid (`baseSpeed`) van de motoren te corrigeren:
    * **Linker Motor Snelheid:** $\text{BaseSpeed} + \text{PID Output}$
    * **Rechter Motor Snelheid:** $\text{BaseSpeed} - \text{PID Output}$

Dit zorgt ervoor dat wanneer de robot naar links afdwaalt (positieve `position`), de linkermotor langzamer gaat en de rechtermotor sneller, waardoor de robot naar rechts stuurt.

---

##  Veiligheid en Debugging

* **DEBUG-Toggle:** De globale `#define DEBUG 0` kan op `1` gezet worden om alle `Debug_print` en `Debug_println` berichten naar de seriële monitor te sturen.
* **Line Lost Stop:** De functie `geenLine()` controleert het contrast tussen de maximale en minimale genormaliseerde sensorwaarde. Als het contrast onder de `contrastDrempel` komt, wordt de lijn als verloren beschouwd en wordt `robot.run` op `false` gezet, waardoor de motoren stoppen.

## Batterij & USB
zorg ervoor dat batterij en de USB nooit samen de robot voeden, want dan gaan er onvoorspelbare dingen geberuen met de USB-poort en de Robot zelf

