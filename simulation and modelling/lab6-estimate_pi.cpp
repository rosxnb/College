#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <chrono>
#include <vector>

template <typename T>
std::ofstream& operator << (std::ofstream& of, const std::vector<std::pair<T, T>>& points)
{
    of.setf(std::ios::left, std::ios::adjustfield);
    of << std::setw(15) << 'x' << std::setw(15) << 'y' << "\n";
    for (auto [x, y]: points)
        of << std::setw(15) << x << std::setw(15) << y << "\n";
    return of;
}

float rand_num()
{
    static auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::mt19937 generator(seed);
    static std::uniform_real_distribution<float> dist(-1.f, 1.f);
    return dist(generator);
}

// this function uses monte-carlo simulation to estimate value of pi
float estimate_pi()
{
    int N = 1'000'000;
    std::vector<std::pair<float, float>> square_coordinates;
    square_coordinates.reserve(N);

    // fill the slots with random numbers
    for (int i = 0; i < N; ++i)
        square_coordinates.emplace_back(rand_num(), rand_num());
    
    // record generated points in the file
    std::ofstream of("points.txt", std::ofstream::out);

        of << square_coordinates;
        std::cout << "points are stored in the external file \n";

        // count number of points in circle
        unsigned circle_points = std::accumulate(
                                    square_coordinates.begin(), square_coordinates.end(), 0U,
                                    [] (unsigned count, std::pair<float, float> point) { 
                                        auto [x, y] = point;
                                        auto r = x*x + y*y;
                                        if (r < 1) return count += 1;
                                        return count;
                                    });

        float prob = static_cast<float>(circle_points) / square_coordinates.size();

    of.close();
    return 4.f * prob;
}

int main()
{
    float pi = estimate_pi();
    std::cout << "\n Estimated value of pi = " << pi << std::endl;

    return 0;
}
