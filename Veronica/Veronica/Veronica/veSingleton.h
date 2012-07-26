#ifndef VEE_SINGLETON_H
#define VEE_SINGLETON_H

/* Singleton for namespace vee
 */

#include "vePrerequisites.h"
#include <assert.h>

namespace vee {

    /* Template class for creating single-instance global classes
     */
    template <typename T> class SingletonVee
    {
	private:
		/** \brief Explicit private copy constructor. This is a forbidden operation.*/
		SingletonVee(const SingletonVee<T> &);

		/** \brief Private operator= . This is a forbidden operation. */
		SingletonVee& operator=(const SingletonVee<T> &);
    
	protected:
        static T* ms_Singleton;

    public:
        SingletonVee( void ) {

            assert( !ms_Singleton );
			ms_Singleton = static_cast< T* >( this );
        }
        ~SingletonVee( void ) {

			assert( ms_Singleton );
			ms_Singleton = 0;
		}

        static T& getSingleton( void ) {

			assert( ms_Singleton );  
			return ( *ms_Singleton );
		}

        static T* getSingletonPtr( void ) { 

			return ms_Singleton; 
		}
    };
};

#endif