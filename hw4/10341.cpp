#include <iostream>
#include <cmath>
#include <iomanip>

int main(void)
{
    int p, q, r, s, t, u;
    static const auto f = [&](double x) -> double {
        return p*std::exp(-x) + q*std::sin(x) + r*std::cos(x)
             + s*std::tan(x) + t*x*x + u;
    };

    while (std::cin >> p >> q >> r >> s >> t >> u) {
        double ans = 0.5, prev = 1., temp;
        
        for (int i = 0; i < 200; i++) {
            if (f(ans) > 0) {
                temp = prev;
                prev = ans;
                ans += std::abs(prev - temp) / 2.;
            } else {
                temp = prev;
                prev = ans;
                ans -= std::abs(prev - temp) / 2.;
            }
        }

        if (std::abs(f(ans) - 0.) > 1e-10)
            std::cout << "No solution\n";
        else
            std::cout << std::fixed << std::setprecision(4)
                      << ans << '\n'; 
    }

    return 0;
}