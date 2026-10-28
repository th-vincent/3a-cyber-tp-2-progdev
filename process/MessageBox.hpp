/*
 * CentraleSupélec - Campus de Paris-Saclay
 * Cursus Ingénieur généraliste - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP
 * Dominique Marcadet - 2026 - CC BY-SA
 *
 * MessageBox.hpp
 */

#pragma once

#include <array>
#include <algorithm>

#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>

#include "../BasicMessageBox.hpp"

/*
 * FIFO d'echange de messages entre producteurs et consommateurs
 * Version pour synchronisation entre processus
 */
class MessageBox : public BasicMessageBox {
public:
    void put( int message ) {

        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(mutex_);
 
        while (count_ >= box_size_) {
            not_full_.wait(lock);   // Forme adaptée à la librairie boost
        }

        basic_put(message);
        ++count_;
  
        not_empty_.notify_one();   // On reveille l'autre thread (il y en un qu'un autre)
    }
 
    int get() {
        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(mutex_);

    
        while (count_ == 0) {
        not_empty_.wait(lock);   // Forme adaptée àn la librairie boost
        }

        int message = basic_get();
        --count_;

        not_full_.notify_one();   // On reveille l'autre thread (il y en un qu'un autre)

        return message;
        }
private:
    boost::interprocess::interprocess_mutex mutex_; // On ajoute un mutex pour la synchronisation
    boost::interprocess::interprocess_condition not_empty_;
    boost::interprocess::interprocess_condition not_full_;
    unsigned count_ = 0;  // Compteur de message disponibles
};
 
