#ifndef VEED_SINGLETON_H
#define VEED_SINGLETON_H

/* Singleton for namespace vee
 */

#include "vePrerequisites.h"
#include <assert.h>

namespace veed {

    /* Template class for creating single-instance global classes
     */
    template <typename T> class SingletonVeed
    {
	private:
		/** \brief Explicit private copy constructor. This is a forbidden operation.*/
		SingletonVeed(const SingletonVeed<T> &);

		/** \brief Private operator= . This is a forbidden operation. */
		SingletonVeed& operator=(const SingletonVeed<T> &);
    
	protected:
        static T* ms_Singleton;

    public:
        SingletonVeed( void ) {

            assert( !ms_Singleton );
			ms_Singleton = static_cast< T* >( this );
        }
        ~SingletonVeed( void ) {

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