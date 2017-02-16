#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StudentRecordNode.h"
#include "StudentRecord.h"

typedef enum
{
	input_command_NEW_STUDENT,
	input_command_PRINT,
	input_command_MODIFY,
	input_command_REMOVE,
	input_command_SORTID,
	input_command_SORTAGE,
	input_command_SAVE,
	input_command_LOAD,	
	input_command_EXIT,
	input_command_ERROR
}input_command;


typedef enum
{	
	input_attribute_ID,
        input_attribute_AGE,
        input_attribute_FIRST,
        input_attribute_LAST,
        input_attribute_EXIT,
        input_attribute_ERROR
}input_attribute;

int flag = 1;


void parseFile(char* filename, struct student_record_node** head);
int getLine(char * buffer, int length);
void displayMenu();
input_command acquireInputCmd();
void processCommand(input_command command, struct student_record_node** head);
int validateIntegerInput(int input, int lowBound, int highBound);
void getStudentInfo(struct student_record_node* node);
void requestStudentId(int* val);
void requestStudentAge(int* val);
void requestStudentFirstName(char * val, int length);
void requestStudentLastName(char * val, int length);
void loadRoaster(struct student_record_node** head);
void modifyNode(input_attribute trait, struct student_record_node* head);
void processAttribute(input_attribute trait, struct student_record_node* node);
void displayMenu2();
input_attribute acquireInputAtr();


int main(void)
{
	input_command command;
	struct student_record_node * head = NULL;
	while (1)
	{
		/* construct a main menu */
		displayMenu();

		/* capture user input */
		command = acquireInputCmd();
	
        /* process the user input*/
		processCommand(command, &head);
	}
}


void parseFile(char* filename, struct student_record_node** head)
{//this creates the linked list in which we are storing the student record
	FILE* file;

	
	int nodeCount = 0;		
	struct student_record_node* first = NULL;	
	struct student_record_node* temp1 = NULL;
	struct student_record_node* temp2 = NULL;
	file = fopen(filename,"r");



	if(file == NULL)
	{
		printf("The file could not be opened.\n");
		exit(1);	

	}

	while(fgets(filename, BUFSIZ, file) != NULL)
	{
		
                if(nodeCount==0)//first node is different, it is not being connected to a node behind it
                {
                first = student_record_allocate();


                sscanf(filename,"%s %s %d %d",first->record_->first_name_,first->record_->last_name_,&first->record_->student_id_,&first->record_->student_age_);
                nodeCount ++;
                continue;

                }
		
		if(nodeCount == 1)
		{
			temp1 = student_record_allocate();
			
			sscanf(filename,"%s %s %d %d",temp1->record_->first_name_,temp1->record_->last_name_,&temp1->record_->student_id_,&temp1->record_->student_age_);
			appendNode(&first,temp1);
			nodeCount ++;
				
			continue;

		}
		
		if(nodeCount%2 == 0)
                {
                        temp2 = student_record_allocate();

                        sscanf(filename,"%s %s %d %d",temp2->record_->first_name_,temp2->record_->last_name_,&temp2->record_->student_id_,&temp2->record_->student_age_);
			appendNode(&temp1,temp2);
                        nodeCount ++;
                        continue;

                }

		if(nodeCount%2 != 0)
                {
                        temp1 = student_record_allocate();

                        sscanf(filename,"%s %s %d %d",temp1->record_->first_name_,temp1->record_->last_name_,&temp1->record_->student_id_,&temp1->record_->student_age_);
                        appendNode(&temp2,temp1);
                        nodeCount ++;
               		continue;         

                }
		
		


		
	}

	
	*head = first;
	fclose(file);

	 



}


         

/**
	This is where we capture user input and 
	fetch the appropriate command based on 
	that input
**/
input_command acquireInputCmd()
{
	char input[3];
	const int num_items = 3;
	int inputChoice;

	/**
		We check for certain conditions
			1. getline returning true
				This returns true when the user supplies input too large for our buffer. In our program,
				that is a security vulenerability, as our input must conform to size constraints.
			2. sscanf returning false
				This returns false when input doesn't conform to the format specifier string, meaning it is
				in the wrong format
	**/
	if (getLine(input, sizeof(input)) ||
		!sscanf(input, "%d", &inputChoice))
	{
		return input_command_ERROR;
	}

	

	if (validateIntegerInput(inputChoice, 1, 9)) //This checks the user input and if he is in the bounds of the options given
	{
		return (input_command)(inputChoice - 1);
	}
	else
	{
		/**
			If the user gave a number outside of the bounds of
			our expectations, we should return an error
		**/
		return input_command_ERROR;
	}
	
}

