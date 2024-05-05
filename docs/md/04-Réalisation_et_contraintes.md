# Réalisations et contraintes

## Historique chronologique

### Au début : L'ESP32-S3

Pour mettre en place notre solution de jumeau maléfique sur les bornes eduroam, nous avons tout d’abord utilisé le matériel fourni par le professeur, c’est à dire une carte ESP32-S3. Cette carte est un microcontrôleur intégrant la gestion du wifi et du bluetooth. Nous avons donc tout d’abord passé un moment à comprendre comment fonctionne l'ESP 32-S3 et mettre en place nos environnements de travail, à l’aide de la documentation officielle afin d’émettre un réseau wifi simple qui utilisait le protocole WPA2 (personnel). Tout le code de l'environnement de l'ESP32 est disponible sur la page github du projet. Sachant que pour mettre en place l'environement de travail nous avons suivis les instructions de la documentations de l'extension VS code de espressif [https://github.com/espressif/vscode-esp-idf-extension/blob/master/docs/tutorial/install.md].

Une fois l’environnement mis en place et avoir compris comment fonctionnait l’ESP32 nous avons été mis devant la dure réalité que l'ESP 32-S3 ne supportait pas le WPA2 Entreprise en mode access point "ESP32-S3 supports Wi-Fi Enterprise only in station mode." de cette documentation [https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/api-guides/wifi-security.html], ce qui a résulté en la perte de plusieurs longues heures de travail. La conclusion suite à cet échec fut la suivante, il nous fallait un nouveau point d'accès wifi comme une borne. Après quelques discussions avec le professeur, il a pu nous fournir une borne Cisco flashé sous OpenWRT.
    

### 2ème solution : La borne OpenWRT

Après l'échec de l'ESP32, il a donc fallu prendre en main la nouvelle technologie qui est la suivante : Une borne cisco sous OpenWRT.

L'avantage : il existe une magnifique interface HTTP pour gérer l'ensemble des fonctionnalités premières de la borne.
L'inconvéniant : c'est quand même vachement plus compliqué de setup une borne Cisco plutôt qu'un ESP32, mais bon avait pas le choix.

Nous avons donc pris du temps pour comprendre le fonctionnement du nouveau matériel et mettre en place notre nouvel environnement de travail. Première étape : il s'agissait de flash notre magnifique nouvelle borne. Je passe l'étape ou nous avons flash la borne 3 ou 4 fois parce que ça marchait pas pour des raisons obscurs, et la fois ou on a flash une snapshot ce qui a donné une image incomplète, sans les drivers wifi, donc impossible d'émettre quoi que ce soit !

Mais je ne vais pas passer l'étape où il a fallu connecter la borne à internet, mais également dans un réseau local pour se ssh pour installer les paquets wpa par défaut et wpa-entreprise. On a tout d'abord essayé un partage de connexion, mais cela ne permettait pas de se ssh. Il a alors fallu à partir de deux interface d'un ordinateur, créer un bridge réseau, l'une des interface connecté à internet via le réseau de la DISI, et l'autre connecté à la borne, ce qui nous a permis de nous ssh en ayant une connexion internet.

Donc finalement, nous avons pu à l'aide de documentation en ligne émettre un réseau wpa-entreprise avec cette borne ! Mais c'est alors que viens le problème suivant : comment est-ce qu'on intercepte les paquets de connexion wifi sans rentrer dans un monde bas niveau dans lequel on a pas envie d'aller ? Et bah il semblerais qu'on peut pas, ou du moins simplement, sans craquer la borne en somme.

Donc, on doit encore écarter cette solution, et en trouver une autre, qui intègre directement l'aspect interception des données, la partie à la limite de l'illégal en somme.

### Solution finale : Hostapd-WPE

Nous voilà à cours de solutions, il nous fallait trouver une alternative pour devenirs de gentils petits hackers très malveillants et intercepter les paquets chiffrés. 

Nous sommes tombés un peu au hasard sur le package Hostapd-wpe (big up au moteur de recherche Google).

Ce package contient une version modifiée de hostapd avec le patch hostapd-wpe. Il met en œuvre des attaques d'usurpation d'Authentificateur IEEE 802.1x pour obtenir les informations d'identification des clients. Bah c'est super ! C'est exactement ce dont on a besoin.

Sans rentrer dans les détails, car ils sont dans la partie `03-Attaque`, nous avons configurer le point d'accès malveillant à l'aide de `hostapd-wpe` qui permet de réaliser l'attaque "evil twin" et surtout d'obtenir les informations d'identification du client échangés lors de l'authentification.


