#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<unistd.h>
#include <stdlib.h>
#ifndef MAX
#define MAX 10
#endif
long ACCOUNT_START=1000;
long ACCOUNT_END=9999;
void displayallUsers(int n);
int searchUser(int accNum , int n);
int changePin(int i , int newPin);
void displayMiniStatForUser(int userIndex);

struct MiniStatement {
    char options[30];
    int amount;
};

struct users
{
	char name[30];
	char lastName[30];
	int pin, password;
	long balance;
	long accNumber;
	int recordIndex;
	struct MiniStatement statementRecord[5];

}user[30];

void displayallUsers(int n) {
    //change template
    char *row1[] = {"Name", "Account Number", "Balance"};
    printf("%*s | %*s | %*s\n", -3, row1[0], -MAX, row1[1], MAX, row1[2]);
    for(int i = 0 ; i < n ; i++) {
        printf("%-3s | %-10ld | %10ld\n", user[i].name, user[i].accNumber, user[i].balance);
    }
    printf("\n");
}
int searchUser(int accNum , int n)
{
    for (int i=0;i<n;i++)
    {
        if(user[i].accNumber==accNum)
        {
            return i;
        }
    }

    return -1;
}

int changePin(int i , int newPin) {
    user[i].pin = newPin;
}

void displayMiniStatForUser(int userIndex) {
    printf("Hello %s\n\n", user[userIndex].name);
    int n = user[userIndex].recordIndex;
    if(n == 0) {
        printf("No transaction found till now\n");
        return ;
    }
    printf("Please find your last 3 transactions\n");
    char *row2[] = {"Particulars", "Amount"};
    printf("%*s | %*s\n", -3, row2[0], -MAX, row2[1]);
    for(int i = n - 1 ; i >= 0 ; i--) {
        printf("%-3s | %-10d\n" , user[userIndex].statementRecord[i].options , user[userIndex].statementRecord[i].amount);
    }
    printf("\n");
}

