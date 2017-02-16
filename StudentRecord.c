#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StudentRecordNode.h"
#include "StudentRecord.h"




struct student_record_node* findNode(struct student_record_node* head)
{
        int val;
        int flag = 1;
        char input[ID_MAX_LENGTH];
        while(flag)
        {
                printf("Enter the Student ID\n");



                if (getLine(input, sizeof(input)) ||
                        !sscanf(input, "%d", &val))
                {
                        printf("Error. Please Try again.\n");
                        continue;
                }
                flag = 0;

        }

        while(head != NULL)
        {
                if(head->record_->student_id_ == val)
                {
                        printf("found node\n");
                        return head;
                }
                head = head->next_;

        }

        return NULL;



}

