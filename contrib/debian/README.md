
Debian
====================
This directory contains files used to package dexmaild/dexmail-qt
for Debian-based Linux systems. If you compile dexmaild/dexmail-qt yourself, there are some useful files here.

## dexmail: URI support ##


dexmail-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install dexmail-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your dexmailqt binary to `/usr/bin`
and the `../../share/pixmaps/dexmail128.png` to `/usr/share/pixmaps`

dexmail-qt.protocol (KDE)

