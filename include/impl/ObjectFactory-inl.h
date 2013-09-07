/**
 * @file ObjectFactory-inl.h
 * @brief Template implementation of a simple object factory
 */
#ifndef OBJECTFACTORY_INL_H
#define	OBJECTFACTORY_INL_H

#include<map>
#include<iostream>
#include<stdexcept>
#include<algorithm>
#include<memory>

namespace seismic {    
        
  /**
   * @brief Factory class that owns instances of objects
   * 
   * @tparam InterfaceType common interface to the constructable objects
   * @tparam IdentifierType type of the identifier used during the construction
   *   
   * Notes: 
   * - The factory is implemented using the singleton pattern. 
   * - It owns an instance of the registered object.
   * - Each registered object is required to have a virtual "create" method that 
   *   returns a pointer to a newly created object of the same type on the heap
   */
  template< class InterfaceType, class IdentifierType >
  class CloneObjectFactory {
  public:

    /**
     * @brief Static method that provides access to the unique factory.
     * 
     * The factory is created on demand.
     * 
     * @return pointer to factory
     */
    static CloneObjectFactory* getFactory() {
      // 
      // As a singleton, this class owns itself through a RAII smart-pointer
      // providing exclusive access.
      //
      static std::auto_ptr< CloneObjectFactory > pnt_(0);
      if ( !pnt_.get() ) {
        pnt_.reset( new CloneObjectFactory );
      }
      return pnt_.get();
    }

    void list() const {
        std::cout << "Map registered types are:" << std::endl;
        for( typename CallbackMap::const_iterator ii = map_.begin(); ii != map_.end(); ++ii ) {
            std::cout << (*ii).first << std::endl;
        }
    }
    
    /**
     * @brief Registers a new type in the factory
     * @param[in] id ID of the new type
     * @param[in] obj pointer to an object to be stored in the factory 
     * @return true is the registration succeeded, false otherwise
     */    
    template< class ObjectType >
    bool registerType(const IdentifierType& id, ObjectType obj) {
      return map_.insert(typename CallbackMap::value_type(id, obj)).second;
    }

    /**
     * @brief Unregisters a type from the factory
     * @param[in] id ID of the type to be removed
     * @return true is the un-registration succeeded, false otherwise
     */
    bool unregisterType(const IdentifierType& id) {
      typename CallbackMap::iterator it = map_.find(id);
      if ( it != map_.end() ) delete it->second;
      return ( map_.erase(id) == 1);
    }

    ///////////////////////////////////////////////
    // METHODS TO CREATE NEW OBJECTS : START
    //
    // TODO: Creation methods are a place where the use of variadic templates is natural (whenever C++11 will be allowed)
    // For the time being creation function accepting up to two parameters are implemented. Can be extended if needs arise.
    //
    /**
     * @brief Creates a new object with a default constructor
     * 
     * @param[in] id ID of the type to be created 
     * @return pointer to the newly created object
     */
    InterfaceType * create(const IdentifierType& id) const {
      typename CallbackMap::const_iterator ii = map_.find(id);
      if (ii == map_.end()) {
        throw std::runtime_error("FATAL ERROR: factory cannot create an unregistered object type");
      }
      return ii->second->create();
    }

    /**
     * @brief Creates a new object with a constructor taking 1 parameter
     * 
     * @param[in] id ID of the type to be created 
     * @param[in] t1 constructor parameter
     * @return pointer to the newly created object
     */
    template< class T1 >
    InterfaceType * create(const IdentifierType& id, T1 t1) const {
      typename CallbackMap::const_iterator ii = map_.find(id);
      if (ii == map_.end()) {
        throw std::runtime_error("FATAL ERROR: factory cannot create an unregistered object type");
      }
      return ii->second->create(t1);
    }
    
    /**
     * @brief Creates a new object with a constructor taking 2 parameters
     * 
     * @param[in] id ID of the type to be created 
     * @param[in] t1 constructor parameter
     * @param[in] t2 constructor parameter
     * @return pointer to the newly created object
     */
    template< class T1, class T2 >
    InterfaceType * create(const IdentifierType& id, T1 t1, T2 t2) const {
      typename CallbackMap::const_iterator ii = map_.find(id);
      if (ii == map_.end()) {
        throw std::runtime_error("FATAL ERROR: factory cannot create an unregistered object type");
      }
      return ii->second->create(t1, t2);
    }        
    //
    // METHODS TO CREATE NEW OBJECTS: END
    ///////////////////////////////////////////////
    
    /**
     * @brief Factory destructor must delete sample objects
     */
    ~CloneObjectFactory() {
      for (typename CallbackMap::iterator ii = map_.begin(); ii != map_.end(); ++ii) {
        delete ( ii->second );
      }
    }
  private:

    //
    // This class must be the only entity able to build itself
    //
    CloneObjectFactory() {
    }

    CloneObjectFactory(const CloneObjectFactory&) {
    }

    typedef std::map< IdentifierType, InterfaceType* > CallbackMap;
    CallbackMap map_;
  };
  
}

#endif	/* OBJECTFACTORY_INL_H */

