#include <iostream>
#include <vector>
#include <iomanip>
template <typename T>
using vector = std::vector<T>;

class Solution {
public:
    Solution()
    : max(0)
    , answer(8, vector<bool>(8, false))
    , board(8, vector<int>(8)) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++)
                std::cin >> board[i][j];
        }
    }

	int solveNQueens() {
        solve(0);
		return max;
	}

private:
    int max;
    vector<vector<bool>> answer;
    vector<vector<int>> board;

	void solve(int col) {
		if (col == 8) {
            int value = 0;
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (answer[i][j] == true) value += board[i][j];
                }
            }
            if (value > max) max = value;
			return;
		}

		for (int i = 0; i < 8; i++) {
			if (is_legal_placement(i, col)) {
				answer[i][col] = true;
				solve(col + 1);
				answer[i][col] = false;
			}
		}
	}

	bool is_legal_placement(int row, int col) {
		// check row
		for (int i = 0; i < 8; i++) {
			if (answer[row][i] == true)
				return false;
		}

		// check 315 degree diagonal
		for (int i = row + 1, j = col - 1; i < 8 && j >= 0; i++, j--) {
			if (answer[i][j] == true)
				return false;
		}

		// check 135 degree diagonal
		for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
			if (answer[i][j] == true)
				return false;
		}

		return true;
	}
};

int main(void)
{
    int n;
    std::cin >> n;

    while (n--) {
        Solution sol;
        std::cout << std::setw(5) << sol.solveNQueens() << '\n';
    }

    return 0;
}