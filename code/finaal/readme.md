#  LineFollow_V2 - Firmware Architectuur en Logica

Dit project is de C++ firmware voor een geavanceerde lijnvolgrobot, PID-regulatie en draadloze communicatie via Bluetooth. De code is gestructureerd voor een **ESP32** microcontroller.

---

## Kernstructuren (`struct`)

De code maakt intensief gebruik van C++ `structs` om gerelateerde data te organiseren, wat de leesbaarheid en het beheer van de robotstatus verbetert:

* **`Sensor`**: Bevat de pin, kalibratiewaarden (`zwart`, `wit` uit EEPROM), ruwe meting (`waarde`) en de genormaliseerde meting (`norm`).
* **`Motor`**: Bevat het motornummer, de huidige snelheid (`speed`) en de fysieke PWM/IN1/IN2 pinnen.
* **`pidController`**: Bevat de operationele toestand van de PID-lus (`kp`, `ki`, `kd`, `error`, `integral`, `derivative`, `output`).
* **`ConfigParams`**: De structuur die **alle** door de gebruiker te configureren parameters bevat (PID-termen, `power`, `interval`, `filterAlpha`, `contrastDrempel`). Dit blok wordt als geheel opgeslagen in de EEPROM.
* **`status robot`**: Een globale struct die de lopende toestand van de robot bijhoudt (`run`, `verbonden`, `eenLijn`).

---

## De Hoofdregelcyclus (`loop()`)

De `loop()` functie voert twee hoofdtaken uit op basis van getimede intervallen:

### 1. Bluetooth Communicatie (Niet-blokkerend)

De code controleert continu (`SerialBT.available()`) op inkomende berichten:

* **Handshake:** Verwerking van de **`PING`**/**`PONG`** routine voor verbindingbeheer en timeout-controle.
* **JSON Parsing:** Inkomende JSON-berichten worden verwerkt om **runtime configuratie** of **commando's** te ontvangen (via functies als `handlePid`, `handleSpeed`, `calibWit`).
* **Controle:** Configuratie-wijzigingen worden enkel geaccepteerd wanneer `robot.run` **`false`** is, om de controlelus niet te verstoren tijdens het rijden.

### 2. De Regelcyclus (PID / Sensorverwerking)

De cruciale lus wordt uitgevoerd op basis van een variabele intervaltimer (`calc.interval`, standaard 2000 microseconden, dus 500 keer per seconde).

#### A. Sensor Normalisatie

* De functie `sensorNormalisatie()` leest de ruwe analoge waarden en gebruikt de gekalibreerde `wit` en `zwart` waarden om een **genormaliseerde** waarde (`0` tot `4095`) te berekenen.

#### B. Positiebepaling

* De code bepaalt de sensor met de hoogste genormaliseerde waarde (`index`).
  
* De locatie van de lijn wordt berekend met Kwadratische Interpolatie, die de pieksensor (s1) en zijn twee directe buren (s0, s2) analyseert om een vloeiende position te bepalen (geschaald van -30.0 tot 30.0). Om de interpolatie te laten werken wanneer de lijn de uiterste sensoren raakt (en er slechts één buur is), gebruikt de code virtuele sensoren.

    Logica: De ontbrekende buitenste buur krijgt een vaste waarde van 0.0f toegekend.

    Doel: Door de interpolatie de waarde van 0.0f te laten meenemen, behoudt de code de analoge nauwkeurigheid van de methode tot aan de rand. Dit voorkomt een abrupte (digitale) stuurcorrectie en               zorgt voor stabiele stuuracties wanneer de robot de randen van de lijn volgt.
    
* Deze ruwe positie wordt door een **Laagdoorlaatfilter** gehaald (`filterPosition`) met `filterAlpha` om ruis te dempen en de stabiliteit te verhogen. (aanpasbaar in GUI)

#### C. Lijnverliesdetectie (`geenLine`)

* De functie `geenLine()` berekent het **contrast** (`maxWaarde - minWaarde`) tussen alle genormaliseerde sensoren.
* Als dit contrast onder de `contrastDrempel` (een configureerbare waarde) valt, wordt aangenomen dat de lijn verloren is.
* Bij een overgang van 'lijn gevonden' naar 'lijn verloren' (`positieve edge`) wordt `robot.run` onmiddellijk op `false` gezet, en gaan de motoren stil.

#### D. PID-Uitvoering

* Als `robot.run` **`true`** is, roept de lus `updatePID(filterPosition, power)` aan.
* De PID-output wordt berekend op basis van de `error` (die gelijk is aan `-filterPosition`), de geaccumuleerde `integral` en de berekende `derivative`.
* De output wordt gebruikt om de basissnelheid (`power`) te moduleren en de snelheden voor de linker- en rechtermotor te bepalen, wat resulteert in sturing.

#### E. Motor Aansturing

* De functie `motors.set_speed(motoren[0].speed, motoren[1].speed)` stuurt de uiteindelijke snelheden van de twee motoren aan 

## Configuratie Permanentie

De firmware zorgt voor permanente opslag van configuraties via de `EEPROM` bibliotheek:

* **EEPROM Adressen:** Adressen worden dynamisch beheerd via de `eepromOffsets` structuur om flexibiliteit in structuurgrootte te behouden.
* **First Flash Check:** Bij de eerste opstart na een flash wordt gecontroleerd op een unieke waarde (`EEPROM_FIRST_CHECK`). Zo niet, dan worden alle sensor- en `ConfigParams` standaardwaarden weggeschreven.
* **Debounced Commit:** De functie `markConfigAsDirty()` wordt aangeroepen na elke configuratiewijziging. De daadwerkelijke `EEPROM.commit()` vindt echter pas plaats in de `loop()` nadat er 2 seconden **geen** configuratiewijzigingen zijn geweest. Dit vermindert de slijtage van het EEPROM-geheugen.
