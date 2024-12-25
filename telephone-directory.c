#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct contact
{
    char fname[15];
    char lname[15];
    char mobile_no[15];
    char tag[15];
};
typedef struct contact contact;
// A utility function to add contact into the directory
typedef struct contact contact;

#include <stdio.h>

void deleteAllContacts() {
    int hi;
    printf("Are you sure you want to delete all contacts?\nIf yes, press 1 and enter. Press any other key to cancel.\n");
    scanf("%d", &hi);
    if (hi == 1) {
        // Delete the phone book file
        if (remove("PhoneBook") == 0) {
            printf("All contacts deleted successfully.\n");
        } else {
            printf("Error deleting contacts.\n");
        }
    } else {
        printf("The contacts have not been deleted.\n");
    }
}

int valid_numeric_input(const char *str)
{
    int i = 0;
    while (str[i])
    {
        if (!isdigit(str[i]))
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int valid_name_input(const char *str)
{
    int i = 0;
    while (str[i])
    {
        if (!isalpha(str[i]) && str[i] != ' ')
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int valid_mobile_number(const char *str)
{
    int length = strlen(str);
    if (length != 10)
    {
        return 0; // Mobile number should have exactly 10 digits
    }
    return valid_numeric_input(str); // Check if the input is numeric
}

void add_contact()
{
    system("cls");
    FILE *fptr;
    contact cn;
    fptr = fopen("PhoneBook", "a");

    printf("\n<Fill details>\n");

    printf("Enter First Name: ");
    scanf("%s", cn.fname);
    while (!valid_name_input(cn.fname))
    {
        printf("Invalid input! Enter a valid First Name: ");
        scanf("%s", cn.fname);
    }

    printf("Enter Last Name: ");
    scanf("%s", cn.lname);
    while (!valid_name_input(cn.lname))
    {
        printf("Invalid input! Enter a valid Last Name: ");
        scanf("%s", cn.lname);
    }

     while (1)
    {
        printf("Enter Mobile Number: ");
        scanf("%s", cn.mobile_no);
        if (!valid_mobile_number(cn.mobile_no))
        {
            printf("Invalid input! Enter a valid 10-digit Mobile Number.\n");
            continue;
        }

        // Check for duplicate phone numbers
        FILE *fptr_check = fopen("PhoneBook", "r");
               int duplicate_found = 0;
        contact temp;
        while (fread(&temp, sizeof(contact), 1, fptr_check))
        {
            if (strcmp(temp.mobile_no, cn.mobile_no) == 0)
            {
                duplicate_found = 1;
                break;
            }
        }

        fclose(fptr_check);

        if (duplicate_found)
        {
            printf("Phone number already exists. Enter a different Mobile Number.\n");
            continue;
        }

        break;
    }

    printf("Enter Tag (Enter 'Other' for nothing): ");
    scanf("%s", cn.tag);

    fwrite(&cn, sizeof(contact), 1, fptr);

    fclose(fptr);

    printf("Enter any key to continue.");
    getch();
    system("cls");
}
// A utility function to print the no.of contacts in the directory
int directory_info(){
    FILE *fptr;

    fptr = fopen("PhoneBook", "r");
    fseek(fptr, 0, SEEK_END);

    return ftell(fptr)/sizeof(contact);
}
// A utility function to know how many contacts are saved within a specified tag in the directory
int tag_info(char tag[])
{
    int num = 0;
    FILE *fptr;
    contact cn;
    fptr = fopen("PhoneBook", "r");

    while(fread(&cn, sizeof(contact), 1, fptr))
    {
        if(strcmp(strlwr(cn.tag), strlwr(tag)) == 0)
            num++;
    }
    return num;
}

//A utility function to display the contacts
void display()
{
    system("cls");
    FILE *fptr;
    contact cn;
    int mode, count = 1, i, n;
    fptr = fopen("PhoneBook", "r");
    if (fptr == NULL) {
        printf("The phone book is empty.\n");
    }
    else{
    printf("1 : View by Time Created (Ascending)\n");
    printf("2 : View by Time Created (Descending)\n");
    printf("Choose Display Mode : ");
    scanf("%d", &mode);
    n = directory_info();
    printf("---------------------------------------------------------------------\n");
    printf("|Total Number of contacts : %2d                                      |\n", n);
    printf("---------------------------------------------------------------------");
    printf("\n|%-3s| %-15s%-15s%-20s%-12s|\n", "Sno", "First Name", "Last Name", "Contact Number", "Tag");
    printf("---------------------------------------------------------------------");

    if(mode == 1)
    {
        while(fread(&cn, sizeof(contact), 1, fptr))
        {
            printf("\n|%-3d| %-15s%-15s%-20s%-12s|", count++, cn.fname, cn.lname, cn.mobile_no, cn.tag);
        }
    }

    else if (mode == 2)
    {
        fseek(fptr,-(sizeof(cn)), SEEK_END);

        for(i = 1; i <= n; ++i)
        {
            fread(&cn, sizeof(contact), 1, fptr);
            printf("\n|%-3d| %-15s%-15s%-20s%-12s|", count++, cn.fname, cn.lname, cn.mobile_no, cn.tag);
            fseek(fptr, -2*sizeof(contact), SEEK_CUR);
        }
    }

    else
        printf("\n|Invalid Selection !!!                                       |");

    printf("\n---------------------------------------------------------------------\n");

    fclose(fptr);

    printf("\n\nEnter any key to continue : ");
	getch();
    system("cls");
    }
}
//This is a utility function which displays all the contacts which are saved within a specified tag
void display_by_tag()
{
    system("cls");
    char tag[20];
    FILE *fptr;
    contact cn;
    int count=1, n;
    fptr = fopen("PhoneBook", "r");
    fflush(stdin);
    printf("Enter Tag : ");
    scanf("%s", tag);

    n = tag_info(tag);
    if (fptr == NULL) {
        printf("The phone book is empty.\n");
    }
    else{
    printf("---------------------------------------------------------------------\n");
    printf("|Total Number of contacts : %2d                                      |\n", n);
    printf("---------------------------------------------------------------------");
    printf("\n|%-3s| %-15s%-15s%-20s%-12s|\n", "Sno", "First Name", "Last Name", "Contact Number", "Tag");
    printf("---------------------------------------------------------------------");
    

    while(fread(&cn, sizeof(contact), 1, fptr))
    {
        if(strcmp(strlwr(cn.tag), strlwr(tag)) == 0)
            printf("\n|%-3d| %-15s%-15s%-20s%-12s|", count++, cn.fname, cn.lname, cn.mobile_no, cn.tag);
    }

    printf("\n---------------------------------------------------------------------\n");

    fclose(fptr);
    fflush(stdin);
    printf("\n\nEnter any key to continue : ");
	getch();
    system("cls");
    }
}

// A utility function to modify a cotact
void modify_contact()
{
    system("cls");
    FILE *fptr, *fptr1;
    contact cn;
    char fname[15];
    char lname[15];
    char modify;
    int found = 0;

    fptr = fopen("PhoneBook", "r");
    fptr1 = fopen("helper", "w");

    printf("Enter the name of the contact to modify:\n");
    printf("Enter First name: ");
    scanf("%s", &fname);
    while (!valid_name_input(fname))
    {
        printf("Invalid input! Enter a valid First Name: ");
        scanf("%s", &fname);
    }

    printf("Enter Last name: ");
    scanf("%s", &lname);
    while (!valid_name_input(lname))
    {
        printf("Invalid input! Enter a valid Last Name: ");
        scanf("%s", &lname);
    }

    fflush(stdin);

    while (fread(&cn, sizeof(contact), 1, fptr))
    {
        if (strcmp(strlwr(cn.fname), strlwr(fname)) == 0 && strcmp(strlwr(cn.lname), strlwr(lname)) == 0)
        {
            found = 1;
            printf("\nModify First Name? <y/n>: ");
            fflush(stdin);
            scanf("%c", &modify);
            if (modify == 'y' || modify == 'Y')
            {
                printf("Enter New First name: ");
                scanf("%s", cn.fname);
                while (!valid_name_input(cn.fname))
                {
                    printf("Invalid input! Enter a valid First Name: ");
                    scanf("%s", cn.fname);
                }
                fflush(stdin);
            }

            printf("\nModify Last Name? <y/n>: ");
            fflush(stdin);
            scanf("%c", &modify);
            if (modify == 'y' || modify == 'Y')
            {
                printf("Enter New Last name: ");
                scanf("%s", cn.lname);
                while (!valid_name_input(cn.lname))
                {
                    printf("Invalid input! Enter a valid Last Name: ");
                    scanf("%s", cn.lname);
                }
                fflush(stdin);
            }

            printf("\nModify Mobile Number? <y/n>: ");
            fflush(stdin);
            scanf("%c", &modify);
            if (modify == 'y' || modify == 'Y')
            {
                while (1)
                {
                    printf("Enter New Mobile Number: ");
                    scanf("%s", cn.mobile_no);
                    if (!valid_mobile_number(cn.mobile_no))
                    {
                        printf("Invalid input! Enter a valid 10-digit Mobile Number.\n");
                        continue;
                    }

                    // Check for duplicate phone numbers
                    FILE *fptr_check = fopen("PhoneBook", "r");
                    int duplicate_found = 0;
                    contact temp;
                    while (fread(&temp, sizeof(contact), 1, fptr_check))
                    {
                        if (strcmp(temp.mobile_no, cn.mobile_no) == 0)
                        {
                            duplicate_found = 1;
                            break;
                        }
                    }

                    fclose(fptr_check);

                    if (duplicate_found)
                    {
                        printf("Phone number already exists. Enter a different Mobile Number.\n");
                        continue;
                    }

                    break;
                }
                fflush(stdin);
            }

            printf("\nModify Tag? <y/n>: ");
            fflush(stdin);
            scanf("%c", &modify);
            if (modify == 'y' || modify == 'Y')
            {
                printf("Enter New Tag: ");
                scanf("%s", cn.tag);
                fflush(stdin);
            }
        }
        fwrite(&cn, sizeof(contact), 1, fptr1);
    }

    fclose(fptr);
    fclose(fptr1);

    if (found == 1)
    {
        fptr1 = fopen("helper", "r");
        fptr = fopen("PhoneBook", "w");

        while (fread(&cn, sizeof(contact), 1, fptr1))
            fwrite(&cn, sizeof(contact), 1, fptr);

        printf("\nContact Modified Successfully\n");
    }
    else
        printf("Contact not found");

    fclose(fptr);
    fclose(fptr1);

    printf("\n\nEnter any key to continue : ");
    getch();
    system("cls");
}


//A utility function to search for the info of a specified contact
void search_contact(){
	system("cls");
	FILE *fp;
	contact cn;
	int c,flag=0;
	fp=fopen("PhoneBook","r");
	if(fp==NULL){
		printf("\nError in opening\n");
		exit(1);
	}
	printf("\n------------------------------------\n");
	printf("***SEARCH MENU***\n");
	printf("----------------------------------------\n");
	printf("1. Search by name\n2. Search by Phone number\n");
	printf("Enter your choice : ");
	scanf("%d",&c);
	fflush(stdin);
	if(c==1){
	char fname[30],lname[30];		
	printf("Enter the name to be searched for:\n");
	printf("Enter first name : ");
	scanf("%s",&fname);
	printf("Enter last name : ");
	scanf("%s",&lname);
	fflush(stdin);
	while(fread(&cn,sizeof(cn),1,fp)==1){
		
		if(strcmp(strlwr(cn.fname),strlwr(fname))==0&&strcmp(strlwr(cn.lname),strlwr(lname))==0){
			flag=1;
			printf("\nDetail information about %s\n",fname);
			printf("---------------------------------------------------------------------\n");
            printf("\n|%-15s%-15s%-20s%-12s|\n", "First Name", "Last Name", "Contact Number", "Tag");
            printf("---------------------------------------------------------------------");
            printf("\n|%-15s%-15s%-20s%-12s|\n",  cn.fname, cn.lname, cn.mobile_no, cn.tag);
			break;
			}
		}
		if(flag==0){
		printf("\nSearch not found\n");
		fclose(fp);}
	}
	else if(c==2){
		char phone[10];
		printf("Enter phone number to search: ");
		scanf("%s",&phone);
		while(fread(&cn,sizeof(cn),1,fp)==1){
			if(strcmp(phone,cn.mobile_no)==0){
				flag=1;
				printf("\n\nDetail information about %s",phone);
				printf("---------------------------------------------------------------------\n");
                printf("\n|%-15s%-15s%-20s%-12s|\n", "First Name", "Last Name", "Contact Number", "Tag");
                printf("---------------------------------------------------------------------");
                printf("\n|%-15s%-15s%-20s%-12s|\n",  cn.fname, cn.lname, cn.mobile_no, cn.tag);
			    break;
			}
		}
		if(flag==0) {
		printf("\nSearch not found\n");
		fclose(fp);
		}
	}
	else{
		printf("Wrong Choice!!");
		fclose(fp);
	}
	printf("Enter any key to continue:");
	getch();
	system("cls");
}

//A utility function to delete a contact from the directory
void delete_contact(){
	contact cn;
	FILE *fptr,*fptr1;
	int flag;
	system("cls");
	fptr=fopen("PhoneBook","r");
	if(fptr==NULL){
		printf("CONTACT'S DATA NOT ADDED YET");
	}
	else{
		fptr1=fopen("helper","w+");
		if(fptr1==NULL)printf("Error in opening the file");
		else{
			
			int choice;
			printf("\n----------------------------------------");
			printf("\n***DELETION MENU***\n");
			printf("----------------------------------------\n");
			printf("1.Deletion through mobile number\n2.Deletion through name\n");
			printf("Enter your choice: ");
			scanf("%d",&choice);
			if(choice==1){
				char mobile_no[25];
				printf("Enter CONTACT's mobile_no:");
				scanf("%s",&mobile_no);
				fflush(stdin);
				while(fread(&cn,sizeof(cn),1,fptr)==1){
					if(strcmp(mobile_no,cn.mobile_no)!=0){
						fwrite(&cn,sizeof(cn),1,fptr1);
					}
					if(strcmp(mobile_no,cn.mobile_no)==0){
						flag=1;
					}
				}
			}
			else if(choice==2){
			char fname[25],lname[25];
			printf("Enter CONTACT's fname: ");
			scanf("%s",&fname);
			printf("Enter CONTACT's lname: ");
			scanf("%s",&lname);
			fflush(stdin);
			while(fread(&cn,sizeof(cn),1,fptr)==1){
				if(strcmp(strlwr(cn.fname),strlwr(fname))!=0||strcmp(strlwr(cn.lname),strlwr(lname))!=0){
					fwrite(&cn,sizeof(cn),1,fptr1);
				}
				if(strcmp(strlwr(cn.fname),strlwr(fname))==0&&strcmp(strlwr(cn.lname),strlwr(lname))==0){
					flag=1;
				}
			}
		}else{
			printf("\nWrong choice!\nEnter any key to continue");
			getch();
			system("cls");
		}
		
			fclose(fptr);
			fclose(fptr1);
			if(flag!=1){
				printf("NO CONTACT'S RECORD TO DELETE!\n");
			}
			else{
				fptr1 = fopen("helper", "r");
				fptr = fopen("PhoneBook", "w");
				while(fread(&cn, sizeof(contact), 1, fptr1))
					fwrite(&cn, sizeof(contact), 1, fptr);
				printf("\nContact Deleted Successfully\n");
				
			}
			fclose(fptr1);
			fclose(fptr);
		}
	}
	printf("Enter any key:");
	getch();
	system("cls");
}

//Driver code
int main()
{
    int operation = 1;

    while(operation)
    {
        printf("\n1 : Create Contact\n");
        printf("2 : Display Directory\n");
        printf("3 : Display by tags\n");
        printf("4 : Modify Contact\n");
        printf("5 : Search Contact\n");
        printf("6 : Delete Contact\n");
        printf("7 : Exit Program\n");
        printf("8 : Delete all contacts\n");
        printf("\nChoose Operation : ");
        scanf("%d", &operation);

        switch(operation)
        {
            case 1 :
                add_contact();
                break;
            case 2 :
                display();
                break;
            case 3 :
                display_by_tag();
                break;
            case 4 :
                modify_contact();
                break;
            case 5:
            	search_contact();
            	break;
            case 6:
            	delete_contact();
            	break;
            case 7:
            	exit(1);
            	break;
            case 8:
                deleteAllContacts();
                break;
            default:
            	system("cls");
            	printf("\nInvalid Operation !!");
                printf("\nEnter 1 to 8 only");
                printf("\n Enter any key to continue");
                getch();
                system("cls");
        }
    }

    return 0;
}
