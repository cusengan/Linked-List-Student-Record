#pragma once

struct student_record
{
	int student_id_;
	int student_age_;
	char* first_name_;
	char* last_name_;
};

enum student_record_constants
{
	NAME_LENGTH = 20,
	ID_MAX_LENGTH = 5,
	AGE_MAX_LENGTH =2
};
/*
	I would have defined them this way, but in C89 we aren't allowed to use
	const values as sizes in arrays.
	static const int NAME_LENGTH = 20;
	static const int  ID_MAX_LENGTH = 5;
	static const int AGE_MAX_LENGTH = 2;

	*/
struct student_record_node* findNode(struct student_record_node* head);

