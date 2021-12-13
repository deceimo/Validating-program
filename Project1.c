/**************************************************************************
*
*	Project1
*
*	This program validates four validation problems.
*	1. Validate date in form dd/mm/yyyy
*	2. Validate CPE student ID number
*	3. Validate street address in Bangkok
*	4. Validate IP address
*
*	Created by Nattapong Saengarunvong	ID:63070503415
*
***************************************************************************/

#include<stdio.h>
#include<string.h>
#include<ctype.h>

int controlDate();
int validateDate(char date[]);
int checkAllNumber(char stringToCheck[]);
int checkDateMonthYear(char stringToCheck[]);
int checkMonthMax30Day(int monthToCheck);

int controlCPE_ID();
int validateCPE_ID(char ID[]);  
int checkAllDigits(char stringToCheck[]);
int checkMiddleID(char stringToCheck[]);
int checkLastID(char stringToCheck[]);
int checkFrontID(char stringToCheck[]);
int checkProgramID(char stringToCheck[]);

int controlAddress();
int validateAddress(char part1[],char part2[],char part3[],char part4[]);
int checkNumberAndSlash(char stringToCheck[]);
int checkFrontAndBackSlash(char stringToCheck[]);
int checkOneSlash(char stringToCheck[]);
int checkLabel(char stringToCheck[]);
int checkLengthPostalCode(char stringToCheck[]);
int check10PostalCode(char stringToCheck[]);

int controlIP();
int validateIP(char IP[]);
int checkNumberAndDot(char stringToCheck[]);
int checkThreeDot(char stringToCheck[]);
int checkDoubleDot(char stringToCheck[]);
int checkMaxIPNumber(char stringToCheck[]);
int checkThreeDigit(char stringToCheck[]);
int checkZeroDot(char stringToCheck[]);



/*
Main function asks what types of validation the user
wants then summary that how many each of validation
that user uses to validate the problem
*/
int main()
{
	int choice=0;						//Receive choice that user type
	int validateCount[4]={0,0,0,0};		//Receive count of each four validate poblems
	char input[32];
	
	while(1)			//User have to choose validate 1 to 4 to proceed that validation
		{
		if(choice==1)
			{
			validateCount[0]+=controlDate();
			}
		else if(choice==2)
			{
			validateCount[1]+=controlCPE_ID();
			}
		else if(choice==3)
			{
			validateCount[2]+=controlAddress();
			}
		else if(choice==4)
			{
			validateCount[3]+=controlIP();
			}	
		else if(choice==5)		//If user types 5,Program will exit and summary how many each validation user uses
			{
			break;
			}
		printf("Validation options:\n");
		printf("\t1-Check date in form dd/mm/yyyy-Buddhist year\n");
		printf("\t2-Check CPE student ID number\n");
		printf("\t3-Check street address in Bangkok\n");
		printf("\t4-Check IP address\n");
		printf("\t5-Exit the program\n");
		printf("What do you want to do?");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%d",&choice);
		}
	printf("\nProgram run summary:\n");
	printf("\tValidation type 1: %d\n",validateCount[0]);
	printf("\tValidation type 2: %d\n",validateCount[1]);
	printf("\tValidation type 3: %d\n",validateCount[2]);
	printf("\tValidation type 4: %d\n",validateCount[3]);
	printf("Goodbye!\n");
}

