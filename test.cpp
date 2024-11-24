#include "test.h"

bool test::checkPassword(QString pass){
    if(regExPass.match(pass).hasMatch()&&pass.size()<=16){
        return true;
     }
    else
     {
      return false;
     }
}
