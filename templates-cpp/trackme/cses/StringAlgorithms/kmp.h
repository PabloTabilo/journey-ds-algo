#ifndef KMP_H
#define KMP_H

#include <vector>
#include <string>

struct kmp{
    std::vector<int> lps; //pi_s
    std::string t;
    int n;
    kmp(std::string & pattern, std::string & a);
    void build();
    std::vector<int> getLps(); // pi_s
};

#endif
