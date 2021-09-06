#include <stdio.h>
#include <iostream>

using namespace std;


typedef struct node{
    int           data;
    struct node*  next;
    node(int d):data(d), next(NULL){}
}node;

node *reverse_without_headnode(node* head) {
    if (head == NULL) {
        return head;
    }
    node *lef = NULL;
    node *mid = head;
    node *rig = mid->next;
    while (rig) {
        mid->next = lef;
        lef = mid;
        mid = rig;
        rig = rig->next;
    }
    mid->next = lef;
    return mid;
}
void print_without_headnode(node *head) {
    if(NULL == head) {
        return;
    }
    while(head){
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}



int main() {
    
    node node0(0);
    node node1(1);
    node node2(2);
    node node3(3);
    node node4(4);
    node node5(5);

    //异常输入
    node *head = NULL;
    head = reverse_without_headnode(head);
    
    //只有头结点
    head = &node0;
    node0.next = NULL;
    print_without_headnode(head);
    head = reverse_without_headnode(head);

    //一个结点
    head = &node0;
    node0.next = &node1;
    node1.next = NULL;
    print_without_headnode(head);
    head = reverse_without_headnode(head);
    print_without_headnode(head);
    
    //两个结点
    head = &node0;
    node0.next = &node1;
    node1.next = &node2;
    node2.next = NULL;
    print_without_headnode(head);
    head = reverse_without_headnode(head);
    print_without_headnode(head);
   
    //三个结点
    head = &node0;
    node0.next = &node1;
    node1.next = &node2;
    node2.next = &node3;
    node3.next = NULL;
    print_without_headnode(head);
    head = reverse_without_headnode(head);
    print_without_headnode(head);

    //五个结点
    head = &node0;
    node0.next = &node1;
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    node5.next = NULL;
    print_without_headnode(head);
    head = reverse_without_headnode(head);
    print_without_headnode(head);
    return 0;
}
