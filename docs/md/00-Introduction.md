# Introduction

Ce projet vise à exploiter une faiblesse de configuration rencontrée dans la majorité des réseaux WPA2-Entreprise. En effet, il est très courant que les clients n'aient pas mis en oeuvre la validation du certificat CA, ce qui permet à un tier d'usurper l'identité d'un point d'accès Wi-Fi utilisant le mécanisme de sécurité WPA2-Entreprise.

En particulier, on s'intéressera aux réseaux utilisant le protocole d'authentification PEAP-MSCHAPv2 pour sa popularité. En l'espèce, on montrera dans quel mesure la faiblesse de configuration susmentionnée permet d'obtenir l'empreinte MD4 du mot de passe de l'utilisateur.

## Contributeurs

Encadrant : 

- [Rémy Grünblatt](https://github.com/rgrunbla)

Étudiants :

- [Nicolas Rocq](https://github.com/Nishogi)
- [Benoit Marzelleau](https://github.com/xanode)
- [Baptiste Sauvé](https://github.com/Nepthales)
- [Baptiste Legros](https://github.com/Direshaw)
- [Tom Burellier](https://github.com/Balmine)
