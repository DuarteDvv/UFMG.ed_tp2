

bool dijkistra_matrix(Adjacency_Matrix &adj_matrix, double energy, int portals)
{
    if (adj_matrix.numberOfV <= 1)
        return true;

    ModMinHeap pq(adj_matrix.numberOfV);

    double dist[adj_matrix.numberOfV];
    bool visited[adj_matrix.numberOfV];

    for (int i = 0; i < adj_matrix.numberOfV; ++i)
    {
        dist[i] = infinity;
        visited[i] = false;
    }

    dist[0] = 0;
    pq.enqueue({{0, 0.0}, 0});

    while (!pq.isEmpty())
    {
        int u = pq.getMin_without_remove().getFirst().getFirst();
        int used_portals = pq.getMin_without_remove().getSecond();
        pq.dequeue();

        // cout << " -> " << u << " " << used_portals << std::endl;

        if (u == adj_matrix.numberOfV - 1)
        {
            if (dist[u] > energy)
                return false;

            return true;
        }

        if (visited[u])
            continue;

        visited[u] = true;

        for (int i = 0; i < adj_matrix.numberOfV; i++)
        {
            if (adj_matrix.matrix[u][i] >= 0)
            {
                int v = i;

                double weight = adj_matrix.matrix[u][i];

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
    }

    return false;
}
