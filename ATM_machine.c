#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//Account structure
typedef struct account_details {
	char name[60];
	int pin;
	int cash;
}account;
//global variable so the present account can be used through out the program
account present_account; //account being used currently

int account_no;	//account no is the location in the data base array where the required account is located
FILE* accounts_ptr = NULL; //file pointor for the acount details file
FILE* summary_ptr = NULL; //file pointor for the summary file
account data_base[50]; //data base to store all accounts from accounts file (Max 50)

time_t t;
int account_counter = 0; //counter to keep check of accounts in the data base array and control the loop and avoid extra iterations

void file_open(int a);//1:append mode or file creation mode   //function to open the files
void file_close(); //closes all files and flushes the file pointors
void account_creation(); //function to deal with account creation stuff
void account_withdrawl(); //function for maintaining the balance regarding account cash withdraw
void account_deposit(); //function for maintaining the balance regarding account cash deposit
void account_balance(); //function for checking balance of account
void account_summary(); //function to show the summary / transaction details of the account since account creation
int account_validation( int); //function to check if the user entered account is a valid account and to get the data in case of a valid account
										//type 1 = new account username check
										//type 2 = old account find


//this function takes all the data from accounts file and stores in data base array
void get_data()
{
	accounts_ptr = fopen("Summary.txt","r"); //opens file in read mode
	char filechar = fgetc(accounts_ptr); //character to check for eof

	while ((filechar != EOF))
	{
		if (filechar == '\n') { //takes data stored at each nenw line

			fscanf(accounts_ptr, "\n%s %d %d", &data_base[account_counter].name, &data_base[account_counter].pin, &data_base[account_counter].cash);

			account_counter++; //counter to keep check of accounts in database array

		}

		filechar = fgetc(accounts_ptr); //takes next character
	}
	fclose(accounts_ptr); //closing file after taking data
	fflush(accounts_ptr);
}

//this function over writes the data in the accounts file with the new updated data
void put_data()
{
	accounts_ptr= fopen("Summary.txt", "w"); //opens file in write mode
	for (int i = 0; i < account_counter; i++)
	{
		fprintf(accounts_ptr,"\n%s %d %d", data_base[i].name, data_base[i].pin, data_base[i].cash);

	}
	fclose(accounts_ptr);//cosing the file
	fflush(accounts_ptr);
}

