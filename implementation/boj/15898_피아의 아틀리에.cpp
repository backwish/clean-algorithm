#include <bits/stdc++.h>
using namespace std;
const int MIN_QUALITY = 0;
const int MAX_QUALITY = 9;
const int INGERDIENT_SIZE = 4;
const int POT_SIZE = 5;
const char WHITE = 'W';
const char RED = 'R';
const char BLUE = 'B';
const char GREEN = 'G';
const char YELLOW = 'Y';
struct Pos{
    int y,x;
};
struct Tile{
    int quality;
    char ele;
    Tile(){
        quality = 0;ele = WHITE;
    }
    void changeQuality(int delta){
        quality+=delta;
        if(quality<MIN_QUALITY) quality = MIN_QUALITY;
        if(quality>MAX_QUALITY) quality = MAX_QUALITY;
    }
    void changeElement(char after){
        if(after!='W') ele = after;
    }
    void mix(Tile rhs){
        changeQuality(rhs.quality);
        changeElement(rhs.ele);
    }
    int getScore(){
        if(ele==RED) return quality*7;
        else if(ele==BLUE) return quality*5;
        else if(ele==GREEN) return quality*3;
        else if(ele==YELLOW) return quality*2;
        return 0;
    }
};

struct Ingredient{
    Tile board[INGERDIENT_SIZE][INGERDIENT_SIZE];
    Ingredient(vector<vector<int>>& qualVec,vector<vector<char>>& eleVec){
        for(int y=0;y<INGERDIENT_SIZE;y++){
            for(int x=0;x<INGERDIENT_SIZE;x++){
                board[y][x].quality = qualVec[y][x];
                board[y][x].ele = eleVec[y][x];
            }
        }
    }
    void rotate(){
        Tile result[INGERDIENT_SIZE][INGERDIENT_SIZE];
        for(int y=0;y<INGERDIENT_SIZE;y++){
            for(int x=0;x<INGERDIENT_SIZE;x++){
                result[y][x] = board[INGERDIENT_SIZE-1-x][y];
            }
        }
        for(int y=0;y<INGERDIENT_SIZE;y++){
            for(int x=0;x<INGERDIENT_SIZE;x++){
                board[y][x] = result[y][x];
            }
        }
    }
    Tile getTile(int y,int x){
        return board[y][x];
    }
};

struct IngredientTable{
    vector<vector<Ingredient>> table;
    int n;
    IngredientTable(int _n,vector<Ingredient>& ingredients) : n(_n){
        for(Ingredient& each:ingredients){
            vector<Ingredient> rotations;
            for(int d=0;d<4;d++){
                rotations.push_back(each);
                each.rotate();
            }
            table.push_back(rotations);
        }
    }
    Ingredient getIngredient(int ingredientNum,int angle){
        return table[ingredientNum][angle];
    }
};

struct Pot{
    Tile board[POT_SIZE][POT_SIZE];
    void mix(int startRow,int startCol,Ingredient& theIngredient){
        for(int y=startRow;y<startRow+INGERDIENT_SIZE;y++){
            for(int x=startCol;x<startCol+INGERDIENT_SIZE;x++){
                board[y][x].mix(theIngredient.getTile(y-startRow,x-startCol));
            }
        }
    }
    int calcScore(){
        int ret = 0;
        for(int y=0;y<POT_SIZE;y++){
            for(int x=0;x<POT_SIZE;x++){
                ret+=board[y][x].getScore();
            }
        }
        return ret;
    }
};

struct Search{
    IngredientTable table;
    int n;
    Search(int _n,vector<Ingredient>& ingredients) : table(_n,ingredients),n(_n){}
    vector<int> buildInitPerm(){
        vector<int> perm(n);
        for(int i=n-3;i<n;i++) perm[i] = i - (n-4);
        return perm;
    }
    vector<int> buildOrder(vector<int>& perm){
        vector<int> order(3);
        for(int i=0;i<perm.size();i++){
            if(perm[i]>0) order[perm[i]-1] = i;
        }
        return order;
    }
    vector<Ingredient> pickIngredients(vector<int>& order,int angles){
        vector<Ingredient> ingredients;
        for(int i=0;i<3;i++){
            ingredients.push_back(table.getIngredient(order[i],angles%4));
            angles/=4;
        }
        return ingredients;
    }
    int calcBest(){
        int best = 0;
        vector<int> perm = buildInitPerm();
        do{
            vector<int> order = buildOrder(perm);
            for(int angles=0;angles<64;angles++){
                vector<Ingredient> ingredients = pickIngredients(order,angles);
                best = max(best,calcBestFromGivenIngredients(ingredients));
            }
        }while(next_permutation(perm.begin(),perm.end()));
        return best;
    }
    Pos getStartPosFromOrder(int serial,int kth){
        Pos pos;
        int idx = ((serial>>(kth*2))&3);
        pos.y = idx/2;pos.x = idx%2;
        return pos;
    }
    int calcBestFromGivenIngredients(vector<Ingredient>& ingredients){
        int best = 0;
        for(int i=0;i<64;i++){
            Pot pot;
            for(int j=0;j<3;j++){
                Pos pos = getStartPosFromOrder(i,j);
                pot.mix(pos.y,pos.x,ingredients[j]);
            }
            best = max(best,pot.calcScore());
        }
        return best;
    }
};

void run(){
    int n;cin>>n;
    vector<vector<int>> qualVec(INGERDIENT_SIZE,vector<int>(INGERDIENT_SIZE));
    vector<vector<char>> eleVec(INGERDIENT_SIZE,vector<char>(INGERDIENT_SIZE));
    vector<Ingredient> ingredients;
    for(int i=0;i<n;i++){
        for(int y=0;y<INGERDIENT_SIZE;y++){
            for(int x=0;x<INGERDIENT_SIZE;x++){
                cin>>qualVec[y][x];
            }
        }
        for(int y=0;y<INGERDIENT_SIZE;y++){
            for(int x=0;x<INGERDIENT_SIZE;x++){
                cin>>eleVec[y][x];
            }
        }
        Ingredient theIngredient(qualVec,eleVec);
        ingredients.push_back(theIngredient);
    }
    Search theSearch(n,ingredients);
    cout<<theSearch.calcBest();
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    run();
}
