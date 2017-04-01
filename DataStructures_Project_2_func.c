/**
 * returns given name without underscore
 * @param name input string
 * @return
 */
char *removeUnderScore(char name[]){
    int i=0;
    char *temp = (char*)malloc(50);
    strcpy(temp,name);
    while(temp[i]){
        if(temp[i]=='_')
            temp[i]=' ';
        i++;
    }
    return temp;
}
/**
 * //search for user that given id , prints comparisans and if user exist returns the user
 * @param root
 * @param id
 * @return
 */
USER *cSearchUser(USER *root,int id){//if return null does not contain node

    if(!(root))
        return NULL;
    printf("%d ile %d karsilastirildi\n",id,root->id);
    if( id == (root)->id )
        return (root);

    else if( id < (root)->id ){
        printf("%d ile %d karsilastirildi\n",id,root->id);
        return cSearchUser(root->left ,id);//error
    }
    else
        return cSearchUser(root->right, id);

}
/**
 * searches tree and if finds returns it
 * @param root
 * @param id
 * @return
 */
USER *searchUser(USER *root,int id){//if return null does not contain node

    if(!(root))
        return NULL;

    if( id == (root)->id )
        return (root);

    else if( id < (root)->id )
        return searchUser((USER *) root->left ,id);

    else
        return searchUser((USER *) root->right, id);

}
/**
 * creates user for the file proccesses
 * @param id
 * @param name
 * @param friends
 * @param friendsCount
 * @return
 */
USER *fCreateNewUser(int id,char name[],int *friends,int friendsCount){

    int i;

    USER *user = (USER*) malloc(sizeof(USER));
    user->right = NULL;
    user->left = NULL;
    user->id=id;
    strcpy(user->name,name);
    user->friends = friends ;
    return user;
}
/**
 * creates user for insertion
 * @param root
 * @return
 */
USER *createNewUser(USER *root){
    int i,x;
    USER *user = (USER*) malloc(sizeof(USER));
    user->right = user->left = NULL;

    printf("ID: \n");
    scanf("%d", &user->id);

    printf("Ad Soyad: \n");
    scanf("%s",user->name);

    printf("Arkadas Sayisi: \n");
    scanf("%d",&x);
    user->friends = (int*)malloc((x+1)*sizeof(int));
    for(i = 0 ; i < x ; i++){
        printf("%d. Arkadas ID: \n",i+1);
        scanf("%d",&(user->friends[i]));
    }
    user->friends[x]=(int)NULL;

    return user;
}
/**
 * inserts the user that created before
 * @param root
 * @param new
 */
void insertNewUser(USER **root , USER *new){

    USER **temp = NULL;

    if( !(*root) ){
        (*root)=new;
        return;
    }
    (temp) = (root);
    while((*temp) != NULL){
        if( new->id < (*temp)->id )
            (temp) = &((*temp)->left);
        else
            (temp) = &((*temp)->right);
    }
    (*temp) = new;

}
/**
 * finds the user with the minimum id number and returns
 * @param root
 * @return
 */
USER *findMin(USER *root){
    USER *current = root;

    while(current->left!=NULL)
        current = current->left;

    return current;
}
/**
 * deletes user with given id from tree
 * @param root
 * @param id
 * @return
 */
USER *deleteUser(USER *root,int id){
    if(root == NULL)
        return root;

    if(id < root->id)
        root->left = deleteUser(root->left,id);

    else if(id > root->id)
        root->right = deleteUser(root->right,id);

    else{
        if(root->left == NULL){
            USER *temp = root->right;
            free(root);
            return temp;
        }
        else if(root->left == NULL){
            USER *temp = root->left;
            free(root);
            return temp;
        }
        USER *temp = findMin(root->right);
        root->id = temp ->id;
        root->right = deleteUser(root->right,temp->id);
    }
    return root;
}
/**
 * looks for the user for the given id
 * @param root
 */
