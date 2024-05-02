
# EAP 

Le protocole EAP (*Extensible Authentification Protocol*) est un protocole de communication réseau qui est utilisé pour authentifier un partenaire.

![Séquence MSCHAPv2](files/eap.png)

Il y a 3 grandes étapes dans la communication entre un partenaire et l'authentificateur (*respectivement Peer et Authenticator ci-dessus*) :
- Une phase d'identification, l'authenticator envoie une requête au peer et recoit une réponse.
- Une phase de challenge du peer, l'authenticator va envoyer de un à plusieurs challenges contenant une méthode d'authentification et le peer va répondre à chaque challenge avant d'en recevoir un autre.
- Une phase de validation, en fonction des réponses du peer, l'authenticator va envoyer un code au peer signifiant le succes (et donc l'établissement de la connexion) ou l'echec.

Ce protocole est considéré comme extensible, car il y a plusieurs de méthodes d'authentification possibles (MD5, OTP, SIM, GTC...) mais il n'est pas nécessaire de refaire un protocole si on souhaite implémenter une autre méthode. 
Dans notre étude, nous utiliserons comme méthode d'authentification MSCHAPv2 qui est adopté par le standard WPA et WPA2.

Le PEAP (*Protected Extensible Authenticator Protocol*) est la version "protégée" concu par Microsoft et Cisco et inspiré par le EAP-TTLS (utilisant un tunnel TLS). Le PEAP se déroule en deux phases, analogue au EAP:
- une phase d'identification du serveur via utilisation de clés publique (PKI), une fois identifié, un tunnel sécurisé chiffre la phase suivante.
- une phase d'identification du client, qui se déroule à l'intérieur du tunnel de la phase 1.

L'utilisation du PEAP nécessite d'avoir un Certificat d'Authentification (*CA*) SSL ou TLS du coté serveur, cependant pour le client, le certificat n'est pas requis.

