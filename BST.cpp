#include <iostream>
using namespace std;
#define EMPTY_SLOT
int TreeSize, Height;

int * allocateMemoryOfArray(){
    int Maxlevel;
    printf("What Height do you want to set the binary tree to? : ");
    if(scanf("%d",&Maxlevel) != 1){
        printf("Invalid input! Please enter a valid number.\n");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return nullptr;
    }
    else{
        Height = Maxlevel;
        if(Height <= 1 || Height > 6){
            if(Height < 1){
                printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tallocateMemoryOfArray\tInvalid input : not support negetive number.\n");
            }else if(Height == 1){
                printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tallocateMemoryOfArray\tInvalid input : Tree cannot be one node.\n");
            }
            else{
                printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tallocateMemoryOfArray\tInvalid input : Height of tree outOfDisplay\n");
            }
            return nullptr;
        }
        
        TreeSize = (1 << Height) - 1;
        int * BTArray = (int *)calloc(TreeSize, sizeof(int));
        if (BTArray == nullptr) {
            printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tallocateMemoryOfArray\tMemory allocation failed.\n");
            return nullptr;
        }else{
            return BTArray;
        }
    }
}
bool * OccupiedElementInArray(int BSTArray[]){
    if(BSTArray == nullptr || TreeSize <= 0){
        return nullptr;
    }else{
        bool * OccupiedArray = (bool *)calloc(TreeSize, sizeof(bool));
        if (OccupiedArray == nullptr) {
            printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tOccupiedElementInArray\tMemory allocation failed.\n");
            return nullptr;
        }
        else{
            return OccupiedArray;
        }
    }
}

void printSpaces(int count) {
    for (int i = 0; i < count; i++) {
        printf(" ");
    }
}

void display(int Array[], bool logic[]) {
    int nodeIndex = 0;
    int maxWidth = (1 << (Height - 1)) * 4 - 1;

    for (int level = 0; level < Height; level++) {
        int nodeInLevel = 1 << level;
        int spaceBetweenNodes = maxWidth / nodeInLevel;
        int leadingSpaces = spaceBetweenNodes / 2;
        
        printSpaces(leadingSpaces);
    
        for (int i = 0; i < nodeInLevel; i++) {
            if (logic[nodeIndex] == false) {
                printf("x");
            } else {
                printf("%d", Array[nodeIndex]);
            }
            nodeIndex++;
            
            if (i < nodeInLevel - 1) {
                printSpaces(spaceBetweenNodes);
            }
        }
        printf("\n");
    }
}

int IsEmptyNode(int BTArray[],bool LogicArray[],int Parent = 0){
    if(!(BTArray[Parent] == '\0' && LogicArray[Parent] == false)){
        //printf("IsEmptyNode\tNotEmpty : Node no.%d Data %d ",Parent, BTArray[Parent]);
        return 0;
    }else{
        //printf("IsEmptyNode\tEmpty : Node no. %d ",Parent);
        return 1;
    }
}

int binarySearchTree(int BTArray[],bool LogicArray[],int Parent, int target){
    if(Parent > TreeSize - 1){
        return TreeSize + 1;
    }
    int c = IsEmptyNode(BTArray,LogicArray,Parent);
    if(c){
        return -Parent;
    }else if(!c && BTArray[Parent] == target){
        return Parent;
    }
    if(BTArray[Parent] > target){
        return binarySearchTree(BTArray, LogicArray, 2 * Parent + 1, target);
    }
    else{
        return binarySearchTree(BTArray, LogicArray, 2 * Parent + 2, target);
    }
}

// wrapping function
int binarySearchTree(int BTArray[], bool LogicArray[], int target){
    return binarySearchTree(BTArray,LogicArray, 0, target);
}

void binaryTreeInsert(int BTArray[], bool LogicArray[], int data, int Parent = 0) {
    Parent = binarySearchTree(BTArray, LogicArray, data);
    if (Parent <= 0) {
        BTArray[abs(Parent)] = data;
        LogicArray[abs(Parent)] = true;
    }
}
int binaryTreeInsert(int BTArray[],bool LogicArray[]){
    int data;
    printf("input :");
    if (scanf("%d", &data) != 1) {
            printf("Invalid input! Please enter a valid number.\n");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 1;
    }else{
        binaryTreeInsert(BTArray,LogicArray,data);
    }
    return 0;
}

