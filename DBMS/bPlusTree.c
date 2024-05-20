#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORDER 4 // Order of B+ tree

typedef struct Node {
    char keys[ORDER - 1][20];
    char meanings[ORDER - 1][50];
    struct Node *pointers[ORDER];
    int num_keys;
    struct Node *next;
} Node;

Node *root = NULL;

Node *create_node() {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->num_keys = 0;
    new_node->next = NULL;
    for (int i = 0; i < ORDER; i++)
        new_node->pointers[i] = NULL;
    return new_node;
}

void split_child(Node *parent, int index, Node *child) {
    Node *new_node = create_node();
    new_node->num_keys = ORDER / 2 - 1;
    for (int i = 0; i < ORDER / 2 - 1; i++) {
        strcpy(new_node->keys[i], child->keys[i + ORDER / 2]);
        strcpy(new_node->meanings[i], child->meanings[i + ORDER / 2]);
    }
    for (int i = 0; i < ORDER / 2; i++)
        new_node->pointers[i] = child->pointers[i + ORDER / 2];
    child->num_keys = ORDER / 2 - 1;
    parent->pointers[index] = child;
    parent->pointers[index + 1] = new_node;
    strcpy(parent->keys[index], child->keys[ORDER / 2 - 1]);
    strcpy(parent->meanings[index], child->meanings[ORDER / 2 - 1]);
    parent->num_keys++;
}

void insert_nonfull(Node *node, char *key, char *meaning) {
    int i = node->num_keys - 1;
    if (node->pointers[0] == NULL) {
        while (i >= 0 && strcmp(key, node->keys[i]) < 0) {
            strcpy(node->keys[i + 1], node->keys[i]);
            strcpy(node->meanings[i + 1], node->meanings[i]);
            i--;
        }
        strcpy(node->keys[i + 1], key);
        strcpy(node->meanings[i + 1], meaning);
        node->num_keys++;
    } else {
        while (i >= 0 && strcmp(key, node->keys[i]) < 0)
            i--;
        i++;
        if (node->pointers[i]->num_keys == ORDER - 1) {
            split_child(node, i, node->pointers[i]);
            if (strcmp(key, node->keys[i]) > 0)
                i++;
        }
        insert_nonfull(node->pointers[i], key, meaning);
    }
}


void insert(char *key, char *meaning) {
    if (root == NULL) {
        root = create_node();
        strcpy(root->keys[0], key);
        strcpy(root->meanings[0], meaning);
        root->num_keys = 1;
    } else {
        if (root->num_keys == ORDER - 1) {
            Node *new_root = create_node();
            new_root->pointers[0] = root;
            split_child(new_root, 0, root);
            root = new_root;
        }
        insert_nonfull(root, key, meaning);
    }
}


void search(Node *node, char *key) {
    int i = 0;
    while (i < node->num_keys && strcmp(key, node->keys[i]) > 0)
        i++;
    if (i < node->num_keys && strcmp(key, node->keys[i]) == 0) {
        printf("Meaning of \"%s\": %s\n", key, node->meanings[i]);
        return;
    }
    if (node->pointers[0] != NULL)
        search(node->pointers[i], key);
    else
        printf("Word \"%s\" not found.\n", key);
}

void free_tree(Node *node) {
    if (node != NULL) {
        for (int i = 0; i < node->num_keys + 1; i++)
            free_tree(node->pointers[i]);
        free(node);
    }
}

int main() {
   
    FILE *fp = fopen("dictionary.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    
    char word[50];
    char meaning[200];
    // separated by space
    while (fscanf(fp, "%s %[^\n]", word, meaning) != EOF) {
        insert(word, meaning);

    }
    // seprated by newline
    // while (fscanf(fp, "%[^\n]\n%[^\n]\n", word, meaning) != EOF) {
    //     insert(word, meaning);
    // }
    
    fclose(fp);

    char search_word[50];
    printf("Enter a word to search in the dictionary: ");
    scanf("%s", search_word);
    search(root, search_word);

    free_tree(root);
    return 0;
}
