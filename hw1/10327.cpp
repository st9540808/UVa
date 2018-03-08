#include <iostream>

int a[1000];

int main(void)
{
    int N;

    while (std::cin >> N) {
        int count = 0;
        
        for (int i = 0; i < N; i++)
            std::cin >> a[i];
  		
        for (int i = 0; i < N - 1; i++) {
            for (int j = i + 1; j < N; j++) {
                if (a[i] > a[j])
                    count++;
            }
        }
        
        std::cout << "Minimum exchange operations : " << count << "\n";
    }
}
