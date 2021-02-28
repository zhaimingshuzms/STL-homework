#ifndef SJTU_EXCEPTIONS_HPP
#define SJTU_EXCEPTIONS_HPP

#include <cstddef>
#include <cstring>
#include <string>

namespace sjtu {

    class exceptions {
    protected:
        const std::string variant = "";
        std::string detail = "";
    public:
        exceptions() {}
        exceptions(const exceptions &ec) : variant(ec.variant), detail(ec.detail) {}
        virtual std::string what() {
            return variant + " " + detail;
        }
    };

    class index_out_of_bound : public exceptions {
        /* __________________________ */
    };

    class runtime_error : public exceptions {
        /* __________________________ */
    };

    class invalid_iterator : public exceptions {
        /* __________________________ */
    };

    class container_is_empty : public exceptions {
        /* __________________________ */
    };
}

#endif
