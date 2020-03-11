#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void main() {
	printf("bip");
	int s = socket(PF_INET6, SOCK_STREAM, 0);
	printf("%i\n", s);
	if (s>-1) {
		struct sockaddr_in6 sin6;
		memset(&sin6, 0, sizeof(sin6));
		sin6.sin6_family = PF_INET6;
		sin6.sin6_port = htons(8080);
		int rc = bind(s, (struct sockaddr*)&sin6, sizeof(sin6));
		printf("%i\n", rc);
		if(rc>-1) {
			rc = listen(s, 1024);
			printf("%i\n", rc);
			if(rc>-1) {
				while(rc > -1){
					int s2 = accept(s, NULL, NULL);
					if(s2>-1) {
						printf("réussi\n");
						char buffer [100];
						read(s2,buffer,100);//write(s2,"test\n",5);
						printf("%s\n",buffer);
						if(memmem("test \r\n\r\n",9,"\r\n\r\n",strlen("\r\n\r\n")+1) == NULL){
							printf("pd");
						} else {
							printf("xd");
						}
						if(memmem(buffer,100,"\r\n\r\n",4) != NULL){
							printf("HERE");
						}
						close(s2);
					}
				}
				close(s);
			}
			else printf("listen échoué\n");
		}
		else printf("bind échoué\n");
	}
	else printf("socket échoué\n");
}
