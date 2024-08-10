#include "queue_class.c"

int main() {
	int message_queue_identifier = create_queue("rahul");
	
	printf("Message Queue Identifier => %d\n", message_queue_identifier);
	while(1) {
		char message[100];
		int a = receive_message(message_queue_identifier, message, sizeof(message));		   
		printf("abcd : %d", a);
		if(a == -1) {
            perror("Failed to receive message");
            continue;
        }
		printf("Data Received : %s \n", message);
	}
	return 0;
}
