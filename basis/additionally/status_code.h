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
    ItemExist,
    ItemDoesNotExist,
    PointerToNullError
}status_code;

#endif