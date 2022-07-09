#ifndef Config_h
#define Config_h

#include <inttypes.h>
#include <EEPROM.h>

template <class T>
class ConfigField {
    public:
        int address = 0;
        int size = 0;
        T data;
};

class Config {
    public:
        static Config config;

        template<class T> 
        void load(ConfigField<T> &field) {
            if(field.size == 0) {
                field.address = nextAddress;
                field.size = sizeof(T);
            }

            EEPROM.get(field.address, field.data);
            nextAddress += field.size;
        }

        template<class T> 
        void save(ConfigField<T> &field) {
            EEPROM.put(field.address, field.data);
        }

    private:
        int nextAddress = 0;
};

#endif
