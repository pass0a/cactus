#ifndef CACTUS_GRADOP_HPP
#define CACTUS_GRADOP_HPP

class GradOp {
public:
    virtual int backward()=0;
};

#endif