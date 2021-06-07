
struct _OpCodeData {
 char* OpcodeNumber;
 char* Instruction;
 char format;
 char* FunctionCode;
};
typedef struct _OpCodeData OpCodeData;

OpCodeData search(char* binaryCode, char* functionCode);
