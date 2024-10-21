// project 2

#include <stdio.h>
#include <malloc.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct stack * stack ;
struct stack {
    char ch ;
    struct stack* next ;
};
struct stack_int {
    int n ;
    struct stack_int* next ;
};

int Pop_int( struct stack_int* S ){
    struct stack_int* firstCell;
    int x ;
        firstCell = S->next;
        x = firstCell->n;
        S->next = firstCell->next;
        free( firstCell );
    return x;
}
void Push_int( int X, struct stack_int*S ){
    struct stack_int* temp;
    temp = ( struct stack_int* )malloc( sizeof( struct stack_int ) );
    if( temp == NULL)
        printf( "Out of space!");
    else{
        temp->n = X;
        temp->next = S->next;
        S->next = temp;
    }
}
struct stack_int*  CreateStack_int(){
    struct stack_int*  S;
    S = (struct stack_int*)malloc( sizeof( struct stack_int  ) );
    if( S == NULL )
        printf( "Out of space!" );
    S->next = NULL;
    return S;
}
// to delete all node in linked list
void DeleteList(struct stack* L){
    struct stack* P, *temp;
    P = L->next;
    L->next = NULL;

    while(P != NULL){
        temp = P->next;
        free(P);
        P=temp;
    }
}
struct stack* MakeEmpty(struct stack* L){
    if(L != NULL)
        DeleteList( L );
    L = (struct stack*)malloc(sizeof(struct stack));
    if(L == NULL)
        printf("Out of memory!\n");
    L->next = NULL;
    return L;
}
int IsLast(struct stack* P, struct stack* L){
    return P->next==NULL;
}
//FindPrevious for any node in list
struct stack* FindPrevious(char X, struct stack* L){
    struct stack* P;
    P = L;
    while(P->next != NULL && P->next->ch != X)
        P = P->next;
    return P;
}
//function to cheack if empty or not
int IsEmpty( stack S ){
    return S->next == NULL;
}
void print_list_int(struct stack_int*  s ){
    struct stack_int* p = s;
    if(IsEmpty(s))
        printf("empty list");
    else{
        while (p->next!=NULL){
            printf("%d",p->next->n);
            p=p->next;
        }
    }
    printf("\n");
}
// print all elemant in stack of list
void print_list(struct stack * s ){
    struct stack*p = s;
    if(IsEmpty(s))
        printf("empty list");
    else{
        while (p->next!=NULL){
            printf("%c",p->next->ch);
            p=p->next;
        }
    }
    printf("\n");
}

