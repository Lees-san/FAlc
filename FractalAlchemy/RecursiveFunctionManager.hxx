#pragma once

#include <concepts>

#include "FunctionRule.hxx"
#include "RecursiveFunctionRule.hxx"
#include "FunctionRelation.hxx"

template <typename Derived, typename T>
concept RecursiveFunction = std::is_base_of<RecursiveFunctionRule<T>, Derived>::value;


/*
Class that manages a function rule and a function relation. In this way a function is linked to
its domain and image.
*/
template<real T, template <real> class RecursiveFunction>
class RecursiveFunctionManager
{
public:
    // Ctors
    RecursiveFunctionManager(FunctionRelation<T> *relation, RecursiveFunction<T> *rule);  // Initializes relation and rule parameters
    template<typename... Args>
    RecursiveFunctionManager(size_t I, size_t J, const T x0, Args... args);               // Initializes a domain and creates an instance of the RecursiveFunction class specified in the template of the RecursiveFunctionManager class
    template<typename... Args>
    RecursiveFunctionManager(size_t I, size_t J, T **domain, const T x0, Args... args);   // Initializes a domain from another function and creates an instance of the RecursiveFunction class specified in the template of the RecursiveFunctionManager class
    ~RecursiveFunctionManager();                                                          // Destructor

    void InitDomainAndX0(const T x0, const T x1);                                         // Inits the domain and first value in image
    void InitX0();                                                                        // Inits first value in image
    void modifyFromLast(const unsigned int i, FunctionRelation<T> **params);              // Modifies the element at index i using the last elements of the images of params
    void modifyFromPrev(const unsigned int i, FunctionRelation<T> **params);              // Modifies the element at index i using the elements at index i-1 from the images of params
    
    // getter functions
    inline FunctionRelation<T>* getRelation() const;
    inline const T getDomainElem(const unsigned int i) const;
    inline const T getImageElem(const unsigned int i) const;
    inline T** getDomain() const;
    inline T** getImage() const;
    inline const bool isDomainAssigned() const;
    inline const bool isDomainAllocated() const;
    inline const T getdx() const;
    inline const size_t getI() const;
    inline const size_t getJ() const;
    inline const T getx0() const;

    // setter functions
    inline void setDomainElem(const T x, const unsigned int i);
    inline void setImageElem(const T x, const unsigned int i);

private:
    // The function rule and relation
    FunctionRelation<T> *relation;
    RecursiveFunction<T> *rule;

    // variables for safety
    bool isFuncAllocated = false;
};

#include "RecursiveFunctionManager_impl.hxx"