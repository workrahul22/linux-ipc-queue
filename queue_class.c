#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#define MAX 10

struct mesg_buffer {
	long mesg_type;
	char mesg_text[100];
};

int create_queue(char *queue_name) {
	key_t queue_key = ftok(queue_name, 65);
	int message_queue_identifier = msgget(queue_key, 0666 | IPC_CREAT);
	return message_queue_identifier;
}

int send_message(int message_queue_identifier, const char *message) {
	struct mesg_buffer message_obj;
	message_obj.mesg_type = 1;
	strncpy(message_obj.mesg_text, message, sizeof(message_obj.mesg_text) - 1);
	message_obj.mesg_text[sizeof(message_obj.mesg_text) - 1] = '\0';
	msgsnd(message_queue_identifier, &message_obj, sizeof(message_obj), 0);
	printf("Data send is : %s \n", message);
	return 0;
}

char *receive_message(int message_queue_identifier, char *buffer, size_t buffer_size) {
	struct mesg_buffer message_received;
	if (msgrcv(message_queue_identifier, &message_received, sizeof(message_received), 1, 0) == -1) {
        fprintf(stderr, "msgrcv failed: %d\n", errno);
		return -1;
    }
	strncpy(buffer, message_received.mesg_text, buffer_size - 1);
	buffer[buffer_size - 1] = '\0';
	printf("Buffer : %s", buffer);
	return 0;
}

int destroy_queue(int message_queue_identifier) {
	msgctl(message_queue_identifier, IPC_RMID, NULL);
	printf("Message queue with id => %d destroyed\n", message_queue_identifier);
	return 0;
}

//int main() {
//	int identifier = create_queue("rahul");
//	destroy_queue(identifier);
//	return 0;
//}