//function to delete the value of top , top is first node after head
char Pop( struct stack* S ){
    struct stack* firstCell;
    char x ;
    if( IsEmpty( S ) )
        printf( "Empty stack" );
    else{
        firstCell = S->next;
        x = firstCell->ch;
        S->next = firstCell->next;
        free( firstCell );
    }
    return x;
}
//function to creation the satack
stack  CreateStack(){
    stack  S;
    S = (struct stack *)malloc( sizeof( struct stack  ) );
    if( S == NULL )
        printf( "Out of space!" );
    S->next = NULL;
    return S;
}
//Push function: equivalent to insert. Inserts element at top , top is first elemant in stack
void Push( char X, stack S ){
    stack temp;
    temp = ( stack )malloc( sizeof( struct stack ) );
    if( temp == NULL)
        printf( "Out of space!");
    else{
        temp->ch = X;
        temp->next = S->next;
        S->next = temp;
    }
}
//function to cheack if is the chracter is space or not
int space (char c){
    if(c==' ' || c=='\t')
        return 1;//is space
    else
        return 0;//not space
}
//method to reverse list of character
struct stack* reverseList(struct stack* head) {
    struct stack* prev = head->next;
    struct stack* nxt = NULL;
    struct stack * o = head;
    head = head->next;
    while (head != NULL){
        struct stack * cur = head;
        nxt = o->next;
        o->next = cur;
        head = head->next;
        cur->next = nxt;
        //printf("%c",head->ch);
    }
    prev->next = NULL;
    return o;
}
//function to return number the precedence , for comprater
int precedence (char c){
    switch (c) {
        case '^':
            return 3;
            break;
        case '/':
        case'*':
            return 2;
            break;
        case '+':
        case '-':
            return 1;
            break;
        default:
            return 0;
            break;
    }
}
//function to detemine number equtions in input file to make array of list of size has same countLinesInFile
int countLinesInFile(char file_name[]) {
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", "input");
        return -1; // Return a sentinel value indicating an error
    }
    int lineCount = 0;
    char ch;

    while ( fscanf(file,"%c",&ch) != EOF) {
        if (ch == '\n') {
            lineCount++;
        }
    }

    fclose(file);

    return lineCount;
}
// function to read the equations , array of stack store infex
void read_equations (struct stack * eqution [] ,char file_name[] ){
    eqution[countLinesInFile(file_name)]=MakeEmpty(NULL);
    char c;
    int index=0;
    eqution[0]=CreateStack();
    FILE* file = fopen(file_name, "r");
    while(fscanf(file,"%c",&c) != EOF){
        if(space(c))
            continue;
        if(c=='\n'){
            index++;
            eqution[index]= CreateStack();
        }
        if(index>0){
            Push(c,eqution[index]);
        } else if (index==0){
            Push(c,eqution[0]);
        }
    }
    //we must reverse because the push method add at first
    for(int i =0 ;i<=countLinesInFile(file_name);i++){
       eqution[i]= reverseList(eqution[i]);
   }
    fclose(file);
}
//function take stack is infix and print prefix , take infix
struct stack * infix_to_prefix (struct stack * infex){
    struct stack * prefix =CreateStack();
    struct stack * opration=CreateStack();
    infex=reverseList(infex);
    char symbol , nxt ;
    while (!IsEmpty(infex)){
        symbol=Pop(infex);
        if(!space(symbol)){
            switch (symbol) {
                // if symbol is right parenthesis push it on the opration
                case ']':
                    Push(symbol,opration);
                    break;
                    /* if symbol is left parenthesis pop all the operators
                   * upto the first right parenthesis */
                case '[' :
                    nxt= Pop(opration);
                    while(nxt != ']' && !IsEmpty(opration)){
                        Push(nxt,prefix);
                        nxt= Pop(opration);
                    }
                    break;
                    /* if symbol is left parenthesis pop all the operators
                   * upto the first right parenthesis */
                case '(' :
                    nxt= Pop(opration);
                    while(nxt != ')'&& !IsEmpty(opration)){
                        Push(nxt,prefix);
                        nxt= Pop(opration);
                    }
                    break;
                    // if symbol is right parenthesis push it on the opration
                case ')':
                    Push(symbol,opration);
                    break;
                    /* if the precedence of the operators
                    * in the stack are greater than or
                    * equle to the current operator then
                    * pop the operators out of stack and
                    * print them onto the screen and push
                    * current operator onto the stack else
                    * push current operator onto the stack*/
                case'+':
                case'-':
                case'*':
                case'/':
                case'^':
                    while (!IsEmpty(opration) && precedence(opration->next->ch)> precedence(symbol)){
                        Push(Pop(opration),prefix);
                    }
                    Push(symbol,opration);
                    break;
                    //if no case from above is number such that store in prefix
                default:
                    Push(symbol,prefix);
                    break;
            }
        }
    }
    // affter cheack all infext I must Empty any existing process inside stack
    while (!IsEmpty(opration)){
        char temp = Pop(opration);
        Push(temp,prefix);
    }
    return prefix;
}
// function to Evaluate	the	prefix .. , take prefix
struct stack_int* Evaluate_the_prefix (struct stack * prefix ){
    //reverse prifix expretion to  make same start from right to left
    prefix= reverseList(prefix);
    struct stack_int* store =CreateStack_int();
    char temp ,c1;
    int n1 , n2 ,res  ;
    while (prefix->next!=NULL){
        if(!IsEmpty(prefix)){
            c1 = Pop(prefix);
        }
            switch (c1) {
                case '+':
                   n1 = Pop_int(store);
                   n2 = Pop_int(store);
                   res = n1+n2;
                   Push_int(res,store);
                    break;
                case '-' :
                    n1 = Pop_int(store);
                    n2 = Pop_int(store);
                    res = n1-n2;
                    Push_int(res,store);
                    break;
                case '*' :
                    n1 = Pop_int(store);
                    n2 = Pop_int(store);
                    res = n1*n2;
                    Push_int(res,store);
                    break;
                case '/'  :
                    n1 = Pop_int(store);
                    n2 = Pop_int(store);
                    res = n1/n2;
                    Push_int(res,store);
                    break;
                case '^':
                    n1 = Pop_int(store);
                    n2 = Pop_int(store);
                    res = n1^n2;
                    Push_int(res,store);
                    break;
                default:
                    // if number
                    Push_int(c1-'0',store);
                    break;
            }
        }
    return store;
    }
