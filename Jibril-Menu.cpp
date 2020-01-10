#include <TXLib.h>

using namespace std;

class MAP{
public:
    HDC Place=NULL;
    COLORREF BackGroundColor=0;
    int coordinates[4][2];
    int nx=20, ny=14;
    int location[14][20];
    int seeS=0, seeH=0;
    int factor=0;

//методы
    MAP();
    void Init();
    void Draw(int xx, int yy);
    int CanMove(int x0, int y0, int x, int y);
    int Get_cell(int x, int y);
    void Set_cell(int x, int y, int n);
    ~MAP();
};

class Object{
public:
    HDC tree=NULL;
    COLORREF BackGroundColor=0;
    int x=0, y=0, DrawX=0, DrawY=0, s=0, h=0;
    int xxx=0, yyy=0, DrawHitX=0, DrawHitY=0, DrawHitS=0, DrawHitH=0;
    int HitX0=0, HitY0=0, HitX=0, HitY=0;
    int factor=0;

//методы
    Object();
    void Init();
    void Draw(int PlayX, int PlayY, int nx, int ny, int seeS, int seeH, int factor);
    void DrawHit(int PlayX, int PlayY, int nx, int ny, int seeS, int seeH, int factor);
    int CanMove(int x0, int y0, int x, int y);
    ~Object();
};

class Button{
public:
    int x0=0, y0=0, x=0, y=0;
    int IndX, IndY;
    char text[100];

//методы
    Button();
    void Init(int xx0, int yy0, int xx, int yy, int IIndX, int IIndY, const char ttext[100]);
    bool Draw(int xx, int yy);
    ~Button();
};

class MENU{
public:
    int type=0, AutorPuch=0;
    bool button=0;
    Button Play, Info, Autor, Exit, Back;
    HDC Raph=txLoadImage("Raphtalia.bmp");

//методы
    MENU();
    void Init();
    void MenuRun();
    void Select();
    void StartMenu();
    void InfoMenu();
    void AutorMenu();
    ~MENU();
};

class Dialog{
public:
    COLORREF FillColor=NULL;
    COLORREF Color=NULL;

//методы
    Dialog();
    void Init();
    void Say(char name[1000], char text[1000]);
    ~Dialog();
};

class Player{
private:
    HDC Sprite=NULL;
    COLORREF BackGroundColor=0;
    int coordinate[4][3][2];
    int SpriteSave=0, Costume=0;
    int x=0, y=0;
    int s=0, h=0;
    int V0=0;

    MAP Map;
    Object Tree;
    MENU Menu;
    Dialog log;

public:
    Player();
    void Init();
    void GetKeyandMove();
    void Act();
    int CanMove(int x0, int y0, int x, int y);
    void Draw();
    void DrawMap();
    void DrawObject();
    void DrawObjectHit();
    void SelectMenu();
    int CheckMenu();
    ~Player();
};



int main(){
    txCreateWindow(1280, 800);
    txBegin();

    Player Jibril;

    Jibril.SelectMenu();
    while(Jibril.CheckMenu()==1){
        txSetFillColor(RGB(0, 0, 0));
        txClear();

        Jibril.GetKeyandMove();
        Jibril.DrawMap();
        Jibril.DrawObjectHit();
        Jibril.Draw();
        Jibril.DrawObject();
        Jibril.Act();

        txSleep(80);
    }

    txEnd();
    return 0;
}



MAP::MAP(){
    Place=txLoadImage("Place.bmp");
    BackGroundColor=RGB(130, 255, 200);

    int tmpcor[4][2]={5, 5, 5, 42, 5, 79, 5, 116};
    for(int i=0; i<4; i++)
        for(int j=0; j<2; j++)
            coordinates[i][j]=tmpcor[i][j];

    seeS=640, seeH=400;
    factor=96;

    Init();
}

