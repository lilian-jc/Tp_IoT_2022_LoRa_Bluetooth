## TP1
Ce script nous permet d'envoyer des données vers le serveur mqtt.
Dans un premier temps la connexion WIFI est initialisée.
La connexion au serveur MQTT, et au topic voulu est ensuite effectuée. Enfin, on récupère les valeurs des pin correspondant aux capteurs d'humidité et de température pour les écrire sur le serveur MQTT.

## TP2
Ce Script nous permet d'établir une relation émetteur/transmetteur entre deux device LoRa.
Dans notre cas, nous nous étions attribué le rôle d'esclave, c'est à dire que notre carte était chargé de se connecter a la carte d'un autre groupe qui elle éest donc le maitre. 
Dans un premier temps, nous avons donc convenu des différents paramètres de la communication sans fil LoRa: Fréquence, bande-passante et facteur d'étalement.
Ensuite nous avons utilisé ces valeurs pour configurer le modem LoRa sur la carte. Puis une fois la communiction établi avec la carte "serveur", nous écoutons et affichons les valeurs réguliérement émises par celui-ci.

## TP3
