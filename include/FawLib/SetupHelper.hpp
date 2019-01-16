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
		size_t install_uncompress (String _app_path, HINSTANCE hInstance, LPCTSTR _resType, LPCTSTR _resId, LPCSTR _zipPwd = nullptr) {
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
						_app_path.replace_self (_T ("/"), _T ("\\"));
						if (*_app_path.crbegin () != _T ('\\'))
							_app_path += _T ('\\');
						if (!Directory::exist (_app_path.c_str ()))
							Directory::create (_app_path.c_str ());
						for (int i = 0; i < _file_count; ++i) {
							GetZipItem (hZip, i, &ze);
							String _tmp = String::format (_T ("%s%s"), _app_path.c_str (), ze.name);
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
		bool install_initRegester (String _app_path, String _exe_path) {
			_app_path.replace_self (_T ("/"), _T ("\\"));
			if (*_app_path.crbegin () != _T ('\\'))
				_app_path += _T ('\\');

			// HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\filezilla.exe
			_exe_path.replace_self (_T ('/'), _T ('\\'));
			string_t _exe_file = Directory::get_filename (_exe_path.str ());
			String _reg_path = String::format (_T ("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\%s"), _exe_file.c_str ());
			String _path_value = String::format (_T ("%s%s"), _app_path.c_str (), _exe_path.c_str ());
			Register::set_path (_reg_path.strw (), _path_value.strw ());
			_path_value = Directory::get_subpath (_path_value.str ());
			Register::set_key (_reg_path.strw (), L"Path", _path_value.strw ());

			// 计算机\HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Uninstall\GitHubDesktop
			_reg_path = String::format (_T ("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\%s"), m_app_name.c_str ());
			Register::set_path (_reg_path.strw (), L"", false);
			Register::set_key (_reg_path.strw (), L"DisplayIcon", _path_value.strw ());
			Register::set_key (_reg_path.strw (), L"DisplayName", m_app_name.strw ());
			//Register::set_key (_reg_path.strw (), L"DisplayVersion", m_app_name.strw ());
			//Register::set_key (_reg_path.strw (), L"EstimatedSize", (DWORD) 12345);
			//Register::set_key (_reg_path.strw (), L"InstallDate", L"20080808");
			Register::set_key (_reg_path.strw (), L"NoModify", (DWORD) 1);
			Register::set_key (_reg_path.strw (), L"NoRepair", (DWORD) 1);
			//Register::set_key (_reg_path.strw (), L"Publisher", L"20080808");
			Register::set_key (_reg_path.strw (), L"InstallLocation", _path_value.strw ());
			_path_value += _T ('\\');
			_path_value += _T ("uninstall.exe");
			Register::set_key (_reg_path.strw (), L"UninstallString", _path_value.strw ());
			//Register::set_key (_reg_path.strw (), L"QuietUninstallString", _path_value.strw ());
			return false;
		}

		// 创建快捷方式
		bool install_setShortcut () {

		}

		// 卸载软件
		bool uninstall () {

		}

	private:
		String m_app_name = _T ("");
	};
}



#endif //FAWLIB__SETUP_HELPER_HPP__
