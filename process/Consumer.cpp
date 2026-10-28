/*
 * CentraleSupélec - Campus de Paris-Saclay
 * Cursus Ingénieur généraliste - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP
 * Dominique Marcadet - 2026 - CC BY-SA
 *
 * Consumer.cpp
 * c++ -std=c++20 Consumer.cpp -o Consumer -lpthread -lrt
 */

#include <iostream>
#include <thread>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/named_semaphore.hpp>

#include "../Random.hpp"
#include "../ProdOrCons.hpp"

#include "MessageBox.hpp"

/*
 * Consommateur de messages
 */
class Consumer : public ProdOrCons< MessageBox > {
public:
    // Le constructeur de ProdOrCons sera utilisé comme constructeur de Consumer
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {

        for (int i = 0; i < nb_messages_;  ++i){
            int random = random_engine_();

            using milliseconds = std::chrono::duration< int, std::milli >;
            std::this_thread::sleep_for( milliseconds(random) );            // Attente avant le retrait

            int message = box_.get();     // On extrait message de la box

            if (message < 0){
                std::cerr << "Erreur : message negatif extrait\n";
            }

            std::cout << message << "\n";

            
        }
    }
};


int main()
{
    using namespace boost::interprocess;

    // On attend le signal du producer qui nous dit que la box est prête

    named_semaphore ready(
        open_only,
        "MessageBox ready"
    );

    ready.wait();
    
    // On ouvre la mémoire partagée
    shared_memory_object shm(
        open_only,
        "SharedMemory",
        read_write
    );

    mapped_region region(shm, read_write);

    // On récupère son address
    void* address = region.get_address();
    MessageBox* box_ = static_cast<MessageBox*>(address);  // On doit converitr le type de pointeur qu'on obtient

    // On crée le consumer et on le lance
    Random engine(100);
    Consumer consumer(2u, *box_, engine, 20);
    consumer();

    return 0;
}

