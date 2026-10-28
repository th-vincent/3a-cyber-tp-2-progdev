/*
 * CentraleSupélec - Campus de Paris-Saclay
 * Cursus Ingénieur généraliste - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP
 * Dominique Marcadet - 2026 - CC BY-SA
 *
 * Consumer.hpp
 */

#pragma once

#include <iostream>
#include <thread>

#include "../ProdOrCons.hpp"
 
#include "osyncstream.hpp"
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
                osyncstream(std::cerr) << "Erreur : message negatif extrait\n";
            }

            osyncstream(std::cout) << message << "\n";

            
        }
    }
};