int Moving(bool LogicArray[], int Parent){
    if(LogicArray[2 * Parent + 1] == false){
        return Parent;}
    return Moving(LogicArray, 2 * Parent + 1);
}
int binaryTreeDelete(int BTArray[], bool LogicArray[], int target, int Parent = 0) {
Parent = binarySearchTree(BTArray, LogicArray, Parent, target);
    if(Parent >= 0 && Parent < TreeSize){
        int temp = BTArray[Parent];
        int lc = 2 * Parent + 1;
        int rc = 2 * Parent + 2;
        if(LogicArray[lc] == false && LogicArray[rc] == false){ //false && false
            BTArray[Parent] = '\0';
            LogicArray[Parent] = false;
        }
        else if(LogicArray[lc] == true && LogicArray[rc] == true){// true && true
            if(LogicArray[2 * rc + 1] == false){
                BTArray[Parent] = binaryTreeDelete(BTArray, LogicArray, BTArray[rc], rc);
            }else{
                int irst = Moving(LogicArray, rc);
                BTArray[Parent] = binaryTreeDelete(BTArray, LogicArray, BTArray[irst],irst);
            }
            
        }else if(LogicArray[lc] == true && LogicArray[rc] == false){
            BTArray[Parent] = binaryTreeDelete(BTArray, LogicArray, BTArray[lc], lc);
        }else{
            BTArray[Parent] = binaryTreeDelete(BTArray, LogicArray, BTArray[rc], rc);
        }
        
        if(BTArray[Parent] > BTArray[rc] && (LogicArray[rc] && LogicArray[Parent])){
            do{
                binaryTreeInsert(BTArray,LogicArray,binaryTreeDelete(BTArray, LogicArray, BTArray[rc],rc));
            }while (BTArray[Parent] < BTArray[rc] && (LogicArray[rc] && LogicArray[Parent]));
        }else if(BTArray[Parent] < BTArray[lc] && (LogicArray[lc] && LogicArray[Parent])){
            do{
                binaryTreeInsert(BTArray,LogicArray,binaryTreeDelete(BTArray, LogicArray, BTArray[lc],lc));
            }while (BTArray[Parent] < BTArray[lc] && (LogicArray[lc] && LogicArray[Parent]));
        }else if(BTArray[Parent] > BTArray[2 * rc + 1] && (LogicArray[2 * rc + 1] && LogicArray[Parent])){
            do {
                binaryTreeInsert(BTArray,LogicArray,binaryTreeDelete(BTArray, LogicArray, BTArray[2 * rc + 1],2 * rc + 1));
            } while (BTArray[Parent] > BTArray[2 * rc + 1] && (LogicArray[2 * rc + 1] && LogicArray[Parent]));
            
        }else if(BTArray[Parent] < BTArray[2 * lc + 1] && (LogicArray[2 * lc + 1] && LogicArray[Parent])){
            do{
                binaryTreeInsert(BTArray,LogicArray,binaryTreeDelete(BTArray, LogicArray, BTArray[2 * lc + 1],2 * lc + 1));
            }while (BTArray[Parent] < BTArray[2 * lc + 1] && (LogicArray[2 * lc + 1] && LogicArray[Parent]));
        }
        return temp;
        
    }
    return -1;
}

int binaryTreeDelete(int BTArray[], bool LogicArray[]){
    int target;
    printf("delete :");
    if (scanf("%d", &target) != 1) {
            printf("Invalid input! Please enter a valid number.\n");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 1;
    }else{
        binaryTreeDelete(BTArray, LogicArray, target, 0);
    }
    return 0;
}


int main(int argc, const char * argv[]) {
    //printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tFunction\t\tstatus\n");
    int * BTArray;
    bool * LogicArray;
    do{
        BTArray = allocateMemoryOfArray();
    }while(BTArray == nullptr);
    LogicArray = OccupiedElementInArray(BTArray);
    printf("Create BT Array :\n");
    display(BTArray, LogicArray);
    int select = 0;
    while(1){
        printf("select function insert(1) delete(2) exit(3):");
        if(scanf("%d",&select) != 1){
            printf("Invalid input! Please enter a valid number.\n");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (select) {
            case 1:
                do{
                }while(binaryTreeInsert(BTArray, LogicArray));
                display(BTArray, LogicArray);
                break;
            case 2:
                do{

                }while(binaryTreeDelete(BTArray, LogicArray));
                display(BTArray, LogicArray);
                break;
            case 3:
                printf("Program exit\n");
                exit(0);
        }
    }
    
    return 0;   
}