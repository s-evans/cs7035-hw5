//
// FILENAME: identity.hpp
//

#ifndef IDENTITY_H
#define IDENTITY_H

template<class T>
struct identity {
    using type = T;
    static inline constexpr type get() {
        return 1;
    }
};

#endif // IDENTITY_H