void MAP::Init(){
    nx=20, ny=14;
    int tmp[14][20]={1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                     1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                     1, 1, 1, 1, 3, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                     1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                     1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                     1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
                     1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1,
                     1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1,
                     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    for(int i=0; i<ny; i++)
        for(int j=0; j<nx; j++)
            location[i][j]=tmp[i][j];
}

void MAP::Draw(int xx, int yy){
    int ss=seeS, hh=seeH, x0=xx-ss, y0=yy-hh, xk=xx+ss, yk=yy+hh;
    if(x0<0){
        x0=0;
        xk=ss*2;
        xx=0;
        ss=0;
    }
    else if(xk>nx*factor){
            xk=nx*factor;
            x0=xk-ss*2;
            xx=nx*factor-seeS;
    }
    if(y0<0){
        y0=0;
        yk=hh*2;
        yy=0;
        hh=0;
    }
    else if(yk>ny*factor){
        yk=ny*factor;
        y0=yk-hh*2;
        yy=ny*factor-seeH;
    }
    if(xk%factor!=0) xk+=factor;
    if(yk%factor!=0) yk+=factor;

    for(int i=y0/factor; i<yk/factor; i++)
        for(int j=x0/factor; j<xk/factor; j++)
            Win32::TransparentBlt(txDC(), j*factor-xx+ss, i*factor-yy+hh, factor, factor, Place, coordinates[location[i][j]][0], coordinates[location[i][j]][1], 32, 32, BackGroundColor);
}

int MAP::CanMove(int x0, int y0, int x, int y){
    int can=1;

    if(x%factor!=0) x+=factor;
    if(y%factor!=0) y+=factor;
    x0/=factor;
    y0/=factor;
    x/=factor;
    y/=factor;

    for(int i=y0; i<y; i++){
        for(int j=x0; j<x; j++){
            if(Get_cell(i, j)!=1) can=0;
        }
    }

    return can;
}

int MAP::Get_cell(int x, int y){
    return location[x][y];
}

void MAP::Set_cell(int x, int y, int n){
    location[x][y]=n;
}

MAP::~MAP(){
    txDeleteDC(Place);
}



Object::Object(){
    Init();
}

void Object::Init(){
    tree=txLoadImage("Tree.bmp");
    BackGroundColor=RGB(130, 255, 200);
    x=1200, y=245, DrawX=0, DrawY=0, s=272, h=265;
    xxx=1400, yyy=775, DrawHitX=100, DrawHitY=265, DrawHitS=85, DrawHitH=55;            //xxx=x+DrawHitX*factor-отступы
    HitX0=114, HitY0=265, HitX=172, HitY=308;
    factor=2;
}

void Object::Draw(int PlayX, int PlayY, int nx, int ny, int seeS, int seeH, int fffactor){
    int xx=x-PlayX+seeS, yy=y-PlayY+seeH;
    if(PlayX<seeS) xx=x;
    else if(PlayX>nx*fffactor-seeS) xx=x-nx*fffactor+seeS*2;
    if(PlayY<seeH) yy=y;
    else if(PlayY>=ny*fffactor-seeH) yy=y-ny*fffactor+seeH*2;

    Win32::TransparentBlt(txDC(), xx, yy, s*factor, h*factor, tree, DrawX, DrawY, s, h, BackGroundColor);
}

void Object::DrawHit(int PlayX, int PlayY, int nx, int ny, int seeS, int seeH, int fffactor){
    int xx=xxx-PlayX+seeS, yy=yyy-PlayY+seeH;
    if(PlayX<seeS) xx=xxx;
    else if(PlayX>nx*fffactor-seeS) xx=xxx-nx*fffactor+seeS*2;
    if(PlayY<seeH) yy=yyy;
    else if(PlayY>=ny*fffactor-seeH) yy=yyy-ny*fffactor+seeH*2;

    Win32::TransparentBlt(txDC(), xx, yy, DrawHitS*factor, DrawHitH*factor, tree, DrawHitX, DrawHitY, DrawHitS, DrawHitH, BackGroundColor);
}

int Object::CanMove(int xx0, int yy0, int xx, int yy){
    int can=1;
    int xxx0=x+HitX0*factor, yyy0=y+HitY0*factor, xxx=x+HitX*factor, yyy=y+HitY*factor;
    if(((xx0>xxx0 && xx0<xxx) || (xx>xxx0 && xx<xxx)) && ((yy0>yyy0 && yy0<yyy) || (yy>yyy0 && yy<yyy))) can=0;

    return can;
}

Object::~Object(){
    txDeleteDC(tree);
}



Button::Button(){

}

void Button::Init(int xx0, int yy0, int xx, int yy, int IIndX, int IIndY, const char ttext[100]){
    x0=xx0, y0=yy0, x=xx, y=yy;
    IndX=IIndX, IndY=IIndY;
    for(int i=0; i<100; i++)
        text[i]=ttext[i];
}

bool Button::Draw(int xx, int yy){
    int IIndX=0, IIndY=0;
    bool is=0;
    if(x0<=xx && x>=xx && y0<=yy && y>=yy) is=1;

    if(is){
        txSetColor(RGB(255, 255, 0));
        txSetFillColor(RGB(0, 0, 0));
        IIndX=IndX;
        IIndY=IndY;
    }
    else txSetColor(RGB(255, 255, 255));

    if(!is) txSetFillColor(RGB(76, 88, 102));
    Win32::RoundRect(txDC(), x0+IndX, y0+IndY, x+IndX, y+IndY, 30, 30);
    if(!is){
        txSetFillColor(RGB(0, 0, 0));
        Win32::RoundRect(txDC(), x0, y0, x, y, 30, 30);
    }
    txSelectFont ("Comic Sans MS", 40);
    txDrawText(x0+IIndX, y0+IIndY, x+IIndX, y+IIndY, text);

    return is;
}

Button::~Button(){

}



MENU::MENU(){
    Init();

    Play.Init(590, 225, 690, 275, 5, -5, "Играть");
    Info.Init(545, 300, 735, 350, 5, -5, "Информация");
    Autor.Init(590, 375, 690, 425, 5, -5, "Автор");
    Exit.Init(590, 700, 690, 750, 5, -5, "Выход");
    Back.Init(585, 700, 695, 750, 5, -5, "Назад");
}

void MENU::Init(){
    type=0, AutorPuch=0;
    button=1;
}

void MENU::MenuRun(){
    while(type!=1 && type!=4){
        if(txMouseButtons()==1) button=0;
        else button=1;

        txSetFillColor(RGB(0, 0, 0));
        txClear();
        txSetColor(RGB(0, 0, 0));
        txRectangle(0, 0, 1280, 800);

        Select();
        if(type!=3) AutorPuch=0;

        txSleep(0);
    }
}

void MENU::Select(){
    if(type==0) StartMenu();
    else if(type==2) InfoMenu();
    else if(type==3) AutorMenu();
}

void MENU::StartMenu(){
    int x=txMouseX(), y=txMouseY();
    bool is;

    is=Play.Draw(x, y);
    if(txMouseButtons()==1 && is && button) type=1;

    is=Info.Draw(x, y);
    if(txMouseButtons()==1 && is && button) type=2;

    is=Autor.Draw(x, y);
    if(txMouseButtons()==1 && is && button) type=3;

    is=Exit.Draw(x, y);
    if(txMouseButtons()==1 && is && button) type=4;
}

void MENU::InfoMenu(){
    int x=txMouseX(), y=txMouseY();
    bool is;
    txSetColor(RGB(255, 255, 255));

    txDrawText(500, 100, 780, 140, "Up - стрелка вверх");
    txDrawText(500, 160, 780, 200, "Down - стрелка вниз");
    txDrawText(480, 220, 800, 280, "Right - стрелка вправо");
    txDrawText(500, 300, 780, 340, "Left - стрелка влево");
    txDrawText(500, 360, 780, 400, "Взаимодействие - Z");
    txDrawText(500, 420, 780, 480, "Menu - Esc");
    txDrawText(480, 600, 800, 660, "За деревом есть дупло");

    is=Back.Draw(x, y);
    if((txMouseButtons()==1 && is && button) || GetAsyncKeyState(VK_ESCAPE)) type=0;
}

void MENU::AutorMenu(){
    int x=txMouseX(), y=txMouseY();
    bool is;

    txSetColor(RGB(255, 255, 255));
    txSelectFont ("Comic Sans MS", 60);
    txDrawText(550, 50, 730, 100, "FireKOT");

    if(AutorPuch>=13){
        txSelectFont ("Comic Sans MS", 30);
        txDrawText(520, 550, 760, 580, "Автор - лох  (с)Kmyn");
    }

    if(550<=x && 730>=x && 50<=y && 100>=y && txMouseButtons()==1 && button) AutorPuch++;

    Win32::TransparentBlt(txDC(), 453, 102, 374, 435, Raph, 0, 0, 374, 435, RGB(0, 0, 0));

    is=Back.Draw(x, y);
    if((txMouseButtons()==1 && is && button) || GetAsyncKeyState(VK_ESCAPE)) type=0;
}

MENU::~MENU(){
    txDeleteDC(Raph);
}



Dialog::Dialog(){
    Init();
}

void Dialog::Init(){
    FillColor=RGB(0, 0, 0);
    Color=RGB(255, 255, 255);
}

void Dialog::Say(char name[1000], char text[1000]){
    bool is=1;
    while(is){
        txSetFillColor(Color);
        txSetColor(Color);
        Win32::RoundRect(txDC(), 5, 610, 1280, 800, 30, 30);

        txSetFillColor(FillColor);
        txSetColor(Color);
        Win32::RoundRect(txDC(), 0, 605, 1275, 795, 30, 30);

        txSetColor(Color);
        txSelectFont ("Comic Sans MS", 40);
        txDrawText(10, 615, 210, 790, name);
        txDrawText(220, 615, 1270, 790, text);

        txSleep(50);
        if(GetAsyncKeyState('Z')) is=0;
    }
}

Dialog::~Dialog(){

}



Player::Player(){
    Init();
}

void Player::Init(){

    Sprite=txLoadImage("Jibril.bmp");
    BackGroundColor=RGB(130, 255, 200);

    int coords[4][3][2]={5, 5,     49, 5,    93, 5,     //координаты спрайтов
                         5, 44,    49, 44,   93, 44,
                         5, 83,    49, 83,   93, 83,
                         5, 122,   49, 122,  93, 122};
    for(int i=0; i<4; i++)
        for(int j=0; j<3; j++)
            for(int k=0; k<2; k++)
                coordinate[i][j][k]=coords[i][j][k];
    SpriteSave=0, Costume=0;

    x=320, y=320;
    s=96, h=96;
    V0=16;
}

void Player::GetKeyandMove(){
    bool Playermove=0;
    int PressKey=-1;

    if(GetAsyncKeyState(VK_DOWN)){
        PressKey=0;
        if(CanMove(x, y+h, x+s, y+h+V0)==1){
            y+=V0;
            Playermove=1;
        }
    }
    else if(GetAsyncKeyState(VK_UP)){
        PressKey=1;
        if(CanMove(x, y-V0+80, x+s, y+80)==1){
            y-=V0;
            Playermove=1;
        }
    }
    if(GetAsyncKeyState(VK_RIGHT)){
        PressKey=2;
        if(CanMove(x+s, y+80, x+s+V0, y+h)==1){
            x+=V0;
            Playermove=1;
        }
    }
    else if(GetAsyncKeyState(VK_LEFT)){
        PressKey=3;
        if(CanMove(x-V0, y+80, x, y+h)==1){
            x-=V0;
            Playermove=1;
        }
    }
    if(x<0) x=0;
    else if(x>(Map.nx-1)*Map.factor) x=(Map.nx-1)*Map.factor;
    if(y<0) y=0;
    else if(y>(Map.ny-1)*Map.factor) y=(Map.ny-1)*Map.factor;

    if(PressKey!=-1){
        SpriteSave=PressKey;
        Costume++;
        Costume%=3;
    }
    if(!Playermove) Costume=0;
    Draw();
}

int Player::CanMove(int x0, int y0, int x, int y){
    int can=1;

    if(Map.CanMove(x0, y0, x, y)!=1) can=0;
    if(Tree.CanMove(x0, y0, x, y)!=1) can=0;

    return can;
}

void Player::Act(){
    if(GetAsyncKeyState('Z')){
        if(SpriteSave==0){
            if(Tree.CanMove(x, y+h, x+s, y+h+V0)==0) log.Say("Из дупла в дереве:\n", "Че ты стучишь?\n");
        }
        else if(SpriteSave==1){
            if(Tree.CanMove(x, y-V0+80, x+s, y+80)==0);
        }
        else if(SpriteSave==2){
            if(Tree.CanMove(x+s, y+80, x+s+V0, y+h)==0);
        }
        else if(SpriteSave==3){
            if(Tree.CanMove(x-V0, y+80, x, y+h)==0);
        }
    }
    else if(GetAsyncKeyState(VK_ESCAPE)){
        Menu.type=0;
        Menu.MenuRun();
    }
}

void Player::Draw(){
    int xx=Map.seeS, yy=Map.seeH;
    if(x<xx) xx=x;
    else if(x>Map.nx*Map.factor-Map.seeS) xx+=x-Map.nx*Map.factor+Map.seeS;
    if(y<yy) yy=y;
    else if(y>Map.ny*Map.factor-Map.seeH) yy+=y-Map.ny*Map.factor+Map.seeH;

    Win32::TransparentBlt(txDC(), xx, yy, s, h, Sprite, coordinate[SpriteSave][Costume][0], coordinate[SpriteSave][Costume][1], 34, 34, BackGroundColor);
}

void Player::DrawMap(){
    Map.Draw(x, y);
}

void Player::DrawObject(){
    Tree.Draw(x, y, Map.nx, Map.ny, Map.seeS, Map.seeH, Map.factor);
}

void Player::DrawObjectHit(){
    Tree.DrawHit(x, y, Map.nx, Map.ny, Map.seeS, Map.seeH, Map.factor);
}

void Player::SelectMenu(){
    if(Menu.type==0) Menu.MenuRun();
}

int Player::CheckMenu(){
    return Menu.type;
}

Player::~Player(){
    txDeleteDC(Sprite);
}
