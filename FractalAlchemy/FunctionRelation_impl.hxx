template<real T>
FunctionRelation<T>::FunctionRelation(size_t I, size_t J)
{
    this->I = I;
    this->J = J;

    // specify size of jagged array
    domain = new T*[I];
    image = new T*[I];
    for (unsigned int i=0; i<I; i++)
    {
        // specify size of the array contained
        domain[i] = new T [J];
        image[i] = new T [J];
        // std::cout << "Array assigned" << std::endl;
    }

    domainAllocated = true;
}

template<real T>
FunctionRelation<T>::FunctionRelation(size_t I, size_t J, T **domain)
{
    this->I = I;
    this->J = J;
    // set the domain (it will be destroyed in another instance, be careful with this)
    this->domain = domain;

    // just set the image
    image = new T*[I];
    for (unsigned int i=0; i<I; i++)
    {
        image[i] = new T [J];
    }
}

template<real T>
FunctionRelation<T>::~FunctionRelation()
{
    // delete image
    for (unsigned int i=0; i<I; i++)
    {
        delete[] image[i];
    }
    delete[] image;

    // if memory was allocated in this instance delete it
    if (domainAllocated)
    {
        for (unsigned int i=0; i<I; i++)
        {
            delete[] domain[i];
        }
        delete[] domain;
    }
}

template<real T>
void FunctionRelation<T>::populateDomainFromInterval(const T x0, const T x1)
{
    // iteratively assign values to the domain
    const T dx = (x1-x0)/((T)I*(T)J);
    for (unsigned int i=0; i<I; i++)
    { 
        for (unsigned int j=0; j<J; j++)
        {
            domain[i][j] = x0 + (dx*((i*(T)J)+j));
        }
    }

    // domain is assigned
    domainAssigned = true;
    this->dx = dx;
}

template<real T>
void FunctionRelation<T>::populateImageFromSimpleFunc(FunctionRule<T> &f)
{
    // give a value in the image for every element in the domain
    for (unsigned int i=0; i<I; i++)
    { 
        for (unsigned int j=0; j<J; j++)
        {
            image[i][j] = f(getDomainElem((unsigned int)(i*J)+j));
        }
    }

    imageAssigned = true;
}

template<real T>
void FunctionRelation<T>::populateImageFromSingleRecursiveFunc(RecursiveFunctionRule<T> &f, FunctionRelation<T> **func)
{
    // initialize first value
    image[0][0] = f.getInitValue();
    //initialize all elements from previous values
    for (unsigned int j=1; j<J; j++)
    {
        image[0][j] = f.getFromPreviousInImage(func, (unsigned int)(j));
    }
    for (unsigned int i=1; i<I; i++)
    { 
        for (unsigned int j=0; j<J; j++)
        {
            image[i][j] = f.getFromPreviousInImage(func, (unsigned int)((i*J)+j));
        }
    }

    imageAssigned = true;
}

template<real T>
inline void FunctionRelation<T>::modifyFromPrevRecursiveFunc(const RecursiveFunctionRule<T> &f, const unsigned int i, FunctionRelation<T> **params)
{
    // set image element using specified index
    setImageElem(f.getFromPreviousInImage(params, i), i);
}

template<real T>
inline void FunctionRelation<T>::modifyFromLastRecursiveFunc(const RecursiveFunctionRule<T> &f, const unsigned int i, FunctionRelation<T> **params)
{
    // set image element using the last element in the image
    setImageElem(f.getFromPreviousInImage(params, (unsigned int)(I*J)), i);
}

template<real T>
inline const T FunctionRelation<T>::getDomainElem(const unsigned int i) const
{
    return domain[(unsigned int)(i/J)][(unsigned int)(i%J)];
}

template<real T>
inline const T FunctionRelation<T>::getImageElem(const unsigned int i) const
{
    return image[(unsigned int)(i/J)][(unsigned int)(i%J)];
}

// Return image and domains as ptrs. Use with care
// ===============================================
template<real T>
inline T** FunctionRelation<T>::getDomain() const
{
    return domain;
}

template<real T>
inline T** FunctionRelation<T>::getImage() const
{
    return image;
}

template<real T>
inline const bool FunctionRelation<T>::isDomainAssigned() const
{
    return domainAssigned;
}

template<real T>
inline const bool FunctionRelation<T>::isDomainAllocated() const
{
    return domainAllocated;
}

template<real T>
inline const T FunctionRelation<T>::getdx() const
{
    return dx;
}

template<real T>
inline const size_t FunctionRelation<T>::getI() const
{
    return I;
}

template<real T>
inline const size_t FunctionRelation<T>::getJ() const
{
    return J;
}

template<real T>
inline void FunctionRelation<T>::setDomainElem(const T x, const unsigned int i)
{
    domain[(unsigned int)(i/J)][(unsigned int)(i%J)] = x;
}

template<real T>
inline void FunctionRelation<T>::setImageElem(const T x, const unsigned int i)
{
    image[(unsigned int)(i/J)][(unsigned int)(i%J)] = x;
}