#GOUNKI
_Auteur : [GitHub](github.com/cedeify/gounki)_

###COMPILATION
Compilation avec le Makefile via la commande:

`make all`

###COMMANDE
`gounki`

###OPTIONS
- `-b [niveau]` ou `-n [niveau]` : Choix du niveau du joueur blanc (`-b`) ou du joueur noir (`-n`). `h` pour un joueur humain, `r1` pour une IA aléatoire, `r2` pour une IA suivant une heuristique sur un seul coup, `r3` pour une IA suivant un algorithme minimax de profondeur par défaut 4. Si ces options ne sont pas utilisées, les joueurs seront pas défaut humain.

- `-c [fichier]` : Charge une configuration du plateau de jeu contenu dans le fichier en paramètre. Cette configuration servira de plateau de départ durant toute la partie. Peut être couplé avec `-t [fichier]`.

- `-t [fichier]` : Joue une suite de coups contenu dans le fichier en paramètre. Peut être couplé avec `-c [fichier]`.

- `-p [valeur]` : Changer la profondeur de l'algorithme minimax. Plus la valeur est importante, plus le temps de calcul sera long.

- `-d` : Désactive la proposition de sauvegarde l'historique de coups à la fin d'une partie. Utile pour automatiser une série de parties. La proposition de sauvegarde est automatiquement désactivée avec l'utilisation de `-s [fichier]`.

- `-s [fichier]` : Sauvegarde automatiquement à la fin d'une partie l'historique des coups dans le fichier en paramètre. Cette option désactive la proposition de sauvegarde de fin de partie.

###FORMAT FICHIER

####LISTE DE COUPS
- Mouvements : On notera le déplacement d’une pièce simplement par sa position initiale, suivie de sa position finale, séparées par un tiret. Exemple : b2-b3. Si le coup fait sortir la pièce (et donc gagner le joueur), on se contentera de noter la case jouée, suivie d’un dièse, comme g8#.

- Déploiements : La notation du déploiement d’une pièce se décompose en trois parties : la position initiale de la pièce, un caractère + ou * selon que le déploiement commence respectivement par les carrées ou par les ronds, les positions des pièces déployées séparées par un tiret (autant de positions que la pièce composée possédait de sous-pièces).

####CONFIGURATION DU PLATEAU
Le format est composé d’une suite de 64 pièces séparées par un retour à la ligne (caractère '\n'). L’ordre des pièces est donné en parcourant le tableau ligne par ligne, par numéros et lettres croissants, c’est-à-dire qu’on donnera les cases dans cet ordre : a1, b1, c1, d1, e1, f1, g1, h1, a2, b2, etc. Les pièces sont représentées par un code à deux caractères. Le premier caractère peut-être B, N ou V, selon respectivement que la pièce est blanche ou noire ou que la case est vide. Le deuxième caractère est un chiffre codant le type de la pièce, suivant le
codage suivant:
- 0 : vide
- 1 : carré
- 2 : rond
- 3 : carré double
- 4 : rond double
- 5 : carré triple
- 6 : rond triple
- 7 : carré rond
- 8 : carré carré rond
- 9 : carré rond rond

###OPTION EN JEU
Plusieurs options sont disponibles pendant une partie, il suffit de taper la lettre correspondante à la place de jouer un coup :
- h : affiche la liste des options.
- v : active/désactive l'affichage de la valeur de l'heuristique du joueur courant.
- a : active/désactive l'affichage de la légende des valeurs des pièces.
- c : affiche l'historique des coups de la partie.
- r : annule le dernier coup joué. Si un joueur humain joue contre une IA, celà annulera les deux derniers coups.
- q : quitte le programme.
- s : sauvegarde l'historique des coups de la partie dans un fichier.
- p : sauvegarde de la configuration du plateau de jeu dans un fichier.
