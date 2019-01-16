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
		static std::string get_subpath (std::string_view _path) {
			size_t p = _path.rfind ('/'), q = _path.rfind ('\\');
			if ((p < q && q != std::string::npos) || p == std::string::npos)
				p = q;
			if (p == std::string::npos)
				return "";
			return std::string (_path.substr (0, p));
		}
		static std::wstring get_subpath (std::wstring_view _path) {
			size_t p = _path.rfind (L'/'), q = _path.rfind (L'\\');
			if ((p < q && q != std::wstring::npos) || p == std::wstring::npos)
				p = q;
			if (p == std::wstring::npos)
				return L"";
			return std::wstring (_path.substr (0, p));
		}
		static std::string get_filename (std::string_view _path) {
			size_t p = _path.rfind ('/'), q = _path.rfind ('\\');
			if ((p < q && q != std::string::npos) || p == std::string::npos)
				p = q;
			if (p == std::string::npos)
				return std::string (_path);
			return std::string (_path.substr (p + 1));
		}
		static std::wstring get_filename (std::wstring_view _path) {
			size_t p = _path.rfind (L'/'), q = _path.rfind (L'\\');
			if ((p < q && q != std::wstring::npos) || p == std::wstring::npos)
				p = q;
			if (p == std::wstring::npos)
				return std::wstring (_path);
			return std::wstring (_path.substr (p + 1));
		}
	};
}



#endif //FAWLIB__DIRECTORY_HPP__
