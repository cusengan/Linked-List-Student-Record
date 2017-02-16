#pragma once


struct student_record_node
{
        struct student_record* record_;
        struct student_record_node* next_;
        struct student_record_node* prev_;
};


void swap(struct student_record_node* node1,struct student_record_node* node2);
void student_record_node_deallocate(struct student_record_node* node);
void appendNode(struct student_record_node** head,struct student_record_node* newNode);
void printNode(struct student_record_node* node, char** string);
void freeNodeList(struct student_record_node* head);
void streamNodeList(char * fileName, struct student_record_node* head);
void printNodeList(struct student_record_node* head);
void sort(struct student_record_node** head, int(*compare_fcn)(struct student_record_node*, struct student_record_node*));
int ageComparator(struct student_record_node* node1, struct student_record_node* node2);
int idComparator(struct student_record_node* node1, struct student_record_node* node2);
void removeNode(struct student_record_node* node);
struct student_record_node* student_record_allocate();
