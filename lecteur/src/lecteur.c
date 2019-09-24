/*****************************************************************************#
#   ___  ____  __    ____  __   ____  __     __   ____    lecteur.c           #
#  / __)(  __)(  )  (  __)/ _\ (  _ \(  )   / _\ (  _ \                       #
# ( (_ \ ) _)  )(    ) _)/    \ ) _ (/ (_/\/    \ ) _ (   Created by romain   #
#  \___/(__)  (__)  (__) \_/\_/(____/\____/\_/\_/(____/   02/07/2019 11:34:42 #
#                                                                             #
#           Contact: romain.leduc@gfi.fr                  Updated by yohan    #
#                                                         2/07/2019 16:39:42  #
#*****************************************************************************/

#include "../inc/lecteur.h"

void	*lire(void *queueName)
{
    mqd_t		mq;
    const char	*queue;
    char		str[SZ_MSG + 1];
    int			n;

    queue = (const char *)queueName;
    mq = __mq_open(queue);
    while ((n = mq_receive(mq, str, sizeof(str) - 1, NULL)) > 0)
    {
        str[n] = '\0';
        insertMongo(str, queueName);
    }
    return (NULL);
}

void	stopRunningAndCloseMq()
{
	pthread_cancel(thr_cell);
    pthread_cancel(thr_qmc[0]);
    pthread_cancel(thr_qmc[1]);
    end();
}

int		main(void)
{
    char				*queueName;
    struct sigaction	act;

    count = 0;
    act.sa_handler = stopRunningAndCloseMq;
    sigaction(SIGINT, &act, NULL);
    initMongoDb();
    queueName = "/CELL";
    if (pthread_create(&thr_cell, NULL, lire, (void *)queueName) < 0)
        fprintf(stderr, "lecteur:cannot create thread for Cell ...\n");
    queueName = "/IMM";
    if (pthread_create(&thr_qmc[0], NULL, lire, (void *)queueName) < 0)
        fprintf(stderr, "lecteur:cannot create thread for Imm ...\n");
    queueName = "/MSS";
    if (pthread_create(&thr_qmc[1], NULL, lire, (void *)queueName) < 0)
        fprintf(stderr, "lecteur:cannot create thread for Mss ...\n");
    pthread_join(thr_cell, NULL);
    pthread_join(thr_qmc[0], NULL);
    pthread_join(thr_qmc[1], NULL);
}
