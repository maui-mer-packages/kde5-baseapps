# 
# Do NOT Edit the Auto-generated Part!
# Generated by: spectacle version 0.27
# 

Name:       kde-baseapps

# >> macros
# << macros

Summary:    Collection of applications used for file and Internet browsing
Version:    4.97.0
Release:    1
Group:      System/Base
License:    GPLv2+
URL:        http://www.kde.org
Source0:    %{name}-%{version}.tar.xz
Source100:  kde-baseapps.yaml
Source101:  kde-baseapps-rpmlintrc
Requires:   kf5-filesystem
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5DBus)
BuildRequires:  pkgconfig(Qt5Xml)
BuildRequires:  pkgconfig(Qt5Network)
BuildRequires:  pkgconfig(Qt5Gui)
BuildRequires:  pkgconfig(Qt5Widgets)
BuildRequires:  pkgconfig(Qt5Concurrent)
BuildRequires:  pkgconfig(Qt5Test)
BuildRequires:  pkgconfig(Qt5PrintSupport)
BuildRequires:  pkgconfig(Qt5Script)
BuildRequires:  pkgconfig(zlib)
BuildRequires:  kf5-rpm-macros
BuildRequires:  extra-cmake-modules
BuildRequires:  qt5-tools
BuildRequires:  karchive-devel
BuildRequires:  kbookmarks-devel
BuildRequires:  kcoreaddons-devel
BuildRequires:  kconfig-devel
BuildRequires:  kconfigwidgets-devel
BuildRequires:  kdbusaddons-devel
BuildRequires:  kio-devel
BuildRequires:  kdelibs4support-devel
BuildRequires:  kparts-devel
BuildRequires:  kdesu-devel
BuildRequires:  kactivities-libs-devel
BuildRequires:  knewstuff-devel
BuildRequires:  kfilemetadata-devel
BuildRequires:  kcmutils-devel
BuildRequires:  baloo-devel
BuildRequires:  baloo-widgets-devel
BuildRequires:  phonon-qt5-devel
BuildRequires:  khtml-devel
BuildRequires:  kded-devel

%description
Collection of applications used for file and Internet browsing


%package devel
Summary:    Development files for %{name}
Group:      Development/Libraries
Requires:   %{name} = %{version}-%{release}

%description devel
The %{name}-devel package contains the files necessary to develop applications
that use %{name}.


%package doc
Summary:    Documentation and user manuals for %{name}
Group:      Documentation
Requires:   %{name} = %{version}-%{release}

%description doc
Documentation and user manuals for %{name}


%prep
%setup -q -n %{name}-%{version}

# >> setup
# << setup

%build
# >> build pre
%kf5_make
# << build pre



# >> build post
# << build post

%install
rm -rf %{buildroot}
# >> install pre
%kf5_make_install
# << install pre

# >> install post
# << install post

%post
# >> post
/bin/touch --no-create %{_datadir}/icons/hicolor &>/dev/null || :
# << post

%postun
# >> postun
if [ $1 -eq 0 ] ; then
/bin/touch --no-create %{_datadir}/icons/hicolor &>/dev/null
/usr/bin/gtk-update-icon-cache %{_datadir}/icons/hicolor &>/dev/null || :
fi
# << postun

%files
%defattr(-,root,root,-)
%doc COPYING COPYING.LIB
%{_kf5_bindir}/*
%{_kf5_plugindir}/*.so
%{_kf5_libdir}/lib*.so.*
%{_kf5_libdir}/libkdeinit5_*.so
%{_kf5_sharedir}/dolphinpart
%{_kf5_datadir}/kbookmark
%{_kf5_datadir}/konqueror
%{_kf5_servicesdir}/*
%{_kf5_servicetypesdir}/*
%{_kf5_sharedir}/appdata/
%{_kf5_sharedir}/templates/
%{_kf5_sharedir}/applications/
%{_kf5_sharedir}/config.kcfg/
%{_kf5_sharedir}/dbus-1/
%{_kf5_sharedir}/icons/hicolor/
%{_kf5_sharedir}/appdata/dolphin.appdata.xml
%{_kf5_sharedir}/kxmlgui5/dolphin/dolphinui.rc
%{_kf5_sharedir}/konqueror/*
%{_kf5_sharedir}/keditbookmarks/*
%{_kf5_configdir}/servicemenu.knsrc
# >> files
# << files

%files devel
%defattr(-,root,root,-)
%{_kf5_libdir}/libKF5Konq.so
%{_kf5_cmakedir}/*
%{_kf5_includedir}/*
%{_kf5_libdir}/lib*.so
# >> files devel
# << files devel

%files doc
%defattr(-,root,root,-)
%{_kf5_htmldir}/en/*
%{_mandir}/man1/*
# >> files doc
# << files doc
