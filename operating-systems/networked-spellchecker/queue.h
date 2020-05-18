// Sean Droke
// Temple University -- CIS 3207
// Project 3

#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue {
    int size;
    struct queue_node* head;
} queue;

queue* create_queue();
int print_queue(queue* root);
int push_queue(queue* root, char* string);
char* pop_queue(queue* root);

#endif