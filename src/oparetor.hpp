/*
Copyright(C) 2018 liuwenjun.All rights reserved.
*/

#ifndef SRC_OPARETOR_HPP_
#define SRC_OPARETOR_HPP_

namespace cactus {

class oparetor {
public:
    virtual void compute(std::vector<std::shared_ptr<cactus::tensor>>& ) = 0;
};
}

#endif  // SRC_OPARETOR_HPP_
