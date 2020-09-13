#pragma once

namespace wklib
{
    namespace locks
    {
        class eresource
        {
        public:
            eresource();
            ~eresource();

            void lock_shared();
            void lock_exclusive();
            void release();
        private:
            ERESOURCE lock;
        };

        template <typename T>
        class auto_rw_lock
        {
        protected:
            explicit auto_rw_lock(T& lock_param) : lock{ lock_param }
            {}

            ~auto_rw_lock()
            {
                lock.release();
            }

            T& lock;
        };

        template <typename T>
        class auto_shared_rw_lock : public auto_rw_lock<T>
        {
        public:
            explicit auto_shared_rw_lock(T& lock_param) : auto_rw_lock{ lock_param }
            {
                lock.lock_shared();
            }
        };

        template <typename T>
        class auto_exclusive_rw_lock : public auto_rw_lock<T>
        {
        public:
            explicit auto_exclusive_rw_lock(T& lock_param) : auto_rw_lock{ lock_param }
            {
                lock.lock_exclusive();
            }
        };

        class mutex
        {
        public:
            mutex();
            void lock();
            void unlock();
        private:
            KMUTEX mtx;
        };
    }
}
