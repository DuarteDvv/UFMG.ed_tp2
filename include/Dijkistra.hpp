

bool dijkistra(Adjacency_List &adj_list, double energy, int portals)
{

    if (adj_list.numberOfV <= 1)
        return true;

    ModMinHeap pq(adj_list.numberOfV);

    double dist[adj_list.numberOfV];
    bool visited[adj_list.numberOfV];

    for (int i = 0; i < adj_list.numberOfV; ++i)
    {
        dist[i] = infinity;
        visited[i] = false;
    }

    dist[0] = 0;
    pq.enqueue({{0, 0.0}, 0}); // usado para chamar o proximo vertex e manter a distancia acumulada

    while (!pq.isEmpty())
    {
        int u = pq.getMin_without_remove().getFirst().getFirst();
        int used_portals = pq.getMin_without_remove().getSecond();
        pq.dequeue();

        // cout << " -> " << u << std::endl;

        if (u == adj_list.numberOfV - 1)
        {
            if (dist[u] > energy)
                return false;

            return true;
        }

        if (visited[u])
            continue;

        visited[u] = true;

        for (int i = 0; i < adj_list.adj_list[u].getSize(); i++)
        {

            int v = adj_list.adj_list[u].getObject(i).getFirst(); // retira da lista de adjacencia os vizinhos

            double weight = adj_list.adj_list[u].getObject(i).getSecond(); // retira da lista de adjacencia o peso

            // cout << weight << " " << v << std::endl;

            if (dist[u] + weight < dist[v])
            {
                if (weight == 0)
                {
                    if (used_portals + 1 > portals)
                        continue;

                    dist[v] = dist[u] + weight;
                    pq.enqueue({{v, dist[v]}, used_portals + 1});
                }
                else
                { // c.c mantem a mesma quantidade
                    dist[v] = dist[u] + weight;
                    pq.enqueue({{v, dist[v]}, used_portals});
                }
            }
        }
    }

    return false;
}