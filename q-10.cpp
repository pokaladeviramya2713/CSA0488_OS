#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MAX_MSG_SIZE 100

// Define a structure for the message
struct message {
    long mtype;
    char mtext[MAX_MSG_SIZE];
};

int main() {
    key_t key;
    int msgid;
    struct message msg_buf;

    // Generate a unique key for the message queue
    key = ftok(".", 'a');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        printf("Child process is waiting for a message...\n");

        // Receive a message from the queue
        if (msgrcv(msgid, &msg_buf, MAX_MSG_SIZE, 1, 0) == -1) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }

        printf("Child process received message: %s\n", msg_buf.mtext);
    } else {
        // Parent process
        printf("Parent process is sending a message...\n");

        // Prepare the message
        strcpy(msg_buf.mtext, "Hello from the parent process!");
        msg_buf.mtype = 1; // Message type

        // Send the message to the queue
        if (msgsnd(msgid, &msg_buf, strlen(msg_buf.mtext) + 1, 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }

        printf("Parent process sent message successfully.\n");
    }

    // Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}

