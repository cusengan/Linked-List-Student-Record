#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StudentRecordNode.h"
#include "StudentRecord.h"

void swap(struct student_record_node* node1,
struct student_record_node* node2)
{
	struct student_record_node* temp;

	if (node1->next_ == node2)
	{
		node1->next_ = node2->next_;
		node2->next_ = node1;
		node2->prev_ = node1->prev_;
		node1->prev_ = node2;
	}
	else if (node2->next_ == node1)
	{
		node2->next_ = node1->next_;
		node1->next_ = node2;
		node1->prev_ = node2->prev_;
		node2->prev_ = node1;
	}
	else
	{
		temp = node1->next_;
		node1->next_ = node2->next_;
		node2->next_ = temp;

		temp = node1->prev_;
		node1->prev_ = node2->prev_;
		node2->prev_ = temp;
	}

	if (node1->prev_)
	{
		node1->prev_->next_ = node1;
	}

	if (node1->next_)
	{
		node1->next_->prev_ = node1;
	}

	if (node2->prev_)
	{
		node2->prev_->next_ = node2;
	}

	if (node2->next_)
	{
		node2->next_->prev_ = node2;
	}
}


void student_record_node_deallocate(struct student_record_node* node)
{
	free(node->record_->first_name_);
	free(node->record_->last_name_);
	free(node->record_);
	free(node);
}


void appendNode(struct student_record_node** head,
struct student_record_node* newNode)
{
	struct student_record_node* iterator = *head;
	if (iterator == NULL)
	{
		*head = newNode;
		return;
	}
	while (iterator->next_ != NULL)
	{
		iterator = iterator->next_;
	}

	iterator->next_ = newNode;
	newNode->prev_ = iterator;
}

void printNode(struct student_record_node* node, char** string)
{
	if (!*string)
	{
		*string = calloc(200, sizeof(char));
	}
	sprintf(*string,
		"struct student_record_node: \n \
		 student first name: %s\n \
		 student second name: %s\n \
		 student id: %d\n \
		 student age: %d\n \
		 prevous: %p\n \
		 next: %p\n",
		node->record_->first_name_,
		node->record_->last_name_,
		node->record_->student_id_,
		node->record_->student_age_,
		node->prev_,
		node->next_);
}

void freeNodeList(struct student_record_node* head)
{
	if (head == NULL)
	{
		return;
	}

	if (head->next_ != NULL)
	{
		freeNodeList(head->next_);
	}
	student_record_node_deallocate(head);
}

void streamNodeList(char * fileName, struct student_record_node* head)
{
	struct student_record_node* iterator = head;
	FILE* outputFile = fopen(fileName, "w");
	if (!outputFile)
	{
		printf("Cannot open output file. Exiting");
		exit(1);
	}

	if (head == NULL)
	{
		printf("Empty List\n");
		return;
	}

	while (iterator != NULL)
	{
		char * output = calloc(1024, sizeof(char));
		printNode(iterator, &output);
		fwrite(output, sizeof(char), strlen(output), outputFile);
		iterator = iterator->next_;
		free(output);
	}

}

void printNodeList(struct student_record_node* head)
{
	struct student_record_node* iterator = head;
	char * output;
	if (head == NULL)
	{
		printf("\n");
		return;
	}

	output = calloc(1024, sizeof(char));
        printNode(iterator, &output);
        printf("%s", output);
        printNodeList(iterator->next_);
        free(output);


}

void sort(struct student_record_node** head, int(*compare_fcn)(struct student_record_node*, struct student_record_node*))
{
	struct student_record_node* iterator = NULL;
	int sorted = 0;
	do
	{
		sorted = 1;
		iterator = *head;
		while (iterator != NULL)
		{
			if (iterator->next_ != NULL)
			{
				if (compare_fcn(iterator, iterator->next_))
				{
					if (iterator == *head)
					{
						*head = iterator->next_;
					}
					swap(iterator, iterator->next_);
					sorted = 0;
				}
			}
			iterator = iterator->next_;
		}
	} while (!sorted);
}

int ageComparator(struct student_record_node* node1, struct student_record_node* node2)
{
	return (node1->record_->student_age_ > node2->record_->student_age_) ? 1 : 0;
}

int idComparator(struct student_record_node* node1, struct student_record_node* node2)
{
	return (node1->record_->student_id_ > node2->record_->student_id_) ? 1 : 0;
}



void removeNode(struct student_record_node* node)
{

		
	if(node->prev_)
	{
        	node->prev_->next_ = node->next_;
	}
	if(node->next_)
	{
        	node->next_->prev_ = node->prev_;
	}
}



struct student_record_node* student_record_allocate()
{
        struct student_record_node* ret =
                calloc(1, sizeof(struct student_record_node));

        ret->record_ = calloc(1, sizeof(struct student_record));
        ret->record_->first_name_ = calloc(1 + NAME_LENGTH, sizeof(char));
        ret->record_->last_name_ = calloc(1 + NAME_LENGTH, sizeof(char));

        return ret;
}


