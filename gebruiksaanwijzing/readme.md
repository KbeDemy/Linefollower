Gebruikershandleiding: LineFollow Robot

Deze handleiding beschrijft de veilige werking, draadloze bediening en configuratie van de LineFollow robot via de bijbehorende applicatie.
Veiligheidsinstructies: Batterijgebruik
Opladen & Batterijtype

De robot gebruikt een LiPo HV 2S batterij met een volledige spanning van 8.7 V. Dit type batterij vereist uiterste voorzichtigheid.

    GEVAAR! LiPo-batterijen zijn zeer brandgevaarlijk bij onjuist gebruik of beschadiging.

    Gebruik enkel de juiste, door de fabrikant gespecificeerde LiPo-lader.

    Laad de batterij altijd op met de individuele cel-balansdraad aangesloten om overladen en celonbalans te voorkomen.

    Zorg dat de batterij fysiek is losgekoppeld van de robot tijdens het opladen.

    De robot en de USB poort van uw computer kan niet tegelijk de USB en de batterij aan doe dit nooit!
Robot Aan/Uit Schakelen

De robot is niet voorzien van een fysieke aan/uit-schakelaar.

    AAN: Sluit de batterij aan op de robot.

    UIT: Koppel de batterij fysiek los van de robot.

Draadloze Communicatie & GUI Bediening

De robot communiceert via Bluetooth met de mobiele applicatie, waardoor er geen handmatige commando's nodig zijn.
Verbinding Maken / Verbreken
Actie	Procedure
Verbinden	
1. Zorg dat de robot is ingeschakeld (batterij aangesloten).
2. Open de app en ga naar de Connectie Tab.
3. Druk op de knop Verbinden. De app zal de status 'Verbonden' weergeven.
   
Verbreken	
De verbinding wordt verbroken door: 
1. In de app op Verbreken te drukken.
2. De applicatie te sluiten.
3. 3. De batterij fysiek uit de robot te halen.

De Vier Applicatie Tabs
1. Connectie Tab 

Toont de huidige verbindingsstatus en bevat de knoppen Verbinden en Verbreken.
2. Sensoren Tab 

Deze tab geeft de live data van de lijnsensoren weer.

    Visualisatie: Een balkgrafiek toont de uitgelezen sensorwaarden.

    Besturingsknoppen:
        Kalibreer Wit/Zwart: Zie de sectie Kalibratie hieronder.

3. Settings Tab
   
Deze tab is bedoeld voor het configureren van de robotparameters.
      
      Start: Start de automatische lijnvolgroutine (PID-controle).
      Stop: Stopt de robot onmiddellijk en schakelt de PID-lus uit.
      Parameters: 
      U kunt de Basis Snelheid (0-255), 
      de PID-parameters (Kp, Ki, Kd) instellen, 
      het minimaal contrast tussen zwart en wit wanneer de robot uitvalt en
      de loogdaarlaatfilter op de position.
      
      Testmodus (ZQSD): Dit biedt de mogelijkheid om de motoren manueel te testen en besturen met de ZQSD-toetsen (of vergelijkbare controls).

      Belangrijk: Manuele besturing is alleen mogelijk wanneer u in deze tab bent. Dit is handig om de robot na lijnverlies snel en handmatig terug op de lijn te plaatsen.

5. Plot Tab 

Deze tab dient voor het analyseren van de prestaties na een run.

    Run Selectie: U kunt eerder uitgevoerde runs selecteren en de data ervan terugkijken.

    Plot Opties: U kunt kiezen welke data wordt weergegeven:

        Individuele sensorwaarden.

        Configuratie-instellingen van de run (Kp, Ki, Kd, Speed).

        De cruciale regelvariabelen: Output (de stuurcorrectie van de PID-regelaar) en Position (de berekende lijnpositie).

Analyse: U kunt inzoomen op de grafiek om oscillatie te detecteren en uw PID-instellingen te finetunen.
Shutterstock

    Verkennen

Kalibratie (Normalisatie)

Kalibratie is het proces waarbij de sensorwaarden softwarematig worden genormaliseerd. Dit zorgt ervoor dat de robot de maximale contrastinformatie tussen de witte ondergrond en de zwarte lijn benut, en maakt de sensoren onderling gelijk.
Stappenplan

    Installeer de App: Ga naar de Connectie Tab en verbind met de robot.

    Kalibratie WIT (Minimale Waarden):

        Plaatsing: Plaats de robot op de witte achtergrond van het parcours dat u gaat gebruiken.

        Controle: Ga naar de Sensoren Tab en controleer of alle sensorbalken een lage waarde (bijna allemaal 'wit') aangeven.

        Uitvoeren: Druk op de knop Kalibreer WIT.

    Kalibratie ZWART (Maximale Waarden):

        Plaatsing: Plaats de robot met de sensoren direct op de zwarte lijn van het parcours.

        Controle: Ga naar de Sensoren Tab en controleer of alle sensorbalken een hoge waarde (bijna allemaal 'zwart') aangeven.

        Uitvoeren: Druk op de knop Kalibreer ZWART.

Let op: Het is cruciaal dat u deze stappen uitvoert op de exacte materialen (wit/zwart) die u tijdens de run zult gebruiken.

Aanbevolen Parameters

De robot rijdt stabiel met de volgende parameters:
Parameter	Waarde	Opmerking
Kp	[7]	Proportionele versterking.
Ki	[0]	Integrale versterking (voor lange-termijn fouten).
Kd	[0]	Differentiële versterking (voor het dempen van schommelingen).
Speed	[140]	De basissnelheid van de robot.
