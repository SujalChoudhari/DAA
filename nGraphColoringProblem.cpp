#include <iostream>

enum Color {
    NONE, RED, GREEN, BLUE, BROWN
};

int graph_matrix[5][5] = { // 0 = there is an edge between nodes, 1 = there is no edge
    {0, 1, 0, 1, 0},
    {1, 0, 0, 0, 1},
    {0, 1, 0, 0, 0},
    {1, 0, 0, 0, 1},
    {0, 0, 0, 0, 0}
};

Color color[4] = { RED, GREEN, BLUE, BROWN };

bool colored[5] = { false };
Color colors_of_nodes[5] = { NONE };

bool is_safe_to_color(int node, Color selected_color) {
    // check if neighbors have same color or not.
    for (int i = 0; i < 5; i++) {
        if (graph_matrix[node][i] == 0) { // is neighbor
            if (colors_of_nodes[i] == selected_color) { // neighbor has same color
                return false;
            }
        }
    }
    return true;
}

void colour_nodes(int node) {
    // Base case: All nodes are colored
    if (node == 5) {
        for (int i = 0; i < 5; i++) {
            std::cout << colors_of_nodes[i] << " ";
        }
        std::cout << std::endl;
        return;
    }

    for (int j = 0; j < 4; j++) {
        if (is_safe_to_color(node, color[j])) {
            colors_of_nodes[node] = color[j];
            colored[node] = true;
            colour_nodes(node + 1);
            colors_of_nodes[node] = NONE; // Backtrack
            colored[node] = false;
        }
    }
}
//
//int main() {
//    colour_nodes(0);
//    return 0;
//}
