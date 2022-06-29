#include <bits/stdc++.h>
using namespace std;
struct GameStatus{
    int n,player;
    vector<int> guilty;
    vector<vector<int>> guiltyDiff;
    vector<bool> alive;
    GameStatus(){
        cin>>n;
        guilty = vector<int>(n);
        guiltyDiff = vector<vector<int>>(n,vector<int>(n));
        alive = vector<bool>(n);
        for(int i=0;i<n;i++){
            cin>>guilty[i];
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cin>>guiltyDiff[i][j];
            }
        }
        fill(alive.begin(),alive.end(),true);
        cin>>player;
    }
    bool checkEndBeforeFirstNight(){
        if(n%2==1){
            int afternoonDead = killAfterNoon();
            if(afternoonDead==player){
                return true;
            }
        }
        return false;
    }
    int findMaxGuiltyIdx(){
        int idx = -1,maxGuilty = 0;
        for(int i=0;i<n;i++){
            if(alive[i] and guilty[i] > maxGuilty){
                maxGuilty = guilty[i];
                idx = i;
            }
        }
        return idx;
    }
    int killAfterNoon(){
        int afternoonDead = findMaxGuiltyIdx();
        alive[afternoonDead] = false;
        return afternoonDead;
    }
    void rollBackAfterNoon(int afternoonDead){
        alive[afternoonDead] = true;
    }
    void killNight(int nightDead){
        alive[nightDead] = false;
        for(int i=0;i<n;i++){
            if(alive[i]){
                guilty[i]+=guiltyDiff[nightDead][i];
            }
        }
    }
    void rollBackNight(int nightDead){
        for(int i=0;i<n;i++){
            if(alive[i]){
                guilty[i]-=guiltyDiff[nightDead][i];
            }
        }
        alive[nightDead] = true;
    }
    bool checkCanKill(int target){
        return alive[target] and target!=player;
    }
    bool checkPlayerAlive(){
        return alive[player];
    }
    int getTotalPlayerNum(){
        return n;
    }
};

int best;
void dfs(int nights,GameStatus& game){
    for(int nightDead=0;nightDead<game.getTotalPlayerNum();nightDead++){
        if(!game.checkCanKill(nightDead)) continue;
        game.killNight(nightDead);
        best = max(best,nights+1);
        int afternoonDead = game.killAfterNoon();
        if(game.checkPlayerAlive()) dfs(nights+1,game);
        game.rollBackAfterNoon(afternoonDead);
        game.rollBackNight(nightDead);
    }
}

void run(){
    GameStatus game;
    if(game.checkEndBeforeFirstNight()){
        cout<<0;
        return;
    }
    best = 0;
    dfs(0,game);
    cout<<best;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    run();
}
