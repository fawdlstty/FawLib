#////////////////////////////////////////////////////////////////////////////////
//
// Class Name:  Directory
// Description: 文件夹类
// Class URI:   https://github.com/fawdlstty/FawLib
// Author:      Fawdlstty
// Author URI:  https://www.fawdlstty.com/
// License:     MIT
// Last Update: Jan 13, 2019
//
////////////////////////////////////////////////////////////////////////////////

#ifndef FAWLIB__DIRECTORY_HPP__
#define FAWLIB__DIRECTORY_HPP__



#include <string>
#include <Windows.h>

#include "String.hpp"



namespace faw {
	class Directory {
		Directory () {}
	public:
		static bool exist (LPCTSTR _path) {
			DWORD _attr = ::GetFileAttributes (_path);
			return (_attr != INVALID_FILE_ATTRIBUTES && _attr & FILE_ATTRIBUTE_DIRECTORY);
		}
		static bool create (LPCTSTR _path, DWORD _attr = 0) {
			bool bRet = (exist (_path) ? true : !!::CreateDirectory (_path, NULL));
			if (bRet) {
				_attr &= (FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_DEVICE | FILE_ATTRIBUTE_NORMAL);
				if (_attr)
					::SetFileAttributes (_path, _attr);
			}
			return bRet;
		}
		static String get_subpath (String _path) {
			size_t _p = _path.rfind_any ({ _T ('/'), _T ('\\') });
			if (_p == _path.size () - 1) {
				_path.left_self (_path.size () - 1);
				_p = _path.rfind_any ({ _T ('/'), _T ('\\') });
			}
			if (_p == String::_npos)
				return _T ("");
			return _path.substr (0, _p + 1);
		}
		static String get_filename (String _path) {
			size_t _p = _path.rfind_any ({ _T ('/'), _T ('\\') });
			if (_p == String::_npos)
				return _path;
			return _path.substr (_p + 1);
		}
		static String get_last_folder (String _path) {
			size_t _p = _path.rfind_any ({ _T ('/'), _T ('\\') });
			if (_p == _path.size () - 1) {
				_path.left_self (_path.size () - 1);
				_p = _path.rfind_any ({ _T ('/'), _T ('\\') });
			}
			if (_p == String::_npos)
				return _path;
			return _path.substr (_p + 1);
		}
		static String get_current_file () {
			String _s { ::GetCommandLine () };
			TCHAR _end_ch = _T (' ');
			if (_s[0] == _T ('"'))
				_end_ch << _s;
			return _s.left (_s.find (_end_ch));
		}
		static String get_current_path () {
			String _s = get_current_file ();
			size_t _p = _s.rfind_any ({ _T ('/'), _T ('\\') });
			return _s.left (_p + 1);
		}
		static String append_folder (String _path, String _folder) {
			String s { _path };
			if (s.find_any ({ _T ('/'), _T ('\\') }) != s.size () - 1)
				s += _T ('\\');
			s += _folder;
			return s;
		}
	};
}



#endif //FAWLIB__DIRECTORY_HPP__
