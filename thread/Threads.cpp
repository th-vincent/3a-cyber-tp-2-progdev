/*
 * CentraleSupélec - Campus de Paris-Saclay
 * Cursus Ingénieur généraliste - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP
 * Dominique Marcadet - 2026 - CC BY-SA
 *
 * Threads.cpp
 * c++ -std=c++20 Threads.cpp -o Threads -lpthread
 */

#include <iostream>
#include <thread>
#include <vector>
 
 
#include "../Random.hpp"

#include "osyncstream.hpp"
#include "Producer.hpp"
#include "Consumer.hpp"
#include "MessageBox.hpp"
 
/*
 * Test avec 1 producteur et 1 consommateur
 */
void one_producer_one_consumer() {
    // TODO :
    Random engine(100);
    MessageBox box;
    Producer producer(1u, box, engine, 20);  // 1u pour unsigned
    Consumer consumer(2u, box, engine, 20);

    std::thread producer_thread(std::ref(producer));  // On crée les threads qui executent les operateurs
    std::thread consumer_thread(std::ref(consumer));

    producer_thread.join();  // On attend la fin des threads avec .join()
    consumer_thread.join();
 
}

/*
 * Test avec plusieurs producteurs et consommateurs
 */
void several_producers_and_consumers() {
    
    MessageBox box;

    std::vector<std::thread> group;

    // On crée 6 générateurs aléatoires
    Random r1(100), r2(100), r3(100), r4(100), r5(100), r6(100);

    // 4 producteurs, 10 messages chacun
    group.push_back(std::thread{Producer{1u, box, r1, 10}});
    group.push_back(std::thread{Producer{2u, box, r2, 10}});
    group.push_back(std::thread{Producer{3u, box, r3, 10}});
    group.push_back(std::thread{Producer{4u, box, r4, 10}});

    // 2 consommateurs, 20 messages chacun
    group.push_back(std::thread{Consumer{5u, box, r5, 20}});
    group.push_back(std::thread{Consumer{6u, box, r6, 20}});

    // Attendre la fin de tous les threads
    for (std::thread &thread : group) {
        thread.join();
    }

}

int main() {
    //one_producer_one_consumer();
    several_producers_and_consumers();
    return 0;
}

