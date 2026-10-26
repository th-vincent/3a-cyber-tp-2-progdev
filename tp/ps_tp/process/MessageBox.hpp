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
        // TODO : ajouter les mecanismes de synchronisation
        basic_put( message );
    }
 
    int get() {
        // TODO : ajouter les mecanismes de synchronisation
        int message{ basic_get() };
        return message;
    }
private:
    // TODO : ajouter les objets de synchronisation
};
 