/*
ControlDate function ask date for validation of date in form dd/mm/yyyy(Buddhist)
then show the statement whether it is valid or not
*/
int controlDate()
{
	char input[256];
	char date[32];						//Receive date from user
	int count=0;						//Count how many times user uses Date validation then send to main function  
	int result=0;						//Receive value from validate function to print statement
	memset(date,0,sizeof(date));
	printf("\nValidate date in form dd/mm/yyyy-Buddhist year(Hit return to stop)\n");
	printf("\tEnter date in form dd/mm/yyyy-Buddhist year:");
	fgets(input,sizeof(input),stdin);
	sscanf(input,"%s",date);
	while(strlen(date)!=0)				//If user types nothing,this function will be exit and go back to main function 
		{
		result=validateDate(date);		//Receive value from validateDate function and print result
		switch(result)
			{
			case 1:
				printf("\t\tValid\n");
				break;
			case 2:
				printf("\t\tNot valid - Input must be in form dd/mm/yyyy\n");
				break;
			case 3:
				printf("\t\tNot valid - Delimiter must be /\n");
				break;
			case 4:
				printf("\t\tNot valid - Day,month and year must be a number\n");
				break;		
			}
		count++;
		result=0;
		memset(date,0,sizeof(date));
		printf("\tEnter date in form dd/mm/yyyy-Buddhist year:");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%s",date);
		}
	printf("\n");
	return count;
}

/*
ValidateDate function gets date from controlDate function then it will
check whether it is valid or not,then send the value to controlDate
function to print statement
*/
int validateDate(char date[])
{
	int result;
	if(strlen(date)!=10)		//Check whether length of date is 10 character or not
		{
		result=2;
		}
	else if((date[2]!='/')||(date[5]!='/'))		//Check whether delimiter is slash or not
		{
		result=3;
		}
	else if(checkAllNumber(date)==0)			//Check whether date is a number or not
		{
		result=4;
		}
	else if(checkDateMonthYear(date)==1)
		{
		printf("\t\tNot valid - Day must be between 1 to 31\n");
		}
	else if(checkDateMonthYear(date)==2)
		{
		printf("\t\tNot valid - Month must be between 1 to 12\n");
		}
	else if(checkDateMonthYear(date)==3)
		{
		printf("\t\tNot valid - Year must be between 2463 to 2663\n");
		}
	else if(checkDateMonthYear(date)==4)
		{
		printf("\t\tNot valid - This month has only 30 days\n");
		}
	else if(checkDateMonthYear(date)==5)
		{
		printf("\t\tNot valid - Month 2 has only 28 days\n");
		}
	else if(checkDateMonthYear(date)==6)
		{
		printf("\t\tNot valid - Month 2 has only 29 days in a leap year\n");
		}
	else if(checkDateMonthYear(date)==7)
		{
		printf("\t\tNot valid - This year is not a leap yaer\n");
		}
	else
		{
		result=1;
		}
	return result;
}

//These functions are used in validateDate.

/*
This function checks whether date that user type has alphabets or not
If there is any alphabet in date,it will send value 0 back to validate Date
function;Otherwise,it will send value 1
*/
int checkAllNumber(char stringToCheck[])
{
	int test;
	int start;
	int arrayNum[8]={0,1,3,4,6,7,8,9};
	
	for(start=0;start<8;start++)
		{
		if(isdigit(stringToCheck[arrayNum[start]]))
			{
			test=1;
			}
		else
			{
			test=0;
			break;
			}
		}
	return test;
}

/*
This function checks correstness of day,month,and year
If there is nothing wrong,it will send value 8 back to 
validate date function;Otherwise,it will send 
values 1 to 8 by its invalidation
*/
int checkDateMonthYear(char stringToCheck[])
{
	int day=0;
	int month=0;
	int year=0;
	int test=0;
	sscanf(stringToCheck,"%d/%d/%d",&day,&month,&year);
	
	if((day>31)||(day<1))				//Check whether day is between 1 to 12 or not
		{
		test=1;
		}
	else if((month>12)||(month<1))		//Check whether month is between 1 to 12 or not
		{
		test=2;
		}
	else if((year>2663)||(year<2463))	//Check whether year is between 2463 to 2663 or not
		{
		test=3;
		}
	else if(checkMonthMax30Day(month)&&(day==31))		//Check whether month has a max 30 days and day is 31 or not
		{
		test=4;
		}
	else if((day>29)&&(month==2)&&(((year-543)%4)!=0))	//Check whether day is more than 29,month is February,and it is not a leap year or not
		{
		test=5;
		}
	else if((day>29)&&(month==2)&&(((year-543)%4)==0))	//Check whether day is more than 29,month is February,and it is a leap year or not
		{
		test=6;
		}
	else if((day==29)&&(month==2)&&(((year-543)%4)!=0))	//Check whether day is 29,month is February,and it is not a leap year or not
		{
		test=7;
		}
	else
		{
		test=8;
		}
	return test;
}

/*
This function checks month of the user whether
it is a month that has only 30 days or not.
If it is,it will send value 1 back to validate date function
;Otherwise,it will send value 0
*/
int checkMonthMax30Day(int monthToCheck)
{
	int month30Day[]={4,6,9,11};
	int start=0;
	int test;
	for(start=0;start<4;start++)
		{
		if(monthToCheck==month30Day[start])
			{
			test=1;
			break;
			}
		else
			{
			test=0;
			}
		}
	return test;
}



/*
ControlCPE_ID function asks ID number for validation of CPE student ID number
then show the statement whether it is valid or not
*/
int controlCPE_ID()
{
	char input[256];
	char ID[32];						//Receive CPE ID from user
	int count=0;						//Count how many times user uses CPE ID validation then send to main function
	int result=0;						//Receive value from validate function to print statement
	memset(ID,0,sizeof(ID));
	printf("\nValidate CPE student ID number(Hit return to stop)\n");	
	printf("\tEnter CPE student ID number:");
	fgets(input,sizeof(input),stdin);
	sscanf(input,"%s",ID);	
	while(strlen(ID)!=0)					//If user types nothing,this function will be exit and go back to main function
		{
		result=validateCPE_ID(ID);			//Receive value from validateCPE_ID function and print result
		switch(result)
			{
			case 1:
				printf("\t\tValid\n");
				break;
			case 2:
				printf("\t\tNot valid - ID must be 11 digits\n");
				break;
			case 3:
				printf("\t\tNot valid - ID must be only number\n");
				break;
			case 4:
				printf("\t\tNot valid - ID must have 07050 in the middle\n");
				break;
			case 5:
				printf("\t\tNot valid - Last two ID digits must not be 00\n");
				break;
			case 6:
				printf("\t\tNot valid - First two ID digits must be between 55 to 63\n");
				break;
			case 7:
				printf("\t\tNot valid - Digit 8 and 9 must be either 34 or 10\n");
				break;
			}
		count++;
		result=0;
		memset(ID,0,sizeof(ID));
		printf("\tEnter CPE student ID number:");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%s",ID);	
		}
	printf("\n");
	return count;
}

/*
ValidateCPE_ID function gets ID from controlCPE_ID function then it will
check whether it is valid or not,then send the value to controlCPE_ID function
to print statement
*/
int validateCPE_ID(char ID[])
{
	int result;
	if(strlen(ID)!=11)				//Check whether ID length is 11 digits or not
		{
		result=2;
		}
	else if(checkAllDigits(ID)==0)	//Check whether ID is a number or not
		{
		result=3;
		}
	else if(checkMiddleID(ID)==0)	//Check whether third to seventh digit are 07050 or not
		{
		result=4;
		}
	else if(checkLastID(ID)==0)		//Check whether last two digits is not 00 or not
		{
		result=5;
		}
	else if(checkFrontID(ID)==0)	//Check whether first two digits is between 55 to 63 or not
		{
		result=6;
		}
	else if(checkProgramID(ID)==0)	//Check whether eighth and ninth is 34 or 10 or not
		{
		result=7;
		}
	else
		{
		result=1;
		}
	return result;
}

//These functions are used in validateCPE_ID.

/*
This function checks whether ID is all the numbers or not
If it is,it will send back value 1 to validateCPE_ID.
;Otherwise,it will send back value 0
*/
int checkAllDigits(char stringToCheck[])
{
	int start=0;
	int test;
	int length=strlen(stringToCheck);
	
	for(start=0;start<length;start++)
		{
		if(isdigit(stringToCheck[start]))
			{
			test=1;
			}
		else
			{
			test=0;
			break;
			}
		}
	return test;
}

