/*
    State Paramenter for Single Server Queueing Model of M/M/1.

    Symbols and meanings:
        p   -   server utilization
        λ   -   arrival rate
        µ   -   service rate
        L   -   average number of items in system
        W   -   average time an item spends in system
        Lq  -   average number of items in queue
        Wq  -   average time an item spends in queue

    Formulas were referenced from following website:
        https://web.pdx.edu/~stipakb/download/PA557/QueuingModelSingleServerFormulas.html
*/

#include <iostream>
#include <cmath>
using std::cout, std::endl, std::cin;

int main()
{
    double arrival_rate, service_rate, standard_deviation;
    cout << "Enter following data about the system: \n";
    cout << "Arrival Rate: "; cin >> arrival_rate;
    cout << "Service Rate: "; cin >> service_rate;

    double server_utilization {arrival_rate / service_rate};
    cout << "\n Server Utilization (p) = " << server_utilization;

    double avg_system_items
    {
        arrival_rate /
        (service_rate - arrival_rate)
    };
    cout << "\n Average Number of items in the system (L) = " << avg_system_items;

    double avg_queue_items 
    {
        pow(arrival_rate, 2) /
        (service_rate * (service_rate - arrival_rate))
    };
    cout << "\n Average Number of items in the queue (Lq) = " << avg_queue_items;

    double avg_system_time
    {
        1 / 
        (service_rate - arrival_rate)
    };
    cout << "\n Average time an item spends in the system (W) = " << avg_system_time;

    double avg_queue_time
    {
        arrival_rate /
        (service_rate * (service_rate - arrival_rate))
    };
    cout << "\n Average time an item spends in the queue (Wq) = " << avg_queue_time << endl;

    return 0;
}
