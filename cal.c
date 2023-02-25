#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
//create a linked list to store numbers
struct node{
   int data;
   struct node *next;
};
int main(int argc, char **argv){
	FILE* file;
	int num;
	struct node* head = NULL;
	struct node* current = NULL;
	struct node* new = NULL;
	int count2 = 0;
	int count3 = 0;
	file = fopen("numbers.txt","r");
	if(file == NULL){
		printf("Error opening file. ");
		exit(1);
	}
	while(fscanf(file,"%d",&num) != EOF){
	 new = (struct node*)malloc(sizeof(struct node));
 	 new->data = num;
	 new->next = NULL;
	 if(head == NULL){
	   head = new;
	   current = new;
	  }
         else{
	   current->next = new;
	   current = new;
	  }	 
	}
	fclose(file);
	current = head;
	pid_t pid = fork();
	if(pid < -1){
		printf("Error creating child process. ");
		exit(1);
	}
	else if(pid == 0){
		while(current != NULL){
			if(current->data %3 == 0){
				count3 += 1;
			}
			current = current->next;
		}
	}
	else{
		wait(NULL);
		current = head;
		while(current != NULL){
			if(current->data %2 == 0){
				count2 += 1;
			}
		}
	}
	printf("Numbers divisible by 3: %d\n",count3);
	printf("NUmbers divisible by 2: %d\n",count2);
	return 0;
}