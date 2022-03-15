#ifndef NEGATIVE_SIZE_ERROR_H
#define NEGATIVE_SIZE_ERROR_H
#include <stdexcept>
/**
 * @brief Classe Eccezione
 * 
 * La classe implementa un'eccezione a run time in
 * caso di indice negativo
 * 
 */
class negative_size_error : public std::runtime_error {
	
	public:
		/**
		 * @brief Costruttore 
		 * 
		 * @param message stringa contenente il messaggio
		 */
		negative_size_error(const std::string &message);

};

#endif