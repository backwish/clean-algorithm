#include <bits/stdc++.h>
using namespace std;
const int R = 10;
const int C = 4;

struct Pos{
    int y,x;
};

/*Board 객체가 Block 객체의 type에 직접 접근하는 설계의 문제가 있지만
Block 객체가 블록 관련된 모든 일을 처리하도록 하면 board의 정보가 필요하고 board의 수정이 필요해서 의존성이 양방향으로 얽히므로
Block 객체는 board 객체를 위한 ADT로 생각하고 클래스를 설계했습니다.*/

struct Block{
    int type,serialNum;
    vector<Pos> tiles;
    Block(int _type,int _serialNum,Pos pos) : type(_type),serialNum(_serialNum){
        tiles.push_back({pos.y,pos.x});
        if(type==2) tiles.push_back({pos.y,pos.x+1});
        if(type==3) tiles.push_back({pos.y+1,pos.x});
    }
};

struct Board{
    int board[R][C];
    int score;
    Board(){
        memset(board,0,sizeof(board));
        score = 0;
    }
    int getMovedTileYPos(int y,int x){
        y++;
        while(y<R and board[y][x]==0) y++;
        return y-1;
    }
    int getMovedBlockYPos(Block& block){
        int y = R;
        for(Pos each:block.tiles){
            y = min(y,getMovedTileYPos(each.y,each.x));
        }
        return y;
    }
    vector<int> getFullRows(){
        vector<int> ret;
        for(int y=R-C;y<R;y++){
            bool toErase = true;
            for(int x=0;x<C;x++){
                if(board[y][x]==0){
                    toErase = false;
                    break;
                }
            }
            if(toErase) ret.push_back(y);
        }
        return ret;
    }
    vector<int> getSpecialEraseRows(){
        vector<int> ret;
        int rowNum = 0;
        for(int y=C;y<R-C;y++){
            for(int x=0;x<C;x++){
                if(board[y][x]>0){
                    rowNum++;
                    break;
                }
            }
        }
        for(int i=0;i<rowNum;i++) ret.push_back(R-1-i);
        return ret;
    }
    void eraseRows(vector<int>& toErase){
        for(int y:toErase){
            for(int x=0;x<C;x++){
                board[y][x] = 0;
            }
        }
    }
    
    void moveRow(int y){
        bool moved[C];
        memset(moved,false,sizeof(moved));
        for(int x=0;x<C;x++){
            if(board[y][x]==0 or moved[x]) continue;
            vector<Pos> block;
            int blockX = x,newY = R;
            if(x+1<C and board[y][x]==board[y][x+1]){
                moved[x] = moved[x+1] = true;
                int newY = min(getMovedTileYPos(y,x),getMovedTileYPos(y,x+1));
                swap(board[y][x],board[newY][x]);
                swap(board[y][x+1],board[newY][x+1]);
            }else{
                moved[x] = true;
                int newY = getMovedTileYPos(y,x);
                swap(board[y][x],board[newY][x]);
            }
        }
    }
    void moveAfterErase(){
        for(int y=R-1;y>=C;y--) moveRow(y);
    }
    void makeScore(){
        while(true){
            vector<int> toErase = getFullRows();
            if(toErase.empty()) break;
            score+=toErase.size();
            eraseRows(toErase);
            moveAfterErase();
        }
    }
    void eraseSpecialCase(){
        vector<int> toErase = getSpecialEraseRows();
        eraseRows(toErase);
        moveAfterErase();
    }
    void allocateBlock(Block& block){
        int y = getMovedBlockYPos(block),x = block.tiles[0].x;
        if(block.type==1){
            board[y][x] = block.serialNum;
        }else if(block.type==2){
            board[y][x] = board[y][x+1] = block.serialNum;
        }else{
            board[y][x] = board[y-1][x] = block.serialNum;
        }
    }
    void runOneStep(Block& block){
        allocateBlock(block);
        makeScore();
        eraseSpecialCase();
    }
    int getScore(){
        return score;
    }
    int getRemainTiles(){
        int ret = 0;
        for(int y=C;y<R;y++){
            for(int x=0;x<C;x++){
                if(board[y][x]>0) ret++;
            }
        }
        return ret;
    }
};

void run(){
    int n;cin>>n;
    Board verticalBoard,horizontalBoard;
    for(int i=1;i<=n;i++){
        int type,y,x;cin>>type>>y>>x;
        int horizontalType = (type==1 ? type : 5-type);
        Block blockVertical(type,i,{y,x});
        Block blockHorizontal(horizontalType,i,{x,y});
        verticalBoard.runOneStep(blockVertical);
        horizontalBoard.runOneStep(blockHorizontal);
    }
    int score = verticalBoard.getScore()+horizontalBoard.getScore();
    int remainTiles = verticalBoard.getRemainTiles()+horizontalBoard.getRemainTiles();
    cout<<score<<'\n'<<remainTiles;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    run();
}
