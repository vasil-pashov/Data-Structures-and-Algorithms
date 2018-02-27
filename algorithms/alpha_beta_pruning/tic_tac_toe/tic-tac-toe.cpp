#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

typedef vector<vector<char>> Desk;

void print_desk(Desk &d) {
    for(auto row : d) {
        for(char el : row) {
            cout<<el<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

bool win(Desk &d, char player) {
    bool wins = true;
    //row chech
    for(size_t i = 0; i < d.size(); ++i) {
        wins = true;
        for(size_t j = 0; j < d.size(); ++j) {
            if(d[i][j] != player) {
                wins = false;
                break;
            }
        }
        if(wins) return true;
    }
    //col check
    for(size_t j = 0; j < d.size(); ++j) {
        wins = true;
        for(size_t i = 0; i < d.size(); ++i) {
            if(d[i][j] != player) {
                wins = false;
                break;
            }
        }
        if(wins) return true;
    }
    //main diag
    wins = true;
    for(size_t i = 0; i < d.size(); ++i) {
        if(d[i][i] != player)  {
            wins = false;
            break;
        }
    }
    if(wins) return true;
    //antidiag
    wins = true;
    for(size_t i = 0; i < d.size(); ++i) {
        if(d[i][d.size() - 1 - i] != player)  {
            wins = false;
            break;
        }
    }
    return wins;
}

bool has_moves(Desk &d) {
    for(size_t i = 0; i < d.size(); ++i) {
        for(size_t j = 0; j < d[i].size(); ++j) {
            if(d[i][j] == '-') {
                return true;
            }
        }
    }
    return false;
}

int winner(Desk &d) {
    if(win(d, 'x')) {
        return 1;
    } else if(win(d, 'o')) {
        return -1;
    }
    return 0;
}

typedef pair<int, int> Pos;

struct Player {
    Player(bool s, char m) : strategy{s}, mark{m} {}

    bool strategy;
    char mark;

    Player other() {
        return {!strategy, mark == 'x' ? 'o' : 'x'};
    }
};


pair<int, Pos> alpha_beta(Player p, Desk d, int a, int b) {
    int win = winner(d);
    if(win == -1 || win == 1) {
        // cout<<"Winner is: "<<(win == -1 ? 'o' : 'x')<<endl;
        // cout<<"Desk is:"<<endl;
        // print_desk(d);
        return {win, {-1,-1}};
    } else if(!has_moves(d)){
        return {0, {-1,-1}}; 
    }
    int infinity = p.strategy ? -100 : 100;
    pair<int, Pos> rez{infinity, {-1, -1}};
    bool loop = true;
    for(size_t i = 0; i < d.size() && loop; ++i) {
        for(size_t j = 0; j < d.size() && loop; ++j) {
            if(p.strategy) {
                if(d[i][j] == '-') {
                    d[i][j] = p.mark;
                    int v = alpha_beta(p.other(), d, max(rez.first, a), b).first;
                    d[i][j] = '-';
                    if(v > rez.first) {
                        rez = {v, {i, j}};
                    }
                    if(rez.first > b) {
                        loop = false;
                        break;
                    }
                }
            } else {
                if(d[i][j] == '-') {
                    d[i][j] = p.mark;
                    int v = alpha_beta(p.other(), d, a, min(rez.first, b)).first;
                    d[i][j] = '-';
                    if(v < rez.first) {
                        rez = {v, {i, j}};
                    }
                    if(rez.first < a) {
                        loop = false;
                        break;
                    }
                }
            }
        }
    }
    return rez;

}

void play(Desk d) {
    while(true) {
        int i, j;
        cin>>i>>j;
        d[i][j] = 'x';
        pair<int, Pos> rez = alpha_beta({0, 'o'}, d, -100, 100);
        d[rez.second.first][rez.second.second] = 'o';
        cout<<"Expexted result: "<<rez.first<<endl;
        print_desk(d);
        //print_desk(d);
    }
}

int main() {
    Desk d({
            {'-','-','-'},
            {'-','-','-'},
            {'-','-','-'}
            });
    play(d);
    return 0;
}
