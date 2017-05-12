#ifndef __CONFIG__
#define __CONFIG__

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0

typedef struct {
	char *path;
	char *position;
	char *brokers;
	char *topic;
} config;

extern void init_config(char *config_file, config *conf);

#endif
