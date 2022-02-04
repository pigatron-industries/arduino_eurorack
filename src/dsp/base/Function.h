#ifndef Function_h
#define Function_h

namespace eurorack {

    class Function {
        public:
            Function() {}
            virtual float get(float phase) = 0;
    };

}

#endif