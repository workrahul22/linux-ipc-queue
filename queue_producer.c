#include <stdio.h>
#include "queue_class.c"

int main(){
	int message_queue_identifier = create_queue("rahul");
	char message[100];
	
	printf("Message Queue Identefier => %d\n", message_queue_identifier);
	
	while(1) {
		printf("Write Data : ");
		fgets(message,MAX,stdin);
		send_message(message_queue_identifier, message);
	}

	return 0;
}
