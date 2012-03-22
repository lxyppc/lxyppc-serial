// Copyright (c) 2005 Daniel Wallin, Arvid Norberg

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
// ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
// SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
// ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

#include <iostream>
#include <cstring>

extern "C"
{
    #include "lauxlib.h"
    #include "lualib.h"
}

#include <luabind/open.hpp>
#include "test.hpp"

extern "C" struct lua_State;

void test_main(lua_State*);
void test_abstract_base_main(lua_State*);
void test_adopt_main(lua_State*);
void test_adopt_wrapper_main(lua_State*);
void test_attributes_main(lua_State*);
void test_automatic_smart_ptr_main(lua_State*);
void test_back_reference_main(lua_State*);
void test_builtin_converters_main(lua_State*);
void test_class_info_main(lua_State*);
void test_collapse_converter_main(lua_State*);
void test_const_main(lua_State*);
void test_construction_main(lua_State*);
void test_create_in_thread_main(lua_State*);
void test_def_from_base_main(lua_State*);
void test_dynamic_type_main(lua_State*);
void test_exception_handlers_main(lua_State*);
void test_exceptions_main(lua_State*);
void test_extend_class_in_lua_main(lua_State*);
void test_free_functions_main(lua_State*);
void test_has_get_pointer_main(lua_State*);
void test_held_type_main(lua_State*);
void test_implicit_cast_main(lua_State*);
void test_implicit_raw_main(lua_State*);
void test_iterator_main(lua_State*);
void test_lua_classes_main(lua_State*);
void test_null_pointer_main(lua_State*);
void test_object_main(lua_State*);
void test_operators_main(lua_State*);
void test_policies_main(lua_State*);
void test_private_destructors_main(lua_State*);
void test_properties_main(lua_State*);
void test_scope_main(lua_State*);
void test_separation_main(lua_State*);
void test_set_instance_value_main(lua_State*);
void test_shadow_main(lua_State*);
void test_shared_ptr_main(lua_State*);
void test_simple_class_main(lua_State*);
void test_smart_ptr_attributes_main(lua_State*);
void test_super_leak_main(lua_State*);
void test_table_main(lua_State*);
void test_tag_function_main(lua_State*);
void test_typetraits_main(lua_State*);
void test_unsigned_int_main(lua_State*);
void test_user_defined_converter_main(lua_State*);
void test_value_wrapper_main(lua_State*);
void test_vector_of_object_main(lua_State*);
void test_virtual_inheritance_main(lua_State*);
void test_yield_main(lua_State*);

struct lua_state
{
    lua_state();
    ~lua_state();

    operator lua_State*() const;
	void check() const;

private:
    lua_State* m_state;
    int m_top;
};

lua_state::lua_state()
    : m_state(lua_open())
{
    luaopen_base(m_state);
#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
	 // lua 5.1 or newer
	 luaL_openlibs(m_state);
#else
	 // lua 5.0.2 or older
    lua_baselibopen(m_state);
#endif
    m_top = lua_gettop(m_state);
    luabind::open(m_state);
}

lua_state::~lua_state()
{
    lua_close(m_state);
}

void lua_state::check() const
{
    TEST_CHECK(lua_gettop(m_state) == m_top);
}

lua_state::operator lua_State*() const
{
    return m_state;
}

int pcall_handler(lua_State* L)
{
	return 1;
}

void dostring(lua_State* state, char const* str)
{
    lua_pushcclosure(state, &pcall_handler, 0);

    if (luaL_loadbuffer(state, str, std::strlen(str), str))
    {
        std::string err(lua_tostring(state, -1));
        lua_pop(state, 2);
		throw err;
    }

    if (lua_pcall(state, 0, 0, -2))
    {
        std::string err(lua_tostring(state, -1));
        lua_pop(state, 2);
		throw err;
    }

    lua_pop(state, 1);
}

bool tests_failure = false;

void report_failure(char const* err, char const* file, int line)
{
	std::cerr << file << ":" << line << "\"" << err << "\"\n";
        tests_failure = true;
}

int main()
{
	lua_state L;
	try
	{
//            test_abstract_base_main(L);
//            L.check();
//            test_adopt_main(L);
//            L.check();
//            test_adopt_wrapper_main(L);
//            L.check();
//            test_attributes_main(L);
//            L.check();
//            //test_automatic_smart_ptr_main(L);
//            //L.check();
//            test_back_reference_main(L);
//            L.check();
//            test_builtin_converters_main(L);
//            L.check();
//            test_class_info_main(L);
//            L.check();
//            test_collapse_converter_main(L);
//            L.check();
//            test_const_main(L);
//            L.check();
//            test_construction_main(L);
//            L.check();
//            test_create_in_thread_main(L);
//            L.check();
//            test_def_from_base_main(L);
//            L.check();
//            test_dynamic_type_main(L);
//            L.check();
//            test_exception_handlers_main(L);
//            L.check();
//            test_exceptions_main(L);
//            L.check();
//            test_extend_class_in_lua_main(L);
//            L.check();
//            test_free_functions_main(L);
//            L.check();
//            //test_has_get_pointer_main(L);
//            //L.check();
//            test_held_type_main(L);
//            L.check();
//            test_implicit_cast_main(L);
//            L.check();
//            test_implicit_raw_main(L);
//            L.check();
//            test_iterator_main(L);
//            L.check();
//            test_lua_classes_main(L);
//            L.check();
//            test_null_pointer_main(L);
//            L.check();
            test_object_main(L);
            L.check();
//            test_operators_main(L);
//            L.check();
//            test_policies_main(L);
//            L.check();
//            test_private_destructors_main(L);
//            L.check();
//            test_properties_main(L);
//            L.check();
//            test_scope_main(L);
//            L.check();
//            test_separation_main(L);
//            L.check();
//            test_set_instance_value_main(L);
//            L.check();
//            test_shadow_main(L);
//            L.check();
//            test_shared_ptr_main(L);
//            L.check();
//            test_simple_class_main(L);
//            L.check();
//            test_smart_ptr_attributes_main(L);
//            L.check();
//            test_super_leak_main(L);
//            L.check();
//            test_table_main(L);
//            L.check();
//            test_tag_function_main(L);
//            L.check();
//            test_typetraits_main(L);
//            L.check();
//            test_unsigned_int_main(L);
//            L.check();
//            test_user_defined_converter_main(L);
//            L.check();
//            test_value_wrapper_main(L);
//            L.check();
//            test_vector_of_object_main(L);
//            L.check();
//            test_virtual_inheritance_main(L);
//            L.check();
//            test_yield_main(L);
//            L.check();
            return tests_failure ? 1 : 0;
	}
	catch (luabind::error const& e)
	{
		std::cerr << "Terminated with exception: \"" << e.what() << "\"\n"
			<< lua_tostring(e.state(), -1) << "\n";
		return 1;
	}
	catch (std::exception const& e)
	{
		std::cerr << "Terminated with exception: \"" << e.what() << "\"\n";
		return 1;
	}
	catch (...)
	{
		std::cerr << "Terminated with unknown exception\n";
		return 1;
	}
}

