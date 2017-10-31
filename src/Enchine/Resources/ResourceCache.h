#pragma once


#include <string>
#include <map>
#include <vector>
#include <queue>
#include <utility>
#include <optional>
#include <functional>

#include <iostream>


namespace Enchine {


    template<typename T>
    class ResourceCache;

    template<typename T>
    class Resource {
        friend class ResourceCache<T>;

    private:
        unsigned int m_id;
        ResourceCache<T> *m_cache;
        bool m_active;

        Resource(ResourceCache<T> *cache, unsigned int id) : m_cache(cache),
                                                     m_id(id),
                                                     m_active(true) {
            m_cache->m_objects[m_id].references++;
        }

    public:
        ~Resource() {
            if(m_active) {
                m_cache->m_objects[m_id].references--;
            }
        }

        // Copy constructor
        Resource(const Resource<T> &other) : m_cache(other.m_cache),
                                             m_id(other.m_id),
                                             m_active(true) {
            this->m_cache->m_objects[m_id].references++;
        }

        // Move constructor
        Resource(Resource &&other) noexcept : m_cache(other.m_cache),
                                              m_id(other.m_id),
                                              m_active(true) {
            other.m_active = false;
        }

        // Copy assignment
        Resource &operator=(const Resource& other) {
            // TODO: Restrict self assignment?
            this->m_id = other.m_id;
            this->m_cache = other.m_cache;
            this->m_cache->m_objects[m_id].references++;
            this->m_active = true;

            return *this;
        }

        // Move assignment
        Resource &operator=(Resource &&other) noexcept {
            // TODO: Restrict self assignment?
            this->m_id = other.m_id;
            this->m_cache = other.m_cache;
            this->m_active = true;
            other.m_active = false;

            return *this;
        }

        T &operator*() {
            return m_cache->get_resource(m_id);
        }

        T *operator->() {
            return &m_cache->get_resource(m_id);
        }

        bool is_valid() const noexcept {
            return m_active && m_cache->contains(m_id);
        }

        unsigned int reference_count() {
            return this->m_cache->m_objects[m_id].references;
        }

        explicit operator bool() const noexcept {
            return m_cache->contains(m_id);
        }

    };



    template<typename T>
    class ResourceCache {
        friend class Resource<T>;

        struct EntryData {
            std::optional<T> resource;
            unsigned int references = 0;

            EntryData() : resource({}) {}

            EntryData(T &&resource) : resource(std::move(resource)) {}
        };

    private:
        std::vector<EntryData> m_objects;
        std::map<std::string, unsigned int> m_indexmapping;
        std::optional<T> m_default_object = {};

        std::function<void(const std::string &)> m_notify_missing_resource;

    public:
        ResourceCache(std::function<void(const std::string &)> &&notify_missing_resource) : m_notify_missing_resource(notify_missing_resource) {}

        ~ResourceCache() = default;

        void set_default(T &&default_object)
        /*TODO: requires !std::is_lvalue_reference<T>::value*/
        {
            m_default_object = std::move(default_object);
        }

        template<typename... Args>
        void emplace_default(Args... args) {
            m_default_object = T(args...);
        }

        void reserve(std::size_t count) {
            m_objects.reserve(count);
        }

        T &get_default() const {
            return *m_default_object;
        }

        Resource<T> get_resource(const std::string &name) {
            auto resource = m_indexmapping.find(name);

            // If resource has an index (has been loaded before)
            if (resource != m_indexmapping.end()) {
                unsigned int id = resource->second;

                // If resource at index isn't currently loaded, place it in the load queue
                if (!contains(id)) {
                    m_notify_missing_resource(name);
                }

                // Return resource handle (even though it might not be loaded)
                return Resource<T>(this, id);
            } else {
                // Generate new id
                auto id = static_cast<unsigned int>(m_objects.size());

                // Place empty entry at back
                m_objects.emplace_back();

                // Map name to id of empty entry
                m_indexmapping.emplace(name, id);

                // Notify external that we're missing a resource
                m_notify_missing_resource(name);

                // Return resource handle even though it's not yet loaded
                return Resource<T>(this, id);
            }
        }

        Resource<T> load(std::string name, T &&resource)
        /*TODO: requires !std::is_lvalue_reference<T>::value*/
        {
            auto resource_entry = m_indexmapping.find(name);
            if (resource_entry != m_indexmapping.end()) {
                // Name exists
                unsigned int id = resource_entry->second;
                m_objects[id].resource = std::move(resource); // TODO: Is move necessary?
                return Resource<T>(this, id);
            } else {
                auto id = static_cast<unsigned int>(m_objects.size());
                m_indexmapping.emplace(name, id);
                m_objects.emplace_back(std::move(resource));  // TODO: Is move necessary?
                return Resource<T>(this, id);
            }
        }

        void unload_all() {
            //m_objects.clear();
            for (auto &object : m_objects) {
                object.resource = {};
            }
        }

    private:
        bool contains(unsigned int id) const {
            return (m_objects.size() > id) && (m_objects[id].resource);
        }

        T &get_resource(unsigned int id) {
            if (contains(id))  // Contains resource
            {
                return *m_objects[id].resource;
            } else if (m_default_object) // Has default resource
            {
                return *m_default_object;
            } else // No default resource
            {
                throw std::out_of_range("Invalid resource dereference (no default)");
            }
        }
    };
}
