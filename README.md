#GOUNKI

###COMPILATION
Compilation avec le Makefile via la commande:`make all`

###COMMANDE
`gounki`

###OPTIONS
`-b [niveau]` ou `-n [niveau]` : Choix du niveau du joueur blanc (`-b`) ou du joueur noir (`-n`). `h` pour un joueur humain, `r1` pour une IA aléatoire, `r2` pour une IA suivant une heuristique sur un seul coup, `r3` pour une IA suivant un algorithme minimax de profondeur par défaut 4.

`-c [fichier]` : Charge une configuration du plateau de jeu contenu dans le fichier en paramètre. Cette configuration servira de plateau de départ durant toute la partie. Peut être couplé avec `-t [fichier]`.

`-t [fichier]` : Joue une suite de coups contenu dans le fichier en paramètre. Peut être couplé avec `-c [fichier]`.