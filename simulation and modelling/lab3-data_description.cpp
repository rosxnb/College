#include <algorithm>
#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>
#include <array>
#include <cmath>
#include <map>

using std::cout, std::cin, std::endl;
using namespace std::chrono;

int rand_mean()
{
    std::default_random_engine eng;
    std::uniform_int_distribution<int> dist(1, 35);
    return dist(eng);
}

float generate_rand()
{
    static int mean = rand_mean();
    static auto seed {steady_clock::now().time_since_epoch().count()};
    static std::mt19937 generator(static_cast<unsigned int>(seed));
    static std::poisson_distribution<int> dist(mean);

    return (float)dist(generator);
}

std::array<float, 1'000> sort_array(std::array<float, 1'000> arr)
{
    std::sort(arr.begin(), arr.end());
    return arr;
}

void descriptive_stats(const std::array<float, 1'000>& slots)
{
    // no of elements
    size_t count {static_cast<size_t>(slots.size())};

    // min, max values
    auto [min, max] {std::minmax_element(begin(slots), end(slots))};
    float minimum {*min};
    float maximum {*max};

    // mean value
    float total_sum = std::accumulate(slots.begin(), slots.end(),
                                 0.f, [] (float sum, float slot_val) { return sum += slot_val; });
    float mean = total_sum / count;
    
    // median value
    std::array<float, 1'000> sorted_slots = sort_array(slots);
    float median = sorted_slots[500];

    // standard deviation
    float total_sq_sum = std::accumulate(slots.begin(), slots.end(),
                                         0.f, [] (float sum_sq, float slot_val) { return sum_sq += (slot_val * slot_val); });
    float standard_deviation = sqrt( (total_sq_sum / count) - (mean * mean) );

    // print descriptive stats
    cout << "\n\t\t Descriptive Stats \n";
    cout << std::string(44, '-') << "\n";
    cout << '|' << std::setw(20) << "min" << std::setw(5) << '|' << std::setw(15) << minimum << std::setw(5) << "| \n";
    cout << '|' << std::setw(20) << "max" << std::setw(5) << '|' << std::setw(15) << maximum << std::setw(5) << "| \n";
    cout << '|' << std::setw(20) << "mean" << std::setw(5) << '|' << std::setw(15) << mean << std::setw(5) << "| \n";
    cout << '|' << std::setw(20) << "median" << std::setw(5) << '|' << std::setw(15) << median << std::setw(5) << "| \n";
    cout << '|' << std::setw(20) << "standard deviation" << std::setw(5) << '|' << std::setw(15) << standard_deviation << std::setw(5) << "| \n";
    cout << '|' << std::setw(20) << "count" << std::setw(5) << '|' << std::setw(15) << count << std::setw(5) << "| \n";
    cout << std::string(44, '-') << "\n";

    // calculate frequency table values 
    std::map<int, int> bins_fq;
    auto start = sorted_slots.begin();
    bins_fq[5]  = static_cast<int>(std::upper_bound(sorted_slots.begin(), sorted_slots.end(), 5.f) - start);
    bins_fq[10] = static_cast<int>(std::upper_bound(sorted_slots.begin(), sorted_slots.end(), 10.f) - start) - (bins_fq[5]);
    bins_fq[15] = static_cast<int>(std::upper_bound(sorted_slots.begin(), sorted_slots.end(), 15.f) - start) - (bins_fq[5] + bins_fq[10]);
    bins_fq[20] = static_cast<int>(std::upper_bound(sorted_slots.begin(), sorted_slots.end(), 20.f) - start) - (bins_fq[5] + bins_fq[10] + bins_fq[15]);
    bins_fq[25] = static_cast<int>(std::upper_bound(sorted_slots.begin(), sorted_slots.end(), 25.f) - start) - (bins_fq[5] + bins_fq[10] + bins_fq[15] + bins_fq[20]);
    bins_fq[30] = static_cast<int>(std::upper_bound(sorted_slots.begin(), sorted_slots.end(), 30.f) - start) - (bins_fq[5] + bins_fq[10] + bins_fq[15] + bins_fq[20] + bins_fq[25]);
    bins_fq[35] = static_cast<int>(std::upper_bound(sorted_slots.begin(), sorted_slots.end(), 35.f) - start) - (bins_fq[5] + bins_fq[10] + bins_fq[15] + bins_fq[20] + bins_fq[25] + bins_fq[30]);
    bins_fq[40] = static_cast<int>(std::upper_bound(sorted_slots.begin(), sorted_slots.end(), 40.f) - start) - (bins_fq[5] + bins_fq[10] + bins_fq[15] + bins_fq[20] + bins_fq[25] + bins_fq[30] + bins_fq[35]);
    bins_fq[45] = static_cast<int>(std::upper_bound(sorted_slots.begin(), sorted_slots.end(), 45.f) - start) - (bins_fq[5] + bins_fq[10] + bins_fq[15] + bins_fq[20] + bins_fq[25] + bins_fq[30] + bins_fq[35] + bins_fq[40]);
    bins_fq[50] = static_cast<int>(std::upper_bound(sorted_slots.begin(), sorted_slots.end(), 50.f) - start) - (bins_fq[5] + bins_fq[10] + bins_fq[15] + bins_fq[20] + bins_fq[25] + bins_fq[30] + bins_fq[35] + bins_fq[40] + bins_fq[45]);

    // print frequency-bins table
    cout << "\n\t\t Frequency Table \n";
    cout << std::string(29, '-') << "\n";
    cout << '|' << std::setw(10) << "Bins" << std::setw(5) << '|' << std::setw(10) << "Frequency" << std::setw(5) << "| \n";
    cout << std::string(29, '-') << "\n";
    for (auto [key, value]: bins_fq)
        cout << '|' << std::setw(10) << key << std::setw(5) << '|' << std::setw(10) << value << std::setw(5) << "| \n";
    cout << std::string(29, '-') << "\n";

    int fq_count {0};
    cout << "\n\t\t Histogram Chart \n";
    for (auto [key, value]: bins_fq)
    {
        auto dots = (value > 10) ? value / 10 : value ? 1 : 0;
        cout << std::setw(5) << key << std::setw(3) << " | " << std::string(static_cast<unsigned int>(dots), '*') << "\n";
        fq_count += value;
    }
}

int main()
{
    std::array<float, 1'000> slots;
    // fill the slots with random value
    for (float& slot: slots)
        slot = generate_rand();

    descriptive_stats(slots);

    return 0;
}
