# $Id$
#
# Special processing of paths depending on whether --prefix,
# --sysconfdir or --localstatedir arguments were given.

AC_DEFUN([ACX_PREFIXHACK],[
	case "$prefix" in
		NONE)
			case "$sysconfdir" in
				'${prefix}/etc')
					sysconfdir=/etc
					AC_MSG_NOTICE([sysconfdir set to $sysconfdir])
					;;
			esac
			case "$localstatedir" in
				'${prefix}/var')
					localstatedir=/var
					AC_MSG_NOTICE([localstate set to $localstatedir])
					;;
			esac
			;;
	esac
])
