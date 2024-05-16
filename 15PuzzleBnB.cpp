#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include <algorithm>

// 15 Puzzle using Branch and Bound


// Directions which a piece can move
enum Direction {
	LEFT, RIGHT, TOP, BOTTOM
};

// Encapsulates the state of the board
class Board {
public:
	std::vector<std::vector<int>> board; // 2d vector representing the board (tried with 1d failed)
	int current_blank_row = -1; // current position of the blank
	int current_blank_col = -1; // current position of the blank

	Board(std::vector<std::vector<int>> board) : board(board) {
		find_blank_position(); // take a look at the board and find the position of the blank
	}

	void find_blank_position() { // update the blank positions
		for (int i = 0; i < board.size(); ++i) {
			for (int j = 0; j < board[i].size(); ++j) {
				if (board[i][j] == 0) {
					current_blank_row = i;
					current_blank_col = j;
					return;
				}
			}
		}
	}

	// Win conditions
	// starting from top left it should be 1 and so on...
	bool check_win() {
		int num = 1;
		for (int i = 0; i < board.size(); ++i) {
			for (int j = 0; j < board[i].size(); ++j) {
				if (board[i][j] != num % (board.size() * board[0].size())) {
					return false;
				}
				++num;
			}
		}
		return true;
	}

	// get the count of not correct elements
	int g_hat() {
		int count = 0;
		int num = 1;
		for (int i = 0; i < board.size(); ++i) {
			for (int j = 0; j < board[i].size(); ++j) {
				if (board[i][j] != num % (board.size() * board[0].size())) {
					count++;
				}
				++num;
			}
		}
		return count;
	}

	// Checks if it is a legal move, it considers edge cases (pun intended).
	bool can_move(Direction dir) {
		switch (dir) {
		case LEFT:
			return current_blank_col > 0;
		case RIGHT:
			return current_blank_col < board[0].size() - 1;
		case TOP:
			return current_blank_row > 0;
		case BOTTOM:
			return current_blank_row < board.size() - 1;
		default:
			return false;
		}
	}

	// Move the hole 
	// Note it check if it can move, if yes moves the hole
	// if no does nothing
	void move_hole(Direction dir) {
		if (!can_move(dir)) {
			return;
		}

		switch (dir) {
		case LEFT:
			std::swap(board[current_blank_row][current_blank_col], board[current_blank_row][current_blank_col - 1]);
			--current_blank_col;
			break;
		case RIGHT:
			std::swap(board[current_blank_row][current_blank_col], board[current_blank_row][current_blank_col + 1]);
			++current_blank_col;
			break;
		case TOP:
			std::swap(board[current_blank_row][current_blank_col], board[current_blank_row - 1][current_blank_col]);
			--current_blank_row;
			break;
		case BOTTOM:
			std::swap(board[current_blank_row][current_blank_col], board[current_blank_row + 1][current_blank_col]);
			++current_blank_row;
			break;
		}

		// print new moved board:
		std::cout << "\nBoard:" << std::endl;
		for (int i = 0; i < board.size(); ++i) {
			for (int j = 0; j < board[i].size(); ++j) {
				std::cout << board[i][j] << "\t";
			}
			std::cout << std::endl;
		}
	}
};

// Tipical node required for branch and bound
struct Node {
	int cost; // stores cost required for selecting the low cost node.
	std::vector<Direction> moves; // stores the moves to get to this node
	std::shared_ptr<Board> board; // stores the state of the board
};


// Make new node of the given parent, considering the given direction
void make_new_node(std::shared_ptr<Node> parent, Direction dir, std::shared_ptr<std::vector<std::shared_ptr<Node>>> node_container) {
	if (parent->board->can_move(dir)) {
		std::shared_ptr<Node> child = std::make_shared<Node>(); // new child node
		child->board = std::make_shared<Board>(*parent->board); // copy the board
		child->board->move_hole(dir); // make changes on it
		child->cost = parent->cost + 1 + child->board->g_hat(); // get new cost
		child->moves = parent->moves; // copy the moves
		child->moves.push_back(dir); // add the move
		node_container->push_back(child); // and to the container
	}
}

// Explores the given node
// check if this is wining node
// if not explore it. i.e. find its children (in all 4 directions, if possible)
std::vector<Direction> explore_node(std::shared_ptr<Node> parent, std::shared_ptr<std::vector<std::shared_ptr<Node>>> node_container) {
	// win check
	if (parent->board->check_win()) {
		return parent->moves;
	}

	// remove the current as it is checked
	node_container->erase(std::remove(node_container->begin(), node_container->end(), parent), node_container->end());

	// add all the four (if possible) to the container
	make_new_node(parent, Direction::LEFT, node_container);
	make_new_node(parent, Direction::RIGHT, node_container);
	make_new_node(parent, Direction::TOP, node_container);
	make_new_node(parent, Direction::BOTTOM, node_container);


	// sort w.r.t cost to get the min cost node.
	std::sort(node_container->begin(), node_container->end(),
		[](std::shared_ptr<Node> a, std::shared_ptr<Node> b) {return a->cost < b->cost; });

	// explore the min cost node.
	return explore_node(node_container->at(0), node_container);
}

std::shared_ptr<std::vector<Direction>> bnb_15_puzzle(std::vector<std::vector<int>> bd) {
	std::shared_ptr < std::vector<std::shared_ptr<Node>>> nodes = std::make_shared<std::vector<std::shared_ptr<Node>>>();

	Node initial = { 0, {}, std::make_shared<Board>(bd) };
	std::vector<Direction> moves = explore_node(std::make_shared<Node>(initial), nodes);

	return std::make_shared<std::vector<Direction>>(moves);
}

void run_15_puzzle_bnb() {
	std::vector<std::vector<int>> board = {
		{1, 2, 3, 4},
		{5, 6, 0, 8},
		{9, 10, 7, 11},
		{13, 14, 15, 12}
	};

	std::shared_ptr<std::vector<Direction>> result = bnb_15_puzzle(board);

	for (auto move : *result.get()) {
		std::cout << move << " ";
	}
	std::cout << std::endl;

}

//int main() {
//	run_15_puzzle_bnb();
//	return 0;
//}
