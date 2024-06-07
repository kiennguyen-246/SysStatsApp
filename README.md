# System Resources Usage Logger

## Description

SysStatsApp is a simple program that logged out the current usage of CPU and RAM to the console interface. To get the resources usage, it access the files located in the `~/proc/` folder of Linux system, namely `~/proc/stat` containing CPU usage information, and `~/proc/meminfo` for RAM usage. 

A shared library is also built, containing functions that provide information about the system resources.

The resository consists of the source code for the program together with its shared libraries, and a Linux service implementing the program as a process. The service, program and shared library are all packaged to a Debian package.

## Install

First, clone this repo into some directory.

Then, run `sudo dpkg -i sysstatsapp.deb` to install the Debian package. After installation, the binary program, the shared library, and a service file will be installed and placed in different locations of your system:
- `sysstatsapp.sh` will be installed to `~/bin/`
- `libsysstats.so` will be installed to `~/lib/`
- `sysstatsapp.service` will be installed to `~etc/systemd/system`

To start the service, run `sudo systemctl start sysstatsapp`.

To view the output, run `journalctl -u sysstatsapp`

The user can also run `~/bin/sysstatsapp.sh` to directly start the resources usage logging program and see the output.
