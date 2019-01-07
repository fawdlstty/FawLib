#ifndef FAWLIB__STRING_HPP__
#define FAWLIB__STRING_HPP__



#include <iostream>
#include <tchar.h>

#include "Encoding.hpp"



namespace FawLib {
	class String {
	public:
		String () {}
		String (const char _c, size_t _len = 1) { m_str.assign (_len, _c); }
		String (const wchar_t _c, size_t _len = 1) { m_str.assign (_len, _c); }
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
		String (const std::string_view &_s): m_str (Encoding::gb18030_to_T (_s)) {}
		String (const std::wstring_view &_s): m_str (Encoding::utf16_to_T (_s)) {}
		String (const String &_s): m_str (_s.m_str) {}
		//
		String &operator= (const char *_s) { m_str = Encoding::gb18030_to_T (std::string_view (_s)); return *this; }
		String &operator= (const wchar_t *_s) { m_str = Encoding::utf16_to_T (std::wstring_view (_s)); return *this; }
		String &operator= (const std::string &_s) { m_str = Encoding::gb18030_to_T (std::string_view (_s)); return *this; }
		String &operator= (const std::wstring &_s) { m_str = Encoding::utf16_to_T (std::wstring_view (_s)); return *this; }
		String &operator= (const std::string_view &_s) { m_str = Encoding::gb18030_to_T (_s); return *this; }
		String &operator= (const std::wstring_view &_s) { m_str = Encoding::utf16_to_T (_s); return *this; }
		String &operator= (const String &_s) { m_str = _s.m_str; return *this; }
		//
		String &operator+= (const char _c) { m_str += (TCHAR) _c; return *this; }
		String &operator+= (const wchar_t _c) { m_str += (TCHAR) _c; return *this; }
		String &operator+= (const char *_s) { m_str += Encoding::gb18030_to_T (std::string_view (_s)); return *this; }
		String &operator+= (const wchar_t *_s) { m_str += Encoding::utf16_to_T (std::wstring_view (_s)); return *this; }
		String &operator+= (const std::string &_s) { m_str += Encoding::gb18030_to_T (std::string_view (_s)); return *this; }
		String &operator+= (const std::wstring &_s) { m_str += Encoding::utf16_to_T (std::wstring_view (_s)); return *this; }
		String &operator+= (const std::string_view &_s) { m_str += Encoding::gb18030_to_T (_s); return *this; }
		String &operator+= (const std::wstring_view &_s) { m_str += Encoding::utf16_to_T (_s); return *this; }
		String &operator+= (const String &_s) { m_str += _s.m_str; return *this; }
		//
		String operator+ (const char _c) { String _o (*this); _o.m_str += (TCHAR) _c; return _o; }
		String operator+ (const wchar_t _c) { String _o (*this); _o.m_str += (TCHAR) _c; return _o; }
		String operator+ (const char *_s) { String _o (*this); _o.m_str += Encoding::gb18030_to_T (std::string_view (_s)); return _o; }
		String operator+ (const wchar_t *_s) { String _o (*this); _o.m_str += Encoding::utf16_to_T (std::wstring_view (_s)); return _o; }
		String operator+ (const std::string &_s) { String _o (*this); _o.m_str += Encoding::gb18030_to_T (std::string_view (_s)); return _o; }
		String operator+ (const std::wstring &_s) { String _o (*this); _o.m_str += Encoding::utf16_to_T (std::wstring_view (_s)); return _o; }
		String operator+ (const std::string_view &_s) { String _o (*this); _o.m_str += Encoding::gb18030_to_T (_s); return _o; }
		String operator+ (const std::wstring_view &_s) { String _o (*this); _o.m_str += Encoding::utf16_to_T (_s); return _o; }
		String operator+ (const String &_s) { String _o (*this); _o.m_str += _s.m_str; return _o; }
		//
		friend String operator+ (const char _c, String &_o) { _o.m_str.insert (_o.m_str.begin (), (TCHAR) _c); }
		friend String operator+ (const wchar_t _c, String &_o) { _o.m_str.insert (_o.m_str.begin (), (TCHAR) _c); }
		friend String operator+ (const char *_s, String &_o) { String _o (_s); _o.m_str += _o; return _o; }
		friend String operator+ (const wchar_t *_s, String &_o) { String _o (_s); _o.m_str += _o; return _o; }
		friend String operator+ (const std::string &_s, String &_o) { String _o (_s); _o.m_str += _o; return _o; }
		friend String operator+ (const std::wstring &_s, String &_o) { String _o (_s); _o.m_str += _o; return _o; }
		friend String operator+ (const std::string_view &_s, String &_o) { String _o (_s); _o.m_str += _o; return _o; }
		friend String operator+ (const std::wstring_view &_s, String &_o) { String _o (_s); _o.m_str += _o; return _o; }
		//
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
		virtual ~String () {}
		//
		bool empty () const { return m_str.empty (); }
		void clear () { m_str.clear (); }
		void free () { string_t _str; _str.swap (m_str); }
		TCHAR &operator[] (size_t n) { return m_str [n]; }
		const TCHAR* c_str () const { return m_str.c_str (); }
#ifdef _UNICODE
		const char* c_astr () const { static std::string _s; _s = Encoding::T_to_gb18030 (m_str); return _s.c_str (); }
		const wchar_t* c_wstr () const { return c_str (); }
#else
		const char* c_astr () const { return c_str (); }
		const wchar_t* c_wstr () const { static std::wstring _s; _s = Encoding::T_to_utf16 (m_str); return _s.c_str (); }
#endif
		friend std::ostream &operator<< (std::ostream &_stm, const String &_s) { _stm << _s.c_astr (); return _stm; }
		friend std::wostream &operator<< (std::wostream &_stm, const String &_s) { _stm << _s.c_wstr (); return _stm; }
		//
		static String formata (const char *_fmt, ...) {
			std::string str_result;
			if (!_fmt || !*_fmt)
				return str_result;
			try {
				va_list ap;
#ifndef __GNUC__
				//来源：http://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
				ptrdiff_t final_n, n = lstrlenA (_fmt) * 2;
				std::unique_ptr<char[]> formatted;
				while (true) {
					formatted.reset (new char[n]);
					va_start (ap, _fmt);
					final_n = _vsnprintf_s (&formatted[0], n, _TRUNCATE, _fmt, ap);
					va_end (ap);
					if (final_n < 0 || final_n >= n)
						n += abs (final_n - n + 1);
					else
						break;
				}
				str_result = formatted.get ();
#else //__GNUC__
				char *buf = nullptr;
				va_start (ap, _fmt);
				int iresult = vasprintf (&buf, _fmt.c_str (), ap);
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
		static String formatw (const wchar_t *_fmt, ...) {}
		static String format (const TCHAR *_fmt, ...) {}

	private:
		string_t m_str;
	};
}

#if _HAS_CXX17
inline namespace FawLib {
	[[nodiscard]] String operator "" fs (const char *_s, size_t _len) noexcept { return String (_s, (size_t) _len); }
	[[nodiscard]] String operator "" fs (const wchar_t *_s, size_t _len) noexcept { return String (_s, (size_t) _len); }
}
#endif



#endif //FAWLIB__STRING_HPP__
