#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<time.h>
//10=prison
//19=club
//28=rest house
//0=start
//int WhichColor(char c);
void SetColor(int ForgC);
//int numberLength(int n);
//struct Board* gotoNode(struct Board* node,int n);
struct Board
{
    char name[25];
    char type;
    int color;
    int br_number;
    int price;
    int rent;
    int owned;
    int no_of_houses;
    int cost_of_house;
    int extra_rent;
    int mortgage;
    struct Board* next;
    struct Board* prev;
};

struct Player
{
    char name[20];
    int player_number;
    struct Board* currentPosition;
    int balance;
    int loan;
    int property[36];
    int play_next;
    int turns;
    int networth;
    struct Player* nextPlayer;
    struct Player* prevPlayer;
};

int WhichColor(char c)
{
    switch(c)
    {
        case 'b':return 9;break;
        case 'w':return 15;break;
        case 'r':return 12;break;
        case 'c':return 11;break;
        case 'p':return 13;break;
        case 'o':return 6;break;
        case 'g':return 10;break;
        case 'y':return 14;break;
    }
}

struct Board* gotoNode(struct Board* node,int n)
{
    while(node->br_number!=n)
    {
        node=node->next;
    }
    return node;
};

struct Player* gotoPlayer(struct Player* node,int n)
{
    while(node->player_number!=n)
    {
        node=node->nextPlayer;
    }
    return node;
};

int numberLength(int n)
{
    int c=0;
    if(n==0)
        return 1;
    while(n!=0)
    {
        c++;
        n=n/10;
    }
    return c;
}

struct Board* createBoard(int R,int C, char name_places[R][C],int prices[],int rent_places[],int cost_of_houses[],int mortgage_places[])
{
    struct Board* head=NULL,*temp,*temp1,*tail;
    for(int i=0;i<R;i++)
    {
        temp=(struct Board*)malloc(sizeof(struct Board));
        temp->owned=-1;
        temp->br_number=i+1;
        temp->next=NULL;
        temp->prev=NULL;
        temp->no_of_houses=0;
        temp->cost_of_house=cost_of_houses[i];
        temp->price=prices[i];
        temp->rent=rent_places[i];
        temp->extra_rent=rent_places[i];
        temp->mortgage=mortgage_places[i];
        temp->type=name_places[i][0];
        if(head== NULL)
        {
            head = temp;
            strcpy(temp->name,*(name_places+i)+1);
            temp->color=WhichColor('w');
            temp->owned=-2;
        }
        else
        {
            temp1=head;
            while(temp1->next!=NULL)
            {
                temp1=temp1->next;
            }
            temp1->next=temp;
            temp->prev=temp1;
            if(name_places[i][0]=='p')
            {
                strcpy(temp->name,*(name_places+i)+2);
                temp->color=WhichColor(name_places[i][1]);
            }
            else
            {
                if(name_places[i][0]=='x' || name_places[i][0]=='o' || name_places[i][0]=='c')
                    {temp->owned=-2;}
                strcpy(temp->name,*(name_places+i)+1);
                temp->color=WhichColor('w');
            }
        }
        if(i==R-1)
        {tail=temp;}
    }
    head->prev=tail;
    tail->next=head;
    printf("BOARD CREATED!\n");
    return head;
};

