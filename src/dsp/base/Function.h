#ifndef Function_h
#define Function_h

class Function {
    public:
        Function() {}
        virtual float get(float phase) = 0;
};

#endif