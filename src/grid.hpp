#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <set>
#include <vector>
#include <random>
#include <list>

class PercoGrid {
private:

    enum CellStates {
        unactivated,
        activated,
        connected
    };

    std::vector<sf::RectangleShape> grid;
    std::vector<float> cell_value;
    sf::RenderWindow *rWindow;

    int cellWidth;
    int cellHeight;

    int nRows;
    int nCols;

    // 0 to 100001
    // Cells with lower value than the threshold gets activated
    int activation_threshold;

    //TODO: Feature: Reverse the activations lol
    // - Should be doable by simply keeping track of activated_indices and unactivated clusters.
    // - Implicitly requires a forward pass first I reckon
    std::list<int> unactivated_indices;
    std::list<std::set<int>> activated_clusters;
    std::set<int> connected_cluster;

    void initialize_grid_values();
    void initialize_grid();
    int get_grid_count();

    sf::Color get_cell_color_by_state(CellStates state);

    std::list<int> get_cell_neighbours(const int &index);

    
public:
    PercoGrid(){};
    PercoGrid(const int &rows, const int &cols, sf::RenderWindow *window);

    PercoGrid::CellStates get_cell_state_by_index(const int &index);

    bool is_connected(const int &index);

    bool is_unactivated(const int &index);

    void draw_grid();

    void update_grid();
};

#endif // GRID_HPP