/**
	This is a bounded getline implementation. An unbounded implementation
	would keep track of the length of buffer and realloc when necessary. As such,
	it would need to pass a double pointer to buffer because realloc is not guranteed
	to return return an address to the existing buffer location. For our implementation,
	we only need the address of a buffer and the length of that buffer
**/

//buffer is temporary memory used to store data for this "job" or use

int getLine(char * buffer, int length)
{
	int charsRead = 0;
	int input = 0;
	int attemptedOverflow = 0;
	/**

			1. Input not being EOF because getc advances through the stream until it reaches the end
			2. Input not being a newline (that will move to what the user wants next)
			3. charsRead < length because we do not want to overflow our input buffer
	**/
	while ( (input = getc(stdin)) != EOF &&
		   input != '\n' &&
		    charsRead < length)
	{
		buffer[charsRead] = input;
		charsRead++;
	}

	
	//stdin needs to be flushed, fflush cannot be used because stdin is an input buffer 

	if (input != '\n' && input != EOF)
	{
		attemptedOverflow = 1; //error!!
		while ((input = getc(stdin)) != EOF &&
			input != '\n') {
		}
	}

	return attemptedOverflow;
}



void addStudent(struct student_record_node** head)
{
	struct student_record_node* input = student_record_allocate();
	getStudentInfo(input);
	appendNode(head, input);
}


void getStudentInfo(struct student_record_node* node)
{
	requestStudentId(&node->record_->student_id_);
	requestStudentAge(&node->record_->student_age_);
	requestStudentFirstName(node->record_->first_name_, NAME_LENGTH);
	requestStudentLastName(node->record_->last_name_, NAME_LENGTH);
}

void requestStudentId(int* val)
{
	char input[ID_MAX_LENGTH];
	printf("Enter the Student ID\n");

	if (getLine(input, sizeof(input)) ||
		!sscanf(input, "%d", val))
	{
		printf("Error. Please Try again\n.");
		requestStudentId(val);
	}
}

void requestStudentFirstName(char * val, int length)
{
	char input[NAME_LENGTH + 1] = { 0 };
	printf("Enter the Student First Name\n");

	if (getLine(input, sizeof(input)) ||
		!sscanf(input, "%s", val))
	{
		printf("Error. Please Try again\n.");
		requestStudentFirstName(val, length);
	}
}

void requestStudentLastName(char * val, int length)
{
	char input[NAME_LENGTH + 1] = { 0 };
	printf("Enter the Student Last Name\n");

	if (getLine(input, sizeof(input)) ||
		!sscanf(input, "%s", val))
	{
		printf("Error. Please Try again\n.");
		requestStudentLastName(val, length);
	}
}

void requestStudentAge(int * val)
{
	char input[AGE_MAX_LENGTH];
	printf("Enter the Student Age\n");

	if (getLine(input, sizeof(input)) ||
		!sscanf(input, "%d", val))
	{
		printf("Error. Please Try again\n.");
		requestStudentAge(val);
	}
}


input_attribute acquireInputAtr()
{
	char input[3];
	const int num_items = 3;
	int inputChoice;

	if (getLine(input, sizeof(input)) ||
		!sscanf(input, "%d", &inputChoice))
	{
		return input_attribute_ERROR;
	}

	
	if (validateIntegerInput(inputChoice, 1, 5))
	{
		return (input_attribute)(inputChoice - 1);
	}
	else
	{
		
		return input_attribute_ERROR;
	}
	
}

   

void displayMenu2()
{
	printf("Please Enter Your Selection Below\n");
	printf("_________________________________\n");
	printf("1. Change student ID.\n");
	printf("2. Change student age.\n");
	printf("3. Change student first name.\n");
	printf("4. Change student last name.\n");
	printf("5. Return to main menu.\n");
	
}

void processAttribute(input_attribute trait, struct student_record_node* node)
{
		
	
	switch(trait)
	{
		case input_attribute_ID:
		{
			requestStudentId(&node->record_->student_id_);
			break;

		}

		case input_attribute_AGE:
		{
			requestStudentAge(&node->record_->student_age_);
			break;

		}
		case input_attribute_FIRST:
		{
			requestStudentFirstName(node->record_->first_name_,NAME_LENGTH);
			break;
		}
		case input_attribute_LAST:
		{
			requestStudentLastName(node->record_->last_name_,NAME_LENGTH);
			break;
		}
		case input_attribute_EXIT:
		{
			flag = 0;				

		}
		case input_attribute_ERROR:
		{
			printf("incorrect input. Try again\n");
			break;
		}

		default:
		{
			printf("Theres a bug somewhere, we shouldn't be here\n");
		}


	}




}


