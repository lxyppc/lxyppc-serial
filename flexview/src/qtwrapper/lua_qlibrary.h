#ifndef LUA_QLIBRARY_H
#define LUA_QLIBRARY_H
#include "lua_qt_wrapper.hpp"
#include "boost/function.hpp"
#include "luabind/class_info.hpp"
using namespace luabind;

/**
  example for invoke dll function

  in the test.dll:
  int test_func(void* input, int input_len, void* output, int* output_len);

  input       input buffer
  input_len   input buffer content size
  output      output buffer, when this value is NULL, espect size will fill in the output_len
  output_len  output buffer content size, before invoke, this value is output buffer size, after
              invoke, it contains the content length in output buffer. When the output buffer size
              is less than required size, the actual buffer size will be fill in the output_len


  in the lua

  local func = QLibrary.resolve("test.dll", "test_func")
  local res = func("123123")  // the result will convert to string
  local result = func.result  // the dll function return code

  local res = func({1,2,3,4,5,6,7})  // the result will convert to table
  local result = func.result         // the dll function return code

  */

// define a involer class
struct QInvoker
{
    QInvoker():m_pfunc(0){}
    QInvoker(const QInvoker& r):m_pfunc(r.m_pfunc){}
    QInvoker(void* pfn):m_pfunc(pfn){}
    QInvoker(uint32_t v):m_pfunc((void*)v){}

    uint32_t value() const {  return (uint32_t)m_pfunc; }
    int result() const { return m_result; }

    int make_call(const QByteArray& input, QByteArray& output)
    {
        if(m_pfunc)
        {
            int set_size = 1024;
            int size = set_size;
            int r = 0;
            output.resize(size);
            r = helper(input.constData(), input.size(), output.data(), &size);
            if(size>set_size && r == 0){
                output.resize(size);
                r = helper(input.constData(), input.size(), output.data(), &size);
            }else{
                output.resize(size);
            }
            m_result = r;
            return r;
        }
        return -1;
    }

    int make_call(const QString& input, QString& output)
    {
        if(m_pfunc)
        {
            QTextCodec* codec = 0;
            codec = QTextCodec::codecForLocale();
            QByteArray arr, result;
            if(codec){
                arr = codec->fromUnicode(input);
            }else{
                arr = arr.data();
            }
            int r = make_call(arr, result);
            if(codec)
            {
                output = codec->toUnicode(result);
            }else{
                output = result.data();
            }
            return r;
        }
        return -1;
    }

protected:
    int helper(const void* input, int in_len, void* output, int* out_len)
    {
        if(!m_pfunc)
        {
            return -1;
        }
        typedef int(* pfn_t)(const void*, int, void*, int*);
        pfn_t fn = (pfn_t)m_pfunc;
        return fn(input, in_len, output, out_len);
    }
private:
    void*  m_pfunc;
    int    m_result;
};

typedef class_<QInvoker>                              LQInvoker;
typedef class_<QLibrary, QObject>                     LQLibrary;

LQInvoker lqinvoker();
LQLibrary lqlibrary();

#endif
