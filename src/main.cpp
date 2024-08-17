#include "ModMinHeap.hpp"
#include "AdjacencyMatrix.hpp"
#include "AdjacencyList.hpp"
#include "Pair.hpp"
#include "Dijkistra.hpp"
#include "Dijkistra_matrix.hpp"
#include "A_star.hpp"
#include "A_star_matrix.hpp"
#include "util.hpp"

#include "chrono"
#include "iomanip"

// 5 4 2 0 1 0 0 0 2 1 1 10 2 0 1 0 3 1 4 2 4 0 2 3 4 1 1
// 5 4 2 0 1 0 0 0 2 1 1 10 2 0 1 0 3 1 4 2 4 0 2 3 4 1 0
// 5 4 2 0 1 0 3 0 2 1 1 10 2 0 1 0 3 1 4 2 4 0 2 3 4 1 1
// 5 3 3 0 1 0 0 0 2 1 1 10 2 0 1 0 3 1 4 0 2 3 4 2 4 1 1
// 4 3 2 0 0 0 2 1 2 11 2 0 1 2 1 2 3 0 2 1 3 1 1

using namespace std::chrono;
using std::cin;
using std::endl;

// Lista é uma boa escolha pois a matriz é esparsa (muitos zeros ou poucas arestas)

int main()
{

    // n: Vertix (Clareira) m:Edges(Trilha) k:portals(Trilhas com custo 0)
    int n, m, k;
    cin >> n >> m >> k;

    Adjacency_List adj_list(n);
    Adjacency_Matrix adj_matrix(n);

    Pair<double, double> *cord_x_y = new Pair<double, double>[n];

    double x, y;

    for (int i = 0; i < n; i++)
    { // coordenada em R² de cada vértice

        cin >> x >> y;
        cord_x_y[i] = Pair<double, double>(x, y);
    }

    int u, v;

    for (int i = 0; i < m; i++)
    { // direção das arestas

        cin >> u >> v;

        adj_list.addEdge(u, v, euclid_dist(cord_x_y[u], cord_x_y[v]));
        adj_matrix.addEdge(u, v, euclid_dist(cord_x_y[u], cord_x_y[v]));
    }

    for (int i = 0; i < k; i++)
    { // direção dos portais

        cin >> u >> v;

        adj_list.addEdge(u, v, 0);
        adj_matrix.addEdge(u, v, 0);
    }

    // s:energy q:number of portals
    double s;
    int q;

    cin >> s >> q;

    // calculate heuristic for A*
    double heuristic[n];
    for (int i = 0; i < n; i++)
        heuristic[i] = euclid_dist(cord_x_y[i], cord_x_y[n - 1]);

    // Testes experimentais
    /*
    cout << std::fixed << std::setprecision(6);
    auto start = high_resolution_clock::now();
    cout << dijkistra(adj_list, s, q) << endl;
    auto end = high_resolution_clock::now();
    duration<double> duration = end - start;

    cout << duration.count() << ",";

    start = high_resolution_clock::now();
    cout << dijkistra_matrix(adj_matrix, s, q) << endl;
    end = high_resolution_clock::now();
    duration = end - start;

    cout << duration.count() << ",";

    start = high_resolution_clock::now();
    cout << A_star(adj_list, s, q, heuristic) << endl;
    end = high_resolution_clock::now();
    duration = end - start;

    cout << duration.count() << ",";

    start = high_resolution_clock::now();
    cout << A_star_matrix(adj_matrix, s, q, heuristic) << endl;
    end = high_resolution_clock::now();
    duration = end - start;

    cout << duration.count();

    */

    // Resultado para VPL

    cout << dijkistra(adj_list, s, q) << " " << A_star(adj_list, s, q, heuristic) << endl;

    return 0;
}
