/**
 * @file SeismicTrace-inl.h
 * @brief Seismic trace
 */
#ifndef SEISMICTRACE_INL_H
#define	SEISMICTRACE_INL_H

#include<vector>
#include<stdexcept>

namespace seismic {
             
    /**
     * @brief Models a seismic trace 
     * 
     * This class is nothing but a std::vector<double> decorated with some metadata
     * 
     * The following is a small example of the basic use of the class:
     * @include example01.cpp
     * 
     */
    class SeismicTrace : public std::vector< float > {
    private:
        typedef float coordinate_type[3];
        
    public:
        /**
         * @brief List of the possible coordinates
         */
        enum CoordinateID {
            /// X axis
            X,
            /// Y axis
            Y,
            /// Z axis
            Z
        };    
                
        /**
         * Returns a reference to the requested trace coordinate
         * 
         * @param[in] id coordinate to be accessed
         * @return reference to the requested coordinate
         */
        float & operator()(const CoordinateID id) {
            return arrayAccessHelper(id,receiverCoords_);
        }        
        
        /**
         * Returns a reference to the requested trace coordinate
         * 
         * @param[in] id coordinate to be accessed
         * @return reference to the requested coordinate
         */
        const float& operator()(const CoordinateID id) const {
            return static_cast< const float&>( const_cast< SeismicTrace& >(*this)(id) );
        }
        
        /**
         * Returns a reference to the requested group (i.e. shot) coordinate
         * 
         * @param[in] id coordinate to be accessed
         * @return reference to the requested coordinate
         */
        float & shot(const CoordinateID id) {
            return arrayAccessHelper(id,sourceCoords_);
        }
        
        /**
         * Returns a reference to the requested group (i.e. shot) coordinate
         * 
         * @param[in] id coordinate to be accessed
         * @return reference to the requested coordinate
         */
        const float & shot(const CoordinateID id) const {
            return static_cast< const float& >( const_cast< SeismicTrace& >(*this).shot(id) );
        }
        
        /**
         * Returns a reference to the sample interval
         *          
         * @return reference to the sample interval
         */
        float& dt() { return dt_; };
        
        /**
         * Returns a reference to the sample interval
         *          
         * @return reference to the sample interval
         */
        const float & dt() const {
            return static_cast< const float &>( const_cast< SeismicTrace&>(*this).dt() );
        }
        
        
    private:    
        
        float & arrayAccessHelper(const CoordinateID id, coordinate_type& array)  {
             switch( id ) {
                case X :
                    return array[0];
                    break;
                case Y :
                    return array[1];
                    break;
                case Z :
                    return array[2];
                    break;
                default:
                    // The following command should NEVER be executed
                    throw std::runtime_error("SeismicTrace: wrong ID used to access shot or receiver coordinates\n");
                    break;
            }
            // The following command should NEVER be executed
            return array[0];
        }
        
        
        float           dt_;
        coordinate_type receiverCoords_;
        coordinate_type sourceCoords_;
    };

}

#endif	/* SEISMICTRACE_INL_H */