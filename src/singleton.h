#ifndef SINGLETON_H
#define SINGLETON_H

/**
 * @brief Template class for creating a Singleton pattern in C++.
 */
template <typename T>
class TempSingleton {
protected:
    //user can't create an instance of Singleton directly, only through getInstance()
    TempSingleton() {}
    virtual ~TempSingleton() {}

public:
    //Delete copy constructor and assignment operator to prevent copying of the singleton instance
    TempSingleton(const TempSingleton&) = delete;
    TempSingleton& operator=(const TempSingleton&) = delete;

    /**
     * @brief Global access point to the unique instance.
     * @return T& Reference to the instance of the derived class.
     */
    static T& getInstance() {
        // The static local variable ensures safe creation of the unique instance
        static T instance;
        return instance;
    }
};

#endif