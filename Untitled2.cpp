#include <TXLib.h>

using namespace std;

class Map{
public:
    HDC Place=0;
    COLORREF BackGroundColor=0;
    int coordinates[4][2];
    int location[14][20];
    int nx=0, ny=0;
    int x=0, y=0, s=0, h=0;
    int factor=0;

//методы
    Map();
    void Init();
    void Draw();
    int Get_cell(int x0, int y);
    void Set_cell(int x, int y, int n);
    int CanMove(int x0, int y0, int x, int y);
    ~Map();
};

class Player{
private:
    HDC Sprite=0;
    COLORREF BackGroundColor=0;
    int alive=1;
    int coordinate[4][3][2];
    int SpriteNum=0, SpriteSave=0, Costume=0;
    int x=0, y=0, s=0, h=0;
    int V0=0;
    int screenS=0, screenH=0, mapS=0, mapH=0;

public:
    Map Chart;

    Player();
    int Alive(){
        return alive;
    }
    void Init();
    void Draw();
    void DrawMap();
    void GetKeyandMove();
    void die(){
        alive=0;
    }
    ~Player();
};

int main(){
    txCreateWindow(576, 576);
    txBegin();

    Player Jibril;
    while(!GetAsyncKeyState(VK_ESCAPE) && Jibril.Alive()==1){
        txSetFillColor(RGB(0, 0, 0));
        txClear();

        Jibril.Chart.Draw();
        Jibril.GetKeyandMove();

        txSleep(75);
    }
    txSetFillColor(RGB(0, 0, 0));
    txClear();

    if(Jibril.Alive()==0){
        HDC  Rphtalia=txLoadImage("Raftal.bmp");
        Win32::TransparentBlt(txDC(), 50, 300, 187, 218, Rphtalia, 0, 0, 374, 435, RGB(0, 0, 0));

        txSelectFont("Comic Sans MS", 50);
        txTextOut(50, 50, "Спасибо за игру!");
        txTextOut(50, 100, "Простите, автора.");
        txTextOut(50, 150, "Ему надо спать.");
        txTextOut(50, 200, "Удачно сдать зачеты");
        txTextOut(50, 510, "made by FireKOT");

        txDeleteDC (Rphtalia);
    }
    txSleep(1000);

    txEnd();
    return 0;
}

Player::Player():Chart(){
    Init();
}

Map::Map(){
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

    SpriteNum=0, SpriteSave=0, Costume=0;
    x=0, y=0, s=96, h=96;
    V0=16;
    screenS=Chart.s, screenH=Chart.h, mapS=Chart.nx*Chart.factor, mapH=Chart.ny*Chart.factor;
}

