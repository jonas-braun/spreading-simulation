#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <vector>




using namespace std;


typedef unordered_multimap<int, int> Graph;
typedef unordered_map<int, int> List;



class FollowerGraph {
        int nnodes;
        int nedges;
        Graph followers;
        List degrees;
        Graph reverse_degrees;

    public:
        FollowerGraph (int, int);
        void save (string);
        vector<int> get_followers (int);

};

FollowerGraph::FollowerGraph (int nnodes_, int nedges_) {

    nnodes = nnodes_;
    nedges = nedges_;

    int x, y;
    int size;
    int break_condition;
    
    // init degrees list
    for (auto i = 0; i<nnodes; i++) {
        degrees.at(i) = 0;
    }
 
    // set random edges
    for (auto i=0; i<nedges; i++) {
        break_condition = 0;
        while (break_condition == 0) {
            x = rand() % nnodes;
            y = rand() % nnodes;

            if (x==y) continue;

            break_condition = 1;
            auto its = followers.equal_range(x);
            //size = distance(its.first, its.second);
            size = followers.count(x);
            cout << size << endl;
            for (auto it = its.first; it != its.second; it++) {
                if (it->second == y) break_condition = 0;
                break;
            }
        }

        followers.insert(Graph::value_type(x, y));
    } 
}

void FollowerGraph::save(string filename) {
    ofstream graph_file;
    graph_file.open(filename);
    
    for (auto it = followers.begin(); it != followers.end(); it++) {
        graph_file << it->first << ',' << it->second << endl;
    }

    graph_file.close();
}


vector<int> FollowerGraph::get_followers (int node) {

    vector<int> followers_;
    auto its = followers.equal_range(node);
    for (auto it = its.first; it != its.second; it++) {
        followers_.push_back(it->second);
    }
    return followers_;
}


int main(int argc, char **argv)
{
    
    srand(time(0));

    int nnodes;
    int nedges;


    nnodes = 10;
    nedges = 10;

    FollowerGraph graph (nnodes, nedges);

    graph.save("random.graph");

    bool infected[nnodes] = {false};
    //for (auto i=0; i<nnodes; i++) cout << infected[i] << endl;

    int origin = rand() % nnodes;
    infected[origin] = true;

    ofstream infected_file;
    infected_file.open("0.nodes");
    for (auto i=0; i<nnodes; i++) infected_file << infected[i] << endl;
    infected_file.close();

    // first infection step
    vector<int> followers = graph.get_followers(origin);

    for (auto it = followers.begin(); it != followers.end(); it++) {
        infected[*it] = true;
    }

    infected_file.open("1.nodes");
    for (auto i=0; i<nnodes; i++) infected_file << infected[i] << endl;
    infected_file.close();

    /*
    for (auto it = followers.begin(); it != followers.end(); it++) {
        cout << it->first << ' ' << it->second << endl;
    }

    auto its = followers.equal_range(4);
    for (auto it = its.first; it != its.second; it++) {
        cout << it->first << ' ' << it->second << endl;
    }
    */
}
