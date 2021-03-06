/*  Yvonne Grealy
	G00306806
	Second Year Advanced Procedural Programming Project */

#include "header.h" //include header.h to access structs, global variables and libraries

void readInLogin(){ //reads in the login credentials from the login file

	
	struct lNode *lHead; //create head for login linkedlist

	if((logPtr = fopen(LOGFILE, "r")) == NULL) //if the file cannot be opened alert the user
	{
		puts("File could not be opened");
	}

	else
	{
		//create linkedlist to hold the login credentials from file
		struct lNode *lSecond;
		struct lNode *lThird;
		lHead=(struct lNode*)malloc(sizeof(struct lNode));
		lSecond=(struct lNode*)malloc(sizeof(struct lNode));
		lThird=(struct lNode*)malloc(sizeof(struct lNode));
		
		//read in login details and save to linkedlist
		fscanf(logPtr, "%s", lHead->login.username);
		fscanf(logPtr, "%s", lHead->login.password);
		
		fscanf(logPtr, "%s", lSecond->login.username);
		fscanf(logPtr, "%s", lSecond->login.password);
		lHead->next=lSecond;
		
		fscanf(logPtr, "%s", lThird->login.username);
		fscanf(logPtr, "%s", lThird->login.password);
		lSecond->next=lThird;
		lThird->next=NULL;
	}
	fclose(logPtr); //close file pointer
	loginSystem(); //call to loginSystem to print astericks to the screen instead of the password
	searchLogin(lHead); //pass head node to search for the inputed credentials in the saved credentials

}//readInLogin

void loginSystem(){ //method to get username and password and print * to screen instead of passwords chars

	char c=' ';
	int counter=0, i = 0;
	__check= false;
	
	fflush(stdin); //flush the standard input
	printf("Enter username: "); 
	scanf("%s", __username); //read in username from user
	printf("**Press Esc to exit**\n"); //alert the user that they can exit using Esc
	printf("Enter password: "); 
	//Hide password by replacing letters with *
	while (__check == false){ //if boolean value check is false...
		c=_getch(); //read in first char
		
		//Esc to exit
		if(c == 27){ //27 is ascii for the ESC key and will allow the user to exit the system

			exit(0);
		}
		//Ascii for all allowed charecters 
		else if ((c > 47 && c < 58) || (c>64 && c < 123)){ //if c is a numeric char or an upper/lowercase letter...
			__password[i] = c; //...position i of the password array is equal to c
			i++; 
			printf("*"); //print an asterisk
		}
		//Allow for character deletion 
		else if (i >= 0 && c == 8){ //if backspace key is pressed...
			i--; //...decrement i value
			printf("\b \b");
		}
		
		// Enter key pressed breaks loop
		else if (c == 13){ //13 is ascii code for return key
			__check = true; //set boolean to true to break loop
		}
	}
	printf("\n\n");
}//end loginSystem()

void searchLogin(struct lNode* lHead) //search inputed value against credentials from file
{
	int compName, compPass; //variables to compare username and password
	struct lNode *temp=(struct lNode*)malloc(sizeof(struct lNode)); //new node created for search
	temp = lHead;  //new node takes value of the head node
	
	while( temp!= NULL ) //while there are still values in the file continue loop
	{
		compName=strcmp(temp->login.username, __username); //compare username input using strcmp and store result
		compPass=strcmp(temp->login.password, __password); //compare password input using strcmp and store result

		if((compName==0)&&(compPass==0)) //if both values are 0 then they are equal and correct
		{
			free(lHead); //free up the space held by login linkedlist
			return; //return when value is found
			
		}//if 
		temp = temp->next; //otherwise go to the next value
	}//while 
	
	printf("\nIncorrect details entered\n"); //if value is not found alert the user
	loginSystem(); //return to the login method to allow user to input details again

}//end searchLogin()

struct node readInEmployees(struct node *head){ //read in employees from employee file

	struct node *temp=(struct node*)malloc(sizeof(struct node)); 
	temp=head; //temp takes value of head

