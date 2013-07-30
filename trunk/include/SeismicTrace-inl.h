#ifndef SEISMICTRACE_INL_H
#define	SEISMICTRACE_INL_H

#include<vector>
#include<stdexcept>

namespace seismic {
            
    enum CoordinateID { X, Y, Z};
    
    class SeismicTrace : public std::vector< float > {
    public:
        typedef float coordinate_type[3];
        
        float & operator()(const CoordinateID id) {
            return arrayAccessHelper(id,receiverCoords_);
        }        
        
        const float& operator()(const CoordinateID id) const {
            return static_cast< const float&>( const_cast< SeismicTrace& >(*this)(id) );
        }
        
        float & shot(const CoordinateID id) {
            return arrayAccessHelper(id,sourceCoords_);
        }
        
        const float & shot(const CoordinateID id) const {
            return static_cast< const float& >( const_cast< SeismicTrace& >(*this).shot(id) );
        }
        
        float& dt() { return dt_; };
        
        const float & dt() const {
            return static_cast< const float &>( const_cast< SeismicTrace&>(*this).dt() );
        }
        
        
    private:    
        
        float & arrayAccessHelper(const CoordinateID id, coordinate_type& array)  {
             switch( id ) {
                case seismic::X :
                    return array[0];
                    break;
                case seismic::Y :
                    return array[1];
                    break;
                case seismic::Z :
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