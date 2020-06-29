#ifndef ERROR_INFO_H
#define ERROR_INFO_H
#include <string>
#include <map>

enum ErrorCode
{
    Unknown = -1,
    Success = 0,
    MallocFail = 1000,
    OpenCameraFail,
    GetExposureFail,
    SetExposureFail,
    GetVideoFpsFail,
    SetVideoFpsFail,
};

extern std::map<int, const char*> ErrorMsg;

class ErrorInfo
{
public:
    ErrorInfo()
    {
        set(Success);
    }
    ErrorInfo(int no)
    {
        set(no);
    }
    void set(int code)
    {
        _code = code;
        auto iter = ErrorMsg.find(code);
        if (iter == ErrorMsg.end()) {
            _msg = ErrorMsg[Unknown];
            return;
        }
        _msg = ErrorMsg[code];
    }
private:
    int _code;
    std::string _msg;
};

struct CameraError : public ErrorInfo
{
    using ErrorInfo::ErrorInfo;
};

class CustomException : public std::exception
{
public:
    CustomException(const std::string &msg)
        :_msg(msg)
    {}
    virtual const char * what() const noexcept override
    {
        return _msg.c_str();
    }
private:
    std::string _msg;
};

class CameraException : public CustomException
{
    using CustomException::CustomException;
};




#endif // ERROR_INFO_H
