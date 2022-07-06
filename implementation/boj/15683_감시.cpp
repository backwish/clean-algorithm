#include <bits/stdc++.h>
using namespace std;
const int dy[4] = {0,1,0,-1};
const int dx[4] = {1,0,-1,0};
const int EMPTY = 0;
const int WALL = 6;

struct Pos{
    int y,x;
};

/*
감시 카메라를 표현하는 Camera 클래스와 사무실을 표현하는 Board 클래스로 나눴습니다. Board 클래스는 Camera들을 가지므로 has-a 관계가 성립합니다.
Camera 클래스는 CCTV 종류의 변경을 고려하면 abstract Camera 클래스와 이를 상속하는 구체적 CameraNo# 클래스로 설계하는게 맞다고 생각드나
해당 문제에서는 가독성이 떨어지는 단점이 더 크다 생각해서 추상화를 하지 않았습니다.
*/

struct Camera{
    Pos pos;
    vector<int> watchDirs;
    Camera(Pos _pos,int mode) : pos(_pos){//mode start at 1
        watchDirs.push_back(0);
        if(mode==5) watchDirs.push_back(1);
        if(mode==2 or mode==4 or mode==5) watchDirs.push_back(2);
        if(mode==3 or mode==4 or mode==5) watchDirs.push_back(3);
    }
    void rotate(){
        for(int& each:watchDirs){
            each=(each+1)%4;
        }
    }
};

struct Board{
    vector<vector<int>> board;
    vector<vector<Camera>> cameraTable;
    int r,c;
    bool checkCamera(int y,int x){
        return board[y][x]!=EMPTY and board[y][x]!=WALL;
    }
    bool checkValid(int y,int x){
        return y>=0 and y<r and x>=0 and x<c;
    }
    vector<Camera> getAllRotation(Camera& theCamera){
        vector<Camera> allRotation;
        for(int k=0;k<4;k++){
            allRotation.push_back(theCamera);
            theCamera.rotate();
        }
        return allRotation;
    }
    void buildCameraTable(){
        for(int y=0;y<r;y++){
            for(int x=0;x<c;x++){
                if(checkCamera(y,x)){
                    Camera theCamera({y,x},board[y][x]);
                    cameraTable.push_back(getAllRotation(theCamera));
                }
            }
        }
    }
    Board(int _r,int _c,vector<vector<int>> _board) : r(_r),c(_c),board(_board){
        buildCameraTable();
    }
    int getNotWatchedSize(){
        int ret = 0;
        for(int y=0;y<r;y++){
            for(int x=0;x<c;x++){
                if(board[y][x]==EMPTY) ret++;
            }
        }
        return ret;
    }
    int getRotateNum(int serialNum,int idx){
        return (serialNum>>(2*idx))&3;
    }
    void setWatch(Camera& theCamera){
        for(int dir:theCamera.watchDirs){
            Pos cameraPos = theCamera.pos;
            int y = cameraPos.y,x = cameraPos.x,mode = board[y][x];
            while(checkValid(y,x) and board[y][x]!=WALL){
                if(board[y][x]==0) board[y][x] = mode;
                y+=dy[dir],x+=dx[dir];
            }
        }
    }
    int getMinNotWatchedSize(){
        int n = cameraTable.size(),iterNum = (1<<(2*n));
        int best = 1e9;
        for(int i=0;i<iterNum;i++){
            auto temp = board;
            for(int j=0;j<n;j++){
                int rotateNum = getRotateNum(i,j);
                setWatch(cameraTable[j][rotateNum]);
            }
            best = min(best,getNotWatchedSize());
            board = temp;
        }
        return best;
    }
};

void run(){
    int r,c;cin>>r>>c;
    vector<vector<int>> board(r,vector<int>(c));
    for(int y=0;y<r;y++){
        for(int x=0;x<c;x++){
            cin>>board[y][x];
        }
    }
    Board theBoard(r,c,board);
    cout<<theBoard.getMinNotWatchedSize();
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    run();
}
