#include <numeric>
#include <map>
#include <random>

#ifndef MINIMARKOV_MINIMARKOV_HPP
#define MINIMARKOV_MINIMARKOV_HPP

template<
        class T,
        class Allocator = std::allocator<T>
> class MarkovChain {

public:
    using ValueType = T;
    using AllocatorType = Allocator;

public:
    explicit MarkovChain(const AllocatorType& allocator = AllocatorType())
    : chain{allocator}
    , gen{std::random_device{}()}
    {};
    MarkovChain(const MarkovChain&) = default;

    MarkovChain& operator=(const MarkovChain&) = default;

    ~MarkovChain() = default;

public:
    template<class Iterator>
    void Train(Iterator begin, Iterator end) {
        while(begin+1 != end) {
            ValueType& current = *begin;
            ValueType& next = *(begin+1);
            AddLink(current, next);
            begin++;
        }
    }

    std::vector<ValueType> Generate(std::size_t maxSize) {
        std::vector<ValueType> r{};
        r.reserve(maxSize);

        auto it = chain.begin();
        std::advance(it, std::uniform_int_distribution<>(0, chain.size())(gen));

        auto last = std::make_pair(it->first, true);
        for(int i = 1; i < maxSize; i++) {
            r.push_back(last.first);
            last = GenerateNext(last.first);
            if (!last.second)
                break;
        }
        std::cout << std::endl;
        return r;
    }

    void Clear() {
        chain.clear();
    }

private:
    void AddLink(const ValueType& a, const ValueType& b) {
        auto r = chain.insert({a, std::map<ValueType, int>{AllocatorType()}});
        std::map<ValueType, int>& link = r.first->second;
        auto linkReturn = link.insert({b, 1});
        if (linkReturn.second)
            return;
        linkReturn.first->second++;
    }

    std::pair<ValueType, bool> GenerateNext(const ValueType& value) {
        auto links = chain.find(value);
        if (links == chain.end())
            return std::make_pair(value, false);

        int sum = std::accumulate(
                links->second.begin(),
                links->second.end(),
                0,
                [](int value, const std::pair<ValueType, int>& p) {
                            return value + p.second;
                        });
        int choice = std::uniform_int_distribution<>(0, sum)(gen);

        auto link = links->second.begin();
        for(link; link != links->second.end(); link++) {
            choice -= link->second;
            if (link->second > choice)
                break;
        }

        return std::make_pair(link->first, true);
    }

private:
    std::map<ValueType, std::map<ValueType, int>> chain;
    std::mt19937 gen;
};

#endif //MINIMARKOV_MINIMARKOV_HPP
