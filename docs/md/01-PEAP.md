
# EAP et PEAP

Le protocole EAP (*Extensible Authentification Protocol*) est un protocole de communication réseau qui est utilisé pour authentifier un partenaire.

PEAP (*Protected Extensible Authentication Protocol*) est un protocole utilisé pour protéger les réseaux Wi-Fi. PEAP est une extension de EAP (*Extensible Authentication Protocol*), qui encapsule les messages EAP dans un tunnel TLS afin d'améliorer la sécurité des échanges.

EAP est un protocole d'authentification dévelopé initialement pour les réseau filaire supportant les connexions point-à-point, où la sécurité physique était présupposée. EAP a ensuite été adopté pour l'authentification 802.1x pour le contrôle d'accès des réseaux locaux, mais il est vite apparût que EAP n'était pas suffisamment sécurisé dans un ensemble de cas d'utilisation.

PEAP a été développé pour pallier à ces faiblesses. En l'espèce, PEAP encapsule la session EAP dans un tunnel TLS, de façon à protéger les échanges entre le client et le serveur d'authentification, qui, entres autres, sont susceptibles de contenir les informations d'identification du client.

![Séquence EAP](files/eap.png)


Un réseau Wi-Fi utilisant 802.1X est composé de trois éléments principaux :
- Le *serveur* est le composant central d'un réseau à accès contrôlé. Il gère les fonctions d'authentification et d'autorisation des supplicants. Situés dans le réseau de confiance, c'est lui qui décide si la connexion d'un supplicant au réseau à accès contrôlé est autorisée ou refusée.
- le *client* est le composant qui contrôle l'accès au réseau. Il fait le lien entre les supplicants et le serveur d'authentification.
- le (ou les) *supplicant* est le composant qui demande l'accès au réseau.

![Architecture 802.1X](files/réseau_802_1x.png)

La connexion à un tel réseau se fait en plusieurs étapes (méthode EAP) :
 1. **Initialisation** : le client détecte la tentative de connexion du supplicant au réseau.
 2. **Identification** :
    - Le client transmet au supplicant la demande d'identification ;
    - le supplicant retourne au client son identité ;
    - le client transmet l'identité du supplicant au serveur.
3. **Négociation EAP** :
    - Le serveur indique au client la méthode d'authentification à utiliser (dans notre cas d'utilisation, MSCHAPv2) ;
    - le client transmet cette information au supplicant ;
    - si le supplicant accepte la méthode d'authentification, il procède à l'étape d'authentification, sinon il envoie au client les méthodes supportées et l'étape de négociation recommence.
4. **Authentification** :
    - le serveur et le supplicant échangent des messages dont la nature est tributaire de la méthode d'authentification utilisée (voir la section sur MSCHAPv2 pour nore cas d'utilisation) ;
    - le serveur indique au client si l'authentification a réussi ou échoué. Le supplicant est connecté au réseau selon le succès de celle-ci.

Le protocole PEAP a la particularité de de procèder à l'authentification du supplicant dans un tunnel TLS au moyen d'une méthode EAP. Cette étape d'authentification précédée d'une phase où le serveur s'authentifie aurpès du supplicant au moyen d'un certificat. Or, la (grande) majorité des réseaux WPA2-Entreprise n'imposent pas aux utilisateurs de valider le certificat du serveur (souvent pour des raisons de simplicité, jugeant que l'import par l'utilisateur d'un certificat sur son équipement est trop délicat pour un public non initié), ce qui rend possible une attaque de type « jumeau maléfique », dans laquelle un attaquant peut se faire passer pour un point d'accès légitime et intercepter les informations d'identification du client.

![Attaque de type "jumeau maléfique"](files/réseau_802_1x_evil.png)