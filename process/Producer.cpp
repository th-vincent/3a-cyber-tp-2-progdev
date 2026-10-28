/*
 * CentraleSupélec - Campus de Paris-Saclay
 * Cursus Ingénieur généraliste - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP
 * Dominique Marcadet - 2026 - CC BY-SA
 *
 * Producer.cpp
 * c++ -std=c++20 Producer.cpp -o Producer -lpthread -lrt
 */

#include <iostream>
#include <thread>
#include <new>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/named_semaphore.hpp>

#include "../Random.hpp"
#include "../ProdOrCons.hpp"

#include "MessageBox.hpp"

/*
 * Producteur de messages
 */
class Producer : public ProdOrCons< MessageBox > {
public:
    // Le constructeur de ProdOrCons sera utilisé comme constructeur de Producer
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        for (int i = 0; i < nb_messages_;  ++i){
            int random = random_engine_();

            box_.put(i);     // On envoit i dans la box

            std::cout << i << "\n";   // Affichage standard

            using milliseconds = std::chrono::duration< int, std::milli >;
            std::this_thread::sleep_for( milliseconds(random) );
        }
    }
};


int main()
{
    using namespace boost::interprocess;

    // Création de la mémoire partagée
    shared_memory_object shm(
        create_only,
        "SharedMemory",
        read_write   // Autorise la lecture et l'ecriture
    );

    // Taille de l'espace qu'elle occupe
    shm.truncate(65536);

    mapped_region region(
        shm,
        read_write
    );

    void *address = region.get_address();  // On récupère l'adresse de la zone

    MessageBox* box_ = new (address) MessageBox();   // On construit une MessageBox à l'addresse address


    // On indique que la MessageBox est prête
    named_semaphore ready(
        open_or_create,
        "MessageBox ready",
        0
    );

    ready.post();


    // On crée le producer et on le lance
    Random engine(100);
    Producer producer(1u, *box_, engine, 20);
    producer();
    
    return 0;
}

