#ifndef SEGYFILE_BINARYFILEHEADERINTERFACE_H
#define	SEGYFILE_BINARYFILEHEADERINTERFACE_H

#include<impl/ObjectFactory-inl.h>

#include<vector>
#include<iostream>
#include<string>

namespace seismic {
    
    /**
     * @brief Interface to a generic binary file header
     * 
     * This interface is meant to be extended to model correctly 
     * the fields in the underlying 400 bytes stream.
     *
     */
    class BinaryFileHeader {
    public:
        /// Number of bytes in the Binary file header
        static const int buffer_size = 400;
         
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
            return const_cast< typename  T::type & >( static_cast<const BinaryFileHeader&>(*this)[id] );
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
            return const_cast<char *>( static_cast<const BinaryFileHeader&>(*this).get() );
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
         * @brief Create a BinaryFileHeader of the same polymorphic type
         * 
         * @return pointer to the newly created object
         */
        virtual BinaryFileHeader * create() const = 0;
                
        /**
         * @brief Virtual destructor of the base class
         */
        virtual ~BinaryFileHeader(){}

        /**
         * @brief Returns a pointer to a newly created object
         * 
         * @param ID object ID
         * @return pointer to a newly created object
         */        
        inline static BinaryFileHeader * create(std::string ID); 
                
    private:
        char buffer_[buffer_size];
    };
 
    /**
     * @brief Output stream operator for BinaryFileHeader
     * 
     * @param cout stream
     * @param bfh input binary file header 
     * @return cout
     * 
     * @relates BinaryFileHeader
     */
    inline std::ostream& operator<<(std::ostream& cout, const BinaryFileHeader& bfh) {
        bfh.print( cout );
        return cout;
    }
    
    /**
     * @brief Master template to be specialized for different standards
     */
    template< class StdTag>
    class ConcreteBinaryFileHeader;
    
    /**
     * @brief Object factory for BinaryFileHeader derived classes
     */
    typedef CloneObjectFactory< BinaryFileHeader , std::string > BinaryFileHeaderCloneFactory;
            
    BinaryFileHeader * BinaryFileHeader::create(std::string ID) {            
            return BinaryFileHeaderCloneFactory::getFactory()->create(ID);
    }
            
}

#endif	/* SEGYFILE_BINARYFILEHEADERINTERFACE_H */

