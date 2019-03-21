#ifndef CACTUS_GRADOP_HPP
#define CACTUS_GRADOP_HPP

class GradOp {
public:
    virtual int backward()=0;
    virtual std::vector<GradOp*> oplist() = 0;
    virtual void reback() = 0;
};

#endif