void modifyNode(input_attribute trait, struct student_record_node* head)
{
        flag = 1; // using global variable flag, when true the modify node menu stays up

        while (flag)
        {

                displayMenu2();
		
		trait = acquireInputAtr();
			
		processAttribute(trait,head);

		
		
        }

                        
}                  

 

void processCommand(input_command command, struct student_record_node** head)
{

	switch (command)
	{
		case input_command_NEW_STUDENT:
		{
			addStudent(head);
			break;
		}
		case input_command_PRINT:
		{
			printNodeList(*head);
			break;
		}
		case input_command_MODIFY:
		{	
			
			input_attribute trait;
			struct student_record_node* headptr = *head;
			headptr = findNode(headptr);
			if(headptr == NULL) /*checks if node exists*/
                        {
                                printf("node was not found\n");
                                break;
                        }
	
			
			modifyNode(trait,headptr); 
			break;	
		}
		case input_command_REMOVE:
		{
			struct student_record_node* headptr = *head;	
			headptr = findNode(headptr);
			if(headptr == NULL) /*checks if node exists*/
			{
				printf("node was not found\n");
				break;	
			}	
			if(headptr->prev_ == NULL && headptr != NULL) /*checks if node is the first node in the linked link and if it exists*/
			{	
				*head = headptr->next_;
			}
			if(headptr != NULL) /*if node exists, remove it*/
			{
				removeNode(headptr);

			}
			student_record_node_deallocate(headptr);
			printf("node was removed\n");	
			break;
		}
                case input_command_SORTID: //using function pointer
		{
			
			int(*idPtr)(struct student_record_node*, struct student_record_node*)= &idComparator;
			sort(head,*idPtr);
		
			break;

		}
		case input_command_SORTAGE: //using function pointer
		{
			int(*agePtr)(struct student_record_node*, struct student_record_node*)= &ageComparator;
                        sort(head,*agePtr);
			break;


		}
		case input_command_SAVE:
		{
			FILE *fp;
                        char fnamer[100];
                        int len;

                       
                        printf("\n\nPlease enter the file name, do not forget the .txt extension \n");
                        fgets(fnamer,100,stdin); /*captures user input up to 100 characters*/
			len = strlen(fnamer);
                        if(len > 0 && fnamer[len-1] == '\n')
                        {
                                fnamer[len-1] = '\0';

                        }
			streamNodeList(fnamer,*head);
			break;
		}
		case input_command_LOAD: 
                {

                        FILE *fp;
                        char fnamer[100]; //name of file
                        int len;

                        freeNodeList(*head);
                        printf("\n\nPlease enter the file name or the full path to the file, do not forget the .txt extension \n");
                        fgets(fnamer,100,stdin); /*captures user input up to 100 chars, the file name is stored in fnamer*/
                        len = strlen(fnamer);

                        if(len > 0 && fnamer[len-1] == '\n')
                        {
                                fnamer[len-1] = '\0';//set a terminating character so extra space is not counted

                        }
                        fp=fopen(fnamer,"r");//opening the file


                        if(fp==NULL)
                        {
                                printf("\nFile NOT FOUND!\n",fnamer);

                                break;

                        }
                        parseFile(fnamer,head);
                        close(fp);
                        break;
                }

		

		case input_command_EXIT:
		{
			printf("Exiting..Bye!\n");
			freeNodeList(*head);
			exit(0);
			break;
		}
		case input_command_ERROR:
		{
			printf("incorrect input. Try again\n");
			break;
		}

	
		default:
		{
			printf("Theres a bug somewhere, we shouldn't be here\n");
		}
	};
}

/**
	True or false return
	This allows us to validate user input against a range of integers
*/
int validateIntegerInput(int input, int lowBound, int highBound)
{
	if (input >= lowBound && input <= highBound)
	{
		return 1;
	}
	
	else
	{
		return 0;
	}
}

/**
	The Main menu of the program
**/
void displayMenu()
{
	printf("Please Enter Your Selection Below\n");
	printf("_________________________________\n");
	printf("1. Enter a new student.\n");
	printf("2. Print Roster.\n");
	printf("3. Modify an existing student's information.\n");
	printf("4. Remove a student.\n");
	printf("5. Sort roster by ID.\n");
	printf("6. Sort roster by AGE.\n"); 
	printf("7. Save current roster to a file.\n");
	printf("8. Load a roster from a file.\n");
	printf("9. Exit Program.\n");
}


