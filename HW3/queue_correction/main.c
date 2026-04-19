#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include "function.h"

Node* createListNode(int x) {
    Node* node=(Node*)malloc(sizeof(Node));
    *(int*)&node->v = x;
    node->next = NULL;
    return node;
}

intptr_t print(Node* head, intptr_t chk2){
    Node* cur = head->next;
    while(cur != NULL){
        chk2 ^= ((intptr_t)cur+cur->v);
        printf("%d ", cur->v);
        cur = cur->next;
    }
    return chk2;
}
void freeList(Node* head){
    Node* cur = head;
    Node* tmp = NULL;
    while(cur != NULL){
        tmp = cur;
        cur = cur->next;
        free(tmp);
    }
}

int main(){
    int n,l,r;
    scanf("%d %d %d", &n, &l, &r);
    Node* head = createListNode(0);
    intptr_t chk = (intptr_t)head;
    Node* cur = head;
    for(int i=0; i<n; i++){
        int tmp;
        scanf("%d", &tmp);
        cur->next = createListNode(tmp);
        cur = cur->next;
        chk ^= ((intptr_t)cur+cur->v);
    }
    solve(head, l, r);
    if(chk != print(head, (intptr_t)head))
        printf("WA\n");
    freeList(head);
    return 0;
}
