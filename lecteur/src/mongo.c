/*****************************************************************************#
#   ___  ____  __    ____  __   ____  __     __   ____    mongo.c             #
#  / __)(  __)(  )  (  __)/ _\ (  _ \(  )   / _\ (  _ \                       #
# ( (_ \ ) _)  )(    ) _)/    \ ) _ (/ (_/\/    \ ) _ (   Created by romain   #
#  \___/(__)  (__)  (__) \_/\_/(____/\____/\_/\_/(____/   02/07/2019 11:34:42 #
#                                                                             #
#           Contact: romain.leduc@gfi.fr                  Updated by yohan    #
#                                                         18/07/2019 16:39:42 #
#*****************************************************************************/

#include "../inc/lecteur.h"

const char *uri_string = "mongodb://localhost:27017/staubliK_db?replicaSet=rs";
const char *baseMongo = "staubliK_db";

mongoc_collection_t *collection;
bson_t *insert;
bson_error_t error;
mongoc_uri_t *uri;
mongoc_client_t *client;

int initMongoDb()
{
    mongoc_init();
    uri = mongoc_uri_new_with_error(uri_string, &error);
    if (!uri)
    {
        fprintf(stderr, "lecteur:mongoc failed to parse URI:<%s> err:<%s>\n",
                uri_string, error.message);
        return (EXIT_FAILURE);
    }
    if (!(client = mongoc_client_new_from_uri(uri)))
        return (EXIT_FAILURE);
    return (0);
}

void insertMongo(char *inputStr, char *queueName)
{
    static pthread_mutex_t  mutex;
    char                    *collectionName;
    int                      lock;

    fprintf(stdout, "total=%d + %s received : <%s>\n", ++count, queueName, inputStr);
    if ((lock = pthread_mutex_lock(&mutex)) != 0)
        fprintf(stderr, "lecteur:pthread_mutex_lock err=%d\n", lock);
    collectionName = (!strcmp(queueName, "/CELL")) ? "celling" : NULL;
    collectionName = (!strcmp(queueName, "/IMM")) ? "imm" : collectionName;
    collectionName = (!strcmp(queueName, "/MSS")) ? "mss" : collectionName;
    collection = mongoc_client_get_collection(client, baseMongo, collectionName);
    insert = bson_new_from_json((unsigned char *)inputStr, -1, &error);
    if (!mongoc_collection_insert_one(collection, insert, NULL, NULL, &error))
        fprintf(stderr, "lecteur:mongoc collection insert err:<%s>\n", error.message);
    pthread_mutex_unlock(&mutex);
}

void end()
{
    bson_destroy(insert);
    // Release our handles and clean up libmongoc
    mongoc_collection_destroy(collection);
    mongoc_uri_destroy(uri);
    mongoc_client_destroy(client);
    mongoc_cleanup();
    fprintf(stdout, "Connection mongo END properly\n");
}