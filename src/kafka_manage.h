#ifndef __KAFKA_MANAGE__
#define __KAFKA_MANAGE__

#include "librdkafka/rdkafka.h"
#define ERROR 0
#define SUCCESS 1

typedef struct handle {
	rd_kafka_t *rk;        /* Producer instance handle */
	rd_kafka_topic_t *rkt; /* Topic object */
	rd_kafka_conf_t *conf; /* Temporary configuration object */
	char errstr[512];      /* librdkafka API error reporting buffer */
	const char *brokers;   /* Argument: broker list */
	const char *topic;
} kafka_handle;

extern int kafka_init(kafka_handle *handle);
extern void kafka_produce(kafka_handle *handle, char msg[512]);
extern void kafka_destroy(kafka_handle *handle);

#endif
