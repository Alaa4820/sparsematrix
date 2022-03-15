#include "sparsematrix.h"
#include <iostream>
/**
 * @brief Funtore predicato
 * 
 * Ritorna true se un intero è pari
 * 
 */
struct is_even{
    bool operator()(int a) const{
        return a % 2 ==0;
    }
};
/**
 * @brief Funtore predicato
 * 
 * Ritona true se la lunghezza di una stringa è maggiore o uguale a 9
 * 
 */
struct string_size_9 {
  bool operator()(const std::string &s) const {
    return s.size()>=9;
  } 
};

/**
 * Struct point che implementa un punto 2D.
 * @brief  Struct point che implementa un punto 2D.
 * 
 */
struct point{
    double x;///< coordinata x del punto
    double y;///< coordinata y del punto
    /**
     * @brief Costruttore di default
     * 
     */
    point(){
        x=0;
        y=0;
    }
    /**
     * @brief Costruttore secondario
     * 
     * @param z ascissa del punto
     * @param k ordinata del punto
     */
    point(double z, double k):x(z), y(k){}

    /**
     * @brief Operatore assegnamento
     * Necessario per la classe sparsematrix
     * 
     * @param other punto
     * @return reference del punto this
     */
    point& operator=(const point &other){
        x=other.x;
        y=other.y;
        return *this;
    }
    /**
     * Ridefinizione dell'operatore di stream << per un point.
     * Necessario per l'operatore di stream della classe sparsematrix.
     * */
    friend std::ostream& operator<<(std::ostream &os, const point &p){
        return os<<"("<<p.x<<", "<<p.y<<")";
    }
};
/**
 * @brief Struct person che rappresenta una persona.
 * 
 *  Struct person che rappresenta una persona.
 */
struct person{
    std::string name;///<  nome della persona
    std::string surname;///< cognome della persona
    unsigned int age;///< età della persona

    /**
    * @brief Costruttore di default
    * 
    */
    person(){
        name=surname="";
        age=0;
    }
    /**
     * @brief Costruttore secondario
     * 
     * @param name nome della persona
     * @param surname cognome della persona
     * @param age età della persona
     */
    person(const std::string name, const std::string surname, unsigned int age)
        :name(name), surname(surname), age(age){}
    
    /**
     * @brief Operatore assegnamento
     * Necessario per la classe sparsematrix
     * 
     * @param other persona
     * @return reference dell'oggetto persona this
     */
    person& operator=(const person &other){
        name=other.name;
        surname=other.surname;
        age=other.age;
        return *this;
    } 
     /**
     * Ridefinizione dell'operatore di stream << per un point.
     * Necessario per l'operatore di stream della classe sparsematrix.
     * 
     * */
    friend std::ostream& operator<<(std::ostream &os, const person &p){
        return os<<p.name<<" "<<p.surname<<" "<<p.age; 
    }
};

/**
 * @brief Funzione che fa da funtore predicato
 * 
 * @param p oggetto person
 * @return true se la persona ha un'età minore di 18
 * @return false altrimenti
 */
bool age_under_18(person p){
    return p.age<18;
}




/**
 * Test dei metodi fondamentali
 * 
 * @brief Test dei metodi fondamentali
 * @param s sparsematrix<int>
 */
void test_sparse_matrix_fundamental_methods(sparsematrix<int> s){
    std::cout<<"******** Test sparse matrix fundamental methods ********"<<std::endl;
    sparsematrix<int>::const_iterator b,e;
    for(b=s.begin(), e=s.end(); b!=e; ++b)
        std::cout<<*b<<" ";
    std::cout<<std::endl;
    sparsematrix<int> sm;
    sparsematrix<int> s2(s);
    
    sparsematrix<int> s3;
    sm=s3=s;

    std::cout<<s2<<std::endl;
    std::cout<<s3<<std::endl;
    std::cout<<sm<<std::endl;

}
/**
 * Test sparse matrix di tipo person
 * @brief Test sparse matrix di tipo person
 * 
 */
void test_sparse_matrix_person(){
    std::cout<<"******** Test sparse matrix person ********"<<std::endl;
    person default_persona("mario", "rossi", 0);
    person p1("davide", "rossi", 12);
    person p2("carlo", "barini", 19);
    person p3("paolo", "rossi", 10);
    sparsematrix<person> persone(3,3, default_persona);
    persone.set(0,0,p1);
    persone.set(2,2,p2);
    persone.set(0,1,p1);
    persone.set(1,2,p2);
    persone.set(1,2,p3);
    std::cout<<persone<< std::endl;

    std::cout<<"People under 18: "<< evaluate(persone,age_under_18)<< std::endl;
    std::cout<<"___________________________________"<<std::endl;
    sparsematrix<person> pp(persone);
    sparsematrix<person> ps=pp;
    
}
/**
 * Test sparse matrix di tipo string
 * @brief Test sparse matrix di tipo string
 * 
 */
