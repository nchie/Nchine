//
// Created by aejt on 11/23/17.
//

#pragma once

#include <thread>
#include <cstddef>
#include <functional>
#include <utility>
#include "../Utilities/locked_queue.h"

namespace Nchine
{
    class BinaryLoader {
        // A LoadTask holds the identifier to be loaded, and also the callback that should be called once it has been loaded
        typedef std::pair<std::string, std::function<void(std::vector<std::byte> &&)> > LoadTask;
        typedef locked_queue<LoadTask> LoadQueue;
    private:
        std::thread m_thread;
        LoadQueue m_queue; // TODO: Make thread-safe

    public:
        BinaryLoader() : m_thread(&BinaryLoader::load_loop, this) { }
        virtual ~BinaryLoader() { m_thread.join(); }

        // Copy constructors: deleted
        BinaryLoader& operator=(const BinaryLoader& other) = delete;
        BinaryLoader(const BinaryLoader& other) = delete;

        // Move constructors: deleted
        BinaryLoader(BinaryLoader&& other) noexcept = delete;
        BinaryLoader& operator=(BinaryLoader&& other) noexcept = delete;


        virtual std::vector<std::byte> load_binary(const std::string& identifier) = 0;

        void load_binary_async(const std::string &identifier, std::function<void(std::vector<std::byte> &&)> callback) {
            // Push a LoadTask onto the queue
            m_queue.push(LoadTask(identifier, callback));
        }

    private:
        void load_loop() {
            // Wait for m_queue to not be empty
            //m_queue.push(LoadTask("asd", [](std::vector<std::byte> &&){}));
            //LoadTask task = m_queue.pop();
            //while(true) {
            //    LoadTask task = m_queue.pop();
            //}

        }


    };
}