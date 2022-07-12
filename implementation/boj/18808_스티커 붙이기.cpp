#include <bits/stdc++.h>
using namespace std;
const int EMPTY = 0;
const int FILL = 1;
struct Sticker{
    vector<vector<int>> board;
    int r,c;
    Sticker(int _r,int _c,vector<vector<int>>& _board) : r(_r),c(_c),board(_board){}
    void rotate(){
        swap(r,c);
        vector<vector<int>> temp(r,vector<int>(c));
        for(int y=0;y<r;y++){
            for(int x=0;x<c;x++){
                temp[y][x] = board[c-1-x][y];
            }
        }
        board = temp;
    }
    int getTile(int y,int x){
        assert(y<r and x<c);
        return board[y][x];
    }
};

struct Notebook{
    vector<vector<int>> board;
    int r,c;
    Notebook(int _r,int _c) : r(_r),c(_c){
        board = vector<vector<int>>(r,vector<int>(c));
    }
    bool canPut(int startY,int startX,Sticker& theSticker){
        assert(theSticker.r+startY<=r and theSticker.c+startX<=c);
        for(int y=0;y<theSticker.r;y++){
            for(int x=0;x<theSticker.c;x++){
                if(board[y+startY][x+startX]==FILL and theSticker.getTile(y,x)==FILL) return false;
            }
        }
        return true;
    }
    void putSticker(int startY,int startX,Sticker& theSticker){
        assert(canPut(startY,startX,theSticker));
        for(int y=0;y<theSticker.r;y++){
            for(int x=0;x<theSticker.c;x++){
                board[y+startY][x+startX] |= theSticker.getTile(y,x);
            }
        }
    }
    void locateSticker(Sticker& theSticker){
        bool fin = false;
        for(int d=0;d<4;d++){
            for(int y=0;y<=r-theSticker.r;y++){
                for(int x=0;x<=c-theSticker.c;x++){
                    if(canPut(y,x,theSticker)){
                        putSticker(y,x,theSticker);
                        fin = true;
                        break;
                    }
                }
                if(fin) break;
            }
            if(fin) break;
            theSticker.rotate();
        }
    }
    int getPutTileNum(){
        int ret = 0;
        for(int y=0;y<r;y++){
            for(int x=0;x<c;x++){
                ret+=board[y][x];
            }
        }
        return ret;
    }
};

void run(){
    int n,m,k;cin>>n>>m>>k;
    Notebook theNotebook(n,m);
    for(int i=0;i<k;i++){
        int r,c;cin>>r>>c;
        vector<vector<int>> board(r,vector<int>(c));
        for(int y=0;y<r;y++){
            for(int x=0;x<c;x++){
                cin>>board[y][x];
            }
        }
        Sticker theSticker(r,c,board);
        theNotebook.locateSticker(theSticker);
    }
    cout<<theNotebook.getPutTileNum();
}



int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    run();
}
