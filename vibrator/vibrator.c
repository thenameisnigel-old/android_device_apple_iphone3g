/*
 * iPhone 3G Vibrator
 *
 * Copyright 2010 iDroid Project
 * Last modified 19/05/11
 *
 * This file is part of iDroid. An android distribution for Apple products.
 * For more information, please visit http://www.idroidproject.org/.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <hardware_legacy/vibrator.h>

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int sendit(int timeout_ms)
{
		int nwr, ret, fd;
		char value[20];

		fd = open("/sys/class/timed_output/vibrator/enable", O_RDWR);
		if(fd < 0)
			return errno;

		nwr = sprintf(value, "%d\n", timeout_ms);

		ret = write(fd, value, nwr);
		close(fd);
		return (ret == nwr) ? 0 : -1;
}
