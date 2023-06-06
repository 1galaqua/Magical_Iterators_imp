#include "MagicalContainer.hpp"
#include <iostream>
#include <cmath>
using namespace ariel;
using namespace std;


MagicalContainer::~MagicalContainer(){

}
MagicalContainer::MagicalContainer ()noexcept{};

bool MagicalContainer::isPrime(int num) const{ //check prime
    if (num <= 1) {
        return false;
        }
    for (int temp = 2; temp <= sqrt(num); ++temp) {
        if (num % temp == 0) {
            return false;
        }
    }
    return true;

}
void MagicalContainer::addElement(int element){//add elemnet to comtainer in sorted way and if the num is prim add to prim container
    auto it = std::find(_container.begin(), _container.end(), element);
    if(it==_container.end()){
        this->_container.insert(upper_bound(_container.begin(),_container.end(),element),element);// isnert sorted
    }
    if(isPrime(element)){
        auto itp = std::find(_prime_container.begin(), _prime_container.end(), element);
        if(itp==_prime_container.end()){
            this->_prime_container.insert(upper_bound(_prime_container.begin(),_prime_container.end(),element),element);// isnert sorted
        }
    }
}

void MagicalContainer::removeElement( int element){
   auto it = std::find(_container.begin(), _container.end(), element);//search the num

    if (it == _container.end()) {//if not exist throw
        throw std::runtime_error("element does not exist");
        }
    _container.erase(std::remove(_container.begin(), _container.end(), element), _container.end());//remove the element from the container
    if(isPrime(element)){
        auto itp = std::find(_prime_container.begin(), _prime_container.end(), element);//search the elemnt in the prime comtainer
        _prime_container.erase(std::remove(_prime_container.begin(), _prime_container.end(), element), _prime_container.end());//remove the element from the prime comtainer
    }
}

size_t MagicalContainer::size() const{
    return this->_container.size();
}

////////////////////////////////////////AscendingIterator///////////////////////////////////
MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer& container,size_t index):magic_container(&container),index(index){}


MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other):magic_container(other.magic_container),index(other.index){}

MagicalContainer::AscendingIterator::~AscendingIterator(){};

MagicalContainer::AscendingIterator&  MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other){
    if (this->magic_container->_container != other.magic_container->_container) {//check if container are the same
        throw std::runtime_error("container are not the same");
        }
    this->magic_container=other.magic_container;
    this->index=other.index;
    return *this;
}
bool MagicalContainer::AscendingIterator:: operator==(const AscendingIterator& other) const{

    return ((this->magic_container == other.magic_container) && (this->index == other.index)) ;
}
bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const{

    return !((this->magic_container == other.magic_container) && (this->index == other.index));

}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const{
    if (this->magic_container->_container != other.magic_container->_container) {//check if container are the same
        throw std::runtime_error("container are not the same");
        }

    return (this->index > other.index);

}
bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const{
    if (this->magic_container->_container != other.magic_container->_container) {//check if container are the same
        throw std::runtime_error("container are not the same");
        }

    return (this->index < other.index);
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() const{
    return AscendingIterator(*magic_container);
}
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() const{
    return AscendingIterator(*magic_container, magic_container->size());
}

int MagicalContainer::AscendingIterator::operator*() const{
    return this->magic_container->_container[this->index];

}
MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++(){
    if (this->index < this->magic_container->size()) {
        this->index+=1;
        return *this;
    }else{throw std::runtime_error("end of the AscendingIterator");}
    
    return *this;
    }


////////////////////////////////////////SideCrossIterator///////////////////////////////////
MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer& container,size_t start,size_t end)
    :magic_container(&container),_start(start),_end(end){
}


MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other)
    :magic_container(other.magic_container),_start(other._start),_end(other._end){}

MagicalContainer::SideCrossIterator::~SideCrossIterator(){};