//main fuction
int main() {

	file_open(0); //opens and closes files so files can be created if they are not present

	get_data(); //gets data from file to data base array
	int choice = 6; //initializing choice variable to take user input
	time(&t);

	printf("\nWelcome to Shreya's Atm\t\t\t\t %s\n", ctime(&t));

	printf("\nTo access the facilities. Kindly Navigate through the given options.\n");

	printf("\n1.Account Creation\n2.Balance Check\n3.Cash Withdrawl\n4.Cash Deposit\n5.Account Statement\n6.Exit\n"); //prints available options to the user

	printf("\n\7Enter Choice : ");
	scanf("%d", &choice); //user inputs choice (1-6)

	file_open(5); //opens the summary file in append mode so it can be appended during runtime

	while (choice != 6) //loop to keep execting the program until user decides to exit
	{
		switch (choice) //choice statement to run the functions according to user request
		{

		case (1)://Account creation
		{
			system("cls");
			printf("\nWelcome to Account Creation\t\t\t\t %s\n", ctime(&t));
			account_creation(); //sends control to accounts function
			printf("\nPress Any Key To Continue!!");
			getchar();
			getchar();
			break;
		}


		case (2)://Balance Check
		{
			system("cls");
			printf("\nWelcome to Balance Check\t\t\t\t %s\n", ctime(&t));
			account_balance(); //sends control to balance check function
			printf("\nPress Any Key To Continue!!");
			getchar();
			getchar();
			break;
		}
		case(3)://Cash Withdrawl
		{
			system("cls");
			printf("\nWelcome to Cash Withdrawl\t\t\t\t %s\n", ctime(&t));
			account_withdrawl(); //sends control to cash withdrawl function
			printf("\nPress Any Key To Continue!!");
			getchar();
			getchar();
			break;
		}
		case(4)://Cash deposit
		{
			system("cls");
			printf("\nWelcome to Cash Deposit\t\t\t\t %s\n", ctime(&t));
			account_deposit(); //sends control to cash deposit function
			printf("\nPress Any Key To Continue!!");
			getchar();
			getchar();
			break;
		}

		case(5)://Account Statement
		{
			system("cls");
			printf("\nWelcome to Account Statement\t\t\t\t %s\n", ctime(&t));
			account_summary(); //sends control to account summary function
			printf("\nPress Any Key To Continue!!");
			getchar();
			getchar();
			break;
		}

			default: //To cater the wrong input
			{

				printf("\n Wrong Input. Try again.");
				printf("\n\7Press any key to retry ");


				break;
			}
		}



		system("cls"); //clear screen

		time(&t); //updates the time and date
		printf("\nWelcome to Nust Atm\t\t %s\n", ctime(&t));

		printf("\nTo access the facilities. Kindly Navigate through the given options.\n");

		printf("\n1.Account Creation\n2.Balance Check\n3.Cash Withdrawl\n4.Cash Deposit\n5.Account Statement\n6.Exit\n");

		printf("\n\7Enter Choice : "); //retakes input for next action
		scanf("%d", &choice);

		//exits if user inputs "6"
	}
	put_data(); //writes the updated data into the accounts file
	file_close(); //closes any files that might not be closed during above functions

	return 0;
}
//file open funtion
void file_open(int a) {
	//0:file check / creation		(any other number):opeining summary

	if (a == 0) {
		accounts_ptr = fopen("Summary.txt", "a+"); //opens/creates accounts file
		if (accounts_ptr == NULL)
		{
			printf("Error Opening Accounts File"); //accounts pointer error handling
		}
		summary_ptr = fopen("Summary.txt", "a+");  //opens/creates summary file
		if (summary_ptr == NULL)
		{
			printf("Error Opening Summary File"); //Summary pointer error handling
		}
		file_close();	//closing files after they are created


	}
	else  //opening the summary file for appending new transaction details
	{
		summary_ptr = fopen("Summary.txt", "a+");

		summary_ptr = fopen("Summary.txt", "a+");
		if (summary_ptr == NULL)
		{
			printf("Error Opening Summary File"); //Summary pointer error handling
		}
	}


}

//file close functions
void file_close() {

	//closing all files and flushing the pointors (just to be sure)
	fclose(accounts_ptr);
	fflush(accounts_ptr);
	fclose(summary_ptr);
	fflush(summary_ptr);

}

//account validation fuction
int account_validation( int type) {

	//compares user input account to the database to check for any duplicates

	//type 1 = new account username check
	//type 2 = old account find

	//flag to return the results of check
	int flag = 0;
	//counter to calculate the required account number in database
	int i = 0;
	//loop to compare usernames in the database with the user input username
	for ( i = 0; i <= account_counter; i++)
	{
		if (strcmp(present_account.name, data_base[i].name) == 0) {
			flag++; //flag is raised and loop breaks if the username is founf in database
			break;
		}

	}
	if ((flag>0) && (type==2)){
		present_account = data_base[i]; //the data from that position is stored in present account variable so it can be used for the required function
		account_no = i;	//account number is stored so it can be used for updating the data in the database in the end

	}


	return flag; //returns the flang. It is non zero if the account is found
}

//account creation function
void account_creation()
{
	//shows the guidelines of the username to create an account

	printf("\n User name should be :\n\n 1.Case Sensitive\t\t 2.Should not contain spaces.\n\n");

	printf("\nEnter Username : "); //takes user name as input and stores it in the global variable (present account [name])
	scanf("%s", &present_account.name);


	while (account_validation( 1) != 0) //in case the username exists in the database, non zero flag is returned
	{
		printf("\nTry Again \n"); //retakes the username from user and validates it
		printf("\nEnter UserName: ");
		scanf("%s", &present_account.name);
	}

	printf("\nUsername can be used.");
	file_close(); //closes the files
	file_open(1);//opens the summary file in append mode

	//inputs pin and cash from user

	printf("\n Enter Pin: ");
	scanf("%d", &present_account.pin);
	printf("\n Input Cash: ");
	scanf("%d", &present_account.cash);
	while (present_account.cash % 500 != 0) //checks if cash is multiply of 500
	{
		printf("\nPlease Enter a multiple of 500\n");
		printf("\n Input Cash: ");
		scanf("%d", &present_account.cash);
	}


	//adds the account to the data base in the last position

	data_base[account_counter]= present_account;

	account_counter++; //increases the account counter

	printf("\nAccount Created Sucessfully\n");

	//stores the new transaction history in the summary file

	fprintf(summary_ptr, "\n %s Type : Account Creation  Amount: %d  Time: %s  \n", present_account.name, present_account.cash, ctime(&t));

	// closes and saves the summary file so the latest transaction data can be used again without exiting the program
	file_close();

}

