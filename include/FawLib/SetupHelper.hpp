////////////////////////////////////////////////////////////////////////////////
//
// Class Name:  SetupHelper
// Description: 安装包帮助类
// Class URI:   https://github.com/fawdlstty/FawLib
// Author:      Fawdlstty
// Author URI:  https://www.fawdlstty.com/
// License:     MIT
// Last Update: Jan 16, 2019
//
////////////////////////////////////////////////////////////////////////////////

#ifndef FAWLIB__SETUP_HELPER_HPP__
#define FAWLIB__SETUP_HELPER_HPP__



#include <Windows.h>

#include "Encoding.hpp"
#include "String.hpp"
#include "Register.hpp"
#include "Directory.hpp"
#include "File.hpp"
#include "unzip.h"



namespace faw {
	class SetupHelper {
	public:
		SetupHelper (LPCTSTR _app_name): m_app_name (_app_name) {}

		// 资源压缩包解压缩（zip压缩文件）
		size_t install_uncompress (HINSTANCE hInstance, LPCTSTR _resType, LPCTSTR _resId, LPCTSTR _destPath, LPCSTR _zipPwd = nullptr) {
			HRSRC hResource = ::FindResource (hInstance, _resId, _resType);
			if (hResource != NULL) {
				DWORD dwSize = 0;
				HGLOBAL hGlobal = ::LoadResource (hInstance, hResource);
				if (hGlobal) {
					DWORD dwSize = ::SizeofResource (hInstance, hResource);
					if (dwSize) {
						LPVOID pBuffer = ::LockResource (hGlobal);
						HZIP hZip = ::OpenZip (pBuffer, dwSize, _zipPwd);
						ZIPENTRY ze = { 0 };
						GetZipItem (hZip, -1, &ze);
						int _file_count = ze.index;
						String _path { _destPath };
						_path.replace_self (_T ("\\"), _T ("/"));
						for (int i = 0; i < _file_count; ++i) {
							GetZipItem (hZip, i, &ze);
							String _tmp = String::format (_T ("%s%s"), _path.c_str (), ze.name);
							if (ze.attr & FILE_ATTRIBUTE_DIRECTORY) {
								if (!Directory::exist (_tmp.c_str ()))
									Directory::create (_tmp.c_str (), ze.attr);
							} else {
								if (File::exist (_tmp.c_str ()))
									File::remove (_tmp.c_str ());
								UnzipItem (hZip, i, _tmp.c_str ());
								ze.attr &= (FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_DEVICE | FILE_ATTRIBUTE_NORMAL);
								if (ze.attr)
									::SetFileAttributes (_tmp.c_str (), ze.attr);
							}
						}
						::CloseZip (hZip);
					}
				}
				::FreeResource (hResource);
			}
			return 0;
		}

		// 设置注册表
		bool install_initRegester () {
			return false;
		}

		// 卸载软件
		bool uninstall () {

		}

	private:
		string_t m_app_name = _T ("");
	};
}



#endif //FAWLIB__SETUP_HELPER_HPP__