void main()
{
    int userNonUser;
    int currentIndex = 0;
    system("cls");

    printf("\n*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *");
    printf("\n*                                                        *");
    printf("\n*                                                        *");
    printf("\n*                     W E L C O M E                      *");
    printf("\n*                                                        *");
    printf("\n*                                                        *");
    printf("\n*                                                        *");
    printf("\n*                          T O                           *");
    printf("\n*                                                        *");
    printf("\n*                                                        *");
    printf("\n*                                                        *");
    printf("\n*       S B M P    C O O P E R A T I V E   B A N K       *");
    printf("\n*                                                        *");
    printf("\n*                                                        *");
    printf("\n*                                                        *");
    printf("\n*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *");


    sleep(4);
    //system("cls");

    start:
	printf("\t\t\t\nAre you existing user or new User?\n");
	printf("Enter 1 for Existing User and 2 for New User:");
    scanf("%d" , &userNonUser);
    printf("\t\t\t\t\t\t\n\n");
    if(userNonUser == 1)
	{
	    goto ab;
	}
	else if(userNonUser == 2)
	{
	    char name[30];
	    char lastName[30];
		printf("Please enter your First Name:\n");
	    scanf("%s" , &name);
	    printf("\n");
	    printf("Enter your last name:\n");
	    scanf("%s",&lastName);
	    printf("\n");
	    memcpy(user[currentIndex].name, name,30);
	    memcpy(user[currentIndex].lastName, lastName,30);

	    pinRenter:
		printf("Enter your pin(4digits):\n");\
		scanf("%d", &user[currentIndex].pin);

		if(user[currentIndex].pin>=1000&&user[currentIndex].pin<=9999)
        {
            printf("\n");
        }
        else
        {
            printf("Pin should be of 4 digits.\n");
            goto pinRenter;
        }

		//printf("Enter your password:\n");
		//scanf("%d",&user[currentIndex].password);
		//printf("\n");
		printf("*Minimum balance required is 1000RS.\n");
		user[currentIndex].balance = 1000;
        user[currentIndex].accNumber = ( (rand() % (ACCOUNT_END-ACCOUNT_START+1) ) + ACCOUNT_START);
        printf("*Your account number is %ld \n please note it...\n" , user[currentIndex].accNumber);
        printf("\n");
        printf("\n");
        printf("         <<<<<<<<<<<<<  Your user id is made successfully  >>>>>>>>>>>>>\n");
        printf("                       ---------------------------------                ");
        user[currentIndex].recordIndex = 0;
		currentIndex++;
		printf("\n");
		printf("\n");

		printf("Would you like to add more user(2 to add user and 3 to continue further):\n");
		int userOptionForNewUser;
		scanf("%d", &userOptionForNewUser);
		printf("\n");

		if(userOptionForNewUser == 2) {
            goto start;
		}else if(userOptionForNewUser == 3){
            goto xy;
		}else {
            printf("Please enter a valid options\n");
            goto start;
		}
	}
    xy:
        displayallUsers(currentIndex);
    ab:
        int choice;
        printf("Please select an option:\n");
        printf("1.Pin change\n");
        printf("2.Withdrawal\n");
        printf("3.Ministatement\n");
        printf("4.Deposit\n");
        printf("5.Balance Inquiry\n");
        printf("6.Exit\n");
        printf("Please enter a choice:");
        scanf("%d",&choice);
        printf("\n");

        switch(choice)
        {
            case 1:
                long num;
                printf("Please enter your account number:\n");
                scanf("%ld",&num);
                int index = searchUser(num , currentIndex);
                printf("\n");
                if(index == -1) {
                    printf("No User with account number %ld is found \n" ,num);
                    goto start;
                }
                int newPin;
                printf("Please enter new pin:");
                scanf("%d", &newPin);
                changePin(index , newPin);
                printf("Your pin change is successful\n");
                //displayallUsers(currentIndex);
                goto xy;
            break;

            case 2:
                int withdraw,pin,choice,totalBalance,confirm;
                long accNumber;
                //printf("Withdrawal\n");
                printf("Please Enter your pin:\n");
                scanf("%d",&pin);
                printf("\n");
                printf("Enter your account number:\n");
                matchAccNum:
                scanf("%ld",&accNumber);
                printf("\n");
                int account;
                account=searchUser(accNumber ,currentIndex);
                if(account == -1)
                {
                    printf("There is no such account number.\n");
                    printf("Please enter your account number again:");
                    goto matchAccNum;
                }
                reEnter:
                printf("AVAILABLE DENOMINATIONS \n 100 500\n");
                printf("Hello %s.\n",user[account].name);
                printf("How much money do you want to withdraw:");
                scanf("%d",&withdraw);
                printf("Enter 1 for confirmation and 2 to re-enter your amount:");
                scanf("%d",&confirm);
                switch(confirm)
                {
                    case 1:
                    goto condition;
                    break;

                    case 2:
                    goto reEnter;
                    break;

                    default:
                    printf("Invalid choice");
                    break;
                }

                condition:

                if(withdraw>user[account].balance)
                {
                    printf("Insufficient balance.");
                    printf("Your total balance is %ldRS.\n8",user[account].balance);
                    invalid:
                    printf("Do you want another transaction or you want to exit?\n Enter 1 for another transaction and 2 to exit\n");
                    scanf("%d",&choice);
                    switch(choice)
                    {
                    case 1:
                        goto xy;
                        break;

                    case 2:
                        goto exit;
                        break;

                    default:
                        printf("invalid statement.");
                        goto invalid;
                        break;
                    }
                    goto xy;
                }
                else
                {
                    user[account].balance = user[account].balance - withdraw;
                    printf("Your money is succesfully withdrawn.");
                    printf("Your final balance is %ld\n",user[account].balance);
                    //user[account].statementRecord[user[account].recordIndex].options = "Debit";
                    memcpy(user[account].statementRecord[user[account].recordIndex].options ,"Debit",30);
                    user[account].statementRecord[user[account].recordIndex].amount = withdraw;
                    user[account].recordIndex++;
                }
                goto xy;
                break;

            case 3:
                printf("ministatement\n");
                int accNumberForMini;
                matchAccForMini:
                printf("Please Enter your Account Number:");
                scanf("%d",&accNumberForMini);
                int accIndex = searchUser(accNumberForMini ,currentIndex);
                if(accIndex == -1)
                {
                    printf("There is no such account number.\n");
                    printf("Please enter your account number again:");
                    goto matchAccForMini;
                }

                displayMiniStatForUser(accIndex);
                int transaction;
                printf("Do you want another transaction or you want to exit?\n Enter 1 for another transaction and 2 to exit\n");
                scanf("%d",&transaction);
                if(transaction == 1) {
                    goto xy;
                }else if(transaction == 2) {
                    goto exit;
                }else {
                    printf("Please enter a valid value\n");
                    goto xy;
                }
                break;

            case 4:
                //printf("Deposit\n");
                int pinToDeposit,depositAmount;
                //long finalDeposit;
                long accNumberToDeposit;
                printf("Please Enter your pin:");
                scanf("%d",&pinToDeposit);
                printf("\n");

                printf("Enter your account number:");
                matchAcc:
                scanf("%ld",&accNumberToDeposit);

                printf("\n");
                int userIndex;
                userIndex=searchUser(accNumberToDeposit ,currentIndex);
                if(userIndex == -1)
                {
                    printf("There is no such account number.\n");
                    printf("Please enter your account number again:");
                    goto matchAcc;
                }
                else
                {
                    enterAmount:
                    printf("Hello %s.\n",user[userIndex].name);
                    printf("How much money do you want to deposit:");
                    scanf("%d",&depositAmount);
                    printf("\n");
                    printf("Enter 1 for confirmation and 2 to re-enter your amount:");
                    scanf("%d",&confirm);
                    if(confirm == 1)
                    {
                        goto statements;
                    }
                    else if(confirm==2)
                    {
                       goto enterAmount;
                    }
                    else
                    {
                        printf("Please enter a valid option.");
                        goto invalid;
                    }
                }

                statements:

                    user[userIndex].balance = user[userIndex].balance + depositAmount;
                    printf("Your money is succesfully Deposited.\n");
                    printf("Your final balance is %ld\n",user[userIndex].balance);

                    //user[account].statementRecord[user[account].recordIndex].options = "Debit";

                    memcpy(user[userIndex].statementRecord[user[userIndex].recordIndex].options ,"Credit",30);
                    user[userIndex].statementRecord[user[userIndex].recordIndex].amount = depositAmount;
                    user[userIndex].recordIndex++;
                    goto xy;

                break;

            case 5:
                int pinToEnquire;
                long accountNumber;
                //printf("Balance Inquiry");
                printf("Enter your pin(4digits):\n");\
                scanf("%d", &user[currentIndex].pin);

                if(user[currentIndex].pin>=1000&&user[currentIndex].pin<=9999)
                {
                    printf("\n");
                }
                else
                {
                    printf("Pin should be of 4 digits.\n");
                    goto pinRenter;
                }
                printf("Enter your account number:\n");
                matchAccNumber:
                scanf("%ld",&accountNumber);
                int acc;
                acc=searchUser(accountNumber ,currentIndex);
                if(acc == -1)
                {
                    printf("There is no such account number.\n");
                    printf("Please enter your account number again:");
                    goto matchAccNumber;
                }
                else
                {
                    //printf("       Your name:%s        ",user[acc].name);
                    //printf("    Your account number is : %d",accountNumber);
                    //printf("  Your balance is : %dRS" ,user[acc].balance);
                    displayallUsers(currentIndex);
                }
                break;

            case 6:

                goto exit;
                break;



            default:
                printf("Please enter a valid options\n");
                goto xy;
                break;


        }


        exit:
            return ;


}
