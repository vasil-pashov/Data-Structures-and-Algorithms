#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <set>

using namespace std;

typedef vector<vector<int>> Matrix;
typedef pair<int, int> Position;

class Board {
    public:

        explicit Board(Matrix desk) : desk{desk}, direction{initial}, id{0}, 
                             parent_id{-1}, level{0}{}

        void evaluate_cost() {
            this->cost = evaluate_heuristics() + level;
        }

        friend bool operator< (const Board &a, const Board &b) {
            if(a.cost == b.cost) {
                return b.level < a.level;
            }
            return b.cost < a.cost;
        }

        Matrix get_desk() const {
            return desk;
        }

        Position get_free() const {
            return free;
        }

        bool in_desk(const Position &p) const {
            return p.first >= 0 && p.first < desk.size() &&
                p.second >= 0 && p.second < desk.size();
        }

        bool is_solution() const {
            for(size_t i = 0; i < desk.size(); ++i) {
                for(size_t j = 0; j < desk.size(); ++j) {
                   Position target = target_position(desk[i][j], desk.size());
                   if(i != target.first || j != target.second) return false;
                }
            }
            return true;
        }

        void find_free() {
            this->free = locate_free_position(); 
        }

        int get_level() const {
            return level;
        }

        void set_level(int new_level) {
            level = new_level;
        }

        void set_id(long long new_id) {
            id = new_id;
        }

        long long get_id() const {
            return id;
        }

        long long get_parent_id() const {
            return parent_id;
        }

        void print() {
            //cout<<"Cost: "<<cost<<endl;
            //cout<<"Level: "<<level<<endl;
            //cout<<"Free: "<<"("<<free.first<<","<<free.second<<")"<<endl;
            //cout<<"ID: "<<id<<endl;
            //cout<<"Parent ID: "<<parent_id<<endl;
            //cout<<"Direction: ";
            switch(direction)  {
                case left: cout<<"left"<<endl; break;
                case right: cout<<"right"<<endl; break;
                case up: cout<<"up"<<endl; break;
                case down: cout<<"down"<<endl; break;
                case initial: cout<<"initial"<<endl; break;
            }
            /*for(size_t i = 0; i < desk.size(); ++i) {
                for(size_t j = 0; j < desk.size(); ++j) {
                    cout<<setw(3)<<desk[i][j];
                }
                cout<<endl;
            }
            cout<<endl;*/
        }

        friend Board slide(Board b, Position new_free) {
            swap(b.desk[new_free.first][new_free.second], b.desk[b.free.first][b.free.second]);
            if(new_free.second < b.free.second) {
                b.direction = right;
            } else if(new_free.second > b.free.second) {
                b.direction = left;
            } else if(new_free.first < b.free.first) {
                b.direction = down;
            } else if(new_free.first > b.free.first) {
                b.direction = up;
            }
            b.level++;
            b.free = new_free;
            b.parent_id = b.id;
            return b;
        }

    private:
        enum Direction {right, up, left, down, initial};

        Matrix desk;
        Position free;
        Direction direction;
        long long id, parent_id, level, cost;

        Position locate_free_position() {
            for(size_t i = 0; i < desk.size(); ++i) {
                for(size_t j = 0; j < desk.size(); ++j) {
                    if(desk[i][j] == 0) {
                        return {i ,j};
                    }
                }
            }
            throw "No free position";
        }

        long long evaluate_heuristics() {
            size_t size = desk.size();
            long long heuristics = 0;
            for(size_t i = 0; i < size; ++i) {
                for(size_t j = 0; j < size; ++j) {
                    int element = desk[i][j]; 
                    if(element) {
                    //cout<<"Current element: "<<element<<endl;
                    //cout<<"Current position: ("<<i<<","<<j<<")"<<endl;
                    Position target = target_position(element, size);
                    //cout<<"Target position: ("<<target.first<<","<<target.second<<")"<<endl;
                    long distance = abs((int)target.first - (int)i) + abs((int)target.second - (int)j);
                    //cout<<"Distance: "<<distance<<endl<<endl;
                    heuristics += distance;
                    }
                }
            }
            return heuristics;
        }

        Position target_position(int element, int n) const {
            if(element) return {(element - 1) / n,  (element - 1) % n};
            else return {n - 1, n - 1};
        }
};

vector<Position> get_possible_moves(const Position &current) {
    return {
        {current.first - 1, current.second}, {current.first + 1, current.second},
        {current.first, current.second - 1}, {current.first , current.second + 1},
    };
}

Matrix init() {
    cout<<"Enter number of tiles (must be a sqare): ";
    int n;
    cin>>n;
    n = sqrt(n);
    Matrix desk(n);
    cout<<"Enter tiles in desk: "<<endl;
    for(int i = 0; i < n; i++) {
        desk[i].resize(n);
        for(int j = 0; j < n; ++j) {
            cin>>desk[i][j];
        }
    }
    return desk;
}

void print_solution(Board &current, vector<Board> &parent) {
    if(current.get_level() == 0) {
        //current.print();
        return;
    }
    print_solution(parent[current.get_parent_id()], parent);
    current.print();
}

void solve(Matrix desk) {
    Board initial(desk);
    initial.set_level(0);
    initial.find_free();
    initial.evaluate_cost();

    vector<Board> parent_ptr = {initial};

    set<Matrix> used;
    used.insert(desk);
    
    priority_queue<Board> q;
    q.push(initial);

    while(!q.empty()) {
        Board current = q.top();
        q.pop();

        if(current.is_solution()) {
            cout<<current.get_level()<<endl;
            print_solution(current, parent_ptr);
            return;
        }

        for(Position new_free : get_possible_moves(current.get_free())) {
            if(current.in_desk(new_free)) {
                Board new_board = slide(current, new_free);
                if(used.find(new_board.get_desk()) == used.end()) {
                    new_board.evaluate_cost();
                    new_board.set_id(used.size());
                    q.push(new_board);
                    used.insert(new_board.get_desk());
                    parent_ptr.push_back(new_board);
                }
            }
        }
    }
}

int main() {
    Matrix desk = init();
    solve(desk);
    return 0;
}
