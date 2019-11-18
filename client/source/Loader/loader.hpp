#ifndef LOADER_H_
#define LOADER_H_

#include "event.hpp"
#include "loader_abst.hpp"

class loader : public loader_abst {
 public:
    loader();
    int load_all() override;
};

#endif  // LOADER_H_
