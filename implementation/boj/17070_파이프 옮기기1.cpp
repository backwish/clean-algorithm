#include <bits/stdc++.h>
using namespace std;
const int HORIZONTAL = 0;
const int VERTICAL = 1;
const int DIAGONAL = 2;
const int EMPTY = 0;
const int WALL = 1;
const int MAX_N = 32;
typedef long long ll;
struct Pos{
    int y,x;
};

/*파이프를 나타내는 Pipe 객체와 집을 나타내는 House 객체를 두고, 
House 객체와 Pipe 객체 사이는 has-a 관계가 있으므로 합성 관계로 표현했습니다.*/

struct Pipe{
    Pos tile[2];
    int mode;
    Pipe(){
        tile[0] = {0,0};
        tile[1] = {0,1};
        mode = HORIZONTAL;
    }
    vector<Pos> getShouldEmptyPos(int nextMode){
        vector<Pos> ret;
        if(nextMode==HORIZONTAL or nextMode==DIAGONAL){
            ret.push_back({tile[1].y,tile[1].x+1});
        }
        if(nextMode==VERTICAL or nextMode==DIAGONAL){
            ret.push_back({tile[1].y+1,tile[1].x});
        }
        if(nextMode==DIAGONAL){
            ret.push_back({tile[1].y+1,tile[1].x+1});
        }
        return ret;
    }
    void moveNext(int nextMode){
        tile[0] = tile[1];
        if(nextMode==HORIZONTAL or nextMode==DIAGONAL)
            tile[1].x++;
        if(nextMode==VERTICAL or nextMode==DIAGONAL)
            tile[1].y++;
        mode = nextMode;
    }
    bool checkEnd(int n){
        return tile[1].y==n-1 and tile[1].x==n-1;
    }
    Pos getSecondTile(){
        return tile[1];
    }
};
struct House{
    vector<vector<int>> house;
    Pipe currPipe;
    int n;
    ll dp[MAX_N][MAX_N][3];
    House(int _n,vector<vector<int>>& _house) : n(_n),house(_house){
        memset(dp,-1,sizeof(dp));
        Pipe thePipe;
        currPipe = thePipe;
    }
    bool checkValid(Pos& pos){
        return pos.y>=0 and pos.y<n and pos.x>=0 and pos.x<n;
    }
    bool checkCanMove(int nextMode){
        if(currPipe.mode==HORIZONTAL and nextMode==VERTICAL) return false;
        if(currPipe.mode==VERTICAL and nextMode==HORIZONTAL) return false;
        vector<Pos> nextPos = currPipe.getShouldEmptyPos(nextMode);
        for(Pos& pos:nextPos){
            if(!checkValid(pos) or house[pos.y][pos.x]==WALL) return false;
        }
        return true;
    }
    ll dfs(){
        ll cases = 0;
        Pos secondTile = currPipe.getSecondTile();
        if(currPipe.checkEnd(n)) return 1;
        if(dp[secondTile.y][secondTile.x][currPipe.mode]!=-1)
            return dp[secondTile.y][secondTile.x][currPipe.mode];
        for(int mode=0;mode<3;mode++){
            if(checkCanMove(mode)){
                Pipe temp = currPipe;
                currPipe.moveNext(mode);
                cases+=dfs();
                currPipe = temp;
            }
        }
        return dp[secondTile.y][secondTile.x][currPipe.mode] = cases;
    }
};

void run(){
    int n;cin>>n;
    vector<vector<int>> grid(n,vector<int>(n));
    for(int y=0;y<n;y++){
        for(int x=0;x<n;x++){
            int val;cin>>val;
            grid[y][x] = val;
        }
    }
    House house(n,grid);
    cout<<house.dfs();
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    run();
}
