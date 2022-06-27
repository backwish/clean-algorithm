#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 20;
const int CLEAN = -1;
const int BLOCK = -2;
const int INF = 1e9;
const char CLEAN_CHAR = '.';
const char DIRTY_CHAR = '*';
const char BLOCK_CHAR = 'x';
const char START_CHAR = 'o';
const int dy[4] = {-1,1,0,0};
const int dx[4] = {0,0,-1,1};

struct Pos{
    int y,x,cost;
};

struct Room{
    int board[MAX_N][MAX_N],dirtyCnt,w,h,startY,startX;
    Room(int _w,int _h) : dirtyCnt(1),w(_w),h(_h){
        for(int y=0;y<h;y++){
            string word;cin>>word;
            for(int x=0;x<w;x++){
                switch(word[x]){
                    case CLEAN_CHAR: board[y][x] = CLEAN;
                        break;
                    case DIRTY_CHAR: board[y][x] = dirtyCnt++;
                        break;
                    case BLOCK_CHAR: board[y][x] = BLOCK;
                        break;
                    case START_CHAR: startY = y;startX = x;board[y][x] = 0;
                        break;
                    default: assert(false);
                        break;
                }
            }
        }
    }
    bool checkValid(int y,int x){
        return y>=0 and y<h and x>=0 and x<w;
    }
    bool checkBlock(int y,int x){
        return board[y][x]==BLOCK;
    }
    bool checkToVisit(int y,int x){
        return board[y][x]>=0;
    }
    vector<int> getDist(int startY,int startX){
        vector<int> dist(dirtyCnt,INF);
        bool visited[MAX_N][MAX_N];
        memset(visited,false,sizeof(visited));
        visited[startY][startX] = 0;
        queue<Pos> q;
        q.push({startY,startX,0});
        while(!q.empty()){
            Pos herePos = q.front();
            q.pop();
            int y = herePos.y,x = herePos.x,cost = herePos.cost;
            if(checkToVisit(y,x)){
                dist[board[y][x]] = cost;
            }
            for(int dir=0;dir<4;dir++){
                int cy = y+dy[dir],cx = x+dx[dir];
                if(checkValid(cy,cx) and !checkBlock(cy,cx) and !visited[cy][cx]){
                    visited[cy][cx] = true;
                    q.push({cy,cx,cost+1});
                }
            }
        }
        return dist;
    }
    vector<vector<int>> getDistMatrix(){
        vector<vector<int>> distMatrix(dirtyCnt);
        for(int y=0;y<h;y++){
            for(int x=0;x<w;x++){
                if(checkToVisit(y,x)){
                    distMatrix[board[y][x]] = getDist(y,x);
                }
            }
        }
        return distMatrix;
    }
    int getDirtyCnt(){
        return dirtyCnt;
    }
};

struct TSP{
    vector<vector<int>> distMatrix;
    int dirtyCnt,best;
    bool checkCanVisitAll(){
        for(int i=0;i<dirtyCnt;i++){
            for(int j=0;j<dirtyCnt;j++){
                if(distMatrix[i][j]==INF) return false;
            }
        }
        return true;
    }
    bool checkAllVisited(vector<bool>& visited){
        for(int i=0;i<visited.size();i++){
            if(!visited[i]) return false;
        }
        return true;
    }
    void dfs(int here,vector<bool>& visited,int cost){
        if(checkAllVisited(visited)){
            best = min(best,cost);
            return;
        }
        if(cost>=best) return;
        for(int there=1;there<dirtyCnt;there++){
            if(!visited[there]){
                visited[there] = true;
                dfs(there,visited,cost+distMatrix[here][there]);
                visited[there] = false;
            }
        }
    }
    int calcBest(){
        vector<bool> visited(dirtyCnt);
        visited[0] = true;
        dfs(0,visited,0);
        return best;
    }
    TSP(int _n,Room& theRoom) : dirtyCnt(_n),best(1e9){
        distMatrix = theRoom.getDistMatrix();
    }
};

void run(){
    while(true){
        int w,h;cin>>w>>h;
        if(w==0 and h==0) break;
        Room theRoom(w,h);
        int dirtyCnt = theRoom.getDirtyCnt();
        TSP tspCalc(dirtyCnt,theRoom);
        if(!tspCalc.checkCanVisitAll()){
            cout<<-1<<'\n';
            continue;
        }
        cout<<tspCalc.calcBest()<<'\n';
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    run();
}
