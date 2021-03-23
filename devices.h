//#ifndef DEVICES_H
//#define DEVICES_H
#include "library.h"
#include "../prjLIB/prjEMETERSTRUCT/emeter-struct.h"
#if defined(_DT03M_RF_) // && defined(__PIC24FJxxxGA410__)
#include "functions-dt03mrf.h"
#endif
#if defined(_DT01M_RF_)
#include "functions-dt01mrf.h"
#endif
#if defined(_DT03P_RF_)
#include "functions-dt03prf.h"
#endif
#if defined(_DT01P_RF_)
#include "functions-dt01prf.h"
#endif

//#endif //DEVICES_H


