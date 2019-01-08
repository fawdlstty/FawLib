////////////////////////////////////////////////////////////////////////////////
//
// Class Name:  Encoding
// Description: 编码转换类
// Class URI:   https://github.com/fawdlstty/FawLib
// Author:      Fawdlstty
// Author URI:  https://www.fawdlstty.com/
// License:     MIT
// Last Update: Jan 08, 2019
//
////////////////////////////////////////////////////////////////////////////////

#ifndef FAWLIB__STRING_HPP__
#define FAWLIB__STRING_HPP__



#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <cstdint>
//#include <algorithm>
#include <tchar.h>

#include "Encoding.hpp"



namespace faw {
	class String {
	public:
		String () {}
		String (const char _c, size_t _len = 1) { m_str.assign (_len, (TCHAR) _c); }
		String (const wchar_t _c, size_t _len = 1) { m_str.assign (_len, (TCHAR) _c); }
		String (const char *_s, size_t _len = std::string::npos) {
			if (_len == std::string::npos) {
				m_str = Encoding::gb18030_to_T (std::string_view (_s));
			} else {
				m_str = Encoding::gb18030_to_T (std::string_view (_s, _len));
			}
		}
		String (const wchar_t *_s, size_t _len = std::wstring::npos) {
			if (_len == std::wstring::npos) {
				m_str = Encoding::utf16_to_T (std::wstring_view (_s));
			} else {
				m_str = Encoding::utf16_to_T (std::wstring_view (_s, _len));
			}
		}
		String (const std::string &_s): m_str (Encoding::gb18030_to_T (std::string_view (_s))) {}
		String (const std::wstring &_s): m_str (Encoding::utf16_to_T (std::wstring_view (_s))) {}
#if _HAS_CXX17
		String (const std::string_view &_s): m_str (Encoding::gb18030_to_T (_s)) {}
		String (const std::wstring_view &_s): m_str (Encoding::utf16_to_T (_s)) {}
#endif
		String (const String &_s): m_str (_s.m_str) {}
		String (const String *_s): m_str (_s->m_str) {}
		//
		String &operator= (const char *_s) { m_str = Encoding::gb18030_to_T (std::string_view (_s)); return *this; }
		String &operator= (const wchar_t *_s) { m_str = Encoding::utf16_to_T (std::wstring_view (_s)); return *this; }
		String &operator= (const std::string &_s) { m_str = Encoding::gb18030_to_T (std::string_view (_s)); return *this; }
		String &operator= (const std::wstring &_s) { m_str = Encoding::utf16_to_T (std::wstring_view (_s)); return *this; }
		String &operator= (const String &_s) { m_str = _s.m_str; return *this; }
		String &operator= (const String *_s) { m_str = _s->m_str; return *this; }
#if _HAS_CXX17
		String &operator= (const std::string_view &_s) { m_str = Encoding::gb18030_to_T (_s); return *this; }
		String &operator= (const std::wstring_view &_s) { m_str = Encoding::utf16_to_T (_s); return *this; }
#endif
		//
		String &operator+= (const char _c) { m_str += (TCHAR) _c; return *this; }
		String &operator+= (const wchar_t _c) { m_str += (TCHAR) _c; return *this; }
		String &operator+= (const char *_s) { m_str += Encoding::gb18030_to_T (std::string_view (_s)); return *this; }
		String &operator+= (const wchar_t *_s) { m_str += Encoding::utf16_to_T (std::wstring_view (_s)); return *this; }
		String &operator+= (const std::string &_s) { m_str += Encoding::gb18030_to_T (std::string_view (_s)); return *this; }
		String &operator+= (const std::wstring &_s) { m_str += Encoding::utf16_to_T (std::wstring_view (_s)); return *this; }
		String &operator+= (const String &_s) { m_str += _s.m_str; return *this; }
		String &operator+= (const String *_s) { m_str += _s->m_str; return *this; }
#if _HAS_CXX17
		String &operator+= (const std::string_view &_s) { m_str += Encoding::gb18030_to_T (_s); return *this; }
		String &operator+= (const std::wstring_view &_s) { m_str += Encoding::utf16_to_T (_s); return *this; }
#endif
		//
		String operator+ (const char _c) { String _o (this); _o.m_str += (TCHAR) _c; return _o; }
		String operator+ (const wchar_t _c) { String _o (this); _o.m_str += (TCHAR) _c; return _o; }
		String operator+ (const char *_s) { String _o (this); _o.m_str += Encoding::gb18030_to_T (std::string_view (_s)); return _o; }
		String operator+ (const wchar_t *_s) { String _o (this); _o.m_str += Encoding::utf16_to_T (std::wstring_view (_s)); return _o; }
		String operator+ (const std::string &_s) { String _o (this); _o.m_str += Encoding::gb18030_to_T (std::string_view (_s)); return _o; }
		String operator+ (const std::wstring &_s) { String _o (this); _o.m_str += Encoding::utf16_to_T (std::wstring_view (_s)); return _o; }
		String operator+ (const String &_s) { String _o (this); _o.m_str += _s.m_str; return _o; }
		String operator+ (const String *_s) { String _o (this); _o.m_str += _s->m_str; return _o; }
#if _HAS_CXX17
		String operator+ (const std::string_view &_s) { String _o (this); _o.m_str += Encoding::gb18030_to_T (_s); return _o; }
		String operator+ (const std::wstring_view &_s) { String _o (this); _o.m_str += Encoding::utf16_to_T (_s); return _o; }
#endif
		//
		friend String operator+ (const char _c, String &_o) { _o.m_str.insert (_o.m_str.begin (), (TCHAR) _c); }
		friend String operator+ (const wchar_t _c, String &_o) { _o.m_str.insert (_o.m_str.begin (), (TCHAR) _c); }
		friend String operator+ (const char *_s, String &_o) { String _so (_s); _so.m_str += _o.m_str; return _so; }
		friend String operator+ (const wchar_t *_s, String &_o) { String _so (_s); _so.m_str += _o.m_str; return _so; }
		friend String operator+ (const std::string &_s, String &_o) { String _so (_s); _so.m_str += _o.m_str; return _so; }
		friend String operator+ (const std::wstring &_s, String &_o) { String _so (_s); _so.m_str += _o.m_str; return _so; }
#if _HAS_CXX17
		friend String operator+ (const std::string_view &_s, String &_o) { String _so (_s); _so.m_str += _o.m_str; return _so; }
		friend String operator+ (const std::wstring_view &_s, String &_o) { String _so (_s); _so.m_str += _o.m_str; return _so; }
#endif
		//
		String operator* (size_t n) {
			String _s;
			if (n == 0 || n == string_t::npos)
				return _s;
			while (n-- > 0)
				_s.m_str += m_str;
			return _s;
		}
		String &operator*= (size_t n) {
			if (n == 0 || n == string_t::npos) {
				m_str.clear ();
			} else {
				string_t _str = m_str;
				while (--n > 0)
					m_str += _str;
			}
			return *this;
		}
		bool operator== (String &_o) { return m_str == _o.m_str; }
		bool is_equal (String &_o) { return m_str == _o.m_str; }
		bool is_equal_nocase (String &_o) {
			size_t size = m_str.size ();
			if (size != _o.m_str.size ())
				return false;
			for (size_t i = 0; i < size; ++i) {
				if (m_str [i] == _o.m_str [i]) {
					continue;
				} else if (m_str [i] >= _T ('a') && m_str [i] <= _T ('z')) {
					if (m_str [i] - _T ('a') + _T ('A') != _o.m_str [i])
						return false;
				} else if (m_str [i] >= _T ('A') && m_str [i] <= _T ('Z')) {
					if (m_str [i] - _T ('A') + _T ('a') != _o.m_str [i])
						return false;
				} else {
					return false;
				}
			}
			return true;
		}
		virtual ~String () {}
		//
		bool empty () const { return m_str.empty (); }
		void clear () { m_str.clear (); }
		void free () { string_t _str = _T (""); _str.swap (m_str); }
		size_t size () const { return m_str.size (); }
		TCHAR &operator[] (size_t n) { return m_str [n]; }
		LPCTSTR c_str () const { return m_str.c_str (); }
		const string_t &str () const { return m_str; }
		string_view_t str_view () const { return string_view_t (m_str); }
		std::string stra () const { return Encoding::T_to_gb18030 (m_str); }
		std::wstring strw () const { return Encoding::T_to_utf16 (m_str); }
		//
		string_t::iterator begin () { return m_str.begin (); }
		string_t::iterator end () { return m_str.end (); }
		string_t::const_iterator cbegin () { return m_str.cbegin (); }
		string_t::const_iterator cend () { return m_str.cend (); }
		string_t::reverse_iterator rbegin () { return m_str.rbegin (); }
		string_t::reverse_iterator rend () { return m_str.rend (); }
		string_t::const_reverse_iterator crbegin () { return m_str.crbegin (); }
		string_t::const_reverse_iterator crend () { return m_str.crend (); }
		//
		String &operator>> (TCHAR &n) {
			if (m_str.empty ()) {
				n = _T ('\0');
			} else {
				n = *m_str.rbegin ();
				m_str.pop_back ();
			}
			return *this;
		}
		String &operator<< (TCHAR n) {
			m_str.push_back (n);
			return *this;
		}
		friend String &operator>> (TCHAR n, String &_o) {
			_o.m_str.insert (_o.m_str.begin (), n);
			return _o;
		}
		friend String &operator<< (TCHAR &n, String &_o) {
			if (_o.m_str.empty ()) {
				n = _T ('\0');
			} else {
				n = *_o.m_str.begin ();
				_o.m_str.erase (_o.m_str.begin ());
			} return _o;
		}
		String &operator>> (intptr_t &n) {
			n = 0;
			intptr_t _level = 1;
			for (size_t i = m_str.size () - 1; i != string_t::npos; --i) {
				if (m_str[i] >= _T ('0') && m_str[i] <= _T ('9')) {
					n += _level * (m_str[i] - _T ('0'));
					m_str.erase (m_str.begin () + i);
					_level *= 10;
				} else if (m_str[i] == _T ('-')) {
					n = 0 - n;
					m_str.erase (m_str.begin () + i);
					break;
				} else {
					break;
				}
			}
			return *this;
		}
		String &operator<< (intptr_t n) {
			String _s;
			bool _sign = (n < 0);
			while (n > 0) {
				_s += (TCHAR) ((n % 10) + _T ('0'));
				n /= 10;
			}
			if (_sign)
				_s += _T ('-');
			_s.reverse_self ();
			*this += _s;
			return *this;
		}
		friend String &operator>> (intptr_t n, String &_o) {
			String _s = (n == 0 ? _T ("0") : _T (""));
			bool _sign = (n < 0);
			while (n > 0) {
				_s += (TCHAR) ((n % 10) + _T ('0'));
				n /= 10;
			}
			if (_sign)
				_s += _T ('-');
			_s.reverse_self ();
			_o.m_str.insert (_o.m_str.begin (), _s.m_str.begin (), _s.m_str.end ());
			return _o;
		}
		friend String &operator<< (intptr_t &n, String &_o) {
			n = 0;
			if (_o.m_str.size () == 0)
				return _o;
			bool _sign = (_o.m_str[0] == _T ('-'));
			size_t i = (_sign ? 1 : 0);
			for (; i < _o.m_str.size () && _o.m_str[i] >= _T ('0') && _o.m_str[i] <= _T ('9'); ++i)
				n = n * 10 + (_o.m_str[i] - _T ('0'));
			if (_sign)
				n = 0 - n;
			_o.m_str.erase (_o.m_str.begin (), _o.m_str.begin () + i);
			return _o;
		}
		String &operator>> (uintptr_t &n) {
			n = 0;
			uintptr_t _level = 1;
			for (size_t i = m_str.size () - 1; i != string_t::npos; --i) {
				if (m_str[i] >= _T ('0') && m_str[i] <= _T ('9')) {
					n += _level * (m_str[i] - _T ('0'));
					m_str.erase (m_str.begin () + i);
					_level *= 10;
				} else {
					break;
				}
			}
			return *this;
		}
		String &operator<< (uintptr_t n) {
			String _s;
			while (n > 0) {
				_s += (TCHAR) ((n % 10) + _T ('0'));
				n /= 10;
			}
			_s.reverse_self ();
			*this += _s;
			return *this;
		}
		friend String &operator>> (uintptr_t n, String &_o) {
			String _s = (n == 0 ? _T ("0") : _T (""));
			while (n > 0) {
				_s += (TCHAR) ((n % 10) + _T ('0'));
				n /= 10;
			}
			_s.reverse_self ();
			_o.m_str.insert (_o.m_str.begin (), _s.m_str.begin (), _s.m_str.end ());
			return _o;
		}
		friend String &operator<< (uintptr_t &n, String &_o) {
			n = 0;
			if (_o.m_str.size () == 0)
				return _o;
			size_t i = 0;
			for (; i < _o.m_str.size () && _o.m_str[i] >= _T ('0') && _o.m_str[i] <= _T ('9'); ++i)
				n = n * 10 + (_o.m_str[i] - _T ('0'));
			_o.m_str.erase (_o.m_str.begin (), _o.m_str.begin () + i);
			return _o;
		}
		//
		friend std::ostream &operator<< (std::ostream &_stm, String &_s) { _stm << _s.stra (); return _stm; }
		friend std::wostream &operator<< (std::wostream &_stm, String &_s) { _stm << _s.strw (); return _stm; }
		//
		size_t find (TCHAR _ch, size_t _off = 0) { return m_str.find (_ch, _off); }
		size_t find (std::string_view _s, size_t _off = 0) {
#ifdef _UNICODE
			std::wstring _tmp_s = Encoding::gb18030_to_utf16 (_s);
			return find (_tmp_s, _off);
#else
			return m_str.find (_s, _off);
#endif
		}
		size_t find (std::wstring_view _s, size_t _off = 0) {
#ifdef _UNICODE
			return m_str.find (_s, _off);
#else
			std::string _tmp_s = Encoding::utf16_to_gb18030 (_s);
			return find (_tmp_s, _off);
#endif
		}
		size_t rfind (TCHAR _ch, size_t _off = 0) { return m_str.rfind (_ch, _off); }
		size_t rfind (std::string_view _s, size_t _off = 0) {
#ifdef _UNICODE
			std::wstring _tmp_s = Encoding::gb18030_to_utf16 (_s);
			return rfind (_tmp_s, _off);
#else
			return m_str.rfind (_s, _off);
#endif
		}
		size_t rfind (std::wstring_view _s, size_t _off = 0) {
#ifdef _UNICODE
			return m_str.rfind (_s, _off);
#else
			std::string _tmp_s = Encoding::utf16_to_gb18030 (_s);
			return rfind (_tmp_s, _off);
#endif
		}
		//
		String trim_left () const { String _s (this); _s.m_str.erase (0, _s.m_str.find_first_not_of (_T (' '))); return _s; }
		String trim_right () const { String _s (this); _s.m_str.erase (_s.m_str.find_last_not_of (' ') + 1); return _s; }
		String trim () const { return trim_left ().trim_right_self (); }
		String upper () const {
			String _s (this);
			//std::transform (_s.m_str.begin (), _s.m_str.end (), _s.m_str.begin (), ::toupper);
			for (size_t i = 0, size = _s.m_str.size (); i < size; ++i) {
				if (_s.m_str [i] >= _T ('a') && _s.m_str [i] <= _T ('z'))
					_s.m_str [i] = _s.m_str [i] - _T ('a') + _T ('A');
			}
			return _s;
		}
		String lower () const {
			String _s (this);
			//std::transform (_s.m_str.begin (), _s.m_str.end (), _s.m_str.begin (), ::tolower);
			for (size_t i = 0, size = _s.m_str.size (); i < size; ++i) {
				if (_s.m_str [i] >= _T ('A') && _s.m_str [i] <= _T ('Z'))
					_s.m_str [i] = _s.m_str [i] - _T ('A') + _T ('a');
			}
			return _s;
		}
		String reverse () const {
			String _s (this);
			size_t size = _s.m_str.size ();
			for (size_t i = 0; i < size / 2; ++i) {
				TCHAR ch = _s.m_str [i];
				_s.m_str [i] = _s.m_str [size - i - 1];
				_s.m_str [size - i - 1] = ch;
			}
			return _s;
		}
		String replace (std::string_view _src, std::string_view _dest) const {
			String _s (this);
#ifdef _UNICODE
			std::wstring _tmp_src = tool_Encoding::gb18030_to_utf16 (_src);
			std::wstring _tmp_dest = tool_Encoding::gb18030_to_utf16 (_dest);
			return replace (_tmp_src, _tmp_dest);
#else
			size_t pos = _s.m_str.find (_src);
			while (pos != std::string::npos) {
				_s.m_str.replace (pos, _src.size (), _dest);
				pos = _src.find (_src, pos + 2);
			}
			return _s;
#endif
		}
		String replace (std::wstring_view _src, std::wstring_view _dest) const {
			String _s (this);
#ifdef _UNICODE
			size_t pos = _s.m_str.find (_src);
			while (pos != std::wstring::npos) {
				_s.m_str.replace (pos, _src.size (), _dest);
				pos = _src.find (_src, pos + 2);
			}
			return _s;
#else
			std::string _tmp_src = Encoding::utf16_to_gb18030 (_src);
			std::string _tmp_dest = Encoding::utf16_to_gb18030 (_dest);
			return replace (_tmp_src, _tmp_dest);
#endif
		}
		String replace (TCHAR _src, TCHAR _dest) const {
			String _s (this);
			size_t pos = _s.m_str.find (_src);
			while (pos != string_t::npos) {
				_s.m_str [pos] = _src;
				pos = _s.m_str.find (_src);
			}
			return _s;
		}
		//
		String &trim_left_self () { m_str.erase (0, m_str.find_first_not_of (_T (' '))); return *this; }
		String &trim_right_self () { m_str.erase (m_str.find_last_not_of (' ') + 1); return *this; }
		String &trim_self () { return trim_left_self ().trim_right_self (); }
		String &upper_self () {
			//std::transform (m_str.begin (), m_str.end (), m_str.begin (), ::toupper);
			for (size_t i = 0; i < m_str.size (); ++i) {
				if (m_str [i] >= _T ('a') && m_str [i] <= _T ('z'))
					m_str [i] = m_str [i] - _T ('a') + _T ('A');
			}
			return *this;
		}
		String &lower_self () {
			//std::transform (m_str.begin (), m_str.end (), m_str.begin (), ::tolower);
			for (size_t i = 0; i < m_str.size (); ++i) {
				if (m_str [i] >= _T ('A') && m_str [i] <= _T ('Z'))
					m_str [i] = m_str [i] - _T ('A') + _T ('a');
			}
			return *this;
		}
		String &reverse_self () {
			size_t size = m_str.size ();
			for (size_t i = 0; i < size / 2; ++i) {
				TCHAR ch = m_str [i];
				m_str [i] = m_str [size - i - 1];
				m_str [size - i - 1] = ch;
			}
			return *this;
		}
		String &replace_self (std::string_view _src, std::string_view _dest) {
#ifdef _UNICODE
			std::wstring _tmp_src = tool_Encoding::gb18030_to_utf16 (_src);
			std::wstring _tmp_dest = tool_Encoding::gb18030_to_utf16 (_dest);
			return replace_self (_tmp_src, _tmp_dest);
#else
			size_t pos = m_str.find (_src);
			while (pos != std::string::npos) {
				m_str.replace (pos, _src.size (), _dest);
				pos = _src.find (_src, pos + 2);
			}
			return *this;
#endif
		}
		String &replace_self (std::wstring_view _src, std::wstring_view _dest) {
#ifdef _UNICODE
			size_t pos = m_str.find (_src);
			while (pos != std::wstring::npos) {
				m_str.replace (pos, _src.size (), _dest);
				pos = _src.find (_src, pos + 2);
			}
			return *this;
#else
			std::string _tmp_src = Encoding::utf16_to_gb18030 (_src);
			std::string _tmp_dest = Encoding::utf16_to_gb18030 (_dest);
			return replace_self (_tmp_src, _tmp_dest);
#endif
		}
		String &replace_self (TCHAR _src, TCHAR _dest) {
			size_t pos = m_str.find (_src);
			while (pos != string_t::npos) {
				m_str [pos] = _src;
				pos = m_str.find (_src);
			}
			return *this;
		}
		//
		std::vector<String> split (TCHAR _sp = _T (' '), bool no_empty = true) {
			size_t start = 0, start_find = 0;
			std::vector<String> v;
			while (start_find < m_str.size ()) {
				size_t p = m_str.find (_sp, start_find);
				if (p == string_t::npos) p = m_str.size ();
				if (!no_empty || p > start)
					v.push_back (m_str.substr (start, p - start));
				start = start_find = p + 1;
			}
			return v;
		}
		std::vector<String> split (string_view_t _sp = _T (" "), bool no_empty = true) {
			size_t start = 0, start_find = 0;
			std::vector<String> v;
			while (start_find < m_str.size ()) {
				size_t p = m_str.find (_sp, start_find);
				if (p == string_t::npos) p = m_str.size ();
				if (!no_empty || p > start)
					v.push_back (m_str.substr (start, p - start));
				start = start_find = p + _sp.size ();
			}
			return v;
		}
		std::vector<String> match_regex (std::string _re) {
			std::string _src = stra ();
			//std::string err = "";
			std::vector<String> v;
			try {
				std::regex r (_re);
				std::smatch m;
				std::string::const_iterator _begin = _src.cbegin (), _end = _src.cend ();
				while (std::regex_search (_begin, _end, m, r)) {
					v.push_back (m [0].str ());
					_begin = m [0].second;
				}
			//} catch (std::exception &e) {
			//	err = e.what ();
			} catch (...) {
			//	err = "未知错误。";
			}
			return v;
		}
		static String format (const char *_fmt, ...) {
			std::string str_result = "";
			if (!_fmt || !*_fmt)
				return str_result;
			try {
				va_list ap;
#ifndef __GNUC__
				//来源：http://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
				size_t final_n, n = lstrlenA (_fmt) * 2;
				std::unique_ptr<char []> formatted;
				while (true) {
					formatted.reset (new char [n]);
					va_start (ap, _fmt);
					final_n = _vsnprintf_s (&formatted [0], n, _TRUNCATE, _fmt, ap);
					va_end (ap);
					if (final_n < 0 || final_n >= n)
						n += abs ((int) (final_n - n + 1));
					else
						break;
				}
				str_result = formatted.get ();
#else //__GNUC__
				char *buf = nullptr;
				va_start (ap, _fmt);
				int iresult = vasprintf (&buf, _fmt, ap);
				va_end (ap);
				if (buf) {
					if (iresult >= 0) {
						iresult = strlen (buf);
						str_result.append (buf, iresult);
					}
					free (buf);
				}
#endif //__GNUC__
			} catch (...) {
			}
			return str_result;
		}
		static String format (const wchar_t *_fmt, ...) {
			std::wstring str_result = L"";
			if (!_fmt || !*_fmt)
				return str_result;
			try {
				va_list ap;
#ifndef __GNUC__
				//来源：http://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
				size_t final_n, n = lstrlenW (_fmt) * 2;
				std::unique_ptr<wchar_t []> formatted;
				while (true) {
					formatted.reset (new wchar_t [n]);
					va_start (ap, _fmt);
					final_n = _vsnwprintf_s (&formatted [0], n, _TRUNCATE, _fmt, ap);
					va_end (ap);
					if (final_n < 0 || final_n >= n)
						n += abs ((int) (final_n - n + 1));
					else
						break;
				}
				str_result = formatted.get ();
#else //__GNUC__
				wchar_t *buf = nullptr;
				va_start (ap, _fmt);
				int iresult = vswprintf (&buf, _fmt, ap);
				va_end (ap);
				if (buf) {
					if (iresult >= 0) {
						iresult = strlen (buf);
						str_result.append (buf, iresult);
					}
					free (buf);
				}
#endif //__GNUC__
			} catch (...) {
			}
			return str_result;
		}
		static size_t npos;

	private:
		string_t m_str;
	};
}

#if _HAS_CXX17
inline namespace _faw {
	[[nodiscard]] ::faw::String operator "" _fs (const char *_s, size_t _len) noexcept { return ::faw::String (_s, (size_t) _len); }
	[[nodiscard]] ::faw::String operator "" _fs (const wchar_t *_s, size_t _len) noexcept { return ::faw::String (_s, (size_t) _len); }
}
#endif



#endif //FAWLIB__STRING_HPP__
