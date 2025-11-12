# Gebruiksaanwijzing

### opladen / vervangen batterijen
gebruik van een LIPO HV 2s batterij deze batterijen hebben een spanning van 8.7 V
deze batterijen zijn gevaarlijk!
laad enkel op met de juiste oplader, laad altijd op met indivuduele cell draadje 


### draadloze communicatie
#### verbinding maken
Zorg dat de robot aan ligt 
open de app en druk op verbinden

als op de app staat dat je verbonden bent ben je verbonden 

Je kan de verbinding ook verbreken door:

1. de app te sluiten 
2. door op verbinding sluiten te drukken in de app
3. door de batterij uit te robot te halen zodat hij geen stroom meer krijgt

#### commando's
Door dat we een app gebruiken is er geen nood aan commando's
maar hier leg ik je uit hoe en wat de app allemaal kan 
we hebben 4 tabs 

### 1 Connectie Tab
Hier word weergegeven als je verbonden bent met de robot 
Door verbinden te drukken, probeert te app te verbinden met de robot
Door verbreken te drukken, verbreek je de verbinding met de robot 

### 2 Sensoren Tab 
In deze tab zie je wat de sensoren uitlezen
in een balkgrafiek wat handig kan zijn voor 
de sensoren te testen.

Vanonder aan deze tab heb je nog 4 knoppen.
Kalibreer wit/zwart zie kalibreer sectie 

Start : start de robot.
Stop : stopt de robot.

### 3 Settings Tab
Hier kan je de Speed van 0-255 instellen 
en de PID parameters instellen 

ook kan je de motoren testen door ZQSD te gebruiken dit kan ook 
handig zijn als de robot van de lijn gaat dan kan je 
hem manueel besturen om terug op de lijn te gaan 

De besturing met ZQSD besturen kan enkel in deze tab!

### 4 Plot Tab

In deze tab heb kan je de bepaalde runs terugbekijken 
je kan de run selecteren, ook kan je kiezen wat de grafiek plot keuze tussen,
elke individuele sensor, de waarde van instelling Kp,Ki,Kd,Speed in de run
en de belangerijke zijn natuurlijk de output, position.

In de grafiek kan je dan inzoomen 
hier kan je zien of je wat oscillatie hebt en kijken of je instelling perfect of het nog beter kan 

### kalibratie
Kalibratie is gelijk aan normalisatie
Door dit te doen word softwarematig alle sensoren zoveel mogelijk gelijk aan elkaar gemaakt,

1. de minimale waarden: dit zijn de wit waarden,
   dus plaats de robot op de witte achtergrond waar de volgende run gaat plaatsvinden
   ga naar app/connect en verbind met de robot
   ga naar app/sensor kijk of de sensorwaarden redelijk juist zijn en bijna allemaal wit zijn
   belangerijk is dat je dit niet op zwart doet
   druk op kalibreer WIT

2. de maximale waarden: dit zijn de zwarte waarden,
   dus plaats de robot op de zwarte lijn waar de volgende run gaat plaatsvinden
   ga naar app/sensor kijk of de sensorwaarden redelijk juist zijn en bijna allemaal zwart zijn
   belangerijk is dat je dit niet op wit doen
   druk op kalibreer ZWART

### settings
De robot rijdt stabiel met volgende parameters: 


### start/stop button
De robot heeft geen hardware switch, het aan uit doen we door de batterij uit te halen 
De robot word gestart en gestopt door start stop te klikken in de app/sensor (tab)
