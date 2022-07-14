#include <bits/stdc++.h>
using namespace std;
const int dy[4] = {-1,0,1,0};
const int dx[4] = {0,1,0,-1};
struct Pos{
    int y,x;
};
int r,c;
bool checkValid(int y,int x){
    return y>=0 and y<r and x>=0 and x<c;
}

/*주사위를 나타내는 Dice 모듈과 지도를 나타내는 Board 모듈로 나눈 후,
주사위가 한 번 굴러갈때 발생하는 역할과 책임은 정보 전문가인 모듈에게 할당했습니다.*/

struct Dice{
    int dir;
    int diceNum[3];
    Pos pos;
    int swapIdx[4] = {2,1,2,1};
    int modifyIdx[4] = {2,0,0,1};
    Dice(){
        dir = 1;pos.y = pos.x = 0;
        diceNum[0] = 1;diceNum[1] = 3;diceNum[2] = 5;
    }
    void movePos(){
        int cy = pos.y+dy[dir],cx = pos.x+dx[dir];
        if(!checkValid(cy,cx)) dir=(dir+2)%4;
        pos.y+=dy[dir];pos.x+=dx[dir];
    }
    void modifyDiceNum(){
        swap(diceNum[0],diceNum[swapIdx[dir]]);
        diceNum[modifyIdx[dir]] = 7 - diceNum[modifyIdx[dir]];
    }
    void moveDice(){
        movePos();
        modifyDiceNum();
    }
    int getFloorNum(){
        return 7 - diceNum[0];
    }
    Pos getPos(){
        return pos;
    }
    void setDirClockwise(){
        dir = (dir+1)%4;
    }
    void setDirAntiClockwise(){
        dir = (dir+3)%4;
    }
};
struct Board{
    vector<vector<int>> board,tileScore,neighborSize;
    Dice theDice;
    int totalScore;
    int getNeighborSizeDfs(int y,int x,int criteria,vector<vector<bool>>& visited){
        visited[y][x] = true;
        int sz = 1;
        for(int dir=0;dir<4;dir++){
            int cy = y+dy[dir],cx = x+dx[dir];
            if(checkValid(cy,cx) and !visited[cy][cx] and board[cy][cx]==criteria){
                sz+=getNeighborSizeDfs(cy,cx,criteria,visited);
            }
        }
        return sz;
    }
    void setNeighborSize(){
        vector<vector<bool>> visited(r,vector<bool>(c));
        for(int y=0;y<r;y++){
            for(int x=0;x<c;x++){
                if(!visited[y][x]){
                    int sz = getNeighborSizeDfs(y,x,board[y][x],visited);
                    neighborSize[y][x] = sz;
                }
            }
        }
    }
    void setTileScoreDfs(int y,int x,int criteria,int sz,vector<vector<bool>>& visited){
        visited[y][x] = true;
        tileScore[y][x] = criteria*sz;
        for(int dir=0;dir<4;dir++){
            int cy = y+dy[dir],cx = x+dx[dir];
            if(checkValid(cy,cx) and !visited[cy][cx] and board[cy][cx]==criteria){
                setTileScoreDfs(cy,cx,criteria,sz,visited);
            }
        }
    }
    void setTileScore(){
        vector<vector<bool>> visited(r,vector<bool>(c));
        for(int y=0;y<r;y++){
            for(int x=0;x<c;x++){
                if(!visited[y][x]){
                    assert(neighborSize[y][x]>0);
                    setTileScoreDfs(y,x,board[y][x],neighborSize[y][x],visited);
                }
            }
        }
    }
    Board(vector<vector<int>>& _board) : board(_board),totalScore(0){
        tileScore = neighborSize = vector<vector<int>>(r,vector<int>(c));
        setNeighborSize();
        setTileScore();
    }
    void setDiceDirection(){
        int A = theDice.getFloorNum();
        Pos dicePos = theDice.getPos();
        int B = board[dicePos.y][dicePos.x];
        if(A>B){
            theDice.setDirClockwise();
        }else if(A<B){
            theDice.setDirAntiClockwise();
        }
    }
    void increseScore(){
        Pos dicePos = theDice.getPos();
        totalScore+=tileScore[dicePos.y][dicePos.x];
    }
    void Onestep(){
        theDice.moveDice();
        increseScore();
        setDiceDirection();
    }
    int getTotalScore(){
        return totalScore;
    }
};
void run(){
    cin>>r>>c;
    int k;cin>>k;
    vector<vector<int>> grid(r,vector<int>(c));
    for(int y=0;y<r;y++){
        for(int x=0;x<c;x++){
            cin>>grid[y][x];
        }
    }
    Board theBoard(grid);
    for(int i=0;i<k;i++){
        theBoard.Onestep();
    }
    cout<<theBoard.getTotalScore();
}



int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    run();
}