void displayBoard(struct Board* board,struct Player* player)
{
    //first line
    struct Board* first=board;
    printf("+");
    for(int i=0;i<9;i++)
    {
        printf("---------------+");
        first=first->next;
    }
    printf("---------------+");
    for(int i=1;i<5;i++)
    {
        printf("\n|");
        if(i==1)
        {
            for(int x=1;x<11;x++)
            {
                char str[15],str2;
                int abc=0;
                struct Player* np1=player,*currentPlayer=player;
                do
                {
                    if(np1->currentPosition->br_number==first->br_number)
                    {
                    //str2=np1->player_number;
                    str[abc]=np1->player_number+'0';
                    abc++;
                    //strcat(str,(char)(player->player_number));
                    }
                    np1=np1->nextPlayer;
                }
                while(np1->player_number!=currentPlayer->player_number);
                str[abc]='\0';
                int lo=(15-strlen(str))/2,hi=(15-strlen(str))/2;
                if((15-strlen(str))%2!=0)
                {hi++;};
                for(int b=0;b<lo;b++)
                {
                    printf(" ");
                }
                printf("%s",str);
                first=first->next;
                SetColor(15);
                for(int c=0;c<hi;c++)
                {
                    printf(" ");
                }
                printf("|");
            }
        }
        else
        if(i==2)
        {
            for(int i=0;i<10;i++)
            {
                first=first->prev;
            }
            for(int x=1;x<11;x++)
            {
                int lo=(15-strlen(first->name))/2,hi=(15-strlen(first->name))/2;
                if((15-strlen(first->name))%2!=0)
                {hi++;};
                for(int b=0;b<lo;b++)
                {
                    printf(" ");
                }
                SetColor(first->color);
                printf("%s",first->name);
                first=first->next;
                SetColor(15);
                for(int c=0;c<hi;c++)
                {
                    printf(" ");
                }
                printf("|");
            }
        }
        else
        if(i==3)
        {
            for(int i=0;i<10;i++)
            {
                first=first->prev;
            }
            for(int x=1;x<11;x++)
            {
                int lo=(15-numberLength(first->price))/2,hi=(15-numberLength(first->price))/2;
                if((15-numberLength(first->price))%2!=0)
                {hi++;};
                for(int b=0;b<lo;b++)
                {
                    printf(" ");
                }
                SetColor(first->color);
                if(first->type=='p' || first->type=='t' || first->type=='r')
                    printf("%d",first->price);
                else
                    printf(" ");
                first=first->next;
                SetColor(15);
                for(int c=0;c<hi;c++)
                {
                    printf(" ");
                }
                printf("|");
            }
        }
        else
        {
            for(int j=0;j<10;j++)
            {
                printf("               |");
            }
        }
    }
    printf("\n+");
    for(int i=0;i<10;i++)
    {
        printf("---------------+");
    }
    //
    //BRIDGE
    first=gotoNode(board,9);
    struct Board* second=gotoNode(board,20);
    for(int i=1;i<9;i++)
    {
        for(int j=1;j<=5;j++)
        {
            printf("\n");
            if(j==5)
                printf("+---------------+");
            else
            if(j==1)
            {
                printf("|");
                char str[15],str2;
                int abc=0;
                struct Player* np1=player,*currentPlayer=player;
                do
                {
                    if(np1->currentPosition->br_number==first->br_number)
                    {
                    //str2=np1->player_number;
                    str[abc]=np1->player_number+'0';
                    abc++;
                    //strcat(str,(char)(player->player_number));
                    }
                    np1=np1->nextPlayer;
                }
                while(np1->player_number!=currentPlayer->player_number);
                str[abc]='\0';
                int lo=(15-strlen(str))/2,hi=(15-strlen(str))/2;
                if((15-strlen(str))%2!=0)
                {hi++;};
                for(int b=0;b<lo;b++)
                {
                    printf(" ");
                }
                printf("%s",str);
                SetColor(15);
                for(int c=0;c<hi;c++)
                {
                    printf(" ");
                }
                printf("|");
            }
            else
            if(j==2)
            {
                printf("|");
                int lo=(15-strlen(first->name))/2,hi=(15-strlen(first->name))/2;
                if((15-strlen(first->name))%2!=0)
                {hi++;};
                for(int b=0;b<lo;b++)
                {
                    printf(" ");
                }
                SetColor(first->color);
                printf("%s",first->name);
                SetColor(15);
                for(int c=0;c<hi;c++)
                {
                    printf(" ");
                }
                printf("|");
            }
            else
            if(j==3)
            {
                printf("|");
                int lo=(15-numberLength(first->price))/2,hi=(15-numberLength(first->price))/2;
                if((15-numberLength(first->price))%2!=0)
                {hi++;};
                for(int b=0;b<lo;b++)
                {
                    printf(" ");
                }
                SetColor(first->color);
                if(first->type=='p' || first->type=='t' || first->type=='r')
                    printf("%d",first->price);
                else
                    printf(" ");
                SetColor(15);
                for(int c=0;c<hi;c++)
                {
                    printf(" ");
                }
                printf("|");
            }
            else
                printf("|               |");
            for(int k=0;k<8;k++)
            {
                if(i==8 && j==5)
                    printf("---------------+");
                else
                    printf("               ");
            }
            if(i==8 && j==5)
                    printf("---------------+");
            else
            if(j==5)
                printf("       +---------------+");
            else
            if(j==1)
            {
                printf("       |");
                char str[15],str2;
                int abc=0;
                struct Player* np1=player,*currentPlayer=player;
                do
                {
                    if(np1->currentPosition->br_number==second->br_number)
                    {
                    //str2=np1->player_number;
                    str[abc]=np1->player_number+'0';
                    abc++;
                    //strcat(str,(char)(player->player_number));
                    }
                    np1=np1->nextPlayer;
                }
                while(np1->player_number!=currentPlayer->player_number);
                str[abc]='\0';
                int lo=(15-strlen(str))/2,hi=(15-strlen(str))/2;
                if((15-strlen(str))%2!=0)
                {hi++;};
                for(int b=0;b<lo;b++)
                {
                    printf(" ");
                }
                printf("%s",str);
                SetColor(15);
                for(int c=0;c<hi;c++)
                {
                    printf(" ");
                }
                printf("|");
            }
            else
            if(j==2)
            {
                printf("       |");
                int lo=(15-strlen(second->name))/2,hi=(15-strlen(second->name))/2;
                if((15-strlen(second->name))%2!=0)
                {hi++;};
                for(int b=0;b<lo;b++)
                {
                    printf(" ");
                }
                SetColor(second->color);
                printf("%s",second->name);
                SetColor(15);
                for(int c=0;c<hi;c++)
                {
                    printf(" ");
                }
                printf("|");
            }
            else
            if(j==3)
            {
                printf("       |");
                int lo=(15-numberLength(second->price))/2,hi=(15-numberLength(second->price))/2;
                if((15-numberLength(second->price))%2!=0)
                {hi++;};
                for(int b=0;b<lo;b++)
                {
                    printf(" ");
                }
                SetColor(second->color);
                if(second->type=='p' || second->type=='t' || second->type=='r')
                    printf("%d",second->price);
                else
                    printf(" ");
                SetColor(15);
                for(int c=0;c<hi;c++)
                {
                    printf(" ");
                }
                printf("|");
            }
            else
                printf("       |               |");
        }
        first=first->prev;
        second=second->next;
    }
    //
    //LAST LINE
    first=board;
    for(int i=1;i<5;i++)
    {
        printf("\n|");
        if(i==1)
        {
            for(int x=1;x<11;x++)
            {
                char str[15],str2;
                int abc=0;
                struct Player* np1=player,*currentPlayer=player;
                do
                {
                    if(np1->currentPosition->br_number==first->br_number)
                    {
                    //str2=np1->player_number;
                    str[abc]=np1->player_number+'0';
                    abc++;
                    str[abc]=' ';
                    abc++;
                    //strcat(str,(char)(player->player_number));
                    }
                    np1=np1->nextPlayer;
                }
                while(np1->player_number!=currentPlayer->player_number);
                str[abc]='\0';
                int lo=(15-strlen(str))/2,hi=(15-strlen(str))/2;
                if((15-strlen(str))%2!=0)
                {hi++;};
                for(int b=0;b<lo;b++)
                {
                    printf(" ");
                }
                printf("%s",str);
                first=first->prev;
                SetColor(15);
                for(int c=0;c<hi;c++)
                {
                    printf(" ");
                }
                printf("|");
            }
        }
        else
        if(i==2)
        {
            for(int k=0;k<10;k++)
            {
                first=first->next;
            }
            for(int x=1;x<11;x++)
            {
                int lo=(15-strlen(first->name))/2,hi=(15-strlen(first->name))/2;
                if((15-strlen(first->name))%2!=0)
                {hi++;};
                for(int b=0;b<lo;b++)
                {
                    printf(" ");
                }
                SetColor(first->color);
                printf("%s",first->name);
                first=first->prev;
                SetColor(15);
                for(int c=0;c<hi;c++)
                {
                    printf(" ");
                }
                printf("|");
            }
        }
        else
        if(i==3)
        {
            for(int k=0;k<10;k++)
            {
                first=first->next;
            }
            for(int x=1;x<11;x++)
            {
                int lo=(15-numberLength(first->price))/2,hi=(15-numberLength(first->price))/2;
                if((15-numberLength(first->price))%2!=0)
                {hi++;};
                for(int b=0;b<lo;b++)
                {
                    printf(" ");
                }
                SetColor(first->color);
                if(first->type=='p' || first->type=='t' || first->type=='r' || first->name[0]=='S')
                    printf("%d",first->price);
                else
                    printf(" ");
                first=first->prev;
                SetColor(15);
                for(int c=0;c<hi;c++)
                {
                    printf(" ");
                }
                printf("|");
            }
        }
        else
        {
            for(int j=0;j<10;j++)
            {
                printf("               |");
            }
        }
    }
    printf("\n+");
    for(int i=0;i<10;i++)
    {
        printf("---------------+");
    }
}

