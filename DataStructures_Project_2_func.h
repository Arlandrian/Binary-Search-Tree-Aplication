
typedef struct {
    int id;
    char name[50];
    int *friends;
    struct USER *left;
    struct USER *right;
}USER;

#include "func.c"
#include <string.h>
#include <malloc.h>

char *removeUnderScore(char name[]);

USER *cSearchUser(USER *root,int id);

USER *searchUser(USER *root,int id);

USER *fCreateNewUser(int id,char name[],int *friends,int friendsCount);

USER *createNewUser(USER *root);

void insertNewUser(USER **root , USER *new);

USER *findMin(USER *root);

USER *deleteUser(USER *root,int id);

void contains(USER *root);

void friends(USER *root);

int returnSize(USER *root);

void printGreater(USER* root,int id);

void printInOrder(USER *root);

void readFromFile(USER **root,int *userCount);

int friendsSize(USER *root,int id);

void freeTheRoot(USER *root);

int printMenu();