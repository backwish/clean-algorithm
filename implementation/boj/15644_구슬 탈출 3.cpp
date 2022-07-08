#include <bits/stdc++.h>
using namespace std;
const int dy[4] = {0,0,1,-1};
const int dx[4] = {1,-1,0,0};
const int SUCCESS = 1;
const int FAIL = -1;
const int NOTEND = 0;
const char dirChar[4] = {'R','L','D','U'};

/*
Marble 객체가 스스로 굴러가는 것이 아니라 Board가 Marble를 설계가 어색할 수 있지만,
Marble 객체가 굴러가는 것은 Board 객체 맥락 안에서 굴러가는 것으로 생각했습니다.
Marble 객체가 스스로 굴러가는 경우 Board 객체와의 결합도가 너무 높아진다 생각했기 때문입니다.
즉, 결합도를 위해 객체의 주체성을 희생시키는 트레이드 오프입니다.
*/

struct Marble{
    int y,x;
    bool exist;
    Marble(){}
    Marble(int _y,int _x) : y(_y),x(_x),exist(true){}
    bool checkCollide(Marble& other){
        if(!exist or !other.exist) return false;
        return y==other.y and x==other.x;
    }
    void moveForward(int dir){
        y+=dy[dir];x+=dx[dir];
    }
    void moveBackward(int dir){
        y-=dy[dir];x-=dx[dir];
    }
    
};

struct Board{
    vector<string> board;
    int r,c;
    Marble red,blue;
    Board(int _r,int _c,vector<string>& _board) : r(_r),c(_c),board(_board){
        for(int y=0;y<r;y++){
            for(int x=0;x<c;x++){
                Marble theMarble(y,x);
                if(board[y][x]=='R'){
                    red = theMarble;
                    board[y][x] = '.';
                }else if(board[y][x]=='B'){
                    blue = theMarble;
                    board[y][x] = '.';
                }
            }
        }
    }
    void resetMarble(Marble& _red,Marble& _blue){
        red = _red;blue = _blue;
    }
    
    bool checkGo(Marble& theMarble){
        return board[theMarble.y][theMarble.x]=='.';
    }
    bool checkHole(Marble& theMarble){
        return board[theMarble.y][theMarble.x]=='O';
    }
    bool checkRedFirst(int dir){
        if(!red.exist) return false;
        Marble temp = blue;
        while(checkGo(temp) and !temp.checkCollide(red)) temp.moveForward(dir);
        return temp.checkCollide(red);
    }
    void moveMarble(Marble& theMarble,Marble& other,int dir){
        while(checkGo(theMarble) and (!other.exist or !theMarble.checkCollide(other))) theMarble.moveForward(dir);
        if(checkHole(theMarble)){
            theMarble.exist = false;
        }else{
            theMarble.moveBackward(dir);
        }
    }
    void tilt(int dir){
        if(checkRedFirst(dir)){
            moveMarble(red,blue,dir);
            moveMarble(blue,red,dir);
        }else{
            moveMarble(blue,red,dir);
            moveMarble(red,blue,dir);
        }
    }
    
    int checkStatus(){
        if(!blue.exist) return FAIL;
        if(!red.exist) return SUCCESS;
        return NOTEND;
    }
};

struct Search{
    int best;
    string bestSequence,theSequence;
    Board theBoard;
    Search(Board _theBoard) : theBoard(_theBoard){
        best = 1e9;
    }
    void dfs(int depth){
        if(depth>10 or depth>=best) return;
        if(theBoard.checkStatus()==SUCCESS){
            best = min(best,depth);
            bestSequence = theSequence;
        } 
        for(int dir=0;dir<4;dir++){
            Marble red = theBoard.red,blue = theBoard.blue;
            theBoard.tilt(dir);
            theSequence+=dirChar[dir];
            if(theBoard.checkStatus()!=FAIL){
                dfs(depth+1);
            } 
            theSequence.pop_back();
            theBoard.resetMarble(red,blue);
        }
    }
    void printBest(){
        cout<<(best==1e9 ? -1 : best)<<'\n';
        if(best<1e9) cout<<bestSequence;
    }
};

void run(){
    int r,c;cin>>r>>c;
    vector<string> grid;
    for(int y=0;y<r;y++){
        string word;cin>>word;
        grid.push_back(word);
    }
    Board board(r,c,grid);
    Search dfsSearch(board);
    dfsSearch.dfs(0);
    dfsSearch.printBest();
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    run();
}
