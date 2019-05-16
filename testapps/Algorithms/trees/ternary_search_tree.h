#ifndef TERNARY_SEARCH_TREE_H_
#define TERNARY_SEARCH_TREE_H_

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <iostream>

struct TernaryTree
{

struct Node
{
    char data;
    bool last = false;

    Node* left = nullptr;
    Node* right = nullptr;
    Node* eq = nullptr;
};

struct FindResult
{
    Node* lastNode = nullptr;
    bool found = false;
};

struct Result
{
    void AddWord(char* word)
    {
        if (count >= 1000)
        {
            return;
        }

        result[count] = (char*)malloc(strlen(word) + 1);
        strcpy(result[count++], word);
    }

    char* result[1000];
    unsigned count = 0;
};

FindResult find(char* word)
{
    return findRec(root, word);
}

void insert(char* word)
{
    if (strcmp(word, "acclimatising") == 0)
    {
        //asm("int $3");
    }
    insertRec(&root, word);
}

void traverse(Node* node, Result* res = nullptr)
{
    char buffer[1000];
    auto depth = 0;
    memset(buffer, 0, sizeof(buffer));
    traverseRec(node, buffer, depth, res);
}

private:
void traverseRec(Node* node, char buffer[1000], int depth, Result* res=nullptr)
{
    if (node)
    {
        traverseRec(node->left, buffer, depth, res);

        buffer[depth] = node->data;

        if (node->last)
        {
            buffer[depth+1] = '\0';

            if (res)
            {
                res->AddWord(buffer);
            }
            else
            {
                printf("word: %s\n", buffer);
            }
        }

        traverseRec(node->eq, buffer, depth + 1, res);

        traverseRec(node->right, buffer, depth, res);
    }
}

FindResult findRec(Node* root, char* word)
{
    if (!root)
    {
        return FindResult();
    }

    if (*word < root->data)
    {
        return findRec(root->left, word);
    }
    else if (*word > root->data)
    {
        return findRec(root->right, word);
    }
    else
    {
        if(*(word + 1))
        {
           return findRec(root->eq, word + 1);
        }
        else
        {
            FindResult result;
            if (root->last)
            {
                result.found = true;
            }

            result.lastNode = root->eq;
            return result;
        }
    }
}

void insertRec(Node** r, char* word)
{
    if (!*r)
    {
        createNode(r, word);
    }

    if ( *word < (*r)->data)
    {
        insertRec(&((*r)->left), word);
    }
    else if (*word > (*r)->data )
    {
        insertRec(&((*r)->right), word);
    }
    else
    {
        if (*(word+1))
        {
            insertRec(&((*r)->eq), word + 1);
        }
        else
        {
            (*r)->last = true;
        }
    }
}

void createNode(Node** node, char* word)
{
    *node = (Node*)malloc(sizeof(Node));
    (*node)->data = *word;

    (*node)->left = nullptr;
    (*node)->right = nullptr;
    (*node)->eq = nullptr;
}

public:
    Node* root = nullptr;

};


#endif /* TERNARY_SEARCH_TREE_H_ */