	if((empPtr = fopen(EMPFILE, "rb")) == NULL) //if file can not be opened alert the user
	{
		puts("\n\n\t\t********Database file was not read in correctly********\n\n");
	}

	else{

		char data[MAXNUM]; //char array with max size 100
		(fgets(data, sizeof data, empPtr)!=NULL); //initial read from file to first node
		//parse data to the format below and read into first node
		sscanf(data, "%d %[^\,], %[^\,], %[^\,], %d %d %d %f %s", &temp->employee.employeeId, temp->employee.employeeName, temp->employee.employeeAddress, 
		temp->employee.department, &temp->employee.joined.day, &temp->employee.joined.month, &temp->employee.joined.year, &temp->employee.salary, 
		temp->employee.email);

		while(fgets(data, sizeof data, empPtr)!=NULL){ //subsequent read in from file to char array using file pointer
			struct node *newNode=(struct node*)malloc(sizeof(struct node));
			newNode->next=NULL; //set new node next to NULL because it will be at the end of the linkedlist
			//parse data to the format below and read into new node
			sscanf(data, "%d %[^\,], %[^\,], %[^\,], %d %d %d %f %s", &newNode->employee.employeeId, newNode->employee.employeeName, newNode->employee.employeeAddress, 
			newNode->employee.department, &newNode->employee.joined.day, &newNode->employee.joined.month, &newNode->employee.joined.year, &newNode->employee.salary, 
			newNode->employee.email);
						
			temp->next=newNode; //temp next points to newNode
			temp=temp->next;
		}
	}
	
	fclose(empPtr); //close file
	
	
}//end readInEmployees

void sort(struct node** head){ //sorts employees from lowest ID number to highest

	__check = false; 
	if (*head == NULL || (*head)->next == NULL) //if the list is empty or there is only one entry, do not sort
		return;

	while (!__check) {
		struct node **prev = head;// pointer to head elements
		struct node *temp = *head;// temp pointer takes head pointer 
		struct node *after = (*head)->next; //after pointer points to node after head

		__check = true;
		while (after) {

			if (temp->employee.employeeId > after->employee.employeeId) { //if node 1 is greater than node 2
				temp->next = after->next; //temp next takes value of after next
				after->next = temp; //after next now points to temp
				*prev = after; //previous pointer points to after value

				__check = false;
			}
			prev = &temp->next; //previous takes address of temp next
			temp = after; //temp takes after pointer
			after = after->next; //after points to after next node
		}
	}
}//sort

int showMenu(){ //method to display user menu

	int mChoice=0;
	do //print the menu below and ask for user input until number 1-7 is entered
	{
		system("cls");
		printf("\t\t\t\t******************\n\n\t\t\t\t    Employee Database\n\n\t\t\t\t******************\n\n\n");
		printf("\n\n\t\t\t\t 1. Add Employee");
		printf("\n\n\t\t\t\t 2. Display Employee Details");
		printf("\n\n\t\t\t\t 3. Update Employee");
		printf("\n\n\t\t\t\t 4. Delete Employee");
		printf("\n\n\t\t\t\t 5. Display all Employees by Department");
		printf("\n\n\t\t\t\t 6. Display Employee Report");
		printf("\n\n\t\t\t\t 7. Exit");
		printf("\n\n\n\t Enter a valid option: ");
		scanf("%d", &mChoice);
		fflush(stdin);
	}while( (mChoice < 1) || (mChoice > 7) );
	return(mChoice); //return user choice
		
}// end showMenu

