#ifndef __Ref_h__
#define __Ref_h__

#include <Arduino.h>
#include <assert.h>

namespace ravensnight::utils {

    enum class RefType : uint8_t {
        owned = 0,
        weak = 1
    };

    template <class T>
    class Ref {

        private:

            T* _ptr = 0;
            RefType _type = RefType::weak;

        public:

            /**
             * Creates an owned reference with given pointer.
             */
            Ref(T* ptr) {
                _ptr = ptr;
                _type = RefType::owned;
            };

            /**
             * Creates a reference with given pointer.
             */
            Ref(T* ptr, RefType type) {
                _ptr = ptr;
                _type = type;
            };

            /**
             * Creates new new empty reference.
             */
            Ref(RefType type) {
                _ptr = 0;
                _type = type;
            }

            /**
             * Creates a new reference from given ref.
             * Note: This will always be a weak reference.
             */
            Ref(Ref& ref) {
                _ptr = ref._ptr;
                _type = RefType::weak;
            }

            ~Ref() {
                clear();
            }

            /**
             * Cleanup object and set pointer to null.
             */
            void clear() {
                if ((_type == RefType::owned) && (_ptr != 0)) {
                    delete _ptr;
                    _ptr = 0;
                }
            }

            /**
             * Check if pointer is NULL
             */
            bool isNULL() const {
                return _ptr == 0;
            }

            /**
             * Return the pointer to origin object.
             */
            T* get() const {
                return _ptr;
            }

            /**
             * Assign a new reference according to previous set type.
             */
            void set(T* ptr) {
                clear();
                _ptr = ptr;
            }

            /**
             * Assign a new WEAK reference from given Ref object.
             * Note: It needs to be ensured, the given reference is cleared manually.
             */
            void set(Ref& ref) {
                clear();
                _ptr = ref._ptr;
                _type = RefType::weak;
            }

            Ref<T>& operator =(T* ptr) {
                set(ptr);
                return *this;
            }

            T& operator *() const {
                assert(_ptr != 0);
                return *_ptr;
            }

            uint8_t operator[] (size_t pos) {
                assert(_ptr != 0);
                uint8_t* p = (uint8_t*)_ptr;

                return p[pos];
            }

            T* operator ->() {
                assert(_ptr != 0);
                return _ptr;
            }
    };
}

#endif // __Ref_h__