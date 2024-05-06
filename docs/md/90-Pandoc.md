
# Annexes

## Génération de pdf avec pandoc

### Introduction

Nous avons été amenés à nous pencher sur un moyen de générer un rendu PDF de notre travail qui soit à la fois joli et facile à mettre en place, c'est à dire ne nécessitant pas de compétences particulières en LaTeX

Nous avons donc choisi d'utiliser `pandoc` qui est un outil de conversion de documents d'un format à un autre. Il est capable de convertir des fichiers markdown en pdf, en utilisant LaTeX pour la mise en page.

![Logo de pandoc](files/Pandoc.png)

Il est possible de spécifier un template LaTeX pour personnaliser le rendu du pdf. Nous avons choisi d'utiliser le template `eisvogel` qui est un template LaTeX spécialement conçu pour être utilisé avec `pandoc`. Il est très complet et permet de générer des documents de qualité.

![Eisvogel template](files/Eisvogel.png)

### Fonctionnement

Tout se passe dans le dossier `docs` qui contient les fichiers markdown à convertir et les fichiers de configuration.

Le dossier `docs` est organisé de la manière suivante :

```
docs
├── files
│   ├── Eisvogel.png
│   ├── Hashcat.png
│   ├── Hostapd-log.png
│   ├── MSCHAPv2_flow.png
│   ├── Pandoc.png
│   ├── eap.png
│   ├── esp32-S3.jpg
│   ├── meraki-mr42.jpg
│   ├── mitm.png
│   ├── raspberry-pi-1.jpg
│   ├── réseau_802_1x.png
│   ├── réseau_802_1x_evil.png
│   └── tsp.png
├── md
│   ├── 00-Introduction.md
│   ├── 01-PEAP.md
│   ├── 02-MSCHAPv2.md
│   ├── 03-Attaque.md
│   ├── 04-Réalisation_et_contraintes.md
│   ├── 90-Pandoc.md
│   ├── 99-Sources.md
│   └── HEADER.YAML
└── pandoc
    └── templates
        └── eisvogel.tex

5 directories, 22 files
```
- `files` contient les images utilisées dans les fichiers markdown
- `md` contient les fichiers markdown et le fichier `HEADER.YAML` qui contient les métadonnées du document
- `pandoc` contient les fichiers de configuration pour `pandoc`

Chaque modification dans le dossier `md` déclenche la génération du pdf et le résultat est push à la racine du dépôt grâce à un job CI.

Ce fonctionnement permet d'avoir toujours le pdf le plus à jour facilement accessible et est issu de nombreuses itérations pour arriver à un résultat satisfaisant.