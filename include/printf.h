#ifndef PRINTF_H
#define PRINTF_H

#include <cstdlib>
#include <vector>

#include "ValueContainer.h"

namespace My{

    int vprintf(const std::string fmt,std::vector<std::shared_ptr<ValueContainer>> args);

    std::string vsprintf(const std::string fmt,std::vector<std::shared_ptr<ValueContainer>> args);

    struct pass{template<typename...Args>explicit pass(Args&&...){}};//variadic expansion helper, from https://stackoverflow.com/a/23859730

    template<typename... Tn> std::vector<std::shared_ptr<ValueContainer>> to_vc_p_vector(Tn... targs){
        std::vector<std::shared_ptr<ValueContainer>> temp;
        pass {(temp.push_back(as_vcp(targs)),0)...};
        return temp;
    }

    template<typename... Tn> std::string sprintf(const std::string fmt,Tn... targs){
        return vsprintf(fmt,to_vc_p_vector(targs...));
    }

    template<typename... Tn> int printf(const std::string fmt,Tn... targs){
        return vprintf(fmt,to_vc_p_vector(targs...));
    }

}

#endif // PRINTF_H
