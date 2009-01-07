%define module_api %(qore --module-api 2>/dev/null)
%define module_dir %(qore --module-dir 2>/dev/null)

%if 0%{?sles_version}

%define dist .sles{?sles_version}

%else
%if 0%{?suse_version}

%if 0%{?suse_version} == 1110
%define dist .opensuse11_1
%endif

%if 0%{?suse_version} == 1100
%define dist .opensuse11
%endif

%if 0%{?suse_version} == 1030
%define dist .opensuse10_3
%endif

%if 0%{?suse_version} == 1020
%define dist .opensuse10_2
%endif

%if 0%{?suse_version} == 1010
%define dist .suse10_1
%endif

%if 0%{?suse_version} == 1000
%define dist .suse10
%endif

%if 0%{?suse_version} == 930
%define dist .suse9_3
%endif

%endif
%endif

Summary: QT Core Module for Qore
Name: qore-qt
Version: 0.0.3
Release: 1%{dist}
License: GPL
Group: Development/Languages
URL: http://www.qoretechnologies.com/qore
Source: http://prdownloads.sourceforge.net/qore/%{name}-%{version}.tar.gz
Source0: %{name}-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root
Requires: /usr/bin/env
Requires: qore-module-api-%{module_api}
BuildRequires: gcc-c++
BuildRequires: qore-devel
BuildRequires: qore
BuildRequires: qt-devel >= 4.3.1

%description
This RPM will not be created as there are no files; it is just a wrapper for
the packages below


%package core-module
Summary: QT4 core module for Qore
Group: Development/Languages
License: GPL
Requires: qore-module-api-%{module_api}
Requires: qt-x11 >= 4.3.1

%description core-module
This module provides functionality enabling qore scripts/programs to use
functionality provided by the QT4 core library.


%files core-module
%defattr(-,root,root,-)
%{_libdir}/libqore-qt-core.so.0.0.0
%{_libdir}/libqore-qt-core.so.0
%{module_dir}/qt-core-api-%{module_api}.qmod
%doc COPYING README RELEASE-NOTES ChangeLog AUTHORS docs/qt-modules-doc.html

%post core-module
ldconfig %{_libdir}

%postun core-module
ldconfig %{_libdir}

%package gui-module
Summary: QT4 GUI module for Qore
Group: Development/Languages
License: GPL
Requires: qore-module-api-%{module_api}
Requires: qore-qt-core-module = %{version}-%{release}
Requires: qt-x11 >= 4.3.1

%description gui-module
This module provides functionality enabling qore scripts/programs to use
functionality provided by the QT4 GUI library.


%files gui-module
%defattr(-,root,root,-)
%{module_dir}/qt-gui-api-%{module_api}.qmod
%{_libdir}/libqore-qt-gui.so.0.0.0
%{_libdir}/libqore-qt-gui.so.0

%post gui-module
ldconfig %{_libdir}

%postun gui-module
ldconfig %{_libdir}

%package opengl-module
Summary: QT4 opengl module for Qore
Group: Development/Languages
License: GPL
Requires: qore-module-api-%{module_api}
Requires: qore-opengl-module = %{version}-%{release}
Requires: qore-qt-gui-module = %{version}-%{release}
Requires: qt-x11 >= 4.3.1

%description opengl-module
This module provides functionality enabling qore scripts/programs to use
functionality provided by the QT4 OpenGL library.


%files opengl-module
%defattr(-,root,root,-)
%{module_dir}/qt-opengl-api-%{module_api}.qmod

%package svg-module
Summary: QT4 SVG module for Qore
Group: Development/Languages
License: GPL
Requires: qore-module-api-%{module_api}
Requires: qore-qt-gui-module = %{version}-%{release}
Requires: qt-x11 >= 4.3.1

%description svg-module
This module provides functionality enabling qore scripts/programs to use 
functionality provided by the QT4 SVG library.


%files svg-module
%defattr(-,root,root,-)
%{module_dir}/qt-svg-api-%{module_api}.qmod

%if 0%{?suse_version}
%debug_package
%endif

%prep
%setup -q
%ifarch x86_64 ppc64 x390x
c64=--enable-64bit
%endif
./configure RPM_OPT_FLAGS="$RPM_OPT_FLAGS" --prefix=/usr --disable-debug $c64

%build
%{__make}

%install
mkdir -p $RPM_BUILD_ROOT/%{module_dir}
mkdir -p $RPM_BUILD_ROOT/usr/share/doc/qore-qt
make install DESTDIR=$RPM_BUILD_ROOT
rm -f $RPM_BUILD_ROOT/%{_libdir}/libqore-qt-core.so
rm -f $RPM_BUILD_ROOT/%{_libdir}/libqore-qt-core.la
rm -f $RPM_BUILD_ROOT/%{_libdir}/libqore-qt-gui.so
rm -f $RPM_BUILD_ROOT/%{_libdir}/libqore-qt-gui.la

%clean
rm -rf $RPM_BUILD_ROOT

%changelog
* Wed Jan 7 2009 David Nichols <david_nichols@users.sourceforge.net>
- updated to version 0.0.3

* Wed Dec 3 2008 David Nichols <david_nichols@users.sourceforge.net>
- updated to v0.0.2, packaging fixes

* Tue Sep 2 2008 David Nichols <david_nichols@users.sourceforge.net>
- initial spec file for separate qt release
