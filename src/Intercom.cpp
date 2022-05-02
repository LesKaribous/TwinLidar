#include "Intercom.h"
#include <Arduino.h>

namespace Intercom{
    
    void init(){
        Serial1.begin(9600);
        Serial1.println("TwinLidar");

        
    }


} // namespace Intercom
