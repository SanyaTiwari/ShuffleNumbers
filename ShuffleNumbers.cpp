#include<iostream>
#include<windows.h>
#include<conio.h>
using namespace std;

int num[9], step=0;
char press[2];
int valid_input(int), userwin();
void level_menu(), driver_func(), initialise(), print_menu(bool), draw_base(int, int, int), draw(int, int, int);
void display(), exit_(), design1(), design2();

COORD coord={0,0};

int main()
{
    system("mode con COLS=700");
    ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);
    SendMessage(GetConsoleWindow(),WM_SYSKEYDOWN,VK_RETURN,0x20000000);
    system("Color 0A");
    system("CLS");
    level_menu();
    driver_func();
    return 0;
}

void gotoxy(int x, int y){
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void level_menu()
{
    system("CLS");
    char ch;
    design1();
    design2();
    design1();
    gotoxy(78,5);
    cout<<"SHUFFLE NUMBERS"<<endl;
    gotoxy(10,10);
    cout<<"1. Press 1 to start"<<endl;
    gotoxy(10,11);
    cout<<"2. Press 2 for rules"<<endl;
    gotoxy(10,12);
    cout<<"3. Press X to exit"<<endl;
    ch=getch();
    if(ch=='X' or ch=='x'){
        display();
        exit_();
    }
    if(ch=='2')
    {
        system("CLS");
        design1();
        design2();
        design1();
        gotoxy(78,5);
        cout<<"SHUFFLE NUMBERS"<<endl;
        gotoxy(10,10);
        cout<<"1. Rearrange the numbers in ascending order"<<endl;
        gotoxy(10,11);
        cout<<"2. Press the corresponding number key to move that number"<<endl;
        gotoxy(10,12);
        cout<<"3. Press 1 to start"<<endl;
        gotoxy(10,13);
        cout<<"4. Press X to exit"<<endl;
        ch=getch();
        if(ch=='X' or ch=='x'){
            display();
            exit_();
        }
    }
}

void driver_func()
{
    int i, x, y, key;
    bool start=true;
    initialise();
    do{
        start:
        print_menu(start);
        i=0;
        for(y=10;y<19;y+=4)
        {
            for(x=50;x<65;x+=7)
            {
                if(start) draw_base(x,y,i);
                else draw(x,y,i);
                ++i;
            }
        }
        start=false;
        if(userwin()==1)
        {
            gotoxy(82,30);
            cout<<"YOU WIN"<<endl;
            display();
            exit_();
        }
        press[0]=getch();
        if(press[0]=='X' or press[0]=='x')
        {
            display();
            exit_();
        }
        key=atoi(press);
        if(valid_input(key)==0) goto start;
        step++;
        if(step==50)
        {
            print_menu(start);
            gotoxy(81,30);
            cout<<"YOU LOSE";
            display();
            exit_();
        }
        for(int i=0;i<9;++i)
        {
            if(num[i]==key)
            num[i]=0;
            else if(num[i]==0)
            num[i]=key;
        }

    }while(1);
}

void initialise()
{
    int i;
    for(i=0;i<4;++i) num[i]=2*(i+1);
    for(int j=1;i<8;++i,j+=2) num[i]=j;
    num[8]=0;
}

void print_menu(bool start)
{
    if(start){
        system("CLS");
        design1();
        design2();
        design1();
        gotoxy(78,5);
        cout<<"SHUFFLE NUMBERS";
        gotoxy(105,10);
        cout<<"X = exit game";
    }
    gotoxy(105,11);
    cout<<"Moves = "<<step;
}

void draw_base(int x , int y , int i)
{
    char p=201, q=205, r=187, s=186, t=200, u=188;
    gotoxy(x,y);
    cout<<p<<q<<q<<q<<r<<endl;
    gotoxy(x,y+1);
    cout<<s<<" ";
    if(num[i]==0) cout<<" ";
    else cout<<num[i];
    cout<<" "<<s<<endl;
    gotoxy(x,y+2);
    cout<<t<<q<<q<<q<<u<<endl;
}

void draw(int x , int y , int i)
{
    gotoxy(x+1,y+1);
    cout<<" ";
    if(num[i]==0) cout<<" ";
    else cout<<num[i];
}

int valid_input(int key)
{
    int valid=0;
    for(int i=0;i<9;++i)
    {
        if(num[i]==key)
        {
            valid=1;
            switch(i)
            {
                case 0 : if(num[1]!=0 && num[3]!=0) valid=0;
                         break;

                case 1 : if(num[0]!=0 && num[2]!=0 && num[4]!=0) valid=0;
                         break;

                case 2 : if(num[1]!=0 && num[5]!=0) valid=0;
                         break;

                case 3 : if(num[0]!=0 && num[4]!=0 && num[6]!=0) valid=0;
                         break;

                case 4 : if(num[1]!=0 && num[3]!=0 && num[5]!=0 && num[7]!=0) valid=0;
                         break;

                case 5 : if(num[2]!=0 && num[4]!=0 && num[8]!=0) valid=0;
                         break;

                case 6 : if(num[3]!=0 && num[7]!=0) valid=0;
                         break;

                case 7 : if(num[4]!=0 && num[6]!=0 && num[8]!=0) valid=0;
                         break;

                case 8 : if(num[5]!=0 && num[7]!=0) valid=0;
                         break;

                default : valid=0;
                          break;
            }
        }
    }
    return valid;
}

int userwin()
{
    int win;
    for(int i=0;i<8;++i)
    {
         if(num[i]!=i+1)
         {   win=0;
             break;
         }
         else  win=1;
    }
    return win;
}

void display()
{
    gotoxy(82,32);
    cout<<"THANKS";
}

void exit_(){
    gotoxy(0,40);
    exit(1);
}

void design1(){
    char a=176,b=177,c=178;
    for(int i=0;i<114;++i) cout<<a<<b<<c;
    cout<<a<<b;

}

void design2(){
    char a=176,b=177,c=178;
    for(int i=0;i<37;++i){
        cout<<c<<c<<b<<b<<a<<a;
        for(int j=0;j<160;++j) cout<<" ";
        cout<<a<<a<<b<<b<<c<<c<<endl;
    }
}