//function to withdraw cash
void account_withdrawl()
{
	//initialization of variables
	int pin_counter = 1;
	int temp_pin = NULL;
	int withdraw_amount = 0;

	//takes username from the user

	printf("\nEnter Username :");
	scanf("%s", present_account.name);

	//checks if username is in the database. If it exists, the data of the user is retrieved and stored in "present account" variable so it can be used
	while (account_validation( 2) == 0)
	{
		printf("\nUser Not found\n");
		printf("\nEnter UserName: ");
		scanf("%s", &present_account.name);
	}

	//gives user 3 tries to input pin. It exits if the pin is entered wrong 3 times
	while ((present_account.pin != temp_pin) && (pin_counter <= 3))
	{
		printf("\n 3 tries allowed for Pin,\nThis is try %d.\n", pin_counter);
		printf("\nEnter Pin : ");
		scanf("%d", &temp_pin);
		pin_counter++;
	}

	//continues the operation if correct pin is entered
	if ((present_account.pin == temp_pin) && (pin_counter <= 3))
	{
		//displays the balance
		printf("\nBalance: %d ", present_account.cash);

		//asks for the withdraw account

		printf("\nEnter withdraw amount: ");
		scanf("%d", &withdraw_amount);

		//checks if withdraw account is less than or equal to balance. Also if it is a multiple of 500

		while ((withdraw_amount > present_account.cash) || (present_account.cash % 500 != 0))
		{
			while (present_account.cash % 500 != 0) //incase it is not the multiple of 500
			{
				printf("\nPlease Enter a multiple of 500\n");
				printf("\nEnter withdraw amount: ");
				scanf("%d", &withdraw_amount);

			}
			if (withdraw_amount > present_account.cash) //incase it is more than the available balance
			{
				printf("\nNot Enough balance");
				printf("\nTry Again or Enter 0");
				printf("\nEnter withdraw amount: ");
				scanf("%d", &withdraw_amount);

			}

		}

		//the present account cash is updated by subtracting the withdraw amount from it
		present_account.cash = (present_account.cash - withdraw_amount);
		//updates the present account in the database
		data_base[account_no] = present_account;

		//prints the remaining balance in the program
		printf("\nRemaining Balance : %d\n", present_account.cash);
		printf("\a\nCollect Your Cash\n");
		printf("\a\nThanks For Your vist.\n");

		//updating transaction data in the summary file
		file_open(1);
		fprintf(summary_ptr, "\n %s Type : Withdrawl  Amount: %d Balance: %d Time: %s  \n", present_account.name, withdraw_amount, present_account.cash, ctime(&t));
		file_close();
	}
}