void test_sparse_matrix_string(){
    std::cout<<"******** Test sparse matrix string ********"<<std::endl;
    sparsematrix<std::string> s(5,5,"/");
    s.set(1,1, "carboidrati");
    s.set(1,3, "proteine");
    s.set(4,1, "grassi saturi");
    s.set(2,3, "grassi insaturi");
    s.set(0,4, "fibre");

    std::cout<<"Print with operator<<"<<std::endl;
    std::cout<<s<<std::endl;

    std::cout<<"Print with const_iterator"<<std::endl;
    sparsematrix<std::string>::const_iterator b,e;
    
    for(b=s.begin(), e=s.end(); b!=e; ++b)
        std::cout<<*b<<" ";

    std::cout<<std::endl;
    std::cout<<"Print a string using operator()"<<std::endl;
    std::cout<<s(1,2)<<std::endl;

    std::cout<<"Test evaluate()"<<std::endl;
    string_size_9 p;
    std::cout<<"String with size >= 9: "<<evaluate(s,p)<<std::endl;
    try{
        s(-1,5);
    }catch(std::out_of_range &e){
        std::cout<<"Negative size error using operator()"<<std::endl;
        std::cerr << e.what() <<std::endl;
    }

    
}
/**
 * Test sparse matrix di tipo point
 * @brief Test sparse matrix di tipo point
 * 
 */
void test_sparse_matrix_point(){
    std::cout<<"******** Test sparse matrix point ********"<<std::endl;
    try{
        sparsematrix<point> sparse_matrix(-2,10,point(0,0));
    }catch(const negative_size_error &e){
        
        std::cerr << e.what() <<std::endl;
    }
    point default_point(-1,-1);
    sparsematrix<point> s(4,6,default_point);
    for(unsigned int i=0; i<s.rows(); ++i)
        for(unsigned int j=0; j<s.columns()-(s.columns()/2); ++j)
            s.set(i,j, point(i,j));
    s.set(0,0, point(100,100));
   
    std::cout<<"Print with operator<<"<<std::endl;
    std::cout<<s<<std::endl;

    std::cout<<"Print with const_iterator"<<std::endl;
    sparsematrix<point>::const_iterator b,e;
    
    for(b=s.begin(), e=s.end(); b!=e; ++b)
        std::cout<<*b<<" ";
    std::cout<<std::endl;
    std::cout<<"Print a point using operator()"<<std::endl;
    std::cout<<s(1,2)<<std::endl;

    try{
        s(-1,5);
    }catch(std::out_of_range &e){
        std::cout<<"Negative size error using operator()"<<std::endl;
        std::cerr << e.what() <<std::endl;
    }


}
/**
 * Test sparse matrix di tipo int
 * @brief Test sparse matrix di tipo int
 * 
 */
void test_sparse_matrix_int(){
    std::cout<<"******** Test sparse matrix int ********"<<std::endl;
    sparsematrix<int> s(1,20,0);
    int k=1;
    for(unsigned int i=0; i<s.rows(); ++i)
        for(unsigned int j=0; j<s.columns(); ++j, ++k)
            s.set(i,j, k);// Test add
    s.set(0,0,0);
    std::cout<<"Print with operator<<"<<std::endl;
    std::cout<<s<<std::endl;

    std::cout<<"Print with const_iterator"<<std::endl;
    sparsematrix<int>::const_iterator b,e;
    
    for(b=s.begin(), e=s.end(); b!=e; ++b)
        std::cout<<*b<<" ";

    std::cout<<std::endl;
    std::cout<<"Print an integer using operator()"<<std::endl;
    std::cout<<s(0,5)<<std::endl;

    std::cout<<"Test evaluate()"<<std::endl;
    is_even ie;
    std::cout<<"Even integers: "<<evaluate(s,ie)<<std::endl;
    try{
        s(-1,5);
    }catch(std::out_of_range &e){
        std::cout<<"Negative size error using operator()"<<std::endl;
        std::cerr << e.what() <<std::endl;
    }


}
/**
 * Test sparse matrix constante passata come parametro
 * @brief  Test sparse matrix constante passata come parametro
 * 
 * @param s sparsematrix 
 * 
 */
void test_const_sparse_matrix(const sparsematrix<int> &s){
    std::cout<<"******** Test const sparse matrix int ********"<<std::endl;
    //cannot call add and empty
    std::cout<<"Print with operator<<"<<std::endl;
    std::cout<<s<<std::endl;
    std::cout<<"Print with const_iterator"<<std::endl;
    sparsematrix<int>::const_iterator b,e;
    for(b=s.begin(), e=s.end(); b!=e; ++b)
        std::cout<<*b<<" ";
    std::cout<<std::endl;

}


int main(){
    sparsematrix<int> s(10,10,0);
    int k=1;
    for(unsigned int i=0; i<s.rows(); ++i)
        for(unsigned int j=0; j<s.columns(); ++j, ++k)
            s.set(i,j, k);
            
    sparsematrix<int>::const_iterator i=s.begin();
    i->value;
    
    test_const_sparse_matrix(s);

    test_sparse_matrix_fundamental_methods(s);

    test_sparse_matrix_int();

    test_sparse_matrix_string();

    test_sparse_matrix_person();
    
    test_sparse_matrix_point();

    return 0;
}
