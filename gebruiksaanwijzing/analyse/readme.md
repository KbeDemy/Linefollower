#  Analyse van het Linefollower Project

Dit document vat de bevindingen en conclusies samen die zijn voortgekomen uit de analysefase van de linefollower-robot. Het project toonde aan dat de beperkingen van de mechanische constructie de prestaties van zelfs geavanceerde softwarematige oplossingen (zoals PID) overtroeven.

---

## 1.  De Logica van de PID-Regelaar

### Uitgebreide Testen vs. Mechanische Beperkingen
Tijdens de ontwikkelingsfase is er uitgebreid geëxperimenteerd met verschillende soorten en configuraties van de PID-regelaar. Hoewel de PID-logica essentieel is voor het sturen, werd al snel duidelijk dat verdere optimalisatie van de parameters of de implementatie **geen significante snelheidsverbetering** meer opleverde.

De primaire reden hiervoor is de **constructie van de robot**. De batterij, die een aanzienlijk gewicht vormt, is te ver van de motorassen geplaatst. Dit verhoogt het traagheidsmoment en de onbalans, waardoor de robot fysiek niet in staat is om sneller door bochten te gaan, onafhankelijk van hoe perfect de PID-correctie ook is. De gewichtsverdeling zou idealiter **dichter bij de motorassen** moeten liggen.

---

## 2.  Sensor Data en de 'Position Quirk'

### De Vraag naar een Low-Pass Filter
Bij het bekijken van de 'position'-gegevens op de grafische weergave ![Grafiek Position Data](gebruiksaanwijzing/analyse/Schermafbeelding%202025-11-29%20153837.png) ontstond aanvankelijk de gedachte dat een low-pass filter nodig was om de ruis van de sensoren te onderdrukken.

Echter, uit de daadwerkelijke testruns bleek dat de fluctuaties op de sensordata **niet significant van invloed** waren op het uiteindelijke stuurgedrag van de robot. Het is een **ongewoon artefact** in de meetgegevens ('a rare quirk') waarvan de exacte oorzaak moeilijk te duiden is. Dit betekende dat de implementatie van een low-pass filter voor dit specifieke doel **niet nodig** was.

---

## 3.  Conclusie over Analyse en Telemetrie 

### De Prijs van Debugging
Achteraf gezien was de inspanning die is gestoken in het bouwen van het uitgebreide analysesysteem en de visualisatie waarschijnlijk niet de moeite waard in verhouding tot de prestatiewinst.

Het systeem verstuurt alle analysedata in JSON-formaat, wat een aanzienlijke overhead met zich meebrengt voor de microcontroller. Hierdoor wordt de code zelf merkbaar vertraagd. De robot zou veel sneller kunnen opereren zonder deze telemetrie.

Gelukkig kan deze vertraging gedeeltelijk worden beperkt: de telemetrie kan worden uitgeschakeld in de sensortab, met de radiobutten, waardoor de prestaties van de robot tijdens een run kunnen worden verbeterd.
