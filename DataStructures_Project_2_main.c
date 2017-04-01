#include <stdio.h>
#include <stdlib.h>
#include "func.h"

int main() {
    system("color 06");

    USER *root=NULL;
    USER *new;
    int choice,id,userCount=0;
    do{
        id=0;
        choice = printMenu();
        switch (choice){
            case 1://InsertUser+//first creating a User then inserting to the tree
                new = createNewUser(root);
                insertNewUser(&root,new);
                printf("\n----------------\nKullanici basarili bir sekilde eklendi.\n");
                break;

            case 2://Delete User+

                if(root == NULL)
                    printf("Kullanici bulunamadi.\n");
                else{
                    printf("Delete User:\n");
                    printf("\n---------------------\n");
                    printInOrder(root);
                    printf("\n-----------------\nID Girin:\n");
                    scanf("%d",&id);
                    if(searchUser(root,id)==NULL)
                        printf("Bu id de bir kullanici bulunamadi.\n");
                    else{
                        deleteUser(root,id);
                        printf("\n-----------------------------------\nKulllanici basarili bir sekilde silindi.\n");
                    }
                }

                break;

            case 3://Contains+

                if(root == NULL)
                    printf("Kullanici bulunamadi.\n");
                else
                    contains(root);

                break;

            case 4://Friends+

                if(root == NULL)
                    printf("Kullanici bulunamadi.\n");
                else
                    friends(root);

                break;

            case 5://Size+
                if(root == NULL)
                    printf("Kullanici bulunamadi.\n");
                else
                    printf("Agacin eleman sayisi: %d\n",returnSize(root));

                break;

            case 6://Print Next+
                if(root == NULL)
                    printf("Kullanici bulunamadi.\n");
                else{
                    printf("\n-----------\nPrint Next:\n");
                    printf("ID Girin:\n");
                    scanf("%d",&id);
                    printInOrder(searchUser(root,id));
                }
                break;

            case 7://Print Greater+
                if(root == NULL)
                    printf("Kullanici bulunamadi.\n");
                else{
                    printf("Print Greater:\n");
                    printf("\n-------------\nID Girin:\n");
                    scanf("%d",&id);
                    printGreater(root,id);
                }
                break;

            case 8://Print In Order+
                if(root == NULL)
                    printf("Kullanici bulunamadi.\n");
                else {
                    printf("In order:\n");
                    printInOrder(root);
                }
                break;

            case 9:
                readFromFile(&root,&userCount);
                break;
            case 175:
                printf("Friends Size\n");
                printf("ID Girin:\n");
                scanf("%d",&id);
                printf("\n---------------\n%d",friendsSize(root,id)-1);
                break;
            default:
                printf("Lutfen tekrar secim yapiniz.");
                break;

        }
        system("pause");
        system("cls");
    }while(choice != 0);
    //freeing the tree after process
    freeTheRoot(root);
    return 0;
}