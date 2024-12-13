
class GraphNode {
public:
    std::mutex mtx;
    std::vector<GraphNode*> neighbors;
};

void work_on_node(GraphNode* node) {
    for (GraphNode* neighbor : node->neighbors) {
        // Lock neighbors in the order they appear
        std::lock_guard<std::mutex> lock(neighbor->mtx);
        // Perform work...
    }
}

void complex_function(std::mutex& mtx1, std::optional<std::mutex>& mtx2) {
    std::lock_guard<std::mutex> lock1(mtx1);

    if (mtx2) {
        std::lock_guard<std::mutex> lock2(*mtx2);
        // Perform work needing both locks
    } else {
        // Perform work needing only mtx1
    }

    // Perform additional work that needs only mtx1
}

