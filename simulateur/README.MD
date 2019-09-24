Simulate data from recording

`./simulateur –l -p <journal> -T<tmin><tdef>`

Où journal est un des fichiers joints (ASCII).

Afin de vous éviter une attente trop longue lors des arrêts de la cellule qui ont été enregistrés, tout délai supérieur à tmax (secondes) est remplacé par tdef, -T15 :5 étant l’option par défaut.
Le simulateur lance le programme « ./collecteur » qui doit se trouver dans le même répertoire.