void addEmployee(struct node** head){ //add employee to linkedlist

	struct node *newEmp=(struct node*)malloc(sizeof(struct node));
	struct node *temp=(struct node*)malloc(sizeof(struct node));
	int d,m,y; //values to read in date
	int leapyr=0; //leapyear value
	char* search, search1; //pointers for email validation
	temp=*head; //temp becomes head pointer
	__check=false;
			
	//ask for user id and check that it is not already in use
	while(!__check){ //keep asking for id until one that is not in use is entered
	
		struct node *checkID=*head; 
		printf("\nEnter Employee Number: ");
		scanf("%d", &newEmp->employee.employeeId); //read in id
		fflush(stdin);
		while(checkID!=NULL){ //go through each node in the list
			if(checkID->employee.employeeId==newEmp->employee.employeeId){ //if stored employee id equals inputted id, alert user
				printf("\n\n\t\t********Sorry that employee ID is already in use********\n\n");
				__check=false; //loop will be repeated
			}
			else{
				__check=true; //if id is not found, set to true to break loop
			}
			checkID=checkID->next; //check next node in linkedlist
		}
	}
	__check=false; //reset to false
	printf("\nEnter Employee Name: ");
	scanf("%30[^\n]s", newEmp->employee.employeeName); //continue reading after spaces in name
	fflush(stdin);
	printf("\nEnter Employee Address: ");
	scanf("%40[^\n]s", newEmp->employee.employeeAddress); //continue reading after spaces in address
	fflush(stdin);
	printf("\nEnter Employee Department: ");
	scanf("%20[^\n]s", newEmp->employee.department); //continue reading after spaces in department
	fflush(stdin);
	while(!__check){
		printf("\nEnter Employee Join Date (dd mm yyyy): ");
		scanf("%d %d %d", &d, &m, &y); //read in day, month and year
		
		if(y % 400==0 || (y%100 !=0 && y%4==0)){ //if either condition is true, set leapyear
			leapyr=1;
		}
		if(y>1970){ //only enter loop if year is greater than given year
			
			if((m==1) || (m==3) || (m==5) || (m==7) || (m==8) || (m==10) || (m==12)){ //if month is equal to any value here, days should be 31 days or less
				if(d<=31){
					__check=true;
				}
				else{
					printf("\n\n\t\t********Invalid date entered********\n\n");
				}
			}
			else if(m==4 || m==6 || m==9 || m==11){ //if month is equal to any value here, days should be 30 days or less
				if(d<=30){
					__check=true;
				}
				else{
					printf("\n\n\t\t********Invalid date entered********\n\n");
				}
			}
			else if(m<0 || m>12){
				__check=false;
				printf("\n\n\t\t********Invalid date entered********\n\n");
			}
		
			else{
				if(leapyr==1){ //if leapyear is set, days can be 29 days or less
					if(d<=29){
						__check=true;
					}
				}
				else if(leapyr==0){ //if leapyear is not set, days can be 28 days or less
					if(d<=28){
						__check=true;
					}
				}
		
			}
		}
		else{
			printf("\n\n\t\t********Invalid date entered********\n\n");
		}
		fflush(stdin);
		leapyr=0; //reset leapyear
	}
	//once date is validated it can be added to newEmp node
	newEmp->employee.joined.day=d; 
	newEmp->employee.joined.month=m;
	newEmp->employee.joined.year=y;

	__check=false; //reset to false
	fflush(stdin);
	printf("\nEnter Employee Salary: ");
	scanf("%f", &newEmp->employee.salary); //read in salary
	
	while(__check==false){ //check for valid email address
		
		fflush(stdin);
		printf("\nEnter Employee email: ");
		scanf("%40s", newEmp->employee.email); //read in email address

		search=strpbrk(newEmp->employee.email, "@"); //if email address does not contain @ symbol, search will be null
		search1=strstr(newEmp->employee.email, ".com"); //if email address does not contain ".com" string, search1 will be null
		if(search && search1){ //while search and search1 are not null allow loop to break
			__check=true;
		}
		else{
			printf("\n\n********Invalid email entered. Please enter a valid email address********\n\n");//else alert user and retry
		}

	}
	//if the list is empty or the head node ID is greater than input, set newEmp as head
	if(temp == NULL || temp->employee.employeeId > newEmp->employee.employeeId) 
	{
		newEmp->next=temp;
		temp=newEmp;
	}
	else{
		//while not at the end of the list and node is smaller than newEmp ID, go to next node until correct insertion point is found
		while(temp->next!=NULL && temp->next->employee.employeeId < newEmp->employee.employeeId)
		{
			temp=temp->next;
		}
		//insert newEmp at correct node and point correct node to it
		newEmp->next = temp->next;
		temp->next = newEmp;
	}//else
	

	//print out new employee details and alert user that they have added employee
	printf(" ID: %d\n Name: %s\n Address: %s\n Department: %s\n Join date: %d/%d/%d\n Salary: %.2f\n Email: %s \n\n", newEmp->employee.employeeId, newEmp->employee.employeeName, newEmp->employee.employeeAddress,
				newEmp->employee.department, newEmp->employee.joined.day, newEmp->employee.joined.month, newEmp->employee.joined.year,
				newEmp->employee.salary, newEmp->employee.email); 
 	printf("\n\n\t\t********Employee added successfully********\n\n");

	system("pause");

}//end addEmployee()

