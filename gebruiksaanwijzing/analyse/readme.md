#  Analyse van het Linefollower Project

Dit document vat de bevindingen en conclusies samen die zijn voortgekomen uit de analysefase van de linefollower-robot. Het project toonde aan dat de beperkingen van de mechanische constructie de prestaties van zelfs geavanceerde softwarematige oplossingen (zoals PID) overtroeven.

---

## 1.  De Logica van de PID-Regelaar

### Uitgebreide Testen vs. Mechanische Beperkingen
Tijdens de ontwikkelingsfase is er uitgebreid geëxperimenteerd met verschillende soorten en configuraties van de PID-regelaar. Hoewel de PID-logica essentieel is voor het sturen, werd al snel duidelijk dat verdere optimalisatie van de parameters of de implementatie **geen significante snelheidsverbetering** meer opleverde.

De primaire reden hiervoor is de **constructie van de robot**. De batterij, die een aanzienlijk gewicht vormt, is te ver van de motorassen geplaatst. Dit verhoogt het traagheidsmoment en de onbalans, waardoor de robot fysiek niet in staat is om sneller door bochten te gaan, onafhankelijk van hoe perfect de PID-correctie ook is. De gewichtsverdeling zou idealiter **dichter bij de motorassen** moeten liggen.

---

## 2.  Sensor Data en de Vreemde 'Glitch'

### Het Filter dat de Robot Vertraagde

Toen ik grafiek bekeek (de afbeelding):
![Grafiek Position Data](Schermafbeelding%202025-11-29%20153837.png)
... zagen we dat de positiegegevens een beetje schommelden ('ruis'). ik dacht dat een filter (low pass, hoog frequente signalen eruit halen)

Het leek op de grafiek alsof het filter hielp:

![Grafiek Filterd Data](Schermafbeelding%202025-11-29%20155315.png)

### Waarom het Filter Fout was
Tijdens het rijden bleek de filtering een slecht idee:

1.  **Vertraging:** Het filteren kost tijd. omdat de hoogfrequente signalen eruit werden gefilterd, betekent dit ook dat de scherpe bochten wat ook een hoogfrequent signaal is er uit wordt gefilter daardoor kreeg de robot de positie-informatie te laat door.
2.  **Gevolg:** De robot stuurde daardoor te laat en werd trager.
3.  **De Vreemde Glitch:** Wat we leerden, is dat de oorspronkelijke schommelingen in de data de robot tijdens het rijden helemaal niet stoorden. Het was een vreemde fout in de meting zelf ('a rare quirk'), en het was beter om de data snel binnen te krijgen dan om het schoon te maken.



## 3.  Conclusie over Analyse en Telemetrie 

### De Prijs van Debugging
Achteraf gezien was de inspanning die is gestoken in het bouwen van het uitgebreide analysesysteem en de visualisatie waarschijnlijk niet de moeite waard in verhouding tot de prestatiewinst.

Het systeem verstuurt alle analysedata in JSON-formaat, wat een aanzienlijke overhead met zich meebrengt voor de microcontroller. Hierdoor wordt de code zelf merkbaar vertraagd. De robot zou veel sneller kunnen opereren zonder deze telemetrie.

Gelukkig kan deze vertraging gedeeltelijk worden beperkt: de telemetrie kan worden uitgeschakeld in de sensortab, met de radiobutten, waardoor de prestaties van de robot tijdens een run kunnen worden verbeterd.

Er zijn zeker betere manieren om dit te doen (BIT of CSV)
