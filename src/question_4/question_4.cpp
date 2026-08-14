#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>


class Graph {
private:

    // a through j is enough for all graphs
    std::vector<std::vector<char>> adjacency;


    int index(char vertex) const {
        return vertex - 'a';
    }


public:

    Graph()
        : adjacency(10) {
    }


    // For graphs I, II and III
    void addUndirectedEdge(
        char a,
        char b
    ) {

        adjacency[index(a)]
            .push_back(b);

        adjacency[index(b)]
            .push_back(a);
    }


    // For directed graph IV
    void addDirectedEdge(
        char from,
        char to
    ) {

        adjacency[index(from)]
            .push_back(to);
    }


    // Use alphabetical neighbour order
    // so traversal result is predictable
    void sortAdjacency() {

        for (std::vector<char>& list
             : adjacency) {

            std::sort(
                list.begin(),
                list.end()
            );
        }
    }


    void printAdjacency(
        const std::vector<char>& vertices
    ) const {

        for (char v : vertices) {

            std::cout
                << v
                << ": ";

            for (char neighbour
                 : adjacency[index(v)]) {

                std::cout
                    << neighbour
                    << " ";
            }

            std::cout << "\n";
        }
    }


    // DFS using stack
    //
    // Push neighbours in reverse alphabetical order
    // because stack is LIFO, so smallest letter
    // ends up being popped first
    void DFS(char start) const {

        std::stack<char> s;

        std::vector<bool>
            visited(10, false);

        s.push(start);

        while (!s.empty()) {

            char current =
                s.top();

            s.pop();

            // Vertex may already have been placed
            // in stack from another path
            if (visited[index(current)]) {
                continue;
            }

            visited[index(current)] =
                true;

            // This is the pop/visit sequence
            std::cout
                << current
                << " ";

            const std::vector<char>& neighbours =
                adjacency[index(current)];

            // Reverse because stack is LIFO
            for (
                auto it = neighbours.rbegin();
                it != neighbours.rend();
                ++it
            ) {

                if (!visited[index(*it)]) {
                    s.push(*it);
                }
            }
        }

        std::cout << "\n";
    }


    // BFS uses queue
    // print each vertex when dequeued
    void BFS(char start) const {

        std::queue<char> q;

        std::vector<bool>
            visited(10, false);

        q.push(start);

        visited[index(start)] =
            true;

        while (!q.empty()) {

            char current =
                q.front();

            q.pop();

            std::cout
                << current
                << " ";

            for (
                char neighbour
                : adjacency[index(current)]
            ) {

                if (!visited[index(neighbour)]) {

                    visited[index(neighbour)] =
                        true;

                    q.push(neighbour);
                }
            }
        }

        std::cout << "\n";
    }
};


// Helper so same output is produced for each graph
void runGraph(
    const std::string& name,
    Graph& graph,
    const std::vector<char>& vertices
) {

    graph.sortAdjacency();

    std::cout
        << "\nGraph "
        << name
        << " adjacency lists:\n";

    graph.printAdjacency(vertices);

    std::cout
        << "DFS pop sequence from a: ";

    graph.DFS('a');

    std::cout
        << "BFS dequeue sequence from a: ";

    graph.BFS('a');
}


int main() {


    // ==================================================
    // GRAPH I
    // ==================================================

    Graph g1;


    // Inner component
    g1.addUndirectedEdge('a', 'c');
    g1.addUndirectedEdge('a', 'd');
    g1.addUndirectedEdge('a', 'e');

    g1.addUndirectedEdge('c', 'd');
    g1.addUndirectedEdge('c', 'f');

    g1.addUndirectedEdge('f', 'e');
    g1.addUndirectedEdge('f', 'b');

    g1.addUndirectedEdge('e', 'b');


    // Outer rectangle is separate connected component
    g1.addUndirectedEdge('g', 'h');
    g1.addUndirectedEdge('h', 'i');
    g1.addUndirectedEdge('i', 'j');
    g1.addUndirectedEdge('j', 'g');


    runGraph(
        "I",
        g1,
        {
            'a', 'b', 'c', 'd', 'e',
            'f', 'g', 'h', 'i', 'j'
        }
    );



    // ==================================================
    // GRAPH II
    // ==================================================

    Graph g2;


    // Top row
    g2.addUndirectedEdge('a', 'b');
    g2.addUndirectedEdge('b', 'c');
    g2.addUndirectedEdge('c', 'd');


    // Bottom row
    g2.addUndirectedEdge('e', 'f');
    g2.addUndirectedEdge('f', 'g');
    g2.addUndirectedEdge('g', 'h');


    // Vertical connections
    g2.addUndirectedEdge('a', 'e');
    g2.addUndirectedEdge('b', 'f');
    g2.addUndirectedEdge('c', 'g');
    g2.addUndirectedEdge('d', 'h');


    runGraph(
        "II",
        g2,
        {
            'a', 'b', 'c', 'd',
            'e', 'f', 'g', 'h'
        }
    );



    // ==================================================
    // GRAPH III
    // ==================================================

    Graph g3;


    g3.addUndirectedEdge('f', 'b');
    g3.addUndirectedEdge('f', 'd');

    g3.addUndirectedEdge('b', 'd');
    g3.addUndirectedEdge('b', 'a');

    g3.addUndirectedEdge('d', 'a');

    g3.addUndirectedEdge('a', 'c');
    g3.addUndirectedEdge('c', 'g');

    g3.addUndirectedEdge('a', 'e');
    g3.addUndirectedEdge('e', 'g');


    runGraph(
        "III",
        g3,
        {
            'a', 'b', 'c', 'd',
            'e', 'f', 'g'
        }
    );



    // ==================================================
    // GRAPH IV
    // ==================================================

    // Graph IV is directed.
    //
    // Weights on diagram are not needed for DFS/BFS.
    // We only care which direction each arrow goes.

    Graph g4;


    // b -> a, weight 2
    g4.addDirectedEdge('b', 'a');

    // a -> c, weight 3
    g4.addDirectedEdge('a', 'c');

    // c -> b, weight 6
    g4.addDirectedEdge('c', 'b');

    // c -> d, weight 1
    g4.addDirectedEdge('c', 'd');

    // d -> a, weight 7
    g4.addDirectedEdge('d', 'a');


    runGraph(
        "IV",
        g4,
        {
            'a', 'b', 'c', 'd'
        }
    );


    return 0;
}
