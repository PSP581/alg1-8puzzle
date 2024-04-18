#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;

// hrací pole
struct State {
    vector<vector<int>> board;
    int empty_row, empty_col;
};

// kontrola platnosti vstupu
bool isValid(int row, int col, int n) {
    return (row >= 0 && row < n && col >= 0 && col < n);
}

// následující stav
vector<State> getSuccessors(const State& state) {
    vector<State> successors;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; ++i) {
        int new_row = state.empty_row + dr[i];
        int new_col = state.empty_col + dc[i];
        if (isValid(new_row, new_col, state.board.size())) {
            State successor = state;
            swap(successor.board[state.empty_row][state.empty_col], successor.board[new_row][new_col]);
            successor.empty_row = new_row;
            successor.empty_col = new_col;
            successors.push_back(successor);
        }
    }
    return successors;
}

// Funkce pro ověření jestli je stav cílový
bool isGoal(const State& state) {
    int n = state.board.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (state.board[i][j] != i * n + j) {
                return false;
            }
        }
    }
    return true;
}


// Funkce pro prohledávání do hloubky
bool dfs(const State& start) {
    stack<State> s;
    unordered_set<string> visited;

    s.push(start);
    visited.insert(to_string(start.empty_row) + "," + to_string(start.empty_col));

    while (!s.empty()) {
        State current = s.top();
        s.pop();

        cout << "Prochazim stav: " << endl;
        for (const auto& row : current.board) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << endl;
        }

        if (isGoal(current)) {
            return true;
        }

        vector<State> successors = getSuccessors(current);
        for (const auto& successor : successors) {
            string key = to_string(successor.empty_row) + "," + to_string(successor.empty_col);
            if (visited.find(key) == visited.end()) {
                s.push(successor);
                visited.insert(key);
            }
        }
    }


    return false;
}


int main() {
    // vstup
    vector<vector<int>> initial_board = {
        {1, 2, 0},
        {3, 4, 5},
        {6, 7, 8} 
    };

    State start;
    start.board = initial_board;

    // Start z prázdného místa
    for (int i = 0; i < initial_board.size(); ++i) {
        for (int j = 0; j < initial_board.size(); ++j) {
            if (initial_board[i][j] == 0) {
                start.empty_row = i;
                start.empty_col = j;
            }
        }
    }

    if (dfs(start)) {
        cout << "Cilova konfigurace je dosazitelna." << endl;
    } else {
        cout << "Cilova konfigurace neni dosazitelna." << endl;
    }

    return 0;
}
