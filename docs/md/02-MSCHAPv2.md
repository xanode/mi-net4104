# MSCHAPv2

Le protocole MSCHAPv2 est un protocole d'authentification de type CHAP (*Challenge Handshake Authentication Protocol*). L'objectif de cette classe de protocoles est de permettre à un client de s'authentifier en respectant les critères suivants :
- pas d'échange en clair du mot de passe ou d'une empreinte de celui-ci ;
- rejouabilité des échanges de nul effet pour un tier qui l'aurait intercepté.

Pour y parvenir, les protocoles de type CHAP réclament une preuve d'identité du client en lui demandant de répondre à un défi qui ne peut être relevé que par une entité connaissant le mot de passe. Par exemple, il pourrait être demandé au client de chiffrer un nombre aléatoire (fourni par l'authentificateur) avec le mot de passe (chose qui ne peut être réalisée qu'en connaissant le mot de passe).

Le protocole MSCHAPv2 fonctionne de la manière suivante :

![Séquence MSCHAPv2](files/MSCHAPv2_flow.png)

1. Le serveur d'authentification envoie 16 octets aléatoires au client (le défi, *SC*) ;
2. Le client, pour prouver son identité, réalise :
    - Génération d'un défi de 16 octets (*CC*) ;
    - Calcul du `ChallengeHash` (*CH*) : `SHA1(CC || SC || username)` ;
    - Calcul de l'empreinte MD4 du mot de passe ;
    - Calcul de la réponse au défi à partir de l'empreinte du défi ;
3. Le client envoie au serveur le nom d'utilisateur et la réponse au défi ;
4. Le serveur vérifie la réponse au défi en vérifiant que la réponse du client est correcte, et accepte ou non l'authentification.

Ainsi la seule inconnue pour un attaquant qui intercepte les échanges est l'empreinte MD4 du mot de passe de l'utilisateur, qui est utilisé pour construire les trois clés DES utilisées pour calculer la réponse au défi. Tout autre élément du protocole est soit envoyé en clair, soit facilement déductible des échanges.