void contains(USER *root){

    int id;
    printf("\nAramak istediginiz ID:\n");
    scanf("%d",&id);
    USER *xUser = cSearchUser(root,id);
    if(!xUser)
        printf("Agacta bulunamadi.\n");
    else
        printf("Kisi bulundu.\nAdi Soyadi: %s\n",removeUnderScore(xUser->name));

}
/**
 * prints the friends of given user
 * @param root
 */
void friends(USER *root){

    system("cls");
    int id,i;
    printf("Arkadaslarini bulmak istediginiz kisinin ID sini girin:");
    scanf("%d",&id);
    int *list = searchUser(root,id)->friends;
    if(list==NULL){
        printf("Kisi bulunamadı");
        return;
    }
    i = 0;
    printf("\n%s in arkadaslari:\n",removeUnderScore(searchUser(root,id)->name));
    while(list[i]){

        if(searchUser(root,list[i]) != NULL)
            printf("%d. Arkadas : %s\n",i+1,removeUnderScore(searchUser(root,list[i])->name));
        i++;
    }

}
/**
 * returns the number of users in the tree
 * @param root
 * @return
 */
int returnSize(USER *root){
    int count=0;
    if(root != NULL){
        count += returnSize(root->left);
        count += returnSize(root->right);
        count++;
    }
    return count;
}
/**
 * prints the users with the greater id number fro given id number
 * @param root
 * @param id
 */
void printGreater(USER* root,int id){
    if(root != NULL){
        if(root->id > id){
            printf("%d\t%s\n",root->id,removeUnderScore(root->name));
        }
        printGreater(root->right,id);
        USER *x=(root->left);
        if( x != NULL && x->id < id){
            return;
        }
        printGreater(root->left,id);
    }
}
/**
 * prints the all users sorted
 * @param root
 */
void printInOrder(USER *root) {
    if(root->left != NULL)
        printInOrder(root->left);

    printf("%d \t %s \n", root->id,removeUnderScore(root->name));

    if(root->right)
        printInOrder(root->right);

}
/**
 * reads the tree from tree.txt file
 * @param root
 * @param userCount
 */
void readFromFile(USER **root,int *userCount){
    FILE *ftree;
    int i,j,friendsCount,id,*friends;
    char name[50];
    ftree = fopen("tree.txt","r");
    if(!ftree){
        printf("Dosya bulunamadi.");
        return;
    }
    fscanf(ftree,"%d\n",userCount);

    for( i = 0 ; i < *userCount ; i++){

        fscanf(ftree,"%d %d %s",&id,&friendsCount ,name);
        friends =(int*) malloc((friendsCount+1)*sizeof(int));

        for( j = 0 ; j < friendsCount ; j++){
            fscanf(ftree,"%d",&friends[j]);
        }

        friends[friendsCount]=(int)NULL;

        insertNewUser(root,fCreateNewUser(id,name,friends,friendsCount));

    }
    fclose(ftree);
}

int friendsSize(USER *root,int id){//case175 easteregg
    return _msize(searchUser(root,id)->friends)/sizeof (int);
}
/**
 * frees the root while ending the program
 * @param root
 */
void freeTheRoot(USER *root){

    if((root->left) != NULL)
        freeTheRoot(root->left);
    if((root->right) != NULL)
        freeTheRoot(root->right);

    free(root);
}
/**
 * prints the menu and returns the selection
 * @return
 */
int printMenu(){
    int choice;
    printf("1.Yeni Kullanici ekle \n");
    printf("2.Kullanici sil \n");
    printf("3.Kullanici var mi? \n");
    printf("4.Kullanicinin Arkadaslarini Listele \n");
    printf("5.Agacin eleman sayisi \n");
    printf("6.PrintNext \n");
    printf("7.PrintGreater \n");
    printf("8.PrintInOrder \n");
    printf("9.Tree.txt dosyasindan oku:\n");
    printf("0.Exit \n");
    scanf("%d",&choice);
    return choice;
}
