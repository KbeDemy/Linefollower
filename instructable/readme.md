# Instructable

Een instructable is een stappenplan - zonder verdere uitleg - hoe je vertrekkend van de bill of materials en gebruik makend van de technische tekeningen de robot kan nabouwen. Ook de nodige stappen om de microcontroller te compileren en te uploaden staan beschreven.  

### stap 1
bestel alle componenten uit de bill of materials  
en 3d print de componenten die in de map /technishe tekeningen/mechanish staatn

### stap 2 
soldeer de pinnen aan de componenten 

Ik heb gekozen voor breakoutboard's om het simpel te houden en als iets kapotgaat kan je het gemakeijk vervangen

### stap 3 
soldeer de vrouwelijk header pinnnen aan het development bordje
doe dit op de juiste plaatsen zorg dat je genoeg plaats hebt tussen het ge 3d printe frame en de pinnen
zie afbeelding 

### stap 4 
plaats de extenden female pinnen op de female pinnen, zorg dat de esp juist is georienteerd

### stap 5 
maak de juiste verbindingen tussen alle componenten volg daarbij het schema in technishe tekeningen / schemaPlanB

### stap 6 
soldeer 2 condenstatoren over de motoren dit zorgt voor spanningspieken te vermijden en is dus in het algemeen wel een goed idee (dit hoeft niet)
soldeer ook 2 draden aan de motor om dan via het "poortje" naar het printplaatje te gaan en ze zo te solderen 

### stap 7 
nu is de laatse stap nog de sensoren juist te verbinden met deze oplossing ben ik zelf niet zo blij maar wat we doen is we nemen dupont draadjes en steken die in de overgebleven 
open female headers, wat we eerst moeten doen is de verbinding tussen de ESP pinnen en de female headers maken hier is een schema van hoe dat er uit ziet 

### stap 7.5
het laatse wat we nog moeten doen is de batterijspanning in onze robot krijgen dit doen we met de male extender cord 
we knippen hem af op maat, boor van de bovenkant een gat in de printplaat ik heb het in bijde hoeken gedaan zodat de uiteinden van de draajes de + en - pads kunnen raken 
soldeer ze aan elkaar 
plaats in parrel over de batterijspanning een condensator van 1000µf deze zal er voor zorgen dat spanningpieken opgevagnen worden 


### stap 8
nu we klaar zijn met alles solderen kunnen we overgaan naar het monteren van alle stukken dus neem je boutjes en moertjes er bij en plaatse het printplaatbord onder het frame lijn het uit met de gaten en 
schroef het aankelaar met de 4 conishe bout en moer , 
