#ifndef STATUS_CODE_H_
#define STATUS_CODE_H_

typedef enum{
    OK,
    InputError,
    FlagError,
    MemoryError,
    OverFlowError,
    OpenFileError,
    DivisionByZero,
    PointerToNullError,
    DoesntExist,
    Missing
}status_code;

#endif