// Check	the	validity	of	equations	(either	valid	or	not) ,, take infex ,, return 0 if invalid
int validity_of_equations (struct stack* infex){
    struct stack* p = infex;
    // The number of right parentheses is equal to the number of left parentheses for He is valid else invalid
    int count_left =0; // counter [
    int count_right=0; // counter ]
    int count_left2 =0; // counter (
    int count_right2=0; // counter )
    int count_left3 =0; // counter {
    int count_right3=0; // counter }
    char temp;
    char temp2;
    struct stack* temp1 ;
    while (!IsEmpty(infex)){
        temp= infex->next->ch;
        if(temp == '['){
            // to caluclate number [
            count_left++;
            // find previous to cheak if previous not opration is invalid
            temp1= FindPrevious(temp,infex);
            if(temp1!=p){
                if(temp1->ch != '+' && temp1->ch != '-' && temp1->ch != '*' && temp1->ch != '/' && temp1->ch != '^' && temp1!=infex )
                    return 0;
            }

            // find affter posetion to cheak if is opration is invalid
            temp2= infex->next->next->ch;
            if(temp2 == '+' || temp2 == '-' || temp2 == '*' || temp2 == '/' || temp2 == '^' )
                return 0;
            // if [ is last is invalid
            if(infex->next->next==NULL)
                return 0;
        }
        else if (temp == ']'){
            // to caluclate number ]
            count_right++;
            // find previous to cheak if previous  opration is invalid
            temp1= FindPrevious(temp,infex);
            if(temp1->ch == '+' || temp1->ch == '-' || temp1->ch == '*' && temp1->ch == '/'  )
                return 0;
            // find affter posetion to cheak if is not opration is invalid
            if(infex->next->next!=NULL){
                temp2= infex->next->next->ch;
                if(temp2 != '+' && temp2 != '-' && temp2 != '*' && temp2 != '/' && temp2 == '^' )
                    return 0;
            }
            // if ] is first is invalid
            if(temp1==p)
                return 0;
        }
        else if (temp == '('){
            // to caluclate number (
            count_left2++;
            // find previous to cheak if previous not opration is invalid
            temp1= FindPrevious(temp,infex);
            if(temp1!=p){
                if(temp1->ch != '+' && temp1->ch != '-' && temp1->ch != '*' && temp1->ch != '/' && temp1->ch != '^' && temp1!=infex )
                    return 0;
            }
            // find affter posetion to cheak if is opration is invalid
            temp2= infex->next->next->ch;
            if(temp2 == '+' || temp2 == '-' || temp2 == '*' || temp2 == '/' || temp2 == '^' )
                return 0;
            // if ( is last is invalid
            if(infex->next->next==NULL)
                return 0;
        }
        else if (temp == ')'){
            // to caluclate number )
            count_right2++;
            // find previous to cheak if previous  opration is invalid
            temp1= FindPrevious(temp,infex);
            if(temp1->ch == '+' || temp1->ch == '-' || temp1->ch == '*' || temp1->ch == '/' || temp1->ch == '^'  )
                return 0;
            // find affter posetion to cheak if is not opration is invalid
            if(infex->next->next!=NULL){
                temp2= infex->next->next->ch;
                if(temp2 != '+' && temp2 != '-' && temp2 != '*' && temp2 != '/' && temp2 != '^' )
                    return 0;
            }
            // if ) is first is invalid
            if(temp1==p)
                return 0;
        }
        else if (temp=='*'){
            // expirtion in end * invalid
            if(infex->next->next==NULL)
                return 0;
            // if after * is any opration is invalid
            temp2= infex->next->next->ch;
            if(temp2 == '*' || temp2 == '/' || temp2 == '+' || temp2 == '-')
                return 0;
            // if befor * is any opration is invalid
            temp1= FindPrevious(temp,infex);
            if(temp1->ch == '*' || temp1->ch == '/' || temp1->ch == '+' || temp1->ch == '-')
                return 0;
            // expirtion in start * invalid
            if(temp1==p)
                return 0;
        }
        else if (temp == '/'){
            // expirtion in end / invalid
            if(infex->next->next==NULL)
                return 0;
            // if after / is any opration is invalid
            temp2= infex->next->next->ch;
            if(temp2 == '*' || temp2 == '/' || temp2 == '+' || temp2 == '-')
                return 0;
            // if befor / is any opration is invalid
            temp1= FindPrevious(temp,infex);
            if(temp1->ch == '*' || temp1->ch == '/' || temp1->ch == '+' || temp1->ch == '-')
                return 0;
            // expirtion in start / invalid
            if(temp1==p)
                return 0;
        }
        else if (temp == '+'){
            // expirtion end in + invalid
            if(infex->next->next==NULL)
                return 0;
            // if after + is * / is invalid
            temp2= infex->next->next->ch;
            if(temp2=='*' || temp2 =='/')
                return 0;
            // if befor + is * / is invalid
            temp1= FindPrevious(temp,infex);
            if(temp1->ch == '*' || temp1->ch == '/')
                return 0;
            // expirtion in start + invalid
            if(temp1==p)
                return 0;
        }
        else if (temp == '-'){
            // expirtion end in - invalid
            if(infex->next->next==NULL)
                return 0;
            // if after - is * / is invalid
            temp2= infex->next->next->ch;
            if(temp2=='*' || temp2 =='/')
                return 0;
            // if befor - is * / is invalid
            temp1= FindPrevious(temp,infex);
            if(temp1->ch == '*' || temp1->ch == '/')
                return 0;
            // expirtion in start - invalid
            if(temp1==p)
                return 0;
        }
        // to move check the next node
        infex=infex->next;
    }
    if(count_left != count_right)
        return 0;
    if(count_left2 != count_right2)
        return 0;
    if(count_left3 != count_right3)
        return 0;
    return 1;
}
int main() {
    char file_name[20];
    printf(" Enter the name of the file you want to read from .. \n");
  scanf("%s", &file_name);
    FILE *fout;
    int cheack=0, n;
    struct stack *equtions[countLinesInFile(file_name)];
    read_equations(equtions,"input.txt");
    print_list(equtions[2]);
    print_list(infix_to_prefix(equtions[2]));
    if(validity_of_equations(equtions[2])==1)
        printf("valid \n");
    else
        printf("invalid");
    print_list_int(Evaluate_the_prefix(infix_to_prefix(equtions[2])));

        return 0;

}