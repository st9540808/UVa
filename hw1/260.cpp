#include <iostream>
#include <unordered_set>

enum class pawn : char { white='w', black='b' };
std::istream& operator>>(std::istream& is, pawn& e) {
    char c;
    std::cin >> c;
    e = static_cast<pawn>(c);
    return is;
}
std::ostream& operator<<(std::ostream& os, pawn& e) {
    std::cout << static_cast<char>(e);
    return os;
}


int N;
pawn board[201][201];

bool dfs(int i, int j) // return if white wins
{
    // std::cout << "dfs(" << i << ", " << j << ")\n";
    static const struct { int i; int j; } move[] = {
        {-1, -1}, {-1, 0}, {0, -1}, {0, 1}, {1, 0}, {1, 1}
    };
    static const auto is_legal_move = [](int i, int j) {
        return (0 <= i && i < N) && (0 <= j && j < N) &&
                board[i][j] == pawn::white;
    };

    if (j == N - 1) return true;
    
    board[i][j] = pawn::black;
    for (const auto& m : move) {
        int newI = i + m.i, newJ = j + m.j;
        if (is_legal_move(newI, newJ) && dfs(newI, newJ))
            return true;
    }
    board[i][j] == pawn::white;
    return false;
}

int main(void)
{
    int count = 1;

    while (std::cin >> N && N != 0) {
        bool win = false;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                std::cin >> board[i][j];
        }
        
        for (int i = 0; i < N; i++) { // column
            if (board[i][0] == pawn::white && dfs(i, 0)) {
                win = true;
                break;
            }
        }
        
        std::cout << count++ << ' ' << (win ? 'W' : 'B') << '\n';
    }

    return 0;
}