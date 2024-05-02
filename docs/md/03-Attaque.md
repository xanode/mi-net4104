# L'attaque

## Evil twin

### Principe
Une attaque de type "evil twin" exploite la façon dont les clients WiFi reconnaissent les réseaux, en se basant principalement sur le nom du réseau (ESSID) sans exiger de la station de base (point d'accès) qu'elle s'authentifie auprès du client. Il s'agit d'une faiblesse de configuration rencontrée dans la majorité des réseaux WPA2-Entreprise, lesquels n'imposent pas aux utilisateurs de contrôler le certificat présenté par le point d'accès pour des raisons de simplicité.

Les points clés sont les suivants de l'attaque sont les suivants :

- **Différenciation difficile** : Il est difficile de différencier un point d'accès légitime d'un point d'accès malveillant lorsque leurs ESSID sont confondus et qu'ils partagent le même mécanisme de sécurité (WPA2-Enterprise dans notre cas). D'autant plus que les réseaux WPA2-Enterprise que l'ont retrouve dans les établissements utilisent souvent plusieurs point d'accès avec le même ESSID pour étendre la courverture de manière transparente pour les utilisateurs finaux.
- **Itinérance des clients et manipulation des connexions** : Le protocole 802.11 permet aux appareils de passer d'un point d'accès à l'autre au sein d'un même ESS. Il est possible d'exploiter cette possibilité en incitant un appareil à se déconnecter de son point d'accès actuel et à se connecter à un point d'accès malveillant. Il est possible d'y parvenir en offrant un signal plus fort ou en perturbant la connexion au point d'accès légitime en envoyant des paquets de désauthentification ou en le brouillant.


### Mise en œuvre

Nous allons configurer le point d'accès malveillant à l'aide de `hostapd-wpe` qui est un correctif de `hostapd` qui permet de réaliser l'attaque "evil twin" et surtout d'obtenir les informations d'identification du client (dont le sujet est traité ci-après) échangés lors de l'authentification (et normalement inaccessibles avec `hostapd` seul).

```bash
# Installation de hostapd-wpe
sudo apt install hostapd-wpe
```

Nous configurons `hostapd-wpe` de la sorte pour qu'il diffuse un point d'accès avec le même ESSID que le réseau cible.

```
interface=wlan0
ssid=eduroam
channel=1
ignore_broadcast_ssid=0
eap_user_file=mi-net4104/hostapd-wpe.eap_user
ca_cert=mi-net4104/attack/ca.pem
server_cert=mi-net4104/attack/server.pem
private_key=mi-net4104/attack/server.pem
private_key_passwd=password
dh_file=mi-net4104/attack/dh
eap_fast_a_id=101112131415161718191a1b1c1d1e1f
eap_server=1
eap_fast_a_id_info=hostapd-wpe
eap_fast_prov=3
ieee8021x=1
pac_key_lifetime=604800
pac_key_refresh_time=86400
pac_opaque_encr_key=000102030405060708090a0b0c0d0e0f
wpa=2
wpa_key_mgmt=WPA-EAP
wpa_pairwise=TKIP CCMP
```

```bash
# Lance le point d'accès malveillant
sudo hostapd-wpe hostapd-wpe.conf -s
```


## MSCHAPv2

Supposons que nous souhaitons nous authentifier auprès d'un réseau Wi-Fi utilisant le protocole PEAP-MSCHAPv2. Pour obtenir les informations d'authentification de d'un utilisateur du réseau cible, diffuser un point d'accès Wi-Fi avec le même SSID que le réseau cible suffit, à condition que les clients tentent de s'y connecter en ne vérifiant pas le certificat CA du serveur d'authentification.

Dès lors, nous pouvons nous concentrer auprès de la méthode d'authentification (MSCHAPv2), et remarquer que l'empreinte MD4 du mot de passe de l'utilisateur est suffisante pour s'authentifier en ce qu'elle agit comme le mot de passe lui-même.

### Attaque par dictionnaire ?

Une première approche pour obtenir le mot de passe de l'utilisateur pourrait être de réaliser une attaque par dictionnaire sur l'empreinte MD4. Par exemple, on pourrait simplement calculer l'empreinte MD4 d'un grand nombre de mots de passe possibles, s'en servir pour calculer la réponse à un défi et comparer avec la réponse fournie par le client.

Le problème de cette approche est que la réussite de cette attaque n'est pas garantie, car le mot de passe de l'utilisateur peut être complexe et ne pas figurer dans le dictionnaire.

### Attaque par force brute ?

Dans la mesure où le mot de passe de l'utilisateur est susceptible d'avoir une longueur arbitraire et d'être composé de caractères d'un large ensemble, il pourrait être intéressant d'attaquer par la force brute l'empreinte MD4 du mot de passe elle-même. Mais cette empreinte est de 128 bits, soit $2^{128}$ possibilités, ce qui est bien trop grand pour être réalisable en un temps raisonnable.

### Diviser pour mieux régner

L'empreinte MD4 que nous essayons d'obtenir est utilisée comme la clef de trois chiffrements DES. Les clés DES étant de 7 octets, chaque opération DES utilise un morceau de 7 octets de l'empreinte MD4. Ainsi, au lieu de chercher l'empreinte MD4 elle-même, on pourrait chercher les trois clés DES qui permettent de la construire. Dès lors, plus besoin d'attaquer par la force brute une empreinte de 128 bits, mais trois clés de 56 bits chacune.

Comme il y a 3 opérations DES et que ces opérations sont indépendantes les unes des autres, on a une complexité globale de $3 \times 2^{56} = 2^{57.59}$, ce qui est bien mieux que $2^{128}$.

Mais il y a quelque chose qui ne va pas. En l'espèce, nous avons besoin de trois clefs DES de 56 bits pour un total de 168 bits, alors que l'empreinte MD4 n'en fait que 128 : il manque 40 bits. Lors de la réalisation de MSCHAPv2, Microsoft a palié à ce problème en ajoutant 40 bits nuls à l'empreinte MD4, rendant la troisième clef DES d'une longueur effective de 16 bits.

Ainsi, il n'y a que $2^{16}$ possibilités pour cette dernière clef DES, ce qui est tout à fait réalisable par la force brute. La complexité totale de l'attaque est donc de $2^{56} + 2^{56} + 2^{16} = 2^{57}$. C'est considérablement mieux.

```
    Clef 1          Clef 2          Clef 3
+-------------+  +-----------+   +-----------+
|?|?|?|?|?|?|?|  |?|?|?|?|?|?|   |?|?|0|0|0|0|
+-------------+  +-----------+   +-----------+
```