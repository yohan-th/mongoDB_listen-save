/*****************************************************************************#
#   ___  ____  __    ____  __   ____  __     __   ____    mq.c                #
#  / __)(  __)(  )  (  __)/ _\ (  _ \(  )   / _\ (  _ \                       #
# ( (_ \ ) _)  )(    ) _)/    \ ) _ (/ (_/\/    \ ) _ (   Created by romain   #
#  \___/(__)  (__)  (__) \_/\_/(____/\____/\_/\_/(____/   02/07/2019 11:34:42 #
#                                                                             #
#           Contact: romain.leduc@gfi.fr                  Updated by yohan    #
#                                                         18/07/2019 16:39:42 #
#*****************************************************************************/

#include "../inc/lecteur.h"

mqd_t __mq_open(const char *queue_name)
{
    mqd_t mq;

    mq = mq_open(queue_name, O_RDONLY);
    if (mq == -1)
    {
        fprintf(stderr, "lecteur:mqopen failed for %s\n", queue_name);
        pthread_exit (NULL);
    }

    return (mq);
}
