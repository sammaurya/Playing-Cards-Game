#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>

struct cards
{
    char card;
    int value;
    int index;
    struct cards *next;
};
struct cards *first=NULL,*Player_1=NULL,*Player_2=NULL,*Player_3=NULL,*Player_4=NULL;
//Functions
void Insert(int [],char);   //Create Linked List of 52 Cards
void GetPlayerName();       //Get Player Names
void Shuffle();             //Shuffle Cards
void Distribute();          //Distribute Card Among 4 Players
void PrintCard(struct cards *); //Shows Card in Console

int i,pos=1,play=1,round=0;
char name_1[20],name_2[20],name_3[20],name_4[20]; //Holds Players Name
char teamA[13],teamB[13],choice;            //Holds Score List
int wonA=0,wonB=0;                          //Holds Number of Times Match Won
int main()
{
    int card[]={2,3,4,5,6,7,8,9,10,15,20,25,30};  //Cards, 15 is Jack,20 is Queen,25 is King,30 is Ace
    Insert(card,'D');
    Insert(card,'H');
    Insert(card,'S');
    Insert(card,'C');
    srand(time(0));
    START:
    system("cls");
    printf("********** PLAYING CARDS**********\n\n");
    GetPlayerName();
    Shuffle();
    printf("Cards Shuffled\n");
    Distribute();
    printf("Press Enter to Distribute Cards\n");
    getch();
    printf("Cards Distributed\n\n");
    printf("Press Enter to START GAME\n");
    getch();
    struct cards *player1,*player2,*player3,*player4;
    player1=Player_1;
    player2=Player_2;
    player3=Player_3;
    player4=Player_4;
    round=0;
    while(play==1&&round!=13)     //Game Loop : 13 Rounds
    {
        system("cls");
        printf("********** PLAYING CARDS**********\n\n");
        printf("Press 1 to Play Round %d : ",round+1);
        scanf("%d",&play);
        printf("\n\t %s\t\t\t\t  %s\n\n",name_1,name_4);
        printf("\t    ");
        PrintCard(player1);
        printf("\t  ");
        PrintCard(player4);
        printf("\n\n\t    ");
        PrintCard(player2);
        printf("\t  ");
        PrintCard(player3);
        printf("\n\n");
        printf("\t %s\t\t\t\t  %s\n\n",name_2,name_3);
        //SCORE
        int sum1=player1->value+player3->value;
        int sum2=player2->value+player4->value;
        printf("Team A Scored : %d + %d = %d",player1->value,player3->value,sum1);
        printf("\nTeam B Scored : %d + %d = %d",player2->value,player4->value,sum2);
        if(sum1>sum2)
        {
            printf("\nTeam A : WON");
            teamA[round]='W';
            teamB[round]='L';
        }
        else if(sum1<sum2)
        {
            printf("\nTeam B : WON");
            teamA[round]='L';
            teamB[round]='W';
        }
        else
        {
            printf("\nTie");
            teamA[round]=teamB[round]='T';
        }
        getch();
        round++;
        player1=player1->next;
        player2=player2->next;
        player3=player3->next;
        player4=player4->next;
    }
    printf("\n\nFinal Result : \n");
    printf("\n\tTeam A : ");
    for(i=0;i<round;++i)
    {
        printf("%c ",teamA[i]);
        if(teamA[i]=='W')
            wonA++;
    }
    printf("\n\tTeam B : ");
    for(i=0;i<round;++i)
    {
        printf("%c ",teamB[i]);
        if(teamB[i]=='W')
            wonB++;
    }
    if(wonA>wonB)
        printf("\n\nTeam A Has WON\n");
    else if(wonA<wonB)
        printf("\n\nTeam B Has WON\n");
    else
        printf("\n\nGame Draw\n");
    getch();
    printf("\nPress Y to Play Again or N to Exit : ");
    scanf(" %c",&choice);
    if(choice=='Y'||choice=='y')
        goto START;
    return 0;
}

void GetPlayerName()
{
    printf("Enter Players Name : \n");
    printf("\nTeam A : ");
    printf("\n\tPlayer 1 : ");
    scanf(" %[^\n]s",name_1);
    printf("\tPlayer 2 : ");
    scanf(" %[^\n]s",name_2);
    printf("\nTeam B : ");
    printf("\n\tPlayer 3 : ");
    scanf(" %[^\n]s",name_3);
    printf("\tPlayer 4 : ");
    scanf(" %[^\n]s",name_4);
}

void Insert(int arr[],char c)
{
    struct cards *ptr,*cpt;
    i=0;
    if(first==NULL)
    {
        ptr=(struct cards *)malloc(sizeof(struct cards));
        ptr->card=c;
        ptr->value=arr[i];
        ptr->index=pos;
        ptr->next=NULL;
        first=ptr;
        while(i<12)
        {
            i++;
            cpt=(struct cards *)malloc(sizeof(struct cards));
            cpt->card=c;
            cpt->value=arr[i];
            ptr->next=cpt;
            ptr=cpt;
            ptr->index=++pos;
        }
        ptr->next=NULL;
    }
    else
    {
        ptr=first;
        while(ptr->next!=NULL)
        {
            ptr=ptr->next;
        }
        i=0;
         while(i<13)
        {
            cpt=(struct cards *)malloc(sizeof(struct cards));
            cpt->card=c;
            cpt->value=arr[i];
            ptr->next=cpt;
            ptr=cpt;
            ptr->index=++pos;
            i++;
        }
        ptr->next=NULL;

    }
}
void Shuffle()
{
    int n,temp;
    struct cards *ptr,*cpt1,*cpt2;
    printf("Enter Number of Times To Shuffle : ");
    scanf("%d",&n);
    while(n>0)
    {
        int mix=rand()%30+1;
        while(mix>0)
        {
            int ind=rand()%52+1;
            int index1=rand()%ind;
            int index2=rand()%52+1;
            ptr=first;
            while(ptr->next!=NULL)
            {
                if(ptr->index==index1)
                {
                    cpt1=ptr;
                }
                if(ptr->index==index2)
                {
                    cpt2=ptr;
                }
                ptr=ptr->next;
            }
            temp=cpt1->index;
            cpt1->index=cpt2->index;
            cpt2->index=temp;
            mix--;
        }
        n--;
    }
}
void Distribute()
{
    int i=0,j=0,k=0,l=0;
    struct cards *ptr,*player1,*player2,*player3,*player4,*cpt;
    ptr=first;
    while(ptr!=NULL)
    {
        if(ptr->index<=13)
        {
            if(Player_1==NULL)
            {
                player1=(struct cards *)malloc(sizeof(struct cards));
                player1->card=ptr->card;
                player1->value=ptr->value;
                player1->index=++i;
                player1->next=NULL;
                Player_1=player1;
            }
            else
            {
                player1=Player_1;
                while(player1->next!=NULL)
                {
                    player1=player1->next;
                }
                cpt=(struct cards *)malloc(sizeof(struct cards));
                cpt->card=ptr->card;
                cpt->value=ptr->value;
                cpt->index=++i;
                player1->next=cpt;
                player1=cpt;
                player1->next=NULL;
            }

        }
        else if(ptr->index>13&&ptr->index<=26)
        {
            if(Player_2==NULL)
            {
                player2=(struct cards *)malloc(sizeof(struct cards));
                player2->card=ptr->card;
                player2->value=ptr->value;
                player2->index=++j;
                player2->next=NULL;
                Player_2=player2;
            }
            else
            {
                player2=Player_2;
                while(player2->next!=NULL)
                {
                    player2=player2->next;
                }
                cpt=(struct cards *)malloc(sizeof(struct cards));
                cpt->card=ptr->card;
                cpt->value=ptr->value;
                cpt->index=++j;
                player2->next=cpt;
                player2=cpt;
                player2->next=NULL;
            }

        }
        else if(ptr->index>26&&ptr->index<=39)
        {
            if(Player_3==NULL)
            {
                player3=(struct cards *)malloc(sizeof(struct cards));
                player3->card=ptr->card;
                player3->value=ptr->value;
                player3->index=++k;
                player3->next=NULL;
                Player_3=player3;
            }
            else
            {
                player3=Player_3;
                while(player3->next!=NULL)
                {
                    player3=player3->next;
                }
                cpt=(struct cards *)malloc(sizeof(struct cards));
                cpt->card=ptr->card;
                cpt->value=ptr->value;
                cpt->index=++k;
                player3->next=cpt;
                player3=cpt;
                player3->next=NULL;
            }

        }
        else
        {
            if(Player_4==NULL)
            {
                player4=(struct cards *)malloc(sizeof(struct cards));
                player4->card=ptr->card;
                player4->value=ptr->value;
                player4->index=++l;
                player4->next=NULL;
                Player_4=player4;
            }
            else
            {
                player4=Player_4;
                while(player4->next!=NULL)
                {
                    player4=player4->next;
                }
                cpt=(struct cards *)malloc(sizeof(struct cards));
                cpt->card=ptr->card;
                cpt->value=ptr->value;
                cpt->index=++l;
                player4->next=cpt;
                player4=cpt;
                player4->next=NULL;
            }
        }
        ptr=ptr->next;
    }
}

void PrintCard(struct cards *player)
{
    if(player->card=='D')
    {
        if(player->value==30)
        {
            printf("Ace of Diamond");
        }
        else if(player->value==25)
        {
            printf("King of Diamond");
        }
        else if(player->value==20)
        {
            printf("Queen of Diamond");
        }
        else if(player->value==15)
        {
            printf("Jack of Diamond");
        }
        else
        {
            printf("%d of Diamond",player->value);
        }
    }
    else if(player->card=='H')
    {
        if(player->value==30)
        {
            printf("Ace of Heart");
        }
        else if(player->value==25)
        {
            printf("King of Heart");
        }
        else if(player->value==20)
        {
            printf("Queen of Heart");
        }
        else if(player->value==15)
        {
            printf("Jack of Heart");
        }
        else
        {
            printf("%d of Heart",player->value);
        }
    }
    else if(player->card=='S')
    {
        if(player->value==30)
        {
            printf("Ace of Spade");
        }
        else if(player->value==25)
        {
            printf("King of Spade");
        }
        else if(player->value==20)
        {
            printf("Queen of Spade");
        }
        else if(player->value==15)
        {
            printf("Jack of Spade");
        }
        else
        {
            printf("%d of Spade",player->value);
        }
    }
    else
    {
        if(player->value==30)
        {
            printf("Ace of Club");
        }
        else if(player->value==25)
        {
            printf("King of Club");
        }
        else if(player->value==20)
        {
            printf("Queen of Club");
        }
        else if(player->value==15)
        {
            printf("Jack of Club");
        }
        else
        {
            printf("%d of Club",player->value);
        }
    }

}
