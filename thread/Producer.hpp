/*
 * CentraleSupélec - Campus de Paris-Saclay
 * Cursus Ingénieur généraliste - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP
 * Dominique Marcadet - 2026 - CC BY-SA
 *
 * Producer.hpp
 */

#pragma once

#include <iostream>
#include <thread>

#include "../ProdOrCons.hpp"
 
#include "osyncstream.hpp"
#include "MessageBox.hpp"

/*
 * Producteur de messages
 */
class Producer : public ProdOrCons< MessageBox > {
public:
    // Le constructeur de ProdOrCons peut être utilisé pour Producer
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {

        for (int i = 0; i < nb_messages_;  ++i){
            int random = random_engine_();

            box_.put(i);     // On envoit i dans la box

            osyncstream(std::cout) << i << "\n";

            using milliseconds = std::chrono::duration< int, std::milli >;
            std::this_thread::sleep_for( milliseconds(random) );
        }

    }
};
 
