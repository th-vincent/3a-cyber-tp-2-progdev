/*
 * CentraleSupélec - Campus de Paris-Saclay
 * Cursus Ingénieur généraliste - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP
 * Dominique Marcadet - 2026 - CC BY-SA
 *
 * osyncstream.hpp
 */

#pragma once

/*******************************************************************

    VOUS N'AVEZ PAS BESOIN DE MODIFIER CE FICHIER

********************************************************************/

#include <boost/config.hpp>

#ifndef BOOST_NO_CXX20_HDR_SYNCSTREAM

#include <syncstream>

using std::osyncstream;

#else

/*
 * Classe permettant d'assurer la sérialisation des affichages
 * Version simplifiée de la classe de même nom de la bibliothèque standard C++20
 *
 * Exemple d'utilisation
 *   { osyncstream( std::cout ) << "hello world\n"; }
 */
 
#include <iostream>
#include <sstream>
#include <mutex>

namespace internal {

class osyncstream {
public:
    osyncstream( std::ostream & out ) : out_( out ) {}
    // L'affichage se fait uniquement à la destruction de l'objet
    ~osyncstream() { 
        std::lock_guard< std::mutex > l( protect_out_ );
        out_ << saved_.str();
    }
    
    // Mémorisation de ce qu'il faut afficher
    osyncstream & operator<<( const std::string & what ) {
        saved_ << what;
        return *this;
    }
    osyncstream & operator<<( const char * what ) {
        saved_ << what;
        return *this;
    }
    osyncstream & operator<<( int what ) {
        saved_ << what;
        return *this;
    }
private:
    static BOOST_INLINE_VARIABLE std::mutex protect_out_;

    std::ostream & out_;
    std::ostringstream saved_;
};

#ifdef BOOST_NO_CXX17_INLINE_VARIABLES
std::mutex osyncstream::protect_out_;
#endif

}

using internal::osyncstream;

#endif

