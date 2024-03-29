/*
 *  Backend
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 * Copyright (C) 2016 EPAM Systems Inc.
 */
#include <linux/kernel.h>
#include <linux/string.h>
#include <algorithm>
#include <atomic>
#include <exception>
#include <fstream>
#include <iostream>
#include <thread>
#include <csignal>
#include <execinfo.h>
#include <getopt.h>
#include <unistd.h>
#include "Version.hpp"
#include <xen/be/Log.hpp>
#include <xen/be/Utils.hpp>
#ifdef WITH_MOCKBELIB
#include "MockBackend.hpp"
#endif
#include "DummyBackend.hpp"

using std::cout;
using std::dynamic_pointer_cast;
using std::endl;
using std::ofstream;
using std::string;
using std::this_thread::sleep_for;
using std::toupper;
using std::transform;
using std::vector;
using XenBackend::Log;
using XenBackend::Utils;

string gLogFileName;

int gRetStatus = EXIT_SUCCESS;

/*******************************************************************************
 *
 ******************************************************************************/

void segmentationHandler(int sig)
{
	void *array[20];
	size_t size;

	LOG("Main", ERROR) << "Segmentation fault!";

	size = backtrace(array, 20);

	backtrace_symbols_fd(array, size, STDERR_FILENO);

	raise(sig);
}

void registerSignals()
{
	struct sigaction act {};

	act.sa_handler = segmentationHandler;
	act.sa_flags = SA_RESETHAND;

	sigaction(SIGSEGV, &act, nullptr);
}

void waitSignals()
{
	sigset_t set;
	int signal;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGTERM);
	sigprocmask(SIG_BLOCK, &set, nullptr);

	sigwait(&set,&signal);

	if (signal == SIGTERM)
	{
		gRetStatus = EXIT_FAILURE;
	}
}

bool commandLineOptions(int argc, char *argv[])
{
	int opt = -1;

	while((opt = getopt(argc, argv, "m:d:v:l:fh?")) != -1)
	{
		switch(opt)
		{
		case 'm':
		{
			string mode = optarg;

			transform(mode.begin(), mode.end(), mode.begin(),
					  (int (*)(int))toupper);

//			if (mode == "DRM")
//			{
//				gDisplayMode = DisplayMode::DRM;
//			}
//			else if (mode == "WAYLAND")
//			{
//				gDisplayMode = DisplayMode::WAYLAND;
//			}
//			else
//			{
//				return false;
//			}

			break;
		}

		case 'd':

//			gDrmDevice = optarg;

			break;

		case 'v':

			if (!Log::setLogMask(string(optarg)))
			{
				return false;
			}

			break;

		case 'l':

			gLogFileName = optarg;

			break;

		case 'f':

			Log::setShowFileAndLine(true);

			break;

		default:

			return false;
		}
	}

	return true;
}

int main(int argc, char *argv[])
{
	try
	{
		registerSignals();

		if (commandLineOptions(argc, argv))
		{
            LOG("Main", INFO) << "backend version:  " << VERSION;
            LOG("Main", INFO) << "libxenbe version: " << Utils::getVersion();

			ofstream logFile;

			if (!gLogFileName.empty())
			{
				logFile.open(gLogFileName);
				Log::setStreamBuffer(logFile.rdbuf());
			}

#ifdef WITH_MOCKBELIB
			MockBackend mockBackend(0, 1);
#endif
#define KERN_INFO
            printf(KERN_INFO "\n dummy main +++\n");
            DummyDevPtr devprt(new DummyDev());
            DummyBackend dummybackend(devprt, "DummyDevName");

            printf(KERN_INFO " dummybackend start +++\n");
            dummybackend.start();
            printf(KERN_INFO " dummybackend start ---\n");

			waitSignals();

            printf(KERN_INFO " dummybackend stop +++\n");
            dummybackend.stop();
            printf(KERN_INFO " dummybackend stop ---\n");
			logFile.close();

            printf(KERN_INFO " dummy main ---\n");
		}
		else
		{
			cout << "Usage: " << argv[0]
				 << " [-l <file>] [-v <level>]"
				 << endl;
			cout << "\t-l -- log file" << endl;
			cout << "\t-v -- verbose level in format: "
				 << "<module>:<level>;<module:<level>" << endl;
			cout << "\t      use * for mask selection:"
				 << " *:Debug,Mod*:Info" << endl;

			gRetStatus = EXIT_FAILURE;
		}
	}
	catch(const std::exception& e)
	{
		Log::setStreamBuffer(cout.rdbuf());

		LOG("Main", ERROR) << e.what();

		gRetStatus = EXIT_FAILURE;
	}

	return gRetStatus;
}

