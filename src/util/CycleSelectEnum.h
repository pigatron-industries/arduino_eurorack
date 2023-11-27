#ifndef CycleSelectEnum_h
#define CycleSelectEnum_h

#include "CycleEnum.h"

template <class T>
class CycleSelectEnum : public CycleEnum<T> {
    public:
        bool autoSelect = true;
        bool selecting = false;
        T selectValue;

        CycleSelectEnum() : CycleEnum<T>() {
        }

        CycleSelectEnum(T value, T last) : CycleEnum<T>(value, last) {
        }

        void setAutoSelect(bool autoSelect) {
            this->autoSelect = autoSelect;
        }

        T cycle(int amount) {
            if(!selecting) {
                selecting = true;
                selectValue = this->value;
            }
            
            if(amount > 0) {
                selectValue = static_cast<T>((selectValue + 1)%(this->last + 1));
            } else if(amount < 0) {
                selectValue = static_cast<T>(selectValue > 0 ? selectValue - 1 : this->last);
            }

            if (autoSelect) {
                return select();
            }
            
            return selectValue;
        }

        T getSelectValue() {
            return selectValue;
        }

        T select() {
            selecting = false;
            this->value = selectValue;
            return this->value;
        }

};

#endif