//function to deposit cash
void account_deposit() {

	//initialization of variables
	int pin_counter = 1;
	int temp_pin = NULL;
	int deposit_amount = 0;

	//taking username input and validating it
	//checks if username is in the database. If it exists, the data of the user is retrieved and stored in "present account" variable so it can be used
	printf("\nEnter Username :");
	scanf("%s", present_account.name);
	while (account_validation( 2) == 0)
	{
		printf("\nUser Not found\n");
		printf("\nEnter UserName: ");
		scanf("%s", &present_account.name);
	}

	//gives user 3 tries to input pin. It exits if the pin is entered wrong 3 times
	while ((present_account.pin != temp_pin) && (pin_counter <= 3))
	{
		printf("\n3 tries allowed for Pin.\nThis is try %d.\n", pin_counter);
		printf("\nEnter Pin : ");
		scanf("%d", &temp_pin);
		pin_counter++;
	}


	//continues the operation if correct pin is entered
	if ((present_account.pin == temp_pin) && (pin_counter <= 3))
	{
		//displays the balance
		printf("\nBalance: %d ", present_account.cash);

		//inputs deposit amount
		printf("\nEnter deposit amount: ");
		scanf("%d", &deposit_amount);

		//checks if it is multiple of 500
		while (present_account.cash % 500 != 0)
		{
			printf("\nPlease Enter a multiple of 500\n");
			printf("\nEnter withdraw amount: ");
			scanf("%d", &deposit_amount);
		}

		//updates the cash in present account by addition
		present_account.cash = (present_account.cash + deposit_amount);
		//updates present account data in the database
		data_base[account_no] = present_account;
		//displays the new balance
		printf("\nNew Balance : %d\n", present_account.cash);
		printf("\a\nThanks For Your vist.\n");

		//updates transaction details in the summary file
		file_open(3);
		fprintf(summary_ptr, "\n %s Type : Deposit  Amount: %d Balance: %d Time: %s  \n", present_account.name, deposit_amount, present_account.cash, ctime(&t));
		file_close();
	}
}
void account_balance()
{
	int pin_counter = 1;
	int temp_pin = NULL;

	//taking username input and validating it
	//checks if username is in the database. If it exists, the data of the user is retrieved and stored in "present account" variable so it can be used

	printf("\nEnter Username :");
	scanf("%s", present_account.name);
	while (account_validation( 2) == 0)
	{
		printf("\nUser Not found\n");
		printf("\nEnter UserName: ");
		scanf("%s", &present_account.name);
	}

	//gives user 3 tries to input pin. It exits if the pin is entered wrong 3 times

	while ((present_account.pin != temp_pin) && (pin_counter <= 3))
	{
		printf("\nThis is try %d. 3 tries allowed for Pin\n", pin_counter);
		printf("\nEnter Pin : ");
		scanf("%d", &temp_pin);
		pin_counter++;
	}

	//if the pin is correct then the balance is displayed
	if ((present_account.pin == temp_pin) && (pin_counter <= 3))
	{
		printf("\nBalance: %d ", present_account.cash);
	}
	printf("\a\nThanks For Your vist.\n");

}
void account_summary() {
	int pin_counter = 1;
	int temp_pin = NULL;
	account temp;

	//taking username input and validating it
	//checks if username is in the database. If it exists, the data of the user is retrieved and stored in "present account" variable so it can be used

	printf("\nEnter Username :");
	scanf("%s", present_account.name);
	while (account_validation( 2) == 0)
	{
		printf("\nUser Not found\n");
		printf("\nEnter UserName: ");
		scanf("%s", &present_account.name);
	}

	//gives user 3 tries to input pin. It exits if the pin is entered wrong 3 times

	while ((present_account.pin != temp_pin) && (pin_counter <= 3))
	{
		printf("\nThis is try %d. 3 tries allowed for Pin\n", pin_counter);
		printf("\nEnter Pin : ");
		scanf("%d", &temp_pin);
		pin_counter++;
	}

	//continuues operation if the pin is correct

	if ((present_account.pin == temp_pin) && (pin_counter <= 3))
	{
		//closes the open files so any data can be saved
		file_close();
		//opens the summary file with the latest data
		file_open(2);

		printf("\n Account Summary.\n\n");

		//variable to check for EOF
		char filechar = fgetc(summary_ptr);

		/*
		*  logic:	The transaction data of each account is stored in the same file. Each line begins with the name of the account.
		*			The algo first reads the name of the account and stores it in a temporary variable. If the temporary variable is
		*			equal to the required account name. The it prints all the data written in that line. It reads till the end of file
		*			as data is stored according to transaction time. In this way it keeps on displaying the data for the required person
		*
		*/

		while ((filechar != EOF))
		{

			if (filechar == '\n') // reads data only if the file pointor is at a new line to avoid any anamolies
			{
				char data[500] = {0}; //initializes the data to an empty array during each iteration of the loop
				strcpy(temp.name,"                      "); //clears the name at each iteration to avoid any anamolies
				fscanf(summary_ptr, "%s", &temp.name); //reads the name of the username written at the start of the line

				if (strcmp(temp.name, present_account.name) == 0) //if the name is the required name. It reads the data written after it
				{
					fgets(data, 499, summary_ptr);
					printf("\n%s", data); //printing the data
				}
			}
			filechar = fgetc(summary_ptr); //get char to check EOF
		}

	}
	file_close(); //closing all files
	printf("\a\nThanks For Your vist.\n");

}

//THE END
