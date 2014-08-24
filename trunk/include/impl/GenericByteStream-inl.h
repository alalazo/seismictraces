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
 * @file GenericByteStream-inl.h
 * @brief Interface to a generic byte stream of known size
 */
#ifndef GENERICBYTESTREAM_INL_H
#define	GENERICBYTESTREAM_INL_H

#include<impl/ObjectFactory-inl.h>

#include<array>
#include<iostream>
#include<memory>

namespace seismic {
    
    template<int size>
    class GenericByteStreamSmartReference;
    
    /**
     * @brief Interface to a generic byte stream of known size
     * 
     * @tparam size stream size in bytes
     * 
     * @todo Write a brief documentation on how to extend this class
     *
     */
    template<int size>    
    class GenericByteStream {
    public:
        /// Number of bytes in the Binary file header
        static const int buffer_size = size;
         
        INTERFACE_USE_FACTORY(GenericByteStream,std::string)
        /// SmartReferenceType for the GenericByteStream
        using smart_reference_type = GenericByteStreamSmartReference< size >;
        
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
            return const_cast< typename  T::type & >( static_cast<const GenericByteStream&>(*this)[id] );
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
            return const_cast<char *>( static_cast<const GenericByteStream&>(*this).get() );
        }
        
        /**
         * @brief Knows how to print the byte stream to a std::ostream
         * 
         * @param[in,out] cout output stream
         */
        virtual void print(std::ostream& cout) const = 0;
        
        /**
         * @brief Knows how to invert the byte order of each field in the stream
         */
        virtual void invertByteOrder() = 0;
        
        /**
         * @brief Check if the values of mandatory fields are set, and throws exceptions if
         * a non-conformity is detected
         */
        virtual void checkConsistencyOrThrow() const = 0;
                
        /**
         * @brief Virtual destructor of the base class
         */
        virtual ~GenericByteStream(){}
        
    private:
        std::array<char,size> buffer_;
    };
         
    /**
     * @brief Read a byte stream from an input stream
     * 
     * @param[in] inputStream input stream
     * @param[in,out] byteStream byte stream
     */
    template<int size>
    inline void read(std::istream& inputStream, std::shared_ptr< GenericByteStream<size> > byteStream) {
        // Read byte stream
        inputStream.read(byteStream->get(), GenericByteStream<size>::buffer_size);
#ifdef LITTLE_ENDIAN
        // If the system is little endian, bytes must be swapped            
        byteStream->invertByteOrder();
#endif  
    }
    
    /**
     * @brief Write a byte stream to an output stream 
     * 
     * @param[in,out] outputStream output stream
     * @param[in] byteStream byte stream
     */
    template<int size>
    inline void write(std::ostream& outputStream, std::shared_ptr< GenericByteStream<size> > byteStream) {
#ifdef LITTLE_ENDIAN
        // If the system is little endian, bytes must be swapped            
        byteStream->invertByteOrder();
#endif  
        // Write byte stream
        outputStream.write(byteStream->get(), GenericByteStream<size>::buffer_size);
#ifdef LITTLE_ENDIAN
        // Return to the original order in memory          
        byteStream->invertByteOrder();
#endif  
    }
    
    /**
     * @brief Output stream operator for a GenericByteStream
     * 
     * @param cout stream
     * @param bstream input byte stream
     * @return cout
     * 
     * @relates GenericByteStream
     */
    template<int size>
    inline std::ostream& operator<<(std::ostream& cout, const GenericByteStream<size>& bstream) {
        bstream.print( cout );
        return cout;
    }
    
    /**
     * @brief RAII class with reference semantic for an object of type GenericByteStreamSmartReference
     */
    template<int size>
    class GenericByteStreamSmartReference {
    public:
        GenericByteStreamSmartReference(){}
        
        template<class T>
        explicit GenericByteStreamSmartReference( T ptr ) : ptr_(ptr) {}
        
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
            // Forward the call to the right object
            return (*ptr_)[id];
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
            return const_cast< typename  T::type & >( static_cast<const GenericByteStreamSmartReference&>(*this)[id] );
        }
        
         /**
         * @brief Returns a raw pointer to the underlying buffer
         * 
         * @return Pointer to the beginning of the buffer
         */
        const char * get() const {
            return ptr_->get();
        }
        
        /**
         * @brief Returns a raw pointer to the underlying buffer
         * 
         * @return Pointer to the beginning of the buffer
         */
        char * get() {
            return const_cast<char *>( static_cast<const GenericByteStreamSmartReference&>(*this).get() );
        }
        
        /**
         * @brief Knows how to print the managed resource
         * 
         * @param[in,out] cout stream to print on
         */
        void print(std::ostream& cout) const {
            (*ptr_).print(cout);
        }
                
        /**
         * @brief Knows how to invert the byte order of each field in the stream
         */
        void invertByteOrder() {
            ptr_->invertByteOrder();
        }
        
        /**
         * @brief Check if the values of mandatory fields are set, and throws exceptions if
         * a non-conformity is detected
         */
        void checkConsistencyOrThrow() const {
            ptr_->checkConsistencyOrThrow();
        }
       
        friend inline 
        void read(std::istream& inputStream, GenericByteStreamSmartReference byteStream) {
            read(inputStream,byteStream.ptr_);
        }
        
        friend inline 
        void write(std::ostream& outputStream, GenericByteStreamSmartReference byteStream) {
            write(outputStream,byteStream.ptr_);
        }
        
    private:
        std::shared_ptr< GenericByteStream<size> > ptr_;        
    };
    
    /**
     * @brief Output stream operator for BinaryFileHeader
     * 
     * @param cout stream
     * @param bstream input binary file header 
     * @return cout
     * 
     * @relates BinaryFileHeader
     */
    template<int size>
    inline std::ostream& operator<<(std::ostream& cout, const GenericByteStreamSmartReference< size > & bstream) {
        bstream.print( cout );
        return cout;
    }    
}

#endif	/* GENERICBYTESTREAM_INL_H */

