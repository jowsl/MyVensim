/*!
 \file Bridge.h
 \brief The classes Handle and Body implements "bridge" design pattern (also known as 
	"handle/body idiom").The class Body was implemented based on the class teCounted
	writed by Ricardo Cartaxo and Gilberto C�mara and founded in the geographic library TerraLib.
 \author Prof. Tiago Garcia de Senna Carneiro - UFOP, MG, Brazil
*/

#ifndef HANDLE_BODY_H
#define HANDLE_BODY_H

/** 
 * \brief
 *
 * The classes Handle and Body implements the "bridge" design pattern (also known as
 * "handle/body idiom").
 * 
 */

template <class T> 
class Handle {
public:	
    Handle<T>(){  
        pImpl_ = new T; 
        pImpl_->attach();  
    }
    
    virtual ~Handle<T>(){ 
        pImpl_->detach(); 	
    }

    Handle<T>( const Handle& hd ):pImpl_( hd.pImpl_ ) { 
        pImpl_->attach();  
    }

    Handle<T>& operator=( const Handle& hd) {
        if ( this != &hd ) {
            hd.pImpl_->attach();
            pImpl_->detach();	
            pImpl_  = hd.pImpl_;
        }
        return *this;
    }
protected:
    T *pImpl_; 
};

/**
 * \brief
 * 
 * The class Implementation was implemented based on the class teCounted writed by Ricardo Cartaxo 
 * and Gilberto C�mara and founded in the geographic library TerraLib.
 */

class Body {	
public:
    Body(): refCount_ ( 0 ){}

    void attach () { refCount_++; }

    void detach (){	
        if ( --refCount_ == 0 ) { 
            delete this; 
        }
    }

    int refCount(){ return refCount_; }

    virtual ~Body(){}

private:
    Body(const Body&);
    Body& operator=(const Body&){return *this;}
    int refCount_; 
};

#endif