void SetColor(int ForgC)
{
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

struct Player *createnew(char *str,struct Board* board,int num)
{
    struct Player *ptr1;
    ptr1=(struct Player*)malloc(sizeof(struct Player));

    strcpy(ptr1->name,str);
    ptr1->player_number=num;

    ptr1->currentPosition=board;

    ptr1->play_next=0;
    ptr1->balance=30000;
    ptr1->networth=ptr1->balance;
    ptr1->loan=0;
    for(int i=0;i<36;i++)
    {
        ptr1->property[i]=0;
    }
    ptr1->turns=1;
    ptr1->nextPlayer=NULL;
    ptr1->prevPlayer=NULL;
    return ptr1;
}

struct Player* insert_node(struct Player *np,struct Player* root)
{
    if(root==NULL)
    {
        root=np;
    }
    else
    {
        struct Player *temp=root;
        while(temp->nextPlayer!=NULL)
        {
            temp=temp->nextPlayer;
        }
        np->prevPlayer=temp;
        temp->nextPlayer=np;
    }
    printf("Player details added. Welcome %s!!\n\n",np->name);
    return root;
};

struct Queue
{
    int front;
    int rear;
    int * arr;
    int size;
};

struct Queue* createQueue(int size)
{
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->size = size;
    queue->front=-1;
    queue->rear=-1;
    queue->arr= (int*)malloc(queue->size * sizeof(int));
    return queue;
}

int isfull(struct Queue* queue)
{
    if(queue->front==0 && queue->rear==5)
    {
        return 1;
    }
    if(queue->front==queue->rear+1)
    {
        return 1;
    }
    return 0;
}

void enqueue(struct Queue* queue,int e)
{
    if(queue->front==-1)
        queue->front=0;
    queue->rear=(queue->rear+1)%6;
    queue->arr[queue->rear]=e;
}

int dequeue(struct Queue* queue)
{
    int e=queue->arr[queue->front];
    if(queue->front==queue->rear)
    {
        queue->front=-1;
        queue->rear=-1;
    }
    else
        queue->front=(queue->front+1)%6;
    return e;
}

int isempty(struct Queue* queue)
{
    if(queue->front==-1)
    {
        return 1;
    }
    return 0;
}

void peek(struct Queue* queue)
{
    if(isempty(queue))
        printf("QUEUE EMPTY!\n");
    else{
        printf("peek: %d\n",queue->arr[queue->front]);
    }
}

void displayQueue(struct Queue* queue)
{
    if(!isempty(queue))
    {
        if(queue->rear>=queue->front)
        {
        for(int i=queue->front;i<=queue->rear;i++)
        {
            printf(" %d ",queue->arr[i]);
        }
        printf("\n");
        }
        else
        {
            for(int i=queue->front;i<6;i++)
            {
            printf(" %d ",queue->arr[i]);
            }
            for(int i=0;i<=queue->rear;i++)
            {
            printf(" %d ",queue->arr[i]);
            }
            printf("\n");
        }
    }
}

void swap(int i,int j,struct Queue* queue)
{
    int x=queue->arr[i];
    queue->arr[i]=queue->arr[j];
    queue->arr[j]=x;
}

void create_CommunityChest_chance(struct Queue* community_chest,struct Queue* chance)
{
    int random[6],random2[6];
    srand(time(NULL));
    for (int f=0;f<6;f++){
        random[f]=(rand()%6)+1;
        enqueue(community_chest,f+1);
        enqueue(chance,f+1);
        random2[f]=(rand()%6)+1;
    }
    for(int i=0;i<6;i+=2)
    {
        swap(random[i]-1,random[i+1]-1,community_chest);
        swap(random2[i]-1,random2[i+1]-1,chance);
    }
    printf("CHEST AND CHANCE CREATED!\n");
}

void BankTransaction(int money,struct Player* player,int ch)
{
    if(ch==1)
    {
        player->balance+=money;
        player->networth+=money;
        printf("\nAmount of Rs %d/- has been credited to your account %s\n",money,player->name);
    }
    else{
        if(player->balance>money)
        {
            player->balance-=money;
            player->networth-=money;
            printf("\nAmount of Rs %d/- has been debited from your account %s\n",money,player->name);
        }
        else
        {
            player->loan+=money-player->balance;
            player->balance=0;
            printf("\nOops looks like you had insufficient balance in your account %s, loan of Rs %d/- has been taken from bank.\n",player->name,player->loan);
        }
    }
}

void community_chest_func(int key,struct Player* player)
{
    switch(key)
    {
        case 1:{
            printf("\n Go to Jail!");
            printf("\n You have been sent to jail!");
            player->currentPosition=gotoNode(player->currentPosition,10);
            player->play_next=3;
            break;}
        case 2:{
            printf("\n Receive Interest on shares from Bank of Rs 1500/-");
            BankTransaction(1500,player,1);
            break;}
        case 3:{
            printf("\n Marriage Celebration, Pay Bank Rs 2000/- ");
            BankTransaction(2000,player,2);
            break;}
        case 4:{
            printf("\n It's your birthday, receive from each player Rs 500/- ");
            struct Player* Current_player=player;
            do
            {
                player=player->nextPlayer;
                BankTransaction(500,Current_player,1);
                BankTransaction(500,player,2);
            }
            while(player->nextPlayer->player_number!=Current_player->player_number);
            break;}
        case 5:{
            struct Board* loc=player->currentPosition;
            int rep=0;
            printf("\n Make general repair on all your properties. For Each house owned pay Rs 100/-");
            for(int i=0;i<36;i++)
            {
                if(player->property[i]!=0)
                {
                    loc=gotoNode(loc,player->property[i]);
                    rep+=(loc->no_of_houses)*100;
                }
            }
            BankTransaction(rep,player,2);
            }
        case 6:{
            printf("\n First prize in reality TV show, Get Rs 2500/-");
            BankTransaction(2500,player,1);}
    }
}

void chance_func(int key,struct Player* player)
{
    switch(key)
    {
        case 1:{
            printf("\n Lottery prize Rs 2500/- !");
            BankTransaction(2500,player,1);
            break;}
        case 2:{
            printf("\n Fine of Rs 1500/- for accident due to driving under the liqor influence.");
            BankTransaction(1500,player,2);
            break;}
        case 3:{
            printf("\n Go back to Mumbai. If you have to pass starting point, collect Rs 1500/- and go to Agra!");
            if(player->currentPosition->br_number<19)
            {
                printf("\n You have reached Mumbai.");
                player->currentPosition=gotoNode(player->currentPosition,1);}
            else{
                printf("\n You have reached Agra.");
                player->currentPosition=gotoNode(player->currentPosition,26);}
            break;}
        case 4:{
            printf("\n Loss due to fire in godown, Rs 3000/-");
            BankTransaction(3000,player,2);
            break;}
        case 5:{
            printf("\n Best performance in Export, collect Rs 3000/-");
            BankTransaction(3000,player,1);
            break;}
        case 6:{
            printf("\nGo to rest house, you cannot play the next turn.");
            player->play_next=0;
            struct Player* Current_player=player;
            do
            {
                player=player->nextPlayer;
                BankTransaction(100,Current_player,1);
                BankTransaction(100,player,2);
            }
            while(player->nextPlayer->player_number!=Current_player->player_number);
            player->currentPosition=gotoNode(player->currentPosition,28);
            break;}
    }
}

struct Player* deletePlayer(struct Player* player,struct Player* tail)
{
    if(player->nextPlayer==player)
        return NULL;
    else
    {
        if(player==tail)
            tail=player->prevPlayer;
        player->prevPlayer->nextPlayer=player->nextPlayer;
        player->nextPlayer->prevPlayer=player->prevPlayer;
    }
    return tail;
}

void displayPlayer(struct Player* player,struct Board* board)
{
    printf("\n_______________________________________________________________\nPLAYER DETAILS\n");
    struct Player* currentplayer= player;

    do
    {
        struct Board* temp = board;
        printf("\n\nPLAYER NUMBER: %d PLAYER NAME: %s BALANCE: %d LOAN: %d\n",player->player_number,player->name,player->balance,player->loan);
        printf("CURRENT POSITION: %s\n",player->currentPosition->name);
        printf("Properties owned: ");
        for(int i=0;i<36;i++)
        {
            if(player->property[i]==1)
            {
                int d=0;
                while(d<i)
                {
                    temp=temp->next;
                    d++;
                }
                SetColor(temp->color);
                printf(" %s,",temp->name);
                SetColor('w');
            }
        }
        player=player->nextPlayer;
    }
    while(player->player_number!= currentplayer->player_number);
    printf("\n_______________________________________________________________\n");
}

int dice()
{
    int num = (rand() % 6)+1;
    return num;
}

void displayDice(int num)
{
    printf("\n");
    switch(num)
        {
        case 1:printf(" -----\n|  .  |\n|     |\n -----");break;
        case 2:printf(" -----\n| . . |\n|     |\n -----");break;
        case 3:printf(" -----\n| . . |\n|  .  |\n -----");break;
        case 4:printf(" -----\n| . . |\n| . . |\n -----");break;
        case 5:printf(" -----\n| ... |\n| . . |\n -----");break;
        case 6:printf(" -----\n| ... |\n| ... |\n -----");break;
        }
    printf("\n");
}

void loading(int n)
{
    for(int i=0;i<n;i++)
    {
        if(i%2==0)
            printf("LOADING -\n");
        else
        if(i%3==1)
            printf("LOADING \\\n");
        else
            printf("LOADING /\n");
        for(int i=0;i<n;i++)
            printf("-");
        printf("\n[");
        for(int j=0;j<i;j++)
        {
            printf("|");
        }
        for(int k=i;k<n-2;k++)
        {
            printf(" ");
        }
        printf("]\n");
        for(int i=0;i<n;i++)
            printf("-");
        printf("\n");
        system("cls");
    }
}

void build_house(struct Player* player)
{
    if(player->balance > player->currentPosition->cost_of_house)
    {
        BankTransaction(player->currentPosition->cost_of_house,player,2);
        player->currentPosition->no_of_houses+=1;
        player->currentPosition->extra_rent+=(int)((player->currentPosition->cost_of_house)/2);
        printf("\nBuilt a house!");
    }
    else
        printf("\nSorry..insufficient balance,cannot build a house");
}

void Game_Flow(struct Board* board,struct Player* player,struct Queue* community_chest,struct Queue* chance)
{
    struct Player* tail=player->prevPlayer;
    struct Board* temp1; //for wealth tax
    struct Player* pla; //for property
    int choice,total_turns=0;
    char c;
    while(1)
    {
        displayBoard(board,player);
        displayPlayer(player,board);
        if(player->play_next==0)
        {
            int sum=0;
            printf("\n%s Please roll the dice (press 1): ",player->name);
            scanf("%d",&choice);
            while(choice!=1)
            {
                printf("PLEASE ENTER 1:");
                scanf("%d",&choice);
            }
            int d1=dice(),d2=dice();
            printf("\nDices Shows:\n");
            displayDice(d1);
            displayDice(d2);
            for(int i=0;i<d1+d2;i++)
            {
                player->currentPosition=player->currentPosition->next;
                if(strcmp(player->currentPosition->name,"START")==0)
                {
                    printf("\nSince you passed START..");
                    player->turns+=1;
                    BankTransaction(1500,player,1);
                }
            }
            printf("\nYou have landed at: ");
            SetColor(player->currentPosition->color);
            printf("%s",player->currentPosition->name);
            SetColor('w');
            if(strcmp(player->currentPosition->name,"START")==0)
            {
                goto label;
            }
            else
            if(strcmp(player->currentPosition->name,"INCOME TAX")==0)
            {
                for(int i=0;i<36;i++)
                {
                    if(player->property[i]==1)
                        sum+=50;
                }
                if(sum>500)
                    sum=500;
                printf("\nRs %d/- will be deducted. \n",sum);
                BankTransaction(sum,player,1);
                printf("Remaining balance of player: %d\n",player->balance);
            }
            else
            if(strcmp(player->currentPosition->name,"WEALTH TAX")==0)
            {
                temp1=player->currentPosition;
                do
                {
                    if(temp1->owned==player->player_number)
                    {
                        sum+=(temp1->no_of_houses)*50;
                    }
                    temp1=temp1->next;
                }
                while(temp1->br_number!=temp1->br_number);
                if(sum>500)
                    sum=500;
                printf("%d will be deducted. \n",sum);
                BankTransaction(sum,player,1);
                printf("Remaining balance of player: %d\n",player->balance);
            }
            else
            if(strcmp(player->currentPosition->name,"PRISION")==0)
            {
                player->play_next=3;
                printf("\nPay Rs 500/- to get out of the prison, or miss %d turns..(PRESS 1 to pay or 0 to continue)",player->play_next);
                scanf("%d",&choice);
                if(choice == 1){
                    BankTransaction(500,player,2);
                    player->play_next=0;
                }
                else
                    {printf("\nturn missed!");
                    player->play_next-=1;}
            }
            else
            if(strcmp(player->currentPosition->name,"REST HOUSE")==0)
            {
                printf("\nCollect Rs 100/- from each player.");
                struct Player* Current_player=player;
                pla=player;
                do
                {
                    pla=pla->nextPlayer;
                    BankTransaction(100,Current_player,1);
                    BankTransaction(100,pla,2);
                }
                while(pla->nextPlayer->player_number!=Current_player->player_number);
            }
            else
            if(strcmp(player->currentPosition->name,"CLUB")==0)
            {
                printf("\nGive Rs 100/- to each player.");
                struct Player* Current_player=player;
                pla=player;
                do
                {
                    pla=pla->nextPlayer;
                    BankTransaction(100,Current_player,2);
                    BankTransaction(100,pla,1);
                }
                while(pla->nextPlayer->player_number!=Current_player->player_number);
            }
            else
            if(strcmp(player->currentPosition->name,"CHANCE")==0 || strcmp(player->currentPosition->name,"COMMUNITY CHEST")==0)
            {
                if(strcmp(player->currentPosition->name,"CHANCE")==0)
                {
                    int e=dequeue(chance);
                    chance_func(e,player);
                    enqueue(chance,e);
                }
                else
                {
                    int e=dequeue(community_chest);
                    community_chest_func(e,player);
                    enqueue(community_chest,e);
                }
            }
            else
            {
                if(player->currentPosition->owned==-1 && player->balance > player->currentPosition->price)
                {
                    printf("\nDo you want to buy this property?(Press 1 to buy) \n");
                    scanf("%d",&choice);
                    if(choice==1)
                    {
                        player->currentPosition->owned=player->player_number;
                        BankTransaction(player->currentPosition->price,player,2);
                        printf("Property brought. \n");
                        player->property[player->currentPosition->br_number - 1]=1;
                        printf("Remaining balance: %d\n",player->balance);
                        player->networth+=player->currentPosition->price;
                    }
                    else
                        printf("Moving onto the next player.\n");
                }
                else
                if(player->currentPosition->owned==-1 && player->balance < player->currentPosition->price)
                {
                    printf("\nInsufficient balance. \n");
                }
                else
                if(player->currentPosition->owned == player->player_number)
                {
                    printf("\nYou own this property!\nChoose an action:\n1:Build house\n2:Sell this property\n3:Continue\nENTER CHOICE: ");
                    scanf("%d",&choice);
                    while(choice<1 || choice>3)
                    {
                        printf("Please enter valid choice: ");
                        scanf("%d",&choice);
                    }
                    switch(choice)
                    {
                        case 1:{
                        build_house(player);
                        break;
                        }
                        case 2:{
                        BankTransaction(player->currentPosition->mortgage,player,1);
                        player->currentPosition->owned=-1;
                        player->currentPosition->no_of_houses=0;
                        player->property[player->currentPosition->br_number - 1]=0;
                        printf("\nThe property was mortgaged!");
                        break;
                        }
                        case 3:{
                        printf("\nContinuing..");
                        break;}
                    }
                }
                else
                {
                    pla=gotoPlayer(player,player->currentPosition->owned);
                    printf("\nSomeone else already owns this place. \n");
                    printf("You'll have to pay rent. \n");
                    printf("This property belongs to: %s\n",pla->name);
                    BankTransaction(player->currentPosition->extra_rent,player,2);
                    BankTransaction(player->currentPosition->extra_rent,pla,1);
                }
            }
        }
        else
        {
            if(strcmp(player->currentPosition->name,"PRISION")==0)
            {
                printf("\n%s you are still in jail!",player->name);
                printf("\nPay Rs 500/- to get out of the prison, or miss %d turns..(PRESS 1 to pay or 0 to continue)",player->play_next);
                scanf("%d",&choice);
                if(choice == 1){
                    BankTransaction(500,player,2);
                    player->play_next=0;
                }
                else
                    {printf("\nturn missed!");
                    player->play_next-=1;}
            }
            else{
            printf("\nYou cannot play this turn!");
            player->play_next-=1;}
        }
        label:
        if(player->nextPlayer==player)
            break;
        if(total_turns>20)
            break;
        if(player->networth > 50000)
            break;
        player=player->nextPlayer;
        printf("\n\n(To continue press 1): ");
        scanf("%d",&choice);
        system("cls");
        if(player->turns%4==0)
        {
            printf("DO YOU WANT TO QUIT? (y/n): ");
            scanf("%c",&c);
            if(c=='y' || c=='Y')
                tail=deletePlayer(player,tail);
        }
        if(player==tail)
            ++total_turns;
    }
    endTheGame(player);
}

struct Player* createPlayer(struct Board* board)
{
    int np;
    char playername[10];
    printf("\n_______________________________________________________________\n");
    printf("\nENTER NUMBER OF PLAYERS: ");
    scanf("%d",&np);
    struct Player* root=NULL,*np1,*np2;
    for(int i=0;i<np;i++)
    {
        printf("\nEnter the name of the player %d (MAX 10 CHARACHTERS): ",i+1);
        scanf("%s",playername);
        np1=createnew(playername,board,i+1);
        i==0?root=insert_node(np1,root):insert_node(np1,root);
    }
    np1=root;
    while(np1->nextPlayer!=NULL)
        {np1=np1->nextPlayer;}
    np1->nextPlayer=root;
    root->prevPlayer=np1;
    np1=root;
    return root;
}

struct Player* whoPlayFirst(struct Player* player)
{
    printf("\nOkay! Lets decide who plays first!");
    struct Player *np1,*np2,*np3=player;
    int sum=0,ch;
    do
    {
        int d1=dice(),d2=dice();
        printf("\n%s Please roll the dice (press 1): ",np1->name);
        scanf("%d",&ch);
        while(ch!=1)
        {
            printf("PLEASE ENTER 1:");
            scanf("%d",&ch);
        }
        printf("\nDices Shows:\n");
        displayDice(d1);
        displayDice(d2);
        if((d1+d2)>sum)
        {
            sum=d1+d2;
            np2=np1;
        }
        np1=np1->nextPlayer;
    }
    while(np1->player_number!=np3->player_number);
    printf("\nSo, %s start the game.\n(PRESS 1 to start)",np2->name);
    scanf("%d",&ch);
    return np2;
};

void endTheGame(struct Player* player)
{

    system("cls");
    printf("CONGRATULATIONS!!!\n");
    if(player->networth > 50000 || player->nextPlayer==player)
    {
        printf("%s WON THE GAME!",player->name);
    }
    else
    {
        struct Player *np2=player;
        int sum=0;
        do
        {
            if(player->networth > sum)
            {
                sum= player->networth;
                np2=player;
            }
            player=player->nextPlayer;
        }
        while(player->player_number!=player->player_number);
        printf("%s WON THE GAME!",np2->name);
    }
}

void introduction()
{
    int t;
    printf("+--    --+  +-----+  +\\    + +-----+  +-----+  +-----+  +         \\  /\n");
    printf("|  \\  /  |  |     |  | \\   | |     |  |     |  |     |  |          \\/\n");
    printf("|   \\/   |  |     |  |  \\  | |     |  +-----+  |     |  |          /\n");
    printf("|        |  |     |  |   \\ | |     |  |        |     |  |         /\n");
    printf("|        |  +-----+  |    \\| +-----+  |        +-----+  +-----+  /\n");
    printf("\n\n");
    printf("PLEASE READ THE RULES BEFORE PLAYING!");
    system("Start MONOPOLY.png");
    system("Start MONOPOLY_RULES.docx");
    printf("\n\nIF YOU HAVE READ THE RULES PRESS 1: ");
    scanf("%d",&t);
}
void main()
{
    loading(50);
    int np,ch,sum;
    char playername[10];
    introduction();
    char name_places[36][25]={"oSTART","poMUMBAI","tRAILWAYS","poPUNE","poAURANGABAD","xINCOME TAX","rELECTRIC Co.","cCHANCE","tROADWAYS","oPRISION","pgJAIPUR","pgUDAIPUR","tWATER WAYS","pgBIKANER","pyMYSORE","pyKOLKATA","cCOMMUNITY CHEST","pyGUWAHATI","oCLUB","pbCHENNAI","cCHANCE","pbHYDERABAD","pbCOCHIN","prVARANASI","xWEALTH TAX","prAGRA","prSHIMLA","oREST HOUSE","ppGOA","cCOMMUNITY CHEST","ppNEW DELHI","ppLAKSHADWEEP","pcAMRITSAR","pcDARJEELING","tAIRWAYS","pcAHMEDABAD"};
    int prices[36]={1500,9500,9000,7000,4400,0,5500,0,3800,0,4000,3200,6500,2500,4000,6500,0,2700,0,7500,0,3500,4100,3000,0,3000,2100,0,5500,0,8000,5000,3500,3000,10500,4400};
    int rent_places[36]={0,1200,1000,900,300,0,750,0,600,0,400,300,500,200,500,700,0,300,0,900,0,400,500,250,0,200,200,0,700,0,1200,500,400,350,1200,400};
    int cost_of_houses[36]={0,7500,0,6500,5000,0,0,0,0,0,5500,4500,0,3000,4500,5500,0,5000,0,6000,0,4500,5000,3000,0,5000,2500,0,5000,0,7500,5500,3000,4000,0,3000};
    int mortgage_places[36]={0,4250,4750,3500,2000,0,1600,0,4750,0,3250,2000,1600,1500,3500,4000,0,2000,0,4000,0,3000,3000,2500,0,4000,1200,0,3000,0,5000,2500,2500,2500,5250,2000};
    struct Board* board = createBoard(36,25,name_places,prices,rent_places,cost_of_houses,mortgage_places);
    struct Queue* community_chest= createQueue(6);
    struct Queue* chance= createQueue(6);
    struct Player* root,* np2;
    create_CommunityChest_chance(community_chest,chance);
    //displayQueue(community_chest);
    //displayQueue(chance);
    root=createPlayer(board);
    srand(time(NULL));
    np2 =whoPlayFirst(root);
    system("cls");
    Game_Flow(board,np2,community_chest,chance);
}
