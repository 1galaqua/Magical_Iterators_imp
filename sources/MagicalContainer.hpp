#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP


#include <cstddef>
#include <stdexcept>
#include <vector>


namespace ariel {

class MagicalContainer {

private:
    std::vector<int> _prime_container;
    std::vector<int> _container;
    size_t index=0;
    bool isPrime(int num) const;

public:
    
    ~MagicalContainer();
    MagicalContainer () noexcept;
    void addElement(int element);
    void removeElement( int element);
    size_t size() const;
    class AscendingIterator;
    class SideCrossIterator;
    class PrimeIterator;

};


class MagicalContainer::AscendingIterator {
private:
    const MagicalContainer* magic_container;
    size_t index;
   
public:
    AscendingIterator(const MagicalContainer& container,size_t index=0);
    AscendingIterator(const AscendingIterator& other);
    ~AscendingIterator();

    AscendingIterator& operator=(const AscendingIterator& other);
    bool operator==(const AscendingIterator& other) const;
    bool operator!=(const AscendingIterator& other) const;

    bool operator>(const AscendingIterator& other) const;
    bool operator<(const AscendingIterator& other) const;

    AscendingIterator begin() const;
    AscendingIterator end() const;

    int operator*() const;
    AscendingIterator& operator++();

   
};


class MagicalContainer::SideCrossIterator {
private:
    const MagicalContainer* magic_container;
    size_t _start;
    size_t cross=0;
    size_t _end;
  
public:
    SideCrossIterator(const MagicalContainer& container,size_t index=0,size_t _end=0);
    SideCrossIterator(const SideCrossIterator& other);
    ~SideCrossIterator();

    SideCrossIterator& operator=(const SideCrossIterator& other);
    bool operator==(const SideCrossIterator& other) const;
    bool operator!=(const SideCrossIterator& other) const;

    bool operator>(const SideCrossIterator& other) const;
    bool operator<(const SideCrossIterator& other) const;

    SideCrossIterator begin() const;
    SideCrossIterator end() const;
    int operator*();
    SideCrossIterator& operator++();
   
};


class MagicalContainer::PrimeIterator {
private:
    const MagicalContainer* magic_container;
    size_t _index;
    
public:
    PrimeIterator(const MagicalContainer& container,size_t index=0);
    PrimeIterator(const PrimeIterator& other);
    ~PrimeIterator();

    PrimeIterator& operator=(const PrimeIterator& other);
    bool operator==(const PrimeIterator& other) const;
    bool operator!=(const PrimeIterator& other) const;

    bool operator>(const PrimeIterator& other) const;
    bool operator<(const PrimeIterator& other) const;

    PrimeIterator begin() const;
    PrimeIterator end() const;

    int operator*() const;
    PrimeIterator& operator++();

};
}

#endif
