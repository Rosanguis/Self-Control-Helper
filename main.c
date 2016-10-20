#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
FILE *pTime;

void shutd(void);
void timeLimit(int timeOnline);
int cycle(int *i,int timeOnline);
int on(int *i,int timeOnline);
void off(int *i,int timeOnline);

int main()
{
    int choice,timeOnline;

    do
    {
        printf("You'd like to£º\n");
        printf("(1)Shut down at 22:00;\n");
        printf("2¡¢Internet time control;\n");
        printf("3¡¢Exit;\n");

        scanf(" %d",&choice);

        switch(choice)
        {
        case(1):printf("The computer is to be shut down at 22:00\n");
        shutd();
        break;
        case(2):printf("How often would you like to have a break?\n");
        scanf(" %d",&timeOnline);
        printf("You will have a break every %d minutes ^_^\n",timeOnline);
        timeLimit(timeOnline);
        case(3):exit(1);
        default:puts("Input error. Please enter 1 to 3");
        }
    }while((choice<1)||(choice>3));

    return 0;
}

void shutd(void)
{
    int hour,result;
    time_t t;
    struct tm *tblock;

    do
    {
    t=time(0);
    tblock=localtime(&t);
    pTime=fopen("C:\\time.txt","w+");

    if(pTime==0)
    {
        printf("Error 01\n");
    }

    fseek(pTime,0,SEEK_SET);
    fprintf(pTime,"%s",asctime(tblock));
    fseek(pTime,-15,SEEK_END);
    fscanf(pTime,"%d",&hour);
    }while(hour<22);

    if(hour==22)
    {
        result=MessageBox(0,"It is 22:00 now. The system is about to shut down.","Shutdown",MB_OK);
        if(result==1)
        {
            system("shutdown -p");
            exit(1);
        }
        else
        {
            printf("Error 02\n");
        }
    }
}

void timeLimit(int timeOnline)
{
    int i;
    i=cycle(&i,timeOnline);
    if(i==1);
    {
        off(&i,timeOnline);
    }

}

int cycle(int *i,int timeOnline)
{
    do
    {
        *i=system("ping 202.108.22.5");
        system("cls");
    }while(*i==1);

    while(*i==0)
    {
        *i=on(i,timeOnline);
        system("cls");
    }

    return *i;
}

int on(int *i,int timeOnline)
{
    int result;
    clock_t start,finish;
    double duration;



    start=clock();

    for(*i;*i==0;*i=system("ping 202.108.22.5"))
    {
        finish=clock();
        duration=((double)(finish-start)/CLOCKS_PER_SEC)/60;
        if(duration>=timeOnline)
        {
            break;
        }

    }

   result=MessageBox(0,"Time's up. Please take a break.","Notice",MB_OK);
    if(result==0)
    {
       printf("Error 03\n");
    }
    else
    {
       system("rundll32.exe user32.dll LockWorkStation");
    }
       
    return *i;
}

void off(int *i,int timeOnline)
{
    int result;

    result=MessageBox(0,"You're offline now. Would you like to exit?","Notice",MB_YESNO);

    switch(result)
    {
        case(0):printf("Error 04\n");
        case(6):exit(1);
        case(7):cycle(i,timeOnline);
    }
}

