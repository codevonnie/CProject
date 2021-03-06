/*  Yvonne Grealy
	G00306806
	Second Year Advanced Procedural Programming Project */

#include "header.h" //include header.h to access structs, global variables and libraries

main(){

	int mChoice=0, count; //holds user choice of menu options
	struct node *head=(struct node*)malloc(sizeof(struct node));//create head node for employees
	head->next=NULL; //set head next to null 
	readInLogin(); //call login method
	readInEmployees(head); //head takes the head value from this method which reads in employees from file
		
	while(mChoice!=7){ //while choice does not equal the exit value 7
		switch(mChoice = showMenu()) 
		{
			case 1: 
			{
				addEmployee(&head);//add an employee to the database
				break;
			}//case1
			
			case 2:
			{
				count=findEmployee(head); //find if employee exists
				if(count>=0){ //if employee exists (if count is equal or greater than 0)
					displayEmployee(head, count); //call display method
				}
				break;
			}//case2
			case 3:
			{
				count=findEmployee(head); //find if employee exists
				if(count>=0){ //if employee exists (if count is equal or greater than 0)
					updateEmployee(&head, count); //call update method
				}
				break;
			}//case3
			case 4:
			{
				count=findEmployee(head);//find if employee exists
				if(count>=0){ //if employee exists (if count is equal or greater than 0)
					deleteEmployee(&head, count); //delete a chosen employee
				}
				break;
			}//case4
			case 5:
			{
				displayByDept(&head); //display all employees by their department
				displayList(head); //print out the list of employees
				sort(&head); //sort the head back into original 
				break;
			}//case5
			case 6:
			{
				employeeReport(head); //displays employee report
				break;
			}//case6
			case 7:
			{
				writeToFile(head); //call method to write linkedlist to file
				exit(0); //exit the program
			}//case7
				
		}//switch
 	}//inner while
	
	system("pause");

}//end main