MagicalContainer::SideCrossIterator&  MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other){
    if (this->magic_container->_container != other.magic_container->_container) {//check if container are the same
        throw std::runtime_error("container are not the same");
        }
    this->magic_container=other.magic_container;
    this->_start=other._start;
    this->_end=other._end;
    return *this;
}
bool MagicalContainer::SideCrossIterator:: operator==(const SideCrossIterator& other) const{

    return ((this->magic_container == other.magic_container) && (this->_start == other._start) && (this->_end == other._end)) ;
}
bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const{

    return !((this->magic_container == other.magic_container) && (this->_start == other._start) && (this->_end == other._end));

}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const{
    if (this->magic_container->_container != other.magic_container->_container) {//check if container are the same
        throw std::runtime_error("container are not the same");
        }
        

    return (this->_start > other._start || this->_end > other._end);

}
bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const{
    if (this->magic_container->_container != other.magic_container->_container) {//check if container are the same
        throw std::runtime_error("container are not the same");
        }
       

    return (this->_start < other._start || this->_end < other._end);
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const{
    return SideCrossIterator(*magic_container);
}
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const{
    int middle = magic_container->size()/2;
    if(magic_container->size()%2==0)
        return SideCrossIterator(*this->magic_container, static_cast<size_t>(middle),static_cast<size_t>(middle));
    return SideCrossIterator(*this->magic_container, static_cast<size_t>(middle), static_cast<size_t>(middle+1));
    
}

int MagicalContainer::SideCrossIterator::operator*() {
    if(this->_start == this->_end){//if its equal we need to point to the left side else to to point to the right side (cross)
        return magic_container->_container[(vector<int>::size_type)_start];
    }
    return magic_container->_container[(vector<int>::size_type)(magic_container->size()-_end)];
    

}
MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++(){
    if(this->_end+this->_start>=this->magic_container->size()){throw std::runtime_error("end of the SideCrossIterator");}

    if (this->_end==this->_start) {//that method help me to decide where to point at next ++
            this->_end+=1;
           
        }else{
            
            this->_start+=1;
        }
        

    return *this;
    }

////////////////////////////////////////PrimeIterator///////////////////////////////////


MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer& container,size_t index)
    :magic_container(&container),_index(index){
         
        
    
    }


MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other)
    :magic_container(other.magic_container),_index(other._index){}

MagicalContainer::PrimeIterator::~PrimeIterator(){};

MagicalContainer::PrimeIterator&  MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other){
    if (this->magic_container->_container != other.magic_container->_container) {//check if container are the same
        throw std::runtime_error("container are not the same");
        }
    this->magic_container=other.magic_container;
    this->_index=other._index;
    
    return *this;
}
bool MagicalContainer::PrimeIterator:: operator==(const PrimeIterator& other) const{

    return ((this->magic_container == other.magic_container) && (this->_index == other._index)) ;
}
bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const{

    return !((this->magic_container == other.magic_container) && (this->_index == other._index));

}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const{
    if (this->magic_container->_container != other.magic_container->_container) {//check if container are the same
        throw std::runtime_error("container are not the same");
        }
        

    return (this->_index > other._index);

}
bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const{
    if (this->magic_container->_container != other.magic_container->_container) {//check if container are the same
        throw std::runtime_error("container are not the same");
        }
        

    return (this->_index < other._index);
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const{
    return PrimeIterator(*magic_container);
}
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const{
  
    return PrimeIterator(*this->magic_container, static_cast<size_t>(this->magic_container->_prime_container.size()));
    
}

int MagicalContainer::PrimeIterator::operator*() const{
    
    
    return magic_container->_prime_container[(this->_index)];
    

}
MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++(){
    if(this->_index>=this->magic_container->_prime_container.size()||this->magic_container->_prime_container.size()<=0){// check if we point on end prime itarator or if have any prime elements
        throw std::runtime_error("end of the PrimeIterator or have no prime elements");
        }
       
        this->_index+=1;
        
    return *this;
    }
