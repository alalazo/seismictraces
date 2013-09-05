#ifndef SEGYFILE_BINARYFILEHEADERINTERFACE_H
#define	SEGYFILE_BINARYFILEHEADERINTERFACE_H

#include<iostream>

namespace seismic {
    
    class BinaryFileHeaderInterface {
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
            return const_cast< typename  T::type & >( static_cast<const BinaryFileHeaderInterface&>(*this)[id] );
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
            return const_cast<char *>( static_cast<const BinaryFileHeaderInterface&>(*this).get() );
        }
        
        /**
         * @brief Knows how to print an concrete binary file header
         */
        virtual void print(std::ostream& cout) const = 0;
        
        /**
         * @brief Knows how to invert the byte order of each field in the binary file header
         */
        virtual void invertByteOrder() = 0;
        
        virtual ~BinaryFileHeaderInterface(){}
        
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
    inline std::ostream& operator<<(std::ostream& cout, const BinaryFileHeaderInterface& bfh) {
        bfh.print( cout );
        return cout;
    }
    
    /**
     * @brief Master template to be specialized for different standards
     */
    template< class StdTag>
    class ConcreteBinaryFileHeader;
    
}

#endif	/* SEGYFILE_BINARYFILEHEADERINTERFACE_H */

