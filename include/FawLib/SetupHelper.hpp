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



#include <functional>
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
		size_t install_uncompress (String _app_path, HINSTANCE hInstance, LPCTSTR _resType, LPCTSTR _resId, LPCSTR _zipPwd = nullptr, std::function<void (size_t)> _callback = [] (size_t) {}) {
			size_t _last = 0;
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
							size_t _moment = i * 100 / (size_t) _file_count;
							if (_moment != _last)
								_callback (_last = _moment);
						}
						_callback (_last = 100);
						::CloseZip (hZip);
					}
				}
				::FreeResource (hResource);
			}
			return 0;
		}

		// 设置注册表
		bool install_initRegester (String _app_path, String _exe_path, String _ico_path, String _publisher, String _version, DWORD _estimated_size) {
			_app_path.replace_self (_T ("/"), _T ("\\"));
			if (*_app_path.crbegin () != _T ('\\'))
				_app_path += _T ('\\');

			// HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\filezilla.exe
			_exe_path.replace_self (_T ('/'), _T ('\\'));
			String _exe_file = Directory::get_filename (_exe_path);
			String _reg_path = String::format (_T ("HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\%s"), _exe_file.c_str ());
			String _path_value = String::format (_T ("%s%s"), _app_path.c_str (), _exe_path.c_str ());
			bool b = Register::set_path (_reg_path.strw (), _path_value.strw ());
			_path_value = Directory::get_subpath (_path_value.str ());
			b = Register::set_key (_reg_path.strw (), L"Path", _path_value.strw ());

			// 计算机\HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\GitHubDesktop
			_reg_path = String::format (_T ("HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\%s"), m_app_name.c_str ());
			std::wstring _reg_path_w = _reg_path.strw ();
			b = Register::set_path (_reg_path_w, L"");
			_ico_path = String::format (_T ("%s%s"), _path_value.c_str (), _ico_path.c_str ());
			b = Register::set_key (_reg_path_w, L"DisplayIcon", _ico_path.strw ());
			b = Register::set_key (_reg_path_w, L"DisplayName", m_app_name.strw ());
			b = Register::set_key (_reg_path_w, L"DisplayVersion", _version.strw ());
			b = Register::set_key (_reg_path_w, L"EstimatedSize", (DWORD) _estimated_size);
			char _buf_time [16];
			time_t t = time (NULL);
			strftime (_buf_time, 16, "%Y%m%d", localtime (&t));
			String _time_value { _buf_time };
			b = Register::set_key (_reg_path_w, L"InstallDate", _time_value.strw ());
			b = Register::set_key (_reg_path_w, L"NoModify", (DWORD) 1);
			b = Register::set_key (_reg_path_w, L"NoRepair", (DWORD) 1);
			b = Register::set_key (_reg_path_w, L"Publisher", _publisher.strw ());
			b = Register::set_key (_reg_path_w, L"InstallLocation", _path_value.strw ());
			_path_value += _T ("uninstall.exe");
			b = Register::set_key (_reg_path_w, L"UninstallString", _path_value.strw ());
			//b = Register::set_key (_reg_path_w, L"QuietUninstallString", _path_value.strw ());
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
