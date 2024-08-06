#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_INPUT_LENGTH 100

typedef struct Message {
    char *sender;
    char *receiver;
    char *content;
    time_t timestamp;
    struct Message *next;
} Message;

Message *createMessage(char *sender, char *receiver, char *content) {
    Message *newMessage = (Message *)malloc(sizeof(Message));
    if (!newMessage) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newMessage->sender = strdup(sender);
    newMessage->receiver = strdup(receiver);
    newMessage->content = strdup(content);
    newMessage->timestamp = time(NULL);
    newMessage->next = NULL;
    return newMessage;
}

void sendMessage(Message **head, char *sender, char *receiver, char *content) {
    Message *newMessage = createMessage(sender, receiver, content);
    if (*head == NULL) {
        *head = newMessage;
    } else {
        Message *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newMessage;
    }
}

void receiveMessages(Message *head, char *receiver) {
    Message *current = head;
    int count = 0;

    printf("Messages for %s:\n", receiver);
    while (current != NULL) {
        if (strcmp(current->receiver, receiver) == 0) {
            printf("Sender: %s\n", current->sender);
            printf("Content: %s\n", current->content);
            printf("Timestamp: %s", ctime(&(current->timestamp)));
            printf("--------------------\n");
            count++;
        }
        current = current->next;
    }

    if (count == 0) {
        printf("No messages found for %s\n", receiver);
    }
}

void freeMessages(Message *head) {
    Message *current = head;
    while (current != NULL) {
        Message *temp = current;
        current = current->next;
        free(temp->sender);
        free(temp->receiver);
        free(temp->content);
        free(temp);
    }
}

int main() {
    Message *messageBox = NULL;
    char sender[MAX_INPUT_LENGTH];
    char receiver[MAX_INPUT_LENGTH];
    char content[MAX_INPUT_LENGTH];

    while (1) {
        printf("1. Send message\n 2. Receive messages\n 3. Exit\n");
        int choice;
        scanf("%d", &choice);
        getchar(); // Consume the newline character left in the buffer

        switch (choice) {
        case 1:
            printf("Enter sender: ");
            fgets(sender, sizeof(sender), stdin);
            sender[strcspn(sender, "\n")] = '\0'; // Remove newline character
            printf("Enter receiver: ");
            fgets(receiver, sizeof(receiver), stdin);
            receiver[strcspn(receiver, "\n")] = '\0'; // Remove newline character
            printf("Enter message content: ");
            fgets(content, sizeof(content), stdin);
            content[strcspn(content, "\n")] = '\0'; // Remove newline character
            sendMessage(&messageBox, sender, receiver, content);
            break;
        case 2:
            printf("Enter receiver: ");
            fgets(receiver, sizeof(receiver), stdin);
            receiver[strcspn(receiver, "\n")] = '\0'; // Remove newline character
            receiveMessages(messageBox, receiver);
            break;
        case 3:
            freeMessages(messageBox);
            return 0;
        default:
            printf("Invalid choice\n");
        }
    }
}
