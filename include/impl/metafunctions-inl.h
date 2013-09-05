/**
 * @file metafunctions-inl.h
 * @brief Generic meta-functions needed in the implementation of the library
 */
#ifndef METAFUNCTIONS_INL_H
#define	METAFUNCTIONS_INL_H

namespace seismic {
    
    /**
     * @brief Computes the return type for an overload of the
     * subscript operator taking an instance of type T as input
     * 
     * @tparam T input type 
     */    
    template<class T>
    struct subscript_return_type {};
    
    /**
     * @brief Aggregates the information on subscript return type
     * to a generic class. Useful for named enumerations.
     * 
     * @tparam input type
     */
    template<class T>
    struct SubscriptReturnTypeAggregator {
        
        typedef typename subscript_return_type<T>::type type;
        
        SubscriptReturnTypeAggregator(T value) : value_(value) {}
        
        const T value_;
    };
    
    /**
     * @brief Convenience function to deduce type T and instantiate a 
     * SubscriptReturnTypeAggregator<T> object
     * 
     * @tparam input type
     * 
     * @param id value
     * @return SubscriptReturnTypeAggregator<T> 
     */
    template<class T>
    SubscriptReturnTypeAggregator<T> field(T id) {
        return SubscriptReturnTypeAggregator<T>(id);
    }
    
}

#endif	/* METAFUNCTIONS_INL_H */

