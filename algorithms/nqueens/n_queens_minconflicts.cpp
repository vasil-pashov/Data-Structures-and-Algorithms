#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

//(column, confilcts_cnt)
typedef pair<size_t, size_t> Queen;
vector<size_t> max_conflicts;
vector<vector<int>> hits;

void hit_diagonal1(int queen, const vector<Queen> &all, int inc) {
    int i = 1;    
    Queen q = all[queen];
    while(queen - i >= 0 && (int)q.first - i >= 0) {
        hits[queen - i][q.first - i] += inc;
        ++i;
    }
    i = 1;
    while(queen + i < all.size() && (int)q.first + i < all.size()) {
        hits[queen + i][q.first + i] += inc;
        ++i;
    }
}

void hit_diagonal2(int queen, const vector<Queen> &all, int inc) {
    int i = 1;    
    Queen q = all[queen];
    while(queen + i < all.size() && (int)q.first - i >= 0) {
        hits[queen + i][q.first - i]+=inc;
        ++i;
    }
    i = 1;
    while(queen - i >= 0  && q.first + i < all.size()) {
        hits[queen - i][q.first + i] += inc;
        ++i;
    }
}

void hit_col(int queen, const vector<Queen> &all, int inc) {
    Queen q = all[queen];
    for(int i = 0; i < all.size(); ++i) {
        if(i != queen) {
            hits[i][q.first] += inc;
        }
    }
}

void print_hits() {
    for(auto i : hits) {
        for(auto j : i) {
            cout<<j<<" ";
        }
        cout<<endl;
    }
}

void update_queen_hits(int queen, const vector<Queen> &all, int inc) {
    hit_diagonal1(queen, all, inc);
    hit_diagonal2(queen, all, inc);
    hit_col(queen, all, inc);
}

bool solved(const vector<Queen> &all) {
    for(auto i : all) {
        if(i.second) return false;
    }
    return true;
}

void generate_initial(vector<Queen> &all) {
    vector<bool> used(all.size(), false);
    for(int i = 0; i < hits.size(); ++i) {
        for(int j = 0; j < hits[i].size(); ++j) {
            hits[i][j] = 0;
        }
    }
    for(size_t i = 0; i < all.size(); ++i) {
        size_t pos = rand() % all.size();
        while(used[pos]) {
            pos = rand() % all.size();
        }
        all[i] = {pos, 0};
        used[pos] = true;
        update_queen_hits(i, all, 1);
    }
}

int count_queen_confilcts(const vector<Queen> &all, Queen current, size_t queen_index) {
    int conflicts = 0;
    for(size_t i = 0; i < all.size(); ++i) {
        if(i != queen_index) {
            if(all[i].first == current.first || queen_index + current.first == i + all[i].first ||
                    queen_index + all[i].first == current.first + i) {
                ++conflicts;
            } 
        }
    }
    return conflicts;

}

int count_queen_confilcts(const vector<Queen> &all, size_t queen_index) {
    return count_queen_confilcts(all, all[queen_index], queen_index);
}

size_t count_all_conflicts(vector<Queen> &all) {
    vector<size_t> max_conflicts_index;
    for(size_t i = 0; i < all.size(); ++i) {
        all[i].second = count_queen_confilcts(all, i);
        if(max_conflicts_index.empty() || all[max_conflicts_index[0]].second == all[i].second) {
            max_conflicts_index.push_back(i);
        } else if(all[max_conflicts_index[0]].second < all[i].second) {
            max_conflicts_index.clear();
            max_conflicts_index.push_back(i);
        }
    }
    return max_conflicts_index[rand() % max_conflicts_index.size()];
}

//Queen find_min_conflicts_position(const vector<Queen> &all, size_t current) {
//    vector<Queen> min_confilcts = {{0, count_queen_confilcts(all, {0, 0}, current)}};
//    for(size_t i = 1; i < all.size(); ++i) {
//        size_t conflicts = count_queen_confilcts(all, {i, all[current].second}, current);
//        if(min_confilcts[0].second > conflicts) {
//            min_confilcts.clear();
//            min_confilcts.emplace_back(i, conflicts);
//        } else if(min_confilcts[0].second == conflicts) {
//            min_confilcts.emplace_back(i, conflicts);
//        }
//    }
//    return min_confilcts[rand() % min_confilcts.size()];
//}


int find_min_conflicts_position(const vector<Queen> &all, size_t current) {
    vector<int> min_conf;
    int min = all.size() + 1;
    for(int i = 0; i < hits.size(); ++i) {
        if(min == hits[current][i]) {
            min_conf.push_back(i);
        } else if(min > hits[current][i]) {
            min = hits[current][i];
            min_conf.clear();
            min_conf.push_back(i);
        }
    }
    //cout<<"Possible moves: ";
    //for(auto i : min_conf) {cout<<i<<" ";}
    //cout<<endl;
    return min_conf[rand() % min_conf.size()];
}

size_t update_and_get_max(vector<Queen> &all, size_t queen_index, size_t old_pos) {
    max_conflicts.clear();
    for(size_t i = 0; i < all.size(); ++i) {
        if(queen_index != i) {
            //new conflicts made when queen moved
            if(all[queen_index].first == all[i].first) {
                ++all[i].second; 
            }
            if(queen_index + all[queen_index].first == i + all[i].first) {
                ++all[i].second; 
            }
            if(queen_index + all[i].first ==  all[queen_index].first + i) {
                ++all[i].second; 
            }
            //decrease old conflicts
            if(old_pos == all[i].first) {
                --all[i].second; 
            }
            if(queen_index + old_pos == i + all[i].first) {
                --all[i].second; 
            }
            if(queen_index + all[i].first ==  old_pos + i) {
                --all[i].second; 
            }
            if(max_conflicts.empty() || all[max_conflicts[0]].second == all[i].second) {
                max_conflicts.push_back(i);
            } else if(all[max_conflicts[0]].second < all[i].second) {
                max_conflicts.clear();
                max_conflicts.push_back(i);
            }
        }
    }
    return max_conflicts[rand() % max_conflicts.size()];
}

void print_desk(const vector<Queen> &all_queens) {
    for(size_t i = 0; i < all_queens.size(); ++i) {
        for(size_t j = 0; j < all_queens.size(); ++j) {
            if(all_queens[i].first == j) cout<<" * ";
            else cout<<" - ";
        }
        cout<<endl;
    }
}

void solve(int size) {
    srand(time(NULL));
    vector<Queen> all(size);
    hits.resize(size);
    for(int i = 0; i < size; ++i) {
        hits[i].resize(size);
    }
    size_t max_conflicts_queen_index;
    while(true) {
        generate_initial(all);
        max_conflicts_queen_index = count_all_conflicts(all);
        for(size_t i = 0; i < 3 * all.size(); ++i) {
            size_t old_pos = all[max_conflicts_queen_index].first,
                   new_pos = find_min_conflicts_position(all, max_conflicts_queen_index);;
            //print_desk(all);
            //print_hits();
            //cout<<"Max conf queen index: "<<max_conflicts_queen_index<<endl;
            //cout<<"Number of conflicts: "<<all[max_conflicts_queen_index].second<<endl;
            //cout<<"Old pos: "<<old_pos<<endl;
            //cout<<"New pos: "<<new_pos<<endl;
            //all[max_conflicts_queen_index] = find_min_conflicts_position(all, max_conflicts_queen_index);
            update_queen_hits(max_conflicts_queen_index, all, -1);
            all[max_conflicts_queen_index].first = new_pos;
            all[max_conflicts_queen_index].second = count_queen_confilcts(all, max_conflicts_queen_index);
            update_queen_hits(max_conflicts_queen_index, all, 1);
            max_conflicts_queen_index = update_and_get_max(all, max_conflicts_queen_index, old_pos);
            if(!all[max_conflicts_queen_index].second) {
                //cout<<all[count_all_conflicts(all)].second<<endl;
                print_desk(all);
                return;
            }
        }
    }
}

int main(int, char **argv) {
    int n;
    cin>>n;
    if(n < 4) {
        cout<<"No solution for less than 4 queens!"<<endl;
    } else {
        solve(n);
    }
    //solve(stoi(argv[1]));
    return 0;
}
