#pragma once


namespace Enchine {

    template<typename T>
    class Cache;

    template<typename T>
    class Resource {
        friend class Cache<T>;

    private:
        unsigned int m_id;
        Cache<T> &m_cache;
        bool m_active;

        Resource(Cache<T> &cache, unsigned int id) : m_cache(cache),
                                                     m_id(id),
                                                     m_active(true) {
            m_cache.m_objects[m_id].references++;
        }

    public:
        ~Resource() {
            m_cache.m_objects[m_id].references--;
        }

        // Copy constructor
        Resource(const Resource &other) : m_cache(other.m_cache),
                                          m_id(other.m_id),
                                          m_active(true) {
            this->m_cache.m_objects[m_id].references++;
        }

        // Move constructor
        Resource(Resource &&other) : m_cache(other.m_cache),
                                     m_id(other.m_id),
                                     m_active(true) {
            other.m_active = false;
        }

        // Copy assignment
        Resource &operator=(const Resource &other) {
            this->m_id = other.m_id;
            this->m_cache = other.m_cache;
            this->m_cache.m_objects[m_id].references++;
            this->m_active = true;

            return *this;
        }

        // Move assignment
        Resource &operator=(Resource &&other) {
            this->m_id = other.m_id;
            this->m_cache = other.m_cache;
            this->m_active = true;
            other.m_active = false;

            return *this;
        }

        T &operator*() {
            return m_cache.get_resource(m_id);
        }

        T *operator->() {
            return &m_cache.get_resource(m_id);
        }

        bool is_valid() const noexcept {
            return m_active && m_cache.contains(m_id);
        }

        unsigned int reference_count() {
            return this->m_cache.m_objects[m_id].references;
        }

        explicit operator bool() const noexcept {
            return m_cache.contains(m_id);
        }

    };
}