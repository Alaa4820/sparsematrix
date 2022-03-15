#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include <algorithm>
#include <iostream>
#include <ostream>
#include <cassert> 
#include <iterator> // std::forward_iterator_tag
#include <cstddef>  // std::ptrdiff_t
#include "negative_size_error.h"
/**
 * @brief Classe sparsematrix
 * 
 * La classe implementa una generica matrice di elementi sparsi nella memoria.
 * 
 * @tparam T 
 */
template<typename T> class sparsematrix{
    public:
        typedef unsigned int index_t;///< tipo che indica un indice 
        typedef unsigned int size_t;///< tipo che indica una dimensione
    
    private:
        /**
         * @brief Struttura element
         * 
         * Struttura dati element interna che viene usata dalla classe per creare un
         * nodo 
         */
        struct element{
            index_t row; ///< indice della riga in cui si trova l'elemento
            index_t column;///< indice della colonna in cui si trova l'elemento
            T value; ///< valore da memorizzare

            /**
             * @brief Costruisce un oggetto element senza dati
             */
            element(){}
            
            /**
             * Costruttore secondario
             * @brief Costruisce un oggetto element a partire dai parametri passati
             * 
             * @param row indice della riga 
             * @param column indice della colonna
             * @param value valore da memorizzare
             * 
             * @post this->row == row
             * @post this->column == column
             * @post this->value == value
             */
            element(index_t row, index_t column, const T &value): row(row), column(column), value(value){}
            
            /**
             * Copy constructor
             * @brief Costruisce un oggetto element a partire da un altro element copiando i dati membro a membro
             * 
             * @param other oggetto element da copiare
             */
            element(const element &other){
                if(this != &other){
                    row=other.row;
                    column=other.column;
                    value=other.value;
                }
            }
            /**
             * Operatore assegnamento
             * @brief Assegna ad un oggetto element un altro element copiando i dati membro a membro
             * 
             * @param other oggetto element da copiare
             * @return reference all'element this
             */
            element& operator=(const element &other){
                if(this != &other){
                    row=other.row;
                    column=other.column;
                    value=other.value;
                }
                return *this;
            }
            /**
             * Distruttore
             */
            ~element(){}


            /**
             * Funzione che implementa l'operatore di stream.
             * La funzione è friend perchè accede ai dati privati di element.
             * 
             * @param os stream di output
             * @param element oggetto element da spedire sullo stream
             * @return reference dello stream di output
             */
            friend std::ostream& operator<<(std::ostream &os, const element& element){
                return os<<element.value;
            }   
        };

        /**
         * @brief Struttura nodo
         * 
         * Struttura dati nodo interna che viene usata per creare la lista
         * che identifica la sparse matrix
         */
        struct nodo{
            element *e;///< puntatore all'oggetto element
            nodo *next; ///< puntatore al nodo successivo della lista

            /**
             * Costuttore di default
             * Costruisce un nodo vuoto
             * 
             * @post e == nullptr
             * @post next == nullptr
             */
            nodo() : next(nullptr), e(nullptr){}
            
            /**
             * Costruttore secondario
             * Costruisce un nodo a partire dai parametri passati
             * L'oggetto element viene creato nello heap
             * Se il nodo successivo non viene specificato, esso sarà nullptr
             * 
             * @param row indice della riga 
             * @param col indice della colonna
             * @param val valore da memorizzare
             * @param n puntatore al nodo successimo
             * 
             * @post e == e(row, col, val)
             * @post next == n
             */
            nodo(index_t row, index_t col, const T &val, nodo *n): e(new element(row,col,val)), next(n){}

            /**
             * Costruttore secondario
             * Costruisce un nodo a partire dai parametri passati
             * Se il nodo successivo non viene specificato, esso sarà nullptr
             * 
             * @param element puntatore ad un oggetto element che contiene i dati
             * @param n puntatore al nodo successivo
             * 
             * @post e == element
             * @post next == n
             */
            nodo(element *element, nodo *n=nullptr): e(element), next(n){}
            

            /**
             * Copy constructor
             * @brief Costruisce un nodo a partire da un altro nodo copiando i dati membro a membro
             * 
             * @param other oggetto nodo da copiare
             */
            nodo(const nodo &other){
                if(this != &other){
                    e=other.e;
                    next=other.next;
                }
            }

            /**
             * Operatore assegnamento
             * @brief Assegna ad un oggetto nodo un altro nodo copiando i dati membro a membro
             * 
             * @param other nodo da copiare
             * @return reference all'element this
             */
            nodo& operator=(const nodo &other){
                if(this != &other){
                    e=other.e;
                    next=other.next;
                }
                return *this;
            }
            /**
             * Distruttore
             */
            ~nodo(){} 
            
            /**
             * Funzione che implementa l'operatore di stream.
             * La funzione è friend perchè accede ai dati privati del nodo.
             * 
             * @param os stream di output
             * @param n nodo da spedire sullo stream
             * @return reference dello stream di output
             */
            friend std::ostream& operator<<(std::ostream &os, const nodo &n){
                return os<<n.e;
            }
        };

    
    nodo *_head;///< puntatore al primo nodo della lista
    T _default_value;///< valore di default della matrice
    size_t _stored_elements;///< numero di elementi salvati
    size_t _rows;///< righe della matrice
    size_t _columns;///< colonne della matrice

    public:
        /**
         * Costruttore di dafault
         * 
         * @post _head == nullptr
         * @post _stored_elements == 0
         * @post _rows == 0
         * @post _column == 0
         * 
         */
        sparsematrix():_head(nullptr), _stored_elements(0), _rows(0), _columns(0), _default_value(){}

        /**
         * Costruttore secondario
         * 
         * @param rows righe della matrice
         * @param columns colonne della matrice
         * @param default_value valore di default
         * 
         * @post _rows == rows
         * @post _columns == columns
         * @post _head == nullptr
         * @post _stored_elements == 0
         */
        sparsematrix(int rows, int columns, const T &default_value) : _head(nullptr), _default_value(default_value), _stored_elements(0){
            if(rows<0 || columns<0)
                throw negative_size_error("Negative sparse matrix's size");
                
            this->_rows=rows;
            this->_columns=columns;
        }

        /**
         * Copy costructor
         * 
         * @param other sparse matrix da copiare
         * 
         * @post _rows == other._rows
         * @post _columns == other._columns
         * @post _stored_elements == other._stored_elements
         * @post _default_value == other._default_value
         * 
         * @throw std::out_of_range possibile eccezione 
         */
        sparsematrix(const sparsematrix &other):_head(nullptr), _stored_elements(0), _rows(other._rows), _columns(other._columns), _default_value(other._default_value){
            nodo *current=other._head;
            try{
                while(current!=nullptr){
                    element *current_element=current->e;
                    set(current_element->row, current_element->column, current_element->value);
                    current=current->next;
                }
            }catch(...){
                empty();
                throw;
            }

        }
        /**
         * Operatore assegnamento
         * 
         * @param other sparsematrix da copiare
         * @return reference della sparsematrix this
         */
        sparsematrix& operator=(const sparsematrix &other){
            if(this != &other){
                sparsematrix tmp(other);
                std::swap(_head, tmp._head);
                std::swap(_default_value, tmp._default_value);
                std::swap(_stored_elements, tmp._stored_elements);
                std::swap(_rows, tmp._rows);
                std::swap(_columns, tmp._columns);
            }
            return *this;
        }
        /**
         * Distruttore
         * @post _head == nullptr
         * @post _stored_elements == 0
         * @post _rows == 0
         * @post _column == 0
         */
        ~sparsematrix(){
           empty();
        }

        /**
         * Svuota la matrice
         * @post _head == nullptr
         * @post _stored_elements == 0
         * @post _rows == 0
         * @post _column == 0
         */
        void empty(){
            nodo *current=_head;
            while(current!=nullptr){
                nodo *next_node=current->next;
                delete current->e; 
                delete current; 
                current=next_node;
            }
            _head=nullptr;
            _stored_elements=0;
            _rows=0;
            _columns=0;
        }

        /**
         * Ritorna il valore di default
         * 
         * @return reference del valore di default 
         */
        const T& default_value()const{
            return _default_value;
        }

        /**
         * Ritorna il numero degli elementi salvati
         * 
         * @return copia del valore degli elementi salvati
         */
        size_t stored_elements() const{
            return _stored_elements;
        }
        
        /**
         * Ritorna il numero delle righe
         * 
         * @return numero delle righe
         */
        size_t rows() const{
            return _rows;
        }
        /**
         * Ritorna il numero delle colonne
         * 
         * @return numero delle colonne
         */
        size_t columns() const{
            return _columns;
        }
        /**
         * Aggiunge un elemento nella matrice
         * 
         * @param i indice della riga
         * @param j indice della colonna
         * @param value valore da memorizzare
         * 
         * @post _stored_elements = _stored_elements + 1
         * 
         * @throw std::out_of_range eccezione in caso di indici fuori range
         * @throw std::bad_alloc possibile eccezione di allocazione
         */
        void set(unsigned int i, unsigned int j, const T& value){ 
            if(i<0 || j<0 || i>=_rows || j>=_columns)
                throw std::out_of_range("Cannot call the set function due to an index out of bound");
           
            //existing node
            nodo *current=_head;
            while(current!=nullptr){
                if(current->e->row==i && current->e->column==j){
                    current->e->value=value;
                    return;
                }  
                current=current->next;
            }

            nodo *aus=new nodo(i,j,value,nullptr);//aus->next is nullptr
            if(_head==nullptr){
                _head=aus;
                _stored_elements++;
                return;
            }
            //node does not exist
            nodo *first_node=_head;
            _head=aus;
            aus->next=first_node;
            _stored_elements++;
            first_node=nullptr;
            
        }

        /**
         * Ritorna il valore dati gli indici
         * 
         * @param i indice della riga
         * @param j indice della colonna
         * 
         * @return reference costante del valore
         * 
         * @throw std::out_of_range eccezione in caso di indici fuori range
         */
        const T& operator()(int i, int j) const{
            if(i<0 || j<0 || i>=_rows || j>=_columns)
                throw std::out_of_range("Cannot read the value due to an index out of bound");

            nodo *current=_head;
            while(current!=nullptr){
                 if(current->e->row==i && current->e->column==j)
                    return current->e->value;

                current=current->next;
            }
            current=nullptr;
            return _default_value;
        }
        /**
         * Funzione globale che implementa l'operatore di stream
         * Stampa su stream la matrice, il valore di default e gli elementi salvati
         * 
         * @param os stream di output
         * @param matrix sparsematrix da spedire sullo stream
         * @return reference dello stream di output
         */
        friend std::ostream & operator<<(std::ostream &os, const sparsematrix &matrix){
            os<<"Default value: "<<matrix.default_value()<<std::endl;
            os<<"Stored elements: "<<matrix.stored_elements()<<std::endl;
            os<<"Sparse Matrix"<<"("<<matrix.rows()<<", "<<matrix.columns()<<")"<<" elements: "<<std::endl;
            for(index_t i=0; i<matrix.rows(); ++i){
                for(index_t j=0; j<matrix.columns(); ++j)
                    os<<" ("<<matrix(i,j)<<") ";
                if(i<matrix.rows()-1)
                    os<<std::endl;
            }
            return os;
        }

        /**
         * Classe const_iterator
         * Gli iteratori iterano sui dati contenuti nella sparsematrix
         * e ritornano un oggetto element che contiene il dato.
         * @brief Classe const_iterator
         */
        class const_iterator {	
	        public:
                typedef std::forward_iterator_tag iterator_category;
                typedef element                   value_type;
                typedef ptrdiff_t                 difference_type;
                typedef const element*            pointer;
                typedef const element&            reference;

	
                const_iterator() : ptr(nullptr){}
                
                const_iterator(const const_iterator &other) : ptr(other.ptr) {}

                const_iterator& operator=(const const_iterator &other) {
                   ptr=other.ptr;
                   return *this;
                }

                ~const_iterator() {}

                reference operator*() const {
                    return *(ptr->e);
                }

                pointer operator->() const {
                    return (ptr->e);
                }
                
            
                const_iterator operator++(int) {
                    const_iterator aus(*this);
                    ptr=ptr->next;     
                    return aus;
                }

                
                const_iterator& operator++() {
                    ptr=ptr->next;
                    return *this;
                }

                
                bool operator==(const const_iterator &other) const {
                   return ptr==other.ptr;
                }
             
                bool operator!=(const const_iterator &other) const {
                    return !(*this == other); 
                }


            private:
                friend class sparsematrix;
                const nodo *ptr;

                const_iterator(const nodo *node):ptr(node){}
		
		
	}; // classe const_iterator

    /**
     * Ritorna un iteratore che punta al primo elemento della lista
     * 
     * @return const_iterator 
     */
	const_iterator begin() const {
		return const_iterator(_head);
	}
	/**
	 * RItorna un iteratore che punta ad un elemento nullo
	 * 
	 * @return const_iterator 
	 */
	const_iterator end() const {
		return const_iterator(nullptr);
	}  

}; // class sparsematrix


/**
 * 
 * Funzione GLOBALE che ritorna il numero dei valori 
 * contenuti in una generica sparsematrix che soddisfano 
 * un predicato generico di tipo P
 * @param M sparsematrix
 * @param predicate predicato
 * 
*/
template<typename T, typename P>
unsigned int evaluate(const sparsematrix<T> &M, P predicate){
    unsigned int cont=0;

    for(unsigned int i=0; i<M.rows(); ++i)
        for(unsigned int j=0; j<M.columns();++j)
            if(predicate(M(i,j)))
                cont++;
    

    return cont;
}

#endif