int findEmployee(struct node *head){ //method to check if employee exists for use with displaying, updating and deleting employees methods

	char empDetails[30], choice; //employee details (name or id) to be stored in array
	int compName, empID, count=0;
	struct node *temp=(struct node*)malloc(sizeof(struct node));
	__check=false; //boolean check if emp has been found
	temp=head; //temp struct takes head values
	printf("Enter Employee ID or Name: ");
	scanf("%30[^\n]s", empDetails); //take in employee details from user
	empID=atoi(empDetails); //make int value from user input to check if it is an int value
	
	while((temp!=NULL)&&(!__check)) //loop while there are still nodes in the linkedlist and while the value has not been found
	{
		compName=strcmp(temp->employee.employeeName, empDetails); //compare employee name with details added by user

		if((compName==0)||(temp->employee.employeeId==empID)){ //if string compare results is 0 or if the id in the current node is equal to user input, return count to caller
			
				__check=true; //change boolean check to true
				return count;
		}
		else{ //if value not found go to next value in linkedlist
			temp=temp->next;
		}
		count++; //increment count (used to get to correct node later)
	}

	if(!__check){ //if after search check is still false tell the user the employee could not be found

		printf("\n\n\t\t********Employee could not be found********\n\n");
		count=-1; //next method will only use count if it is 0 or greater
	}
	system("pause");
	return count; //return dud value to caller
	
}//findEmployee()

void displayEmployee(struct node *head, int count){ //display employee details if employee was found in previous method

	struct node *temp=(struct node*)malloc(sizeof(struct node));
	int i;
	temp=head; //temp takes values of head

	for(i=0; i<count;i++){ //loop goes to the node that was found to contain employee in prev method
		temp=temp->next;
	}
	//print out emp details to user
	printf(" ID: %d\n Name: %s\n Address: %s\n Department: %s\n Join date: %d/%d/%d\n Salary: %.2f\n Email: %s \n\n", temp->employee.employeeId, temp->employee.employeeName, temp->employee.employeeAddress,
			temp->employee.department, temp->employee.joined.day, temp->employee.joined.month, temp->employee.joined.year,
			temp->employee.salary, temp->employee.email); 
		
	system("pause");

}//end displayEmployee

void updateEmployee(struct node **head, int count){ //update employee as selected by user using count from findEmployee method

	struct node *temp=(struct node*)malloc(sizeof(struct node));
	int i;
	char choice=' ';
	__check=false;
	temp=*head; //temp gets pointer address for head of linkedlist

	for(i=0; i<count;i++){//loop goes to the node that was found to contain employee in prev method
		temp=temp->next;
	}
	
	while(!__check){ //while check is false continue looping

		//print out selected employee
		printf(" ID: %d\n Name: %s\n Address: %s\n Department: %s\n Join date: %d/%d/%d\n Salary: %.2f\n Email: %s \n\n", temp->employee.employeeId, temp->employee.employeeName, temp->employee.employeeAddress,
					temp->employee.department, temp->employee.joined.day, temp->employee.joined.month, temp->employee.joined.year,
						temp->employee.salary, temp->employee.email); 
		
		printf("Do you wish to change employee Address, Department or Salary? (e to exit)");
		scanf(" %c", &choice); //get user to input which detail they wish to change or e to exit
		fflush(stdin); //flush buffer

		switch(choice)//using user choice
		{
			case 'a':
			case 'A': //upper or lowercase A for address
				{
						printf("Please enter amended address: ");
						scanf("%40[^\n]s", &temp->employee.employeeAddress); //get input of amended address and overwrite previous employee address in node
						__check=true; //set check to true
						break; //break from switch
				}
			case 'd':
			case 'D': //upper or lowercase D for department
				{	
						printf("Please enter amended department: ");
						scanf("%15[^\n]s", &temp->employee.department); //get input of amended department and overwrite previous employee department in node
						__check=true; //set check to true
						break; //break from switch
				}
			case 's':
			case 'S':
				{
						printf("Please enter emended salary: ");
						scanf("%f", &temp->employee.salary); //get input of amended salary and overwrite previous employee salary in node
						__check=true; //set check to true
						break; //break from switch
				}
			case 'e':
			case 'E':
				{
						return; //exit method if user enters upper or lowercase E
				}
			default:
				{		//tell the user if they input an invalid entry and loop back over the while loop
						printf("\n\n\t\t********Sorry that is not a valid option********\n\n");
					
				}

		}//end switch
	}//end while
	printf("\n\n\t\t********Employee details updated successfully********\n\n"); //confirm that the user has amended the details
	system("pause");
}//updateEmployee

void deleteEmployee(struct node **head, int count){ //delete employee inputted by user and found in findEmployee method

	struct node *temp1=(struct node*)malloc(sizeof(struct node)); 
	struct node *temp2=(struct node*)malloc(sizeof(struct node)); 
	int i;
	temp1 = *head; //temp1 gets address of head of linkedlist
	if(count==0){ //if the node to be deleted is at the start of the linkedlist use this code
		*head=temp1->next; //head points to the value pointed to by temp1
		free(temp1); //temp1 is freed from memory
		printf("\n\n\t\t********Employee Deleted********\n\n"); //confirm to user that employee has been deleted
		system("pause");
		return; //exit method
	}
	 
	for(i=0; i<count-1;i++){ //if it is not the first node that is required use loop to get to the node before the node to be deleted
		temp1=temp1->next;
	}

	temp2=temp1->next; //temp2 takes value of the node for deletion
	temp1->next=temp2->next; //temp1 now points to what temp2 used to point to
	free(temp2); //temp2 is freed from memory

	printf("\n\n\t\t********Employee Deleted********\n\n");//confirm to user that employee has been deleted
	system("pause");

}//deleteEmployee

void displayByDept(struct node **head){

	struct node **prev=head;
	int compare; //save strcmp value
	__check=false;

	if(*head==NULL || (*head)->next == NULL) //if list is empty
		return;
	
	while(!__check){ //while check is false
		struct node *temp=*head;
		struct node *node = (*head)->next;
		//**prev=head;
		__check=true; //check is true

		while(node){ //while curr is not null
			compare=strcmp(temp->employee.department,node->employee.department);
			if(compare>0){ //if temp dept is greater than curr dept
				temp->next=node->next; //temp next is now curr next
				node->next=temp; //curr next points to temp
				*prev=node; //prev is equal to curr
				__check=false; //check is false
			}//if
			prev=&temp->next;
			temp=node; //temp is equal to curr
			node=node->next; //curr is equal to curr next
		}
	}

}//displayByDept

