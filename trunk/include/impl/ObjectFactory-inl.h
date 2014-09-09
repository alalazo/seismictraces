/*
 *  SeismicTraces : another C++ library that reads files in SEG-Y format
 * 
 *  Copyright (C) 2014  Massimiliano Culpo
 * 
 *  This file is part of SeismicTraces.
 *
 *  SeismicTraces is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SeismicTraces is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 * 
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with SeismicTraces.  If not, see <http://www.gnu.org/licenses/>.
 */

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
    /// Type of the handles that are returned by the factory
    using handle_type = std::shared_ptr<InterfaceType>;
            
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
      static std::unique_ptr< CloneObjectFactory > pnt_(nullptr);
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

    /**
     * @brief Creates a new object
     * 
     * @tparam ArgsType types of the parameters
     * 
     * @param[in] id ID of the type to be created 
     * @param[in] args arguments to be passed to the create method
     * 
     * @return pointer to the newly created object
     */
    template< class... ArgsType >
    handle_type create(const IdentifierType& id, ArgsType&... args) const {
      typename CallbackMap::const_iterator ii = map_.find(id);
      if (ii == map_.end()) {
        throw std::runtime_error("FATAL ERROR: factory cannot create an unregistered object type");
      }
      return ii->second->create(args...);
    }

    // METHODS TO CREATE NEW OBJECTS: END
    ///////////////////////////////////////////////        
  private:

    //
    // This class must be the only entity able to build itself
    //
    CloneObjectFactory() = default;

    CloneObjectFactory(const CloneObjectFactory&) = delete;

    using CallbackMap = std::map< IdentifierType, std::shared_ptr<InterfaceType> >;
    CallbackMap map_;
  };

/**
 * @brief Defines factory_type and handle_type. Requires an implementation to 
 * define a create method stemming from the default constructor.
 * Add a static create method as a proxy to the factory.
 */  
#define INTERFACE_USE_FACTORY(T,KEY) using handle_type = std::shared_ptr<T>; \
        using factory_type = CloneObjectFactory< T, KEY >; \
        virtual handle_type create() const = 0;  \
        inline static handle_type create(const KEY & ID) { \
                return T::factory_type::getFactory()->create(ID); \
        }

/**
 * @brief Adds a concrete create method stemming from default constructor
 */
#define FACTORY_ADD_CREATE(T) using concrete_type = T; \
        handle_type create() const override { \
            return std::make_shared<concrete_type>(); \
        }
}

#endif	/* OBJECTFACTORY_INL_H */

