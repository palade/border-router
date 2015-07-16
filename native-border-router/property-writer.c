#include "net/ip/uip.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>

#define USER_HOME "HOME" 
#define GATEWAY_PROPERTIES "/gateway.properties"

char* getHomeDir() {
  	char *homedir = getenv(USER_HOME);
 
        if (homedir == NULL) {
		uid_t uid = getuid();
		struct passwd *pw = getpwuid(uid);
	 
		if (pw == NULL) {
		        printf("Failed\n");
		        exit(EXIT_FAILURE);
		}
        	homedir = pw->pw_dir;
	}
	return homedir;
}

char* concat(char *s1, char *s2) {
	char *result = malloc(strlen(s1)+strlen(s2)+1);
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}

void printToFile(char *property, char *file) {
	if (fopen(file, "w") == NULL) {
	    printf("Error opening file!\n");
	    exit(1);
	} else {
	    remove(file);	
	}
	FILE *f = fopen(file, "w");
	fprintf(f,"%s", property);
	fclose(f);
}


char* uint8_tToString(uint8_t *a) {
  char* buffer2;
  int i;

  buffer2 = malloc(9);
  if (!buffer2)
    return NULL;

  buffer2[8] = 0;
  for (i = 0; i <= 7; i++)
    buffer2[7 - i] = (((*a) >> i) & (0x01)) + '0';

  puts(buffer2);

  return buffer2;
}

char* formatProperty(uint8_t *u8) {
	uint16_t a;
	unsigned int i;
	int f;
        char *property = malloc(100);

	for(i = 0, f = 0; i < sizeof(uip_ipaddr_t); i += 2) {
		a = (u8[i] << 8) + u8[i + 1];
		if(a == 0 && f >= 0) {
			if(f++ == 0) {
				property = concat(property, "::");
	      		}
	    	} else {
	      		if(f > 0) {
				f = -1;
	      		} else if(i > 0) {
				property = concat(property, ":");
	      		}
			char* temp = malloc(9);	
                  	sprintf(temp, "%x", a);
			property = concat(property, temp);
	    	}
	}
	return property;
}

void writeProperty1(char *property) {
	char *homeDir = getHomeDir(); 
        char *file = concat(homeDir, GATEWAY_PROPERTIES);  
        printToFile(property, file);  
}

void writeProperty2(uint8_t *a) {
	char *property = formatProperty(a);
	char *homeDir = getHomeDir(); 
        char *file = concat(homeDir, GATEWAY_PROPERTIES); 
        property = concat("address=", property); 
        printToFile(property, file);  
}

/*
int main(int argc, char **argv) {
        writeProperty("address=192.168.1.1");  
}*/
