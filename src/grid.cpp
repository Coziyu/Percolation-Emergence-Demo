#include "grid.hpp"
#include "logging.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <random>
#include <utility>

#define MIN_RNG_VAL 0
#define MAX_RNG_VAL 100000

void PercoGrid::initialize_grid_values() {
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(MIN_RNG_VAL, MAX_RNG_VAL);

    log_info("Setting grid rng values with range: ", MIN_RNG_VAL, MAX_RNG_VAL);

    for(int i = 0; i < get_grid_count(); i++){
        cell_value.push_back(distrib(gen));
    }
}

int PercoGrid::get_grid_count() {
    return nCols * nRows; 
}

PercoGrid::PercoGrid(const int &cWidth, const int &cHeight, sf::RenderWindow *window): 
    rWindow{window}, 
    cellWidth{cWidth},
    cellHeight{cHeight},
    nRows(window->getSize().x / cellWidth),
    nCols(window->getSize().y / cellHeight),
    activation_threshold{MAX_RNG_VAL + 1}
{    
    log_info("Reserving memory for ", nRows * nCols, "cells");

    grid.reserve(nRows * nCols);
    cell_value.reserve(nRows * nCols);

    initialize_grid_values();
    initialize_grid();
};

void PercoGrid::initialize_grid(){
    log_info("Initializing grid");
    

    for(int index = 0; index < get_grid_count(); index++){
        sf::RectangleShape new_rect(sf::Vector2f(cellWidth, cellHeight));
        
        int x_offset = index % nCols;
        int y_offset = index / nCols;
        new_rect.setPosition(cellWidth * x_offset, cellHeight * y_offset);

        new_rect.setOutlineThickness(1.0f);

        // If on the left border:
        if (x_offset == 0){
            connected_cluster.insert(index);
            new_rect.setFillColor(get_cell_color_by_state(CellStates::connected));
        }
        else{
            unactivated_indices.push_back(index);
            new_rect.setFillColor(get_cell_color_by_state(CellStates::unactivated));
        }

        grid.push_back(new_rect);
    }
}


void PercoGrid::draw_grid(){
    for(sf::RectangleShape &cell : grid){
        rWindow->draw(cell);
    }
}

void PercoGrid::update_grid(){
    /* TODO: Implement Update Grid
     - Iterate through unactivated cells: 
     - - Activate them if cell surpass the threshold
     - - Add cell to exisiting or new cluster
     - - Untag cell as unactivated
     - - Check if newly activated cell is adjacent to connected cell
     - - - If connected, connect every cell in the cluster
    */
    //TODO: Parallelize

    std::vector<int> activated_indices;

    for(auto index : unactivated_indices){
        // Activate cells
        if (cell_value[index] <= activation_threshold){
            activated_indices.push_back(index);
        }
    }

    for (auto index : activated_indices){
        unactivated_indices.remove(index);
    }
}

sf::Color PercoGrid::get_cell_color_by_state(CellStates state){
    switch (state){
    case unactivated:
        return sf::Color(0, 128, 255);
        break;
    case activated:
        return sf::Color(192, 192, 48);
        break;
    case connected:
        return sf::Color(255, 255, 0);
        break;
    }
};

PercoGrid::CellStates PercoGrid::get_cell_state_by_index(const int &index){
    if (is_connected(index))
    {
        return CellStates::connected;
    }
    
    else if (is_unactivated(index)){
        return CellStates::activated;
    }

    else {
        return CellStates::unactivated;
    }
};

bool PercoGrid::is_connected(const int &index){
    auto it = std::find(connected_cluster.begin(), connected_cluster.end(), index);
    return (it != connected_cluster.end()) || ((index % nCols) == 0);
}

bool PercoGrid::is_unactivated(const int &index){
    return cell_value[index] > activation_threshold;
}

std::list<int> PercoGrid::get_cell_neighbours(const int &index){
    std::list<int> neighbours;

    int row = index / nCols;
    int col = index % nCols;

    // Top neighbor
    if (row > 0) {
        int topIndex = (row - 1) * nCols + col;
        neighbours.push_back(topIndex);
    }

    // Bottom neighbor
    if (row < nRows - 1) {
        int bottomIndex = (row + 1) * nCols + col;
        neighbours.push_back(bottomIndex);
    }

    // Left neighbor
    if (col > 0) {
        int leftIndex = row * nCols + (col - 1);
        neighbours.push_back(leftIndex);
    }

    // Right neighbor
    if (col < nCols - 1) {
        int rightIndex = row * nCols + (col + 1);
        neighbours.push_back(rightIndex);
    }

    return neighbours;
}