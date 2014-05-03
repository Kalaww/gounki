#GOUNKI

###COMPILATION
Compilation avec le Makefile via la commande:

`make all`

###COMMANDE
`gounki`

###OPTIONS
`-b [niveau]` ou `-n [niveau]` : Choix du niveau du joueur blanc (`-b`) ou du joueur noir (`-n`). `h` pour un joueur humain, `r1` pour une IA aléatoire, `r2` pour une IA suivant une heuristique sur un seul coup, `r3` pour une IA suivant un algorithme minimax de profondeur par défaut 4. Si ces options ne sont pas utilisées, les joueurs seront pas défaut humain.

`-c [fichier]` : Charge une configuration du plateau de jeu contenu dans le fichier en paramètre. Cette configuration servira de plateau de départ durant toute la partie. Peut être couplé avec `-t [fichier]`.

`-t [fichier]` : Joue une suite de coups contenu dans le fichier en paramètre. Peut être couplé avec `-c [fichier]`.

###FORMAT FICHIER

####LISTE DE COUPS
- Mouvements : On notera le déplacement d’une pièce simplement par sa position initiale, suivie de sa position finale, séparées par un tiret. Exemple : b2-b3. Si le coup fait sortir la pièce (et donc gagner le joueur), on se contentera de noter la case jouée, suivie d’un dièse, comme g8#.

- Déploiements : La notation du déploiement d’une pièce se décompose en trois parties : la position initiale de la pièce, un caractère + ou * selon que le déploiement commence respectivement par les carrées ou par les ronds, les positions des pièces déployées séparées par un tiret (autant de positions que la pièce composée possédait de sous-pièces).