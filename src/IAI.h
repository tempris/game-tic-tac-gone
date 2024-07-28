#ifndef IAI_H
#define IAI_H

#include "Grid.h"

class IAI {
public:
    virtual ~IAI() = default;
    virtual void makeMove(IGrid& grid) = 0;
};

#endif // IAI_H
