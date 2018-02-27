#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct AugmentingPath {

    AugmentingPath() : AugmentingPath(vector<int>(), 0) {};

    AugmentingPath(vector<int> path, int max_flow) : 
        path{path}, max_flow{max_flow} {}

    vector<int> path;
    int max_flow;
};

class Graph {

    public:
        Graph() : Graph(0, 0) {}

        Graph(int n, int m) : nodes{n}, edges{m} {
            initialize_adjacency_matrix();
        }

        Graph(const Graph &other) :  nodes{other.nodes}, edges{other.edges} {
            copy_adjacency_matrix(other);
        }

        Graph(Graph&& other) : Graph() {
            swap(*this, other);
        }

        Graph& operator= (Graph other) {
            swap(*this, other);
            return *this;
        }

        ~Graph() {
            deallocate_adjacency_matrix();
        }

        friend void swap(Graph &first, Graph &second) {
            swap(first.nodes, second.nodes);
            swap(first.edges, second.edges);
            swap(first.adjacency_matrix, second.adjacency_matrix);
        }

        //UGLY
        void read_graph() {
            int from, to, capacity;
            for(int i = 0; i < edges; i++) {
                cin>>from>>to>>capacity;
                adjacency_matrix[from][to] = capacity;
            }
        }

        void ford_fulkerson(int source, int sink) {
            AugmentingPath augmented_path;
            int to, c = 0;
            while(find_augmenting_path(source, sink, augmented_path)) {
                c++;
                to = sink;
                for(size_t i = 1; i < augmented_path.path.size(); ++i) {
                    int from = augmented_path.path[i];
                    adjacency_matrix[from][to] -= augmented_path.max_flow;
                    adjacency_matrix[to][from] += augmented_path.max_flow;
                    to = from;
                }
                print();
                cout<<endl;
            }
        }

        bool find_augmenting_path(int source, int sink, AugmentingPath &augmented_path) {
            queue<int> q;
            q.push(source);

            int parent_pointers[nodes];
            bool visited[nodes];

            for(int i = 0; i < nodes; i++) {
                parent_pointers[i] = -1;
                visited[i] = false;
            }

            visited[source] = true;

            do {
                int current = q.front();
                q.pop();
                for(int i = 0; i < nodes; i++) {
                    if(adjacency_matrix[current][i] > 0 && !visited[i]) {
                        q.push(i);
                        visited[i] = true;
                        parent_pointers[i] = current;
                    }
                }
            } while(!q.empty() && visited[sink] != true);
            
            if(visited[sink] == true) {
                augmented_path = compute_augmented_path(sink, parent_pointers);
                return true;
            } else {
                return false;
            }
        }

        void print() {
            for(int i = 0; i < nodes; ++i) {
                for(int j = 0; j < nodes; ++j) {
                    cout<<adjacency_matrix[i][j]<<"  ";
                }
                cout<<endl;
            }
        }

    private:
        int **adjacency_matrix, nodes, edges;

        void initialize_adjacency_matrix() {
            if(nodes) {
                adjacency_matrix = new int* [nodes];
                for(int i = 0; i < nodes; i++) {
                    adjacency_matrix[i] = new int[nodes];
                    for(int j = 0; j < nodes; ++j) {
                        adjacency_matrix[i][j] = 0;
                    }
                }
            } else {
                adjacency_matrix = nullptr;
            }
        }

        void deallocate_adjacency_matrix() {
            for(int i = 0; i < nodes; i++) {
                delete [] adjacency_matrix[i];
            }
            delete [] adjacency_matrix;
        }

        void copy_adjacency_matrix(const Graph &other) {
            adjacency_matrix = new int* [nodes];
            for(int i = 0; i < nodes; ++i) {
                adjacency_matrix[i] = new int[nodes];
                copy(other.adjacency_matrix[i], other.adjacency_matrix[i] + nodes, adjacency_matrix[i]);
            }
        }

        AugmentingPath compute_augmented_path(int sink, int* parent_pointers) {
                int flow = adjacency_matrix[parent_pointers[sink]][sink],
                    current = sink;
                vector<int> augmenting_path = {current};

                while(parent_pointers[current] != -1) {
                    flow = min(flow, adjacency_matrix[parent_pointers[current]][current]);
                    current = parent_pointers[current];
                    augmenting_path.push_back(current);
                }
                
                return {augmenting_path, flow};
        }


};

int main() {
    Graph g(6, 10);
    g.read_graph();
    g.print();
    g.ford_fulkerson(0, 5);
    g.print();
    return 0;
}
