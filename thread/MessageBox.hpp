/*
 * CentraleSupélec - Campus de Paris-Saclay
 * Cursus Ingénieur généraliste - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP
 * Dominique Marcadet - 2026 - CC BY-SA
 *
 * MessageBox.hpp
 */

#pragma once

#include <mutex>
#include <condition_variable>

#include "../BasicMessageBox.hpp"

/*
 * FIFO d'echange de messages entre producteurs et consommateurs
 * Version pour synchronisation entre threads
 */
class MessageBox : public BasicMessageBox {
public:
    void put( int message ) {

        std::unique_lock<std::mutex> lock(mutex_);
 
        not_full_.wait(lock, [this]() {
        return count_ < box_size_;    // On regarde s'il reste de la place, sinon, on attend
        });

        basic_put(message);
        ++count_;
  
        not_empty_.notify_one();   // On reveille l'autre thread (il y en un qu'un autre)
    }
 
    int get() {
        std::unique_lock<std::mutex> lock(mutex_);

    
        not_empty_.wait(lock, [this]() {
        return count_ > 0;   // On regarde si la boite contient un message, sinon, on attend
        });

        int message = basic_get();
        --count_;

        not_full_.notify_one();   // On reveille l'autre thread (il y en un qu'un autre)

        return message;
        }
private:
    std::mutex mutex_; // On ajoute un mutex pour la synchronisation
    std::condition_variable not_empty_;
    std::condition_variable not_full_;
    unsigned count_ = 0;  // Compteur de message disponibles
};
 
