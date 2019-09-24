/*****************************************************************************#
#   ___  ____  __    ____  __   ____  __     __   ____    main.h              #
#  / __)(  __)(  )  (  __)/ _\ (  _ \(  )   / _\ (  _ \                       #
# ( (_ \ ) _)  )(    ) _)/    \ ) _ (/ (_/\/    \ ) _ (   Created by romain   #
#  \___/(__)  (__)  (__) \_/\_/(____/\____/\_/\_/(____/   02/07/2019 11:34:42 #
#                                                                             #
#           Contact: romain.leduc@gfi.fr                  Updated by yohan    #
#                                                         18/07/2019 16:39:42 #
#*****************************************************************************/

#ifndef MAIN_H_
# define MAIN_H_
# define SZ_MSG 512

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <mqueue.h>
# include <string.h>
# include <mongoc.h>
# include <signal.h>
# include <stdbool.h>
# include <pthread.h>
# include <errno.h>
# include <sys/socket.h>
# include <netdb.h>
# include <regex.h>

pthread_t	thr_cell;
pthread_t	thr_qmc[2];

int     	count;

void    	stopRunningAndCloseMq();
int     	initMongoDb();
mqd_t   	__mq_open(const char *queue_name);
void		insertMongo(char *inputStr, char *queueName);
void		end();

#endif
