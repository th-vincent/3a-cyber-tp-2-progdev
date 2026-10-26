# 3IF1020

Ce dépôt contient les éléments pédagogiques du cours de troisième année 
**3IF1020 – Ateliers de programmation et outils de développement**
de la dominante **Informatique et Numérique** (campus de Paris-Saclay).

- Le dossier `cours` contient les exemples montrés en cours ;
- le dossier `td` contient les squelettes des fichiers pour les 4 TDs ;
- le dossier `tp` contient les squelettes des fichiers pour les 3 TPs.

## Sur GitLab

1. Faire une copie de ce projet dans votre espace GitLab (un *`Fork`*, bouton en haut à droite)

## Sur votre environnement, dans un Terminal :

2. Configurer votre identité Git (en utilisant bien sûr vos propres prénom et nom) :
```sh
git config --global user.name "Prénom Nom"
git config --global user.email "prenom.nom@student-cs.fr"
```

3. Créer une paire de clefs SSH :
```sh
ssh-keygen
```

4. Copier la clef publique (le contenu du fichier `~/.ssh/id_ed25519.pub`)

## Sur GitLab

5. Afficher la fenêtre de réglages de vos préférences (menu **Edit profile** accessible par l'icône de votre 
avatar), sélectionner l'onglet `SSK Keys` (dans `Access`), coller votre clef publique dans le champ `Key`, 
changer le titre éventuellement et cliquer sur le bouton `Add key`

## Sur votre environnement, dans un Terminal :

6. Dans votre répertoire de travail, faire une copie locale de votre dépôt (en remplaçant 
`<username>` par votre identifiant, l'URL **`Clone with SSH`** est accessible dans le menu **`Code`** en haut à droite sur GitLab) :
```sh
git clone git@gitlab-student.centralesupelec.fr:<username>/3if1020.git
```

7. Pour les TPs, au minimum à chaque fois qu'il est indiqué dans le sujet ***add, commit 
& push***, en étant dans le dossier correspondant au TP sur lequel vous travaillez : 
```sh
git add .
git commit -m "un commentaire approprié"
git push
```