void Map::Init(){
    Place=txLoadImage("Place.bmp");
    BackGroundColor=RGB(130, 255, 200);

    int coor[4][2]={5, 5, 5, 42, 5, 79, 5, 116};
    for(int i=0; i<4; i++){
        for(int j=0; j<2; j++){
            coordinates[i][j]=coor[i][j];
        }
    }

    nx=20, ny=14;
    int loca[14][20]={1, 3, 3, 3, 3, 1, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3,
                      1, 3, 3, 3, 3, 1, 2, 2, 2, 2, 3, 3, 3, 1, 2, 2, 1, 3, 3, 3,
                      1, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1, 1, 1, 3, 3, 1, 3, 3, 3,
                      1, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1, 2, 2, 3, 3, 1, 3, 3, 3,
                      1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 3, 1, 3, 3, 3, 3, 1, 3, 3, 3,
                      2, 2, 2, 1, 3, 1, 2, 2, 1, 3, 3, 1, 3, 3, 1, 1, 1, 1, 3, 3,
                      3, 3, 3, 1, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 2, 2, 1, 3, 3,
                      3, 3, 3, 1, 3, 1, 3, 3, 1, 1, 1, 1, 3, 3, 1, 3, 3, 1, 3, 3,
                      1, 1, 1, 1, 1, 1, 3, 3, 1, 2, 2, 1, 3, 3, 2, 3, 3, 1, 3, 3,
                      1, 2, 2, 2, 2, 1, 3, 3, 1, 1, 3, 1, 3, 3, 3, 3, 1, 1, 3, 3,
                      1, 3, 3, 3, 3, 1, 3, 3, 1, 1, 3, 1, 3, 3, 3, 3, 1, 2, 3, 3,
                      1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1, 0, 3, 3,
                      2, 2, 2, 3, 3, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 3, 2, 3, 3, 3,
                      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
    for(int i=0; i<ny; i++){
        for(int j=0; j<nx; j++){
            location[i][j]=loca[i][j];
        }
    }

    s=288, h=288;
    factor=96;
}

void Player::GetKeyandMove(){
    bool Playermove=0;
    SpriteNum=-1;

    if(GetAsyncKeyState(VK_DOWN)){
        SpriteNum=0;
        if(Chart.CanMove(x, y+h, x+s, y+h+V0)==1){
            y+=V0;
            Playermove=1;
        }
        else if(Chart.CanMove(x, y+h, x+s, y+h+V0)==2) die();
    }
    else if(GetAsyncKeyState(VK_UP)){
        SpriteNum=1;
        if(Chart.CanMove(x, y-V0+80, x+s, y+80)==1){
            y-=V0;
            Playermove=1;
        }
        else if(Chart.CanMove(x, y-V0+80, x+s, y+80)==2) die();
    }
    if(GetAsyncKeyState(VK_RIGHT)){
        SpriteNum=2;
        if(Chart.CanMove(x+s, y+80, x+s+V0, y+h)==1){
            x+=V0;
            Playermove=1;
        }
        else if(Chart.CanMove(x+s, y+80, x+s+V0, y+h)==2) die();
    }
    else if(GetAsyncKeyState(VK_LEFT)){
        SpriteNum=3;
        if(Chart.CanMove(x-V0, y+80, x, y+h)==1){
            x-=V0;
            Playermove=1;
        }
        else if(Chart.CanMove(x-V0, y+80, x, y+h)==2) die();
    }
    if(x<0) x=0;
    if(y<0) y=0;
    if(x>Chart.nx*Chart.factor) x=Chart.nx*Chart.factor;
    if(y>Chart.ny*Chart.factor) y=Chart.ny*Chart.factor;

    Chart.x=x;
    Chart.y=y;

    if(SpriteNum!=-1){
        SpriteSave=SpriteNum;
        Costume++;
        Costume%=3;
    }
    if(!Playermove) Costume=0;
    Draw();
}

void Player::Draw(){
    int xx=screenS, yy=screenH;
    if(x<xx) xx=x;
    else if(x>mapS-screenS) xx=x-screenS;
    if(y<yy) yy=y;
    else if(y>mapH-screenH) yy=y-screenH;

    Win32::TransparentBlt(txDC(), xx, yy, s, h, Sprite, coordinate[SpriteSave][Costume][0], coordinate[SpriteSave][Costume][1], 34, 34,  BackGroundColor);  //надо делать ровно по размеру и перед цветом 2 0 писать
}

void Map::Draw(){
    int mapX0=x-s, mapY0=y-h, mapX=x+s, mapY=y+h, xx=x, yy=y, ss=s, hh=h;
    if(mapX0<0){
        mapX0=0;
        mapX=s*2;
        ss=0;
        xx=0;
    }
    if(mapY0<0){
        mapY0=0;
        mapY=h*2;
        hh=0;
        yy=0;
    }
    if(mapX>nx*factor){
        mapX=nx*factor;
        mapX0=mapX-s*2;
        xx=nx*factor-s;
    }
    if(mapY>ny*factor){
        mapY=ny*factor;
        mapY0=mapY-2*h;
        yy=ny*factor-h;
    }
    if(mapX%factor!=0) mapX+=factor;
    if(mapY%factor!=0) mapY+=factor;

    for(int i=mapY0/factor; i<mapY/factor; i++){
        for(int j=mapX0/factor; j<mapX/factor; j++){
            Win32::TransparentBlt(txDC(), j*factor-xx+ss, i*factor-yy+hh, factor, factor, Place, coordinates[location[i][j]][0], coordinates[location[i][j]][1], 32, 32,  BackGroundColor);
        }
    }
}

int Map::Get_cell(int xx, int yy){
    return location[xx][yy];
}

void Map::Set_cell(int xx, int yy, int n){
    location[yy][xx]=n;
}

int Map::CanMove(int x0, int y0, int xx, int yy){
    bool tmp=1;
    if(xx%factor!=0) xx+=factor;
    if(yy%factor!=0) yy+=factor;
    x0/=factor;
    y0/=factor;
    xx/=factor;
    yy/=factor;

    for(int i=y0; i<yy; i++){
        for(int j=x0; j<xx; j++){
            if(Get_cell(i, j)!=1 && Get_cell(i, j)!=0) tmp=0;
            else if(Get_cell(i, j)==0){
                return 2;
            }
        }
    }

    return tmp;
}

Map::~Map(){
    txDeleteDC(Place);
}

Player::~Player(){
    txDeleteDC(Sprite);
}
