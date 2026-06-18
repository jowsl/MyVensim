
#ifndef HANDLE_BODY_H
#define HANDLE_BODY_H

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

