#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void addNewcontact();
void display();
void deletecontact();
void editcontact();
int searchcontact();

typedef struct contact
{
    int number;
    char name[20];
    char phone[15];
    char email[20];
    struct contact *next;
    } Contact;
Contact *firstc,*currentc,*newc;

int cnum = 0;

int main()
{
    FILE *datafile;
    char *filename = "contactdatabase.txt";
    char ch;
    firstc = NULL;
    datafile = fopen(filename,"r");
    if(datafile)
    {
	    firstc = (struct contact *)malloc(sizeof(struct contact));

	    currentc = firstc;
	    while(1)
     	    {
		    newc = (struct contact *)malloc(sizeof(struct contact));
		    fread(currentc,sizeof(struct contact),1,datafile);
		    if(currentc->next == NULL)
			    break;
		    currentc->next = newc;
		    currentc = newc;
	    }
	    fclose(datafile);
	    cnum = currentc->number;

    }

    do
    {
	fflush(stdin);//flushes the output buffer of a stream.
	system("color 2F");
        puts("\n\t\t\t    Welcome To Our Phonebook");
        puts("\t\t\t--------------------------------");
        puts("\t\t\t(1) - Add A New Contact");
        puts("\t\t\t(2) - Delete Contact");
        puts("\t\t\t(3) - Display Contact List");
        puts("\t\t\t(4) - Edit Contact");
        puts("\t\t\t(5) - Search A Contact By Name");
        puts("\t\t\t--------------------------------");
        puts("\t\t\t(Q) - Save And Quit\n");
        printf("\t\t\t\tYour choice:");
        ch = getchar();
        ch = toupper(ch);/*changes user input case to upper case*/

        switch(ch)
        {
            case '1':
                puts("\n\t\t\tAdd A New Contact\n");
                fflush(stdin);
                addNewcontact();
                break;
            case '2':
                puts("\n\t\t\tDelete Contact\n");
                deletecontact();
                break;
            case '3':
                puts("\n\t\t\tDisplay Contact List\n");
                display();
                break;
            case '4':
                puts("\n\t\t\tEdit Contact\n");
                editcontact();
                break;
            case '5':
                puts("\n\t\t\tSearch A Contact By Name\n");
                searchcontact();
                break;
            case 'Q':
                puts("\n\t\t\t\tSave and Quit\n");
                default:
                break;
        }
    }
    while(ch != 'Q');

    currentc = firstc;

    if(currentc == NULL)
	    return(0);


    datafile = fopen(filename,"w");

    if(datafile == NULL)
    {
	    printf("\t\t\tThere is no contact to write %s\n",filename);
	    return(1);
    }

    while(currentc != NULL)
    {
	    fwrite(currentc,sizeof(struct contact),1,datafile);
	    currentc = currentc->next;
    }
    fclose(datafile);
    return(0);
}

void addNewcontact()
{
    newc = (struct contact *)malloc(sizeof(struct contact));

    if(firstc==NULL)
        firstc = currentc = newc;

    else
    {
        currentc = firstc;

        while(currentc->next != NULL)
        currentc = currentc->next;
        currentc->next = newc;
        currentc = newc;
    }

    cnum++;
    printf("\t\t\tContact Number %d\n",cnum);
    currentc->number = cnum;

    printf("\t\t\tEnter Contact Name : ");
    gets(currentc->name);
    printf("\t\t\tEnter Contact Phone Number : ");
    gets(currentc->phone);
    printf("\t\t\tEnter Contact Email : ");
    gets(currentc->email);
    printf("\t\t\tContact Added!\n\n");

    currentc->next = NULL;

}

void display()
{
    if(firstc==NULL)
        puts("\t\t\tThere re no contacts to display!");

    else
    {
	    printf("\t%6s %-20s %-15s %-15s\n","Acct No#","Name","Phone","Email");
        puts("\t------- -------------------- ------------- ------------------");

        currentc=firstc;

        do
        {

                printf("\t%6d: %-20s %-15s %-20s\n",\
                currentc->number,\
                currentc->name,\
                currentc->phone,\
                currentc->email);
        }

        while((currentc=currentc->next) != NULL);
    }
}
void deletecontact()
{
    int record;
    struct contact *previousc;
    if(firstc==NULL)
    {
        puts("\t\t\tThere are no contacts to delete!\n");
	return;
    }

    display();
    printf("\n\t\t\tEnter contact account number to delete: ");
    scanf("%d",&record);
    currentc = firstc;

    while(currentc != NULL)
    {
        if(currentc->number == record)
	{
	    if(currentc == firstc)
		firstc=currentc->next;
	    else
		previousc->next = currentc->next;

        free(currentc);
	    printf("\t\t\tContact %d deleted!\n",record);
	    return;
	}

	else
	{
        previousc = currentc;
	    currentc = currentc->next;
	}
    }
    printf("\t\t\tContact %d not found!\n",record);
 }

void editcontact(){
    int record, result;
    if(firstc==NULL)
    {
        puts("\t\t\tThere are no contacts to Edit!\n");
	return;
    }

    display();
    printf("\n\t\t\tEnter contact account number to Edit or change: ");
    scanf("%d",&record);
    result = findnum(record);

    if( result >0 ){
	    printf("\t\t\tContact %d:\n",currentc->number);
	    printf("\t\t\tName: %s\n",currentc->name);
	    if(prompt())
		    gets(currentc->name);
	    printf("\t\t\tPhone: %s\n",currentc->phone);
	    if(prompt())
		    gets(currentc->phone);
	    printf("\t\t\tEmail: %s\n",currentc->email);
	    if(prompt())
		    gets(currentc->email);
	    return;
	}
    printf("\t\t\tcontact %d was not found!\n",record);
}

int findnum (int recordnum)
{
    int record;
    record = recordnum;
    currentc = firstc;
    while(currentc != NULL)
    {

        if(currentc->number == record)
	     {
           return 1;
         }

	else
	{
	    currentc = currentc->next;
	}
    }
    return -1;
}
int searchcontact(void)
{
     char buff[20];

     if(firstc==NULL)
	{
        puts("\t\t\tThere are no contacts to find!\n");
	    return 1;
    }

    printf("\t\t\tEnter contact name: ");
    fflush(stdin);
    gets(buff);

    currentc = firstc;
    while(currentc != NULL)
    {
        if( strcmp(currentc->name, buff) == 0 )
	    {
			printf("\n\t%6s %-20s %-15s %-15s\n","Acct No#","Name","Phone","Email");
            printf("\n\t%6d: %-20s %-15s %-20s\n",\
            currentc->number,\
            currentc->name,\
            currentc->phone,\
            currentc->email);


			return 0;
	    }
		else
		{
			currentc = currentc->next;
		}
    }
    printf("\t\t\tcontact %s was not found!\n",buff);
          return 1;
}

int prompt(void)
{
	char ch;
    fflush(stdin);
	printf("\t\t\tUpdate? (Y to update any other key to not)");
	ch = getchar();
	ch = toupper(ch);
	fflush(stdin);
	if(ch == 'Y')
	{
		printf("\t\t\tEnter new value: ");
		return(1);
	}
	else
		return(0);
}


