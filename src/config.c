#include <string.h>

#include "config.h"
#include "ini.h"

static int handler(void* conf, const char* section, const char* name,
		const char* value) {

	config* cnf = (config*) conf;

	if (MATCH("file", "path")) {

		cnf->path = strdup(value);
	} else if (MATCH("file", "position")) {

		cnf->position = strdup(value);
	} else if (MATCH("kafka", "brokers")) {

		cnf->brokers = strdup(value);
	} else if (MATCH("kafka", "topic")) {

		cnf->topic = strdup(value);
	} else {

		return 0;
	}

	return 1;
}

void init_config(char *config_file, config *conf){

	if (ini_parse(config_file, handler, conf) < 0) {
		printf("Can't load 'config.ini'\n");
	}
}