void employeeReport(struct node *head){

	struct dnode *dept=(struct dnode*)malloc(sizeof(struct dnode));
	struct node *temp=(struct node*)malloc(sizeof(struct node));
	struct node *check=(struct node*)malloc(sizeof(struct node));
	int yrsEmployeed; // to store years employeed
	char buffer[5]; // strftime function - buffer to hold year
	int compare, i, cmpExisting;
	int count=1;
	FILE *stPtr; // file pointer
	time(&curtime); //current time
	dept->next=NULL;
	temp=head;

	//inital read
	strcpy(dept->department.departName, temp->employee.department); //copy the name of the department into departmentName 
	dept->department.numOfEmployees=1; //add  employee to department
	dept->department.totalSalary=temp->employee.salary;//add  employee salary to totalsalary
	info = localtime( &curtime ); //get local time
	strftime(buffer,5,"%Y", info); //store year into buffer

	if(buffer-temp->employee.joined.year<5){ //if employee has worked for less than 5 years give 3% of salary bonus
		
		dept->department.totalBonus=temp->employee.salary*.03;
	}
	else if(buffer-temp->employee.joined.year>=5 && buffer-temp->employee.joined.year<=10){ //if employed for 5+ years and less than 10 give 4% salary bonus

		dept->department.totalBonus=temp->employee.salary*.04;
	}
	else{
		dept->department.totalBonus=temp->employee.salary*.05; //if employed for over 10 years give 5% bonus
	}
	dept->department.totalOutlay=dept->department.totalBonus+dept->department.totalSalary;

	check=head->next; //check is equal to head next so not to compare with self

	while(check!=NULL){

			compare=strcmp(dept->department.departName, check->employee.department); //compare current department name with check department name
			if(compare==0){ //if they are equal add details to dept node
				dept->department.numOfEmployees++; //increment number of employees
				dept->department.totalSalary+=check->employee.salary;//add employee salary to totalsalary
				info = localtime( &curtime ); //get local time
				strftime(buffer,5,"%Y", info); //store year into buffer

				if(buffer-check->employee.joined.year<5){ //if employee has worked for less than 5 years give 3% of salary bonus
		
					dept->department.totalBonus+=check->employee.salary*.03; //add to current total
				}
				else if(buffer-check->employee.joined.year>=5 && buffer-check->employee.joined.year<=10){ //if employed for 5+ years and less than 10 give 4% salary bonus

					dept->department.totalBonus+=check->employee.salary*.04;//add to current total
				}
				else{
					dept->department.totalBonus+=check->employee.salary*.05; //if employed for over 10 years give 5% bonus
				}
				dept->department.totalOutlay=dept->department.totalBonus+dept->department.totalSalary; //total outlay is equal to totalBonus and totalSalary
			}
			
			check=check->next; //go to next employee
			
		}//inner while
		temp=temp->next;

	//subsequent read for all other employees
		while(temp!=NULL){ 

			struct dnode *newNode=(struct dnode*)malloc(sizeof(struct dnode));
			count++;
			newNode->next=NULL;
			strcpy(newNode->department.departName, temp->employee.department); //copy the name of the department into departmentName 
			newNode->department.numOfEmployees=1; //add  employee to department
			newNode->department.totalSalary=temp->employee.salary;//add  employee salary to totalsalary
			info = localtime( &curtime ); //get local time
			strftime(buffer,5,"%Y", info); //store year into buffer

			if(buffer-temp->employee.joined.year<5){ //if employee has worked for less than 5 years give 3% of salary bonus
		
				newNode->department.totalBonus=temp->employee.salary*.03;
			}
			else if(buffer-temp->employee.joined.year>=5 && buffer-temp->employee.joined.year<=10){ //if employed for 5+ years and less than 10 give 4% salary bonus

				newNode->department.totalBonus=temp->employee.salary*.04;
			}
			else{
				newNode->department.totalBonus=temp->employee.salary*.05; //if employed for over 10 years give 5% bonus
			}
			newNode->department.totalOutlay=newNode->department.totalBonus+newNode->department.totalSalary;

			check=head;

			for(i=0; i<count;i++){//loop goes to the next node after current
					check=check->next;
				}
		
		while(check!=NULL){

			compare=strcmp(newNode->department.departName, check->employee.department);
			if(compare==0){
				newNode->department.numOfEmployees++;
				newNode->department.totalSalary+=check->employee.salary;//add  employee salary to totalsalary
				info = localtime( &curtime ); //get local time
				strftime(buffer,5,"%Y", info); //store year into buffer

				if(buffer-check->employee.joined.year<5){ //if employee has worked for less than 5 years give 3% of salary bonus
		
					newNode->department.totalBonus+=check->employee.salary*.03;//add to current total
				}
				else if(buffer-check->employee.joined.year>=5 && buffer-check->employee.joined.year<=10){ //if employed for 5+ years and less than 10 give 4% salary bonus

					newNode->department.totalBonus+=check->employee.salary*.04;//add to current total
				}
				else{
					newNode->department.totalBonus+=check->employee.salary*.05; //if employed for over 10 years give 5% bonus
				}
				newNode->department.totalOutlay=newNode->department.totalBonus+newNode->department.totalSalary;//total outlay is equal to totalBonus and totalSalary
			}
			
			check=check->next; //go to next employee
			
		}//inner while
		__check=deleteDuplicates(&dept, newNode); //call method to check there are no duplicate department nodes and pass dept list and newNode
		if(__check!=true){ //if method returns false then node is added to linked list or if true node is not added to linked list
			newNode->next = dept->next;
			dept->next = newNode;
		}
		temp=temp->next;  //go to next employee
	}//outer while
	
	if((stPtr=fopen("departments.txt", "w"))==NULL){ //try to open file and alert user if it can't be
		puts("\n\n\t\t********Could not write to file********\n\n");
	}
	else{//if file can be opened
		while(dept!=NULL){ // write all nodes in linked list

			fprintf(stPtr, " Department: %s\n No. of Employees: %d\n Total Salary: %.2f\n Total Bonus: %.2f\n Total Outlay: %.2f\n\n", dept->department.departName, dept->department.numOfEmployees, 
				dept->department.totalSalary, dept->department.totalBonus, dept->department.totalOutlay);
			printf(" Department: %s\n No. of Employees: %d\n Total Salary: %.2f\n Total Bonus: %.2f\n Total Outlay: %.2f\n\n", dept->department.departName, dept->department.numOfEmployees, 
				dept->department.totalSalary, dept->department.totalBonus, dept->department.totalOutlay);
			dept = dept->next; 
		}
		fclose(stPtr); //close file
	}
	system("pause");
}//employeeReport

