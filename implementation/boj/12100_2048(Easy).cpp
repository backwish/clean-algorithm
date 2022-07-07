#include <bits/stdc++.h>
using namespace std;
const int dy[4] = {0,0,1,-1};
const int dx[4] = {1,-1,0,0};
const int EMPTY = 0;
struct Pos{
    int y,x;
    void moveNext(int dir){
        y+=dy[dir];
        x+=dx[dir];
    }
    void movePrev(int dir){
        y-=dy[dir];
        x-=dx[dir];
    }
};

/*Board 객체는 보드 위의 블록을 한 방향으로 이동시키는 moveBoard 함수와 보드에서 최대 블록을 반환하는 getMaxBlock 함수를 제공하고, 
run 함수에서 이를 사용하여 최대 5번 이동하여 만들 수 있는 가장 큰 블록의 값을 구합니다.*/

struct Board{
    int n;
    vector<vector<int>> board;
    vector<vector<bool>> merged;
    Board(int _n,vector<vector<int>>& _board) : n(_n),board(_board){}
    bool checkValid(int y,int x){
        return y>=0 and y<n and x>=0 and x<n;
    }
    Pos getFrom(int fix,int k,int dir){
        Pos from;
        (dir<2 ? from.y : from.x) = fix;
        int var = (dir%2==0 ? n-1-k : k);
        (dir<2 ? from.x : from.y) = var;
        return from;
    }
    Pos getTo(Pos& start,int dir){
        Pos end = start;
        end.moveNext(dir);
        while(checkValid(end.y,end.x) and board[end.y][end.x]==EMPTY) end.moveNext(dir);
        return end;
    }
    bool checkCanMerge(Pos& start,Pos& next){
        return checkValid(next.y,next.x) and board[start.y][start.x]==board[next.y][next.x] and !merged[next.y][next.x];
    }
    void mergeBlock(Pos& from,Pos& to){
        board[to.y][to.x]<<=1;
        board[from.y][from.x] = EMPTY;
        merged[to.y][to.x] = true;
    }
    void moveBlock(Pos& from,Pos& to){
        swap(board[from.y][from.x],board[to.y][to.x]);
    }
    void moveBoard(int dir){
        merged = vector<vector<bool>>(n,vector<bool>(n));
        for(int fix=0;fix<n;fix++){
            for(int k=0;k<n;k++){
                Pos from = getFrom(fix,k,dir);
                if(board[from.y][from.x]==EMPTY) continue;
                Pos to = getTo(from,dir);
                if(checkCanMerge(from,to)){
                    mergeBlock(from,to);
                }else{
                    to.movePrev(dir);
                    moveBlock(from,to);
                }
            }
        }
    }
    int getMaxBlock(){
        int ret = 0;
        for(int y=0;y<n;y++){
            for(int x=0;x<n;x++){
                ret = max(ret,board[y][x]);
            }
        }
        return ret;
    }
};

int getDir(int serialNum,int turn){
    return (serialNum>>(turn*2))&3;
}

void run(){
    int n;cin>>n;
    vector<vector<int>> grid(n,vector<int>(n));
    for(int y=0;y<n;y++){
        for(int x=0;x<n;x++){
            cin>>grid[y][x];
        }
    }
    int best = 0,turnNum = 5;
    for(int i=0;i<(1<<turnNum*2);i++){
        Board board(n,grid);
        for(int j=0;j<turnNum;j++){
            int dir = getDir(i,j);
            board.moveBoard(dir);
        }
        best = max(best,board.getMaxBlock());
    }
    cout<<best;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    run();
}
