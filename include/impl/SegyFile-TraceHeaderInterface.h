/**
 * @file SegyFile-TraceHeaderInterface.h
 * @brief Generic interface to a trace header
 */
#ifndef SEGYFILE_TRACEHEADERINTERFACE_H
#define	SEGYFILE_TRACEHEADERINTERFACE_H

#include<impl/ObjectFactory-inl.h>

#include<vector>
#include<iostream>

namespace seismic {
    
    /**
     * @brief Interface to a generic trace header
     * 
     * This interface is meant to be extended to model correctly 
     * the fields in the underlying 240 bytes stream.
     */
    class TraceHeaderInterface {
    public:
        static const int buffer_size = 240;
  
        TraceHeaderInterface() : buffer_(buffer_size,0) {}
        
        /**
         * @brief Returns a reference to the underlying bytes interpreted as the correct type
         * 
         * @tparam T subscript type
         * 
         * @param[in] id value associated with the requested field
         * @return reference to the requested field 
         */
        template<class T>
        typename T::type const & operator[](T const id) const {
            // Pointer needed to induce aliasing
            const char * pnt(&buffer_[id.value_]);
            return *( reinterpret_cast<typename T::type const *>( pnt ) );
        }
        
        /**
         * @brief Returns a reference to the underlying bytes interpreted as the correct type
         * 
         * @tparam T subscript type
         * 
         * @param[in] id value associated with the requested field
         * @return reference to the requested field 
         */
        template<class T>
        typename T::type & operator[](T const id) {            
            return const_cast< typename  T::type & >( static_cast<const TraceHeaderInterface&>(*this)[id] );
        }
                        
        /**
         * @brief Returns a raw pointer to the underlying buffer
         * 
         * @return Pointer to the beginning of the buffer
         */
        const char * get() const {
            return &buffer_[0];
        }
        
        /**
         * @brief Returns a raw pointer to the underlying buffer
         * 
         * @return Pointer to the beginning of the buffer
         */
        char * get() {
            return const_cast<char *>( static_cast<const TraceHeaderInterface&>(*this).get() );
        }
        
        /**
         * @brief Knows how to print an concrete binary file header
         */
        virtual void print(std::ostream& cout) const = 0;
        
        /**
         * @brief Knows how to invert the byte order of each field in the binary file header
         */
        virtual void invertByteOrder() = 0;
        
        /**
         * @brief Check if the values of mandatory fields are set, and throws exceptions if
         * a non-conformity is detected
         */
        virtual void checkConsistencyOrThrow() const = 0;
        
        /**
         * @brief Create a TraceHeaderInterface of the same polymorphic type
         * 
         * @return pointer to the newly created object
         */
        virtual TraceHeaderInterface * create() const = 0;
                
        /**
         * @brief Virtual destructor of the base class
         */
        virtual ~TraceHeaderInterface(){}

        /**
         * @brief Returns a pointer to a newly created object
         * 
         * @param ID object ID
         * @return pointer to a newly created object
         */        
        inline static TraceHeaderInterface * create(std::string ID); 
                
    private:
        //char buffer_[buffer_size];
        std::vector<char> buffer_;
    };

    /**
     * @brief Output stream operator for TraceHeaderInterface
     * 
     * @param cout stream
     * @param bfh input binary file header 
     * @return cout
     * 
     * @relates TraceHeaderInterface
     */
    inline std::ostream& operator<<(std::ostream& cout, const TraceHeaderInterface& th) {
        th.print( cout );
        return cout;
    }
    
    /**
     * @brief Master template to be specialized for different standards
     */
    template<class StdTag>
    class ConcreteTraceHeader;
    
    /**
     * @brief Object factory for TraceHeaderInterface derived classes
     */
    typedef CloneObjectFactory< TraceHeaderInterface , std::string > TraceHeaderCloneFactory;
            
    TraceHeaderInterface * TraceHeaderInterface::create(std::string ID) {            
            return TraceHeaderCloneFactory::getFactory()->create(ID);
    }
    
}

#endif	/* SEGYFILE_TRACEHEADERINTERFACE_H */

