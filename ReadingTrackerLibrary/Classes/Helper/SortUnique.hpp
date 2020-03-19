//
//  SortUnique.hpp
//  ReadingTrackerLibrary
//
//  Created by Frobu on 3/19/20.
//  Copyright © 2020 Russell Goddard. All rights reserved.
//

#ifndef SortUnique_hpp
#define SortUnique_hpp

#include <vector>

namespace rtl {

    //TODO: this whole thing will probably look stupid to me in 6 months
    //had issue with std::unique not actually removing items even with custom comparator
    //forced to make my own
    template <typename T>
    void uniqueVector(std::vector<T>& input) {
        int index = 1;
        
        while (index < input.size()) {
            if (*input.at(index - 1) == *input.at(index)) {
                input.erase(std::begin(input) + index);
            }
            else {
                ++index;
            }
        }
        
        return;
    }

    template <typename T>
    bool sortPointers(T lhs, T rhs) {
        return *lhs < *rhs;
    }

    template <typename T>
    void SortUnique(std::vector<T>& input) {
        std::sort(std::begin(input), std::end(input), sortPointers<T>);
        uniqueVector(input);
        
        return;
    }
}

#endif /* SortUnique_hpp */
