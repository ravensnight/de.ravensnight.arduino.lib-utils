#ifndef __Ref_h__
#define __Ref_h__

namespace ravensnight::utils {

    template <class T>
    class Ref {

        private:

            T* _ptr = 0;
            bool _owned = false;

        public:

            Ref() {
                _ptr = 0;
                _owned = false;
            }

            Ref(T* ptr) {
                _ptr = ptr;
                _owned = true;
            };

            ~Ref() {
                clear();
            }

            void clear() {
                if ((_owned) && (_ptr != 0)) {
                    delete _ptr;
                    _ptr = 0;
                    _owned = false;
                }
            }

            bool isNULL() {
                return _ptr == 0;
            }

            T* get() const {
                return _ptr;
            }

            /**
             * Creates a weak reference. 
             * Linked object will not be deleted with destruction or reference
             */
            void attach(T* ptr) {
                clear();

                _ptr = ptr;
                _owned = false;
            }

            /**
             * Creates a strong reference. 
             * Linked object will be deleted with destruction of reference
             */
            void aggregate(T* ptr) {
                clear();

                _ptr = ptr;
                _owned = true;
            }

            Ref<T>& operator =(T* ptr) {
                aggregate(ptr);
                return *this;
            }

            T& operator *() {
                return *_ptr;
            }
    };
}

#endif // __Ref_h__