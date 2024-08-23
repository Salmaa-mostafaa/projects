#include<stdio.h>
#include<math.h>
#include"string.h"
#include <stdlib.h>

struct student{
	int id;
	char name[50];
	int age;
	float gpa;
};
struct node{
	struct student data;
	struct node *next;
};
struct node *head=NULL;

void addStudent(const struct student *const ptr);
void displayStudents(void);
void searchStudentByID(int id);
void updateStudent(int id);
float calculateAverageGPA(void);
void searchHighestGPA(void);
void deleteStudent(int id);

int main(void){
	setvbuf(stdout,NULL,_IONBF,0);
	setvbuf(stderr,NULL,_IONBF,0);
	struct student s;
	int id;

	printf("1)Add student\n2)Display all students\n3)Search for a student id\n4)Update student information\n5)Calculate average GPA\n6)Find student with Highest GPA\n7)Delete student\n8)Exit\n");
	int no;
	printf("Choise:");
	scanf("%d",&no);
	while(no!=8){
	switch(no){
	case 1:
		 printf("\n*\n");
		     printf("Please Enter Student Name :\n");
		     scanf("%s",s.name);
		     printf("Please Enter Student id :\n");
		     scanf("%d",&s.id);
		     printf("Please Enter Student age :\n");
		     scanf("%d",&s.age);
		     printf("Please Enter Student gpa :\n");
		     scanf("%f",&s.gpa);
		     addStudent(&s);
	          break;
	case 2:
		printf("\n*\n");
		    displayStudents();
		      break;
	case 3:
		 printf("\n*\n");
		    printf("Enter ID:\n");
		    scanf("%d",&id);
		    printf("\n*\n");
		    searchStudentByID(id);
		      break;
	case 4:
		 printf("\n*\n");
		    printf("Enter ID:\n");
		    scanf("%d",&id);
		printf("\n*\n");
		    updateStudent(id);
		      break;
	case 5:
		 printf("\n*\n");
		float s=calculateAverageGPA();
		printf("Averge GPA=%f\n",s);
		      break;
	case 6:
		 printf("\n*\n");
	     searchHighestGPA();
		      break;
	case 7:
		 printf("\n*\n");
		   printf("Enter ID:\n");
		   scanf("%d",&id);
		   printf("\n*\n");
		   deleteStudent(id);
		      break;
	}
	printf("\n*\n");
	printf("1)Add student\n2)Display all students\n3)Search for a student id\n4)Update student information\n5)Calculate average GPA\n6)Find student with Highest GPA\n7)Delete student\n8)Exit\n");
	printf("Choise:");
			      scanf("%d",&no);
	}
	printf("Exit");
	return 0;
}
void addStudent(const struct student *const ptr){
    struct node*link=(struct node*)malloc(sizeof(struct node));
    struct node *current=head;
      while(current!=NULL){
          if(current->data.id==ptr->id){
        	  printf("Error\n");
        	  return;
          }
    	  current=current->next;
      }
    link->data.id=ptr->id;
    strcpy(link->data.name,ptr->name);
    link->data.age=ptr->age;
    link->data.gpa=ptr->gpa;
    link->next=head;
    head=link;
}
void displayStudents(void){
	struct node *current=head;
	if(head==NULL){
		printf("List is empty\n");
		return;
	}
	while(current!=NULL){
		printf("Name:%s\tID:%d\tAge:%d\tGPA:%.2f\n",current->data.name,current->data.id,current->data.age,current->data.gpa);
	current=current->next;
	}
}
void searchStudentByID(int id){
	struct node *current=head;
	while(current!=NULL){
		if(current->data.id==id){
			printf("Name:%s\tID:%d\tAge:%d\tGPA:%.2f\n",current->data.name,current->data.id,current->data.age,current->data.gpa);
				return;
		}
		current=current->next;
	}
	printf("Student was not found\n");
}
void updateStudent(int id){
	struct node *current=head;
	while(current!=NULL){
		if(current->data.id==id){
				printf("Enter name :\n");
				scanf("%s",current->data.name);
				printf("Enter age :\n");
				scanf("%d",&current->data.age);
				printf("Enter gpa :\n");
				scanf("%f",&current->data.gpa);
				return;
			}
		current=current->next;
	}
	printf("Student is not found\n");
}
float calculateAverageGPA(void){
	struct node *current=head;
	int no_student=0;
	float gpa=0,av_gpa;
	if(head==NULL){
			printf("List is empty\n");
			return 0;
		}
	while(current!=NULL){
		 no_student++;
		 gpa+=current->data.gpa;
		 current=current->next;
	}
	av_gpa=gpa/no_student;
	return av_gpa;
}
void searchHighestGPA(void){
	struct node *current=head;
	struct node *max=head;
	float mx=0;
	if(head==NULL){
		printf("List is empty\n");
		return;
	}
	while(current!=NULL){
		if(mx<current->data.gpa){
			mx=current->data.gpa;
		}
		current=current->next;
	}
	while(max!=NULL){
		if(max->data.gpa==mx){
			printf("Name:%s\tID:%d\tAge:%d\tGPA:%.2f\n",max->data.name,max->data.id,max->data.age,max->data.gpa);
			return;
		}
		max=max->next;
	}
}
void deleteStudent(int id){
	struct node *current=head;
	struct node *link=head->next;
	if(head==NULL){
			printf("List is empty\n");
			return;
		}
	if(head->data.id==id){
		head=head->next;
		free(current);
		printf("success\n");
		return;
	}
	while(link!=NULL){
		if(link->data.id==id){
		    current->next=link->next;
			free(link);
			printf("success\n");
			return;
		}
		current=current->next;
		link=link->next;
	}
	printf("Student was not found\n");
}
