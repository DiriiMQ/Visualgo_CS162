//
// Created by dirii on 14/04/2023.
//

#ifndef VISUALGO_CS162_TOSTRINGWITHPRECISION_HPP
#define VISUALGO_CS162_TOSTRINGWITHPRECISION_HPP

#include <sstream>

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 2)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return std::move(out).str();
}

#endif //VISUALGO_CS162_TOSTRINGWITHPRECISION_HPP