/*
This function checks whether third to seventh digit are 07050 or not
If it is,it will send back value 1 to validateCPE_ID.
;Otherwise,it will send back value 0
*/
int checkMiddleID(char stringToCheck[])
{
	int test;
	int start=0;
	char middle[]={'0','7','0','5','0'};
	
	for(start=0;start<5;start++)
		{
		if(middle[start]==stringToCheck[start+2])
			{
			test=1;					
			}
		else
			{
			test=0;
			break;
			}
		}
	return test;
}

/*
This function checks whether last two digits is not 00 or not
If it is,it will send back value 1 to validateCPE_ID.
;Otherwise,it will send back value 0
*/
int checkLastID(char stringToCheck[])
{
	int test;
	if((stringToCheck[9]=='0')&&(stringToCheck[10])=='0')
		{
		test=0;
		}
	else
		{
		test=1;
		}
	return test;
}

/*
This function checks whether first two digits is between 55 to 63 or not
If it is,it will send back value 1 to validateCPE_ID.
;Otherwise,it will send back value 0
*/
int checkFrontID(char stringToCheck[])
{
	int test;
	if((stringToCheck[0]!='5')&&(stringToCheck[0]!='6'))
		{
		test=0;
		}
	else if((stringToCheck[0]=='5')&&(stringToCheck[1]<'5'))
		{
		test=0;
		}
	else if((stringToCheck[0]=='6')&&(stringToCheck[1]>'3'))
		{
		test=0;
		}
	else
		{
		test=1;
		}
	return test;
}

/*
This function checks whether eighth and ninth is 34(International)
or 10(Regular) or not.If it is,it will send back value 1 to validateCPE_ID
;Otherwise,it will send back value 0
*/
int checkProgramID(char stringToCheck[])
{
	int test;
	if((stringToCheck[7]=='3')&&(stringToCheck[8]=='4'))
		{
		test=1;
		}
	else if((stringToCheck[7]=='1')&&(stringToCheck[8]=='0'))
		{
		test=1;
		}
	else
		{
		test=0;
		}
	return test;
}



/*
ControlAddress function asks house address for validation of street address in Bangkok
then show the statement whether it is valid or not
*/
int controlAddress()
{
	char input[256];
	char part1[32],part2[32],part3[32],part4[32];	//Receive address from the user,break in four parts
	int count=0;									//Count how many times user uses address validation then send to main function
	int result=0;									//Receive value from validate function to print statement
	memset(part1,0,sizeof(part1));
	memset(part2,0,sizeof(part2));
	memset(part3,0,sizeof(part3));
	memset(part4,0,sizeof(part4));
	printf("\nValidate street address in Bangkok(Hit return to stop)\n");
	printf("\tEnter street address in Bangkok:");
	fgets(input,sizeof(input),stdin);
	sscanf(input,"%s %s %s %s",part1,part2,part3,part4);
	while(strlen(part1)!=0)									//If user types nothing,this function will be exit and go back to main function
		{
		result=validateAddress(part1,part2,part3,part4);	//Receive value from validateAddress function and print result	
		switch(result)
			{
			case 1:
				printf("\t\tValid\n");
				break;
			case 2:
				printf("\t\tNot valid - House number must have only number and slash\n");
				break;
			case 3:
				printf("\t\tNot valid - House number must not start or end with slash\n");
				break;
			case 4:
				printf("\t\tNot valid - House number has 1 slash at most\n");
				break;				
			case 5:
				printf("\t\tNot valid - Label must be Street,Road,or Lane\n");
				break;
			case 6:
				printf("\t\tNot valid - Postal code must be only a number\n");
				break;
			case 7:
				printf("\t\tNot valid - Postal code must have 5 digits\n");
				break;
			case 8:
				printf("\t\tNot valid - Postal code must begin with 10\n");
				break;
			}
		count++;
		result=0;
		memset(part1,0,sizeof(part1));
		memset(part2,0,sizeof(part2));
		memset(part3,0,sizeof(part3));
		memset(part4,0,sizeof(part4));
		printf("\tEnter street address in Bangkok:");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%s %s %s %s",part1,part2,part3,part4);
		}
	printf("\n");
	return count;
}

/*
ValidateAddress function gets address from controlAddress function then it will
check whether it is valid or not,then send the value to controlAddress function
to print statement 
*/
int validateAddress(char part1[],char part2[],char part3[],char part4[])
{
	int result;	
	if(checkNumberAndSlash(part1)==0)				//Check whether house number has only number and slash or not
		{
		result=2;
		}
	else if(checkFrontAndBackSlash(part1)==0)		//Check whether house number does not has a slash at front or back or not
		{
		result=3;
		}
	else if(checkOneSlash(part1)==0)				//Check whether house number has only one slash or not
		{
		result=4;
		}
	else if(checkLabel(part3)==0)					//Check whether label is Road,Lane,or Street or not
		{
		result=5;
		}
	else if(checkLabel(part3)==1)					//Check whether label is Road,Lane,or Street or not
		{
		if(checkAllDigits(part4)==0)				//Check whether postal code is all number or not
			{
			result=6;
			}
		else if(checkLengthPostalCode(part4)==0)	//Check whether postal code has 5 digits or not
			{
			result=7;
			}
		else if(check10PostalCode(part4)==0)		//Check whether postal code first and second digits are 10 or not
			{
			result=8;
			}
		else
			{
			result=1;
			}
		}	
	else if(checkLabel(part3)==2)					//Check whether label is Road,Lane,or Street or not
		{
		if(checkLengthPostalCode(part3)==0)			//Check whether postal code has 5 digits or not
			{
			result=7;
			}
		else if(check10PostalCode(part3)==0)		//Check whether postal code first and second digits are 10 or not
			{
			result=8;
			}
		else
			{
			result=1;
			}
		}
	return result;
}

//These function ar used in validateAddress

/*
This function checks house number has only number and slash or not
If it is,it will send back value 1 to validateAddress function
;Otherwise,it will send back value 0
*/
int checkNumberAndSlash(char stringToCheck[])
{
	int test;
	int length=strlen(stringToCheck);
	int start=0;
	
	for(start=0;start<length;start++)
		{
		if(isdigit(stringToCheck[start]))
			{
			test=1;
			}
		else if(stringToCheck[start]=='/')
			{
			test=1;
			}
		else
			{
			test=0;
			break;
			}
		}
	return test;
}

/*
This function checks whether house number does not has a slash at front or back or not
If it is,it will send back value 1 to validateAddress function
;Otherwise,it will send back value 0
*/
int checkFrontAndBackSlash(char stringToCheck[])
{
	int test=1;
	int length=strlen(stringToCheck);
	
	if(stringToCheck[0]=='/')
		{
		test=0;
		}
	else if(stringToCheck[length-1]=='/')
		{
		test=0;
		}
	return test;
}

/*
This function checks Check whether house number has only oen slash or not
If it is,it will send back value 1 to validateAddress function
;Otherwise,it will send back value 0
*/
int checkOneSlash(char stringToCheck[])
{
	int test=1;
	int count=0;
	int length=strlen(stringToCheck);
	int start;
	
	for(start=0;start<length;start++)
		{
		if(stringToCheck[start]=='/')
			{
			count++;
			}
		}
	if(count>1)
		{
		test=0;
		}
	return test;
}

/*
This function checks whether label is Road,Lane,or Street or not
If it is one of them,it will send back value 1 to validateAddress function
But if they are all number,it will send back value 2 to validateAddress function
But if they are not two of them,it will send back value 0
*/
int checkLabel(char stringToCheck[])
{
	int test;
	char label[3][16]={"Street","Road","Lane"};
	int length=strlen(stringToCheck);
	int start;
	
	for(start=0;start<3;start++)
		{
		if(strcmp(stringToCheck,label[start])==0)
			{
			test=1;
			break;
			}
		else
			{
			test=0;
			}
		}
	if(test==0)
		{
		for(start=0;start<length;start++)
			{
			if(isdigit(stringToCheck[start]))
				{
				test=2;
				}
			else
				{
				test=0;
				break;
				}
			}
		}	
	return test;
}

/*
This function checks whether postal code has 5 digits or not
If it is,it will send back value 1 to validateAddress function
;Otherwise,it will send back value 0
*/
int checkLengthPostalCode(char stringToCheck[])
{
	int test=1;
	
	if(strlen(stringToCheck)!=5)
		{
		test=0;
		}
	return test;
}

/*
This function checks whether postal code first and second digits are 10 or not
If it is,it will send back value 1 to validateAddress function
;Otherwise,it will send back value 0
*/
int check10PostalCode(char stringToCheck[])
{
	int test=1;
	
	if((stringToCheck[0]!='1')||(stringToCheck[1]!='0'))
		{
		test=0;
		}
	return test;
}



/*
ControlIP function asks IP address for validation of IP address
then show the statement whether it is valid or not
*/
int controlIP()
{
	char input[256];
	char IPAddress[32];					//Receive IP from user
	int count=0;						//Count how many times user uses IP validation then send to main function  
	int result=0;						//Receive value from validate function to print statement
	memset(IPAddress,0,sizeof(IPAddress));
	printf("\nValidate IP address(Hit return to stop)\n");
	printf("\tEnter IP address:");
	fgets(input,sizeof(input),stdin);
	sscanf(input,"%s",IPAddress);
	while(strlen(IPAddress)!=0)			//If user types nothing,this function will be exit and go back to main function 
		{
		result=validateIP(IPAddress);	//Receive value from validateIP function and print result
		switch(result)
			{
			case 1:
				printf("\t\tValid\n");
				break;
			case 2:
				printf("\t\tNot valid - Size of IP address must be between 7 to 15\n");
				break;
			case 3:
				printf("\t\tNot valid - IP address must be only number and dot\n");
				break;
			case 4:
				printf("\t\tNot valid - IP address must have 3 dots\n");
				break;
			case 5:
				printf("\t\tNot valid - IP address must not start with dot\n");
				break;
			case 6:
				printf("\t\tNot valid - IP address must have numbers between dot\n");	
				break;			
			case 7:
				printf("\t\tNot valid - IP address must not be 0.0.0.0\n");
				break;
			case 8:
				printf("\t\tNot valid - IP address must not start with 0\n");
				break;
			case 9:
				printf("\t\tNot valid - IP address number must not be more than 255\n");
				break;
			case 10:
				printf("\t\tNot valid - IP address must not have 0 at front\n");
				break;
			case 11:
				printf("\t\tNot valid - IP address must have 3 digits at most\n");
				break;
			}
		count++;
		result=0;
		memset(IPAddress,0,sizeof(IPAddress));
		printf("\tEnter IP address:");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%s",IPAddress);
		}
	printf("\n");
	return count;
}

/*
ValidateIP function gets IP address from controlIP function then it will
check whether it is valid or not,then send the value to controlIP
function to print statement
*/
int validateIP(char IP[])
{
	int result;
	if((strlen(IP)>15)||(strlen(IP)<7))		//Check whether IP address' length is between 7 to 15 or not
		{
		result=2;
		}
	else if(checkNumberAndDot(IP)==0)		//Check whether IP address has only number and dot or not
		{
		result=3;
		}
	else if(checkThreeDot(IP)==0)			//Check whether IP address has three dots or not
		{
		result=4;
		}
	else if(IP[0]=='.')						//Check whether IP address is not start with dot or not
		{
		result=5;
		}
	else if(checkDoubleDot(IP)==0)			//Check whether IP address does not have two or three close dots or not 
		{
		result=6;
		}
	else if((strcmp(IP,"0.0.0.0"))==0)		//Check whether IP address is not in "0.0.0.0" pattern or not
		{
		result=7;
		}
	else if(IP[0]=='0')						//Check whether IP address is not start with number zero or not
		{
		result=8;
		}
	else if(checkMaxIPNumber(IP)==0)		//Check whether each of four parts in IP address is not more than 255 or not
		{
		result=9;
		}
	else if(checkZeroDot(IP)==0)			//Check whether there is number zero after dot or not
		{
		result=10;
		}									
	else if(checkThreeDigit(IP)==0)			//Check whether each of four parts in IP address has three digits at most or not 
		{
		result=11;
		}
	else
		{
		result=1;
		}
	return result;
}

//These functions are used in validateIP.

/*
This function checks whether IP address has only number and dot or not
If it is,it will send back value 1 to validateIP function
;Otherwise,it will send back value 0
*/
int checkNumberAndDot(char stringToCheck[])
{
	int start=0;
	int length=strlen(stringToCheck);
	int test;
	
	for(start=0;start<length;start++)
		{
		if(isdigit(stringToCheck[start]))
			{
			test=1;
			}
		else if(stringToCheck[start]=='.')
			{
			test=1;
			}
		else
			{
			test=0;
			break;
			}
		}
	return test;
}

/*
This function checks whether IP address has three dots or not
If it is,it will send back value 1 to validateIP function
;Otherwise,it will send back value 0
*/
int checkThreeDot(char stringToCheck[])
{
	int start=0;
	int length=strlen(stringToCheck);
	int count=0;
	int test=0;
	
	for(start=0;start<length;start++)
		{
		if(stringToCheck[start]=='.')
			{
			count++;
			}
		}
	if(count==3)
		{
		test=1;
		}
	return test;
}

/*
This function checks whether IP address does not have two or three close dots or not
If it is,it will send back value 1 to validateIP function
;Otherwise,it will send back value 0
*/
int checkDoubleDot(char stringToCheck[])
{
	int start=0;
	int test=1;
	int length=strlen(stringToCheck);
	
	for(start=0;start<(length-1);start++)
		{
		if(stringToCheck[start]=='.')
			{
			if(stringToCheck[start+1]=='.')
				{
				test=0;
				break;
				}
			}
		}
	return test;
}

/*
This function checks whether each of four parts in IP address is not more than 255 or not
If it is,it will send back value 1 to validateIP function or not
;Otherwise,it will send back value 0
*/
int checkMaxIPNumber(char stringToCheck[]) 
{
	int part[4];
	int start=0;
	int test=1; 
	sscanf(stringToCheck,"%d.%d.%d.%d",&part[0],&part[1],&part[2],&part[3]);
	
	for(start=0;start<4;start++)
		{
		if(part[start]>255)
			{
			test=0;
			break;
			}
		}
	return test;
}

/*
This function checks whether there is number zero after dot or not
If it is,it will send back value 1 to validateIP function or not
;Otherwise,it will send back value 0
*/
int checkZeroDot(char stringToCheck[])
{
	int test=1;
	int start=0;
	int length=strlen(stringToCheck);
	
	for(start=0;start<(length-1);start++)
		{
		if(stringToCheck[start]=='.')
			{
			if(stringToCheck[start+1]=='0')
				{
				test=0;
				break;
				}
			}
		}
	return test;
}

/*
This function checks whether each of four parts in IP address has three digits at most or not
If it is,it will send back value 1 to validateIP function or not
;Otherwise,it will send back value 0
*/
int checkThreeDigit(char stringToCheck[])
{
	char *token;
	char part[4][8];
	int start=0;
	int test=1;
	
	token = strtok(stringToCheck,"."); 
	
	for(start=0;start<4;start++)
		{
		strcpy(part[start],token);
		token = strtok(NULL,".");
		}
		
	for(start=0;start<4;start++)
		{
		if(strlen(part[start])>3)
			{
			test=0;
			break;
			}
		}
	return test;
}
