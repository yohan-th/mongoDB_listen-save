#!/bin/sh
#
# Le binaire "lecteur" s'éxecute en arrière et devient un job attaché a la
# session du terminal.
# Le binaire "simulateur.back" se limite à l'envoi de 500 données. Il est placé dans
# une boucle.
# Le fichier err.txt contient les erreurs des 2 binaires.
# Le fichier log.txt contient les éléments reçu par "lecteur" avant de les
# envoyer dans base de donné mongo.

#!/bin/bash

make re;
./lecteur/./lecteur 2> err.txt 1> log.txt &
if false
then
    while true;
    do
        # simulateur ancienne version
        ./simulateur.back/.simulateur<./simulateur.back/simu 2>>log
    done
else
    while true;
    do
        # simulateur nouvelle version
        ./simulateur.new/simulateur -l < ./simulateur.new/simu_long >>log
    done
fi
