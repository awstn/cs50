#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Make node struct. The elements of the Linked List
//hellooo 
typedef struct node
{
    string phrase;
    struct node *next;
}
node;

#define LIST_SIZE 4

void add(node **head);
void unload(node *head);
bool search(string input, node *n);
void visualizer(node *head);


int main(void)
{
    node *head = NULL;
    // Why use the address for double pointer?
    add(&head);

    string promptUser = get_string("\n\nWhat would you like to search for?\n\n");
    if (!search(promptUser, head))
    {
        printf("Not Found!\n");
    }
    else
    {
        printf("Found!\n");

    }

    unload(head);
}

void add(node **head)
{
    string input = "void";

    while (strcmp(input, "stop") != 0)
    {
        input = get_string("Phrase: ");
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("Error allocating memory for new node.");
            return;
        }
        new_node->phrase = input;
        new_node->next = *head;
        *head = new_node;

        visualizer(*head);
    }
}

bool search(string input, node *n)
{
    node *ptr = n;

    while (ptr != NULL)
    {
        if (strcmp(input,ptr->phrase) == 0)
            return true;

        ptr = ptr->next;
    }
    return false;
}

void unload(node *head)
{
    if (head == NULL)
        return;

    unload(head->next);
    free(head);
}

void visualizer(node *head)
{
    printf("\n---- LINKED LIST VISUALIZER ----\n\n");
    while (head != NULL)
    {
        printf("Node Address: %p\nNode Phrase: %s\nNode Next: %p\n\n", head, head->phrase, head->next);
        head = head->next;
    }
    printf("\n---- LINKED LIST VISUALIZER ----\n\n");

}