boolean deleteDuplicates(struct dnode **head, struct dnode *newNode){ //method to check for duplicates in department report list

	struct dnode *temp=*head;
	struct dnode *newN=newNode;
	int compare;
	
	while(temp!=NULL){ //check all nodes in dept linked list
		compare=strcmp(temp->department.departName, newN->department.departName); //compare existing dept list names with newNode name

		if(compare==0){ //if they are equal return true and newNode will not be added to dept linked list
			return true;
		}
		temp=temp->next;
	}

	return;
}

void writeToFile(struct node *head){ //method to write employee linked list to file

	struct node *temp=head;
	FILE *stPtr; //file pointer
	if((stPtr=fopen("Employees.txt", "w"))==NULL){
		puts("\n\n\t\t********Could not write to file********\n\n"); //if file can't be opened alert user
	}
	else{
		while( temp!= NULL ){ //print each node in linked list
			fprintf(stPtr, "%d %s,%s,%s, %d %d %d %.2f %s\n", temp->employee.employeeId, temp->employee.employeeName, 
				temp->employee.employeeAddress,	temp->employee.department, temp->employee.joined.day, temp->employee.joined.month, temp->employee.joined.year,
				temp->employee.salary, temp->employee.email); 
			temp = temp->next; 
		}
	}
	fclose(stPtr); //close file pointer
	printf("\n\n********Your changes have been saved to file********\n\n");//tell user file has been written successfully
	system("pause");

}//writeToFile

void displayList(struct node* head){ //method to employee details

	struct node *temp; 
	temp =(struct node*)malloc(sizeof(struct node)); 
	temp = head; 
	while( temp!= NULL ){//loop for each node of linked list
		printf(" Department: %s\n ID: %d\n Name: %s\n Address: %s\n Join date: %d/%d/%d\n Salary: %.2f\n Email: %s \n\n", temp->employee.department, temp->employee.employeeId, 
			temp->employee.employeeName, temp->employee.employeeAddress, temp->employee.joined.day, temp->employee.joined.month, temp->employee.joined.year,
						temp->employee.salary, temp->employee.email); 
		temp = temp->next; 
	}

	system("pause");
	
}

