/*
 * Copyright (C) 2008 The Android Open Source Project
 * Copyright (C) 2011 The iDroid Project <http://www.idroidproject.org>
 * Based heavily on work by Alexey Roslyakov <alexey.roslyakov@newsycat.com> which is Copyright (C) 2010, 2011 Nitdroid Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#define LOG_TAG "sensors"
#define SENSORS_SERVICE_NAME "sensors"

#include <cutils/log.h>

#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/poll.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/select.h>
#include <linux/netlink.h>

#include <hardware/sensors.h>
#include <cutils/native_handle.h>
#include <cutils/sockets.h>
#include <cutils/properties.h>

/******************************************************************************/
#define ID_BASE SENSORS_HANDLE_BASE
#define ID_ACCELERATION (ID_BASE+0)

#define DEFAULT_THRESHOLD 100
#define SYSFS_PATH "/sys/devices/i2c-0/0-003a/"

static int sensor_fd = -1;
static float delay = 10000;

/******************************************************************************/
/*
 * the following is the list of all supported sensors
 */
static const struct sensor_t sensors_list[] =
{
    {
        .name = "LIS331DL",
        .vendor = "STMicroelectronics",
        .version = 1,
        .handle = ID_ACCELERATION,
        .type = SENSOR_TYPE_ACCELEROMETER,
        .maxRange = (GRAVITY_EARTH * 2.3f),
        .resolution = (GRAVITY_EARTH * 2.3f) / 128.0f,
        .power = 0.4f,
		.minDelay = 10000,
        .reserved = {},
	},
};

static int sensors_get_list(struct sensors_module_t *module,
                            struct sensor_t const** list)
{
    *list = sensors_list;
    return 1;
}

static int sensors_set_delay_idroid(struct sensors_poll_device_t *dev, int handle, int64_t ns)
{
	delay = ns/1000;
	return 0;
}

/** Close the sensors device */
static int sensors_close_idroid(struct hw_device_t *dev)
{
    struct sensors_control_device_t *device_control = (void *) dev;
    LOGD("%s\n", __func__);
    if (sensor_fd > 0) {
        close(sensor_fd);
        sensor_fd = -1;
    }
    free(device_control);
    return 0;
}

static int sensors_activate_idroid(struct sensors_poll_device_t *dev, int handle, int enabled)
{
    if (1) {
		if (sensor_fd < 0) {
        	sensor_fd = open(SYSFS_PATH "position", O_RDONLY | O_NONBLOCK);
        	if (sensor_fd < 0) {
            	LOGE("Opening position failed in %s: %s", __FUNCTION__, strerror(errno));
            	return -1;
        	}
    	}
   }

    LOGD("%s\n", __func__);
    return 0;
}

static int sensors_poll_idroid(struct sensors_poll_device_t *dev, sensors_event_t* event, int count)
{
    fd_set rfds;
    char coord[20];
    int ret, fd;
    struct timeval timeout;

    fd = sensor_fd;
    if (fd < 1) {
        LOGE("Bad position file descriptor: %d", fd);
        return -1;
    }

    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);
	
	usleep(delay);
	
    do {
        timeout.tv_sec = 0;
        timeout.tv_usec = 1000000;
        ret = select(fd + 1, &rfds, NULL, NULL, &timeout);
    } while (ret < 0 && errno == EINTR);

    if (ret < 0) {
        LOGE("%s select error: %s", __func__, strerror(errno));
        return -errno;
    }

    lseek(fd, 0, SEEK_SET);
    ret = read(fd, coord, sizeof(coord));
    if (ret < 0) {
        LOGE("%s read error: %s", __func__, strerror(errno));
        return -errno;
    }

    int x = 0, y = 0, z = 0;
    sscanf(coord, "%d, %d, %d\n", &x, &y, &z);
	/* nickp666: I know this is incredibly fucking retarded, but for the moment it will have to do, I dont have a lot of time right now, and this works so bite me you fuckers!
	 * --BEGIN FILTHY HAXX--
	 */
	event->acceleration.x = (signed char) x * (GRAVITY_EARTH / 64.0f);
	event->acceleration.y = (signed char) y * (GRAVITY_EARTH / 64.0f);
	event->acceleration.z = (signed char) z * (GRAVITY_EARTH / 64.0f);
	/**
	 * --END FILTHY HAXX--
	 */
	event->timestamp = 0;
	event->version = sizeof(struct sensors_event_t);
	event->type = ID_ACCELERATION;

    return 1;
}

/******************************************************************************/

/**
 * module methods
 */

/** Open a new instance of a sensors device using name */
static int open_sensors(const struct hw_module_t* module, char const* name,
                        struct hw_device_t** device)
{
    int status = -EINVAL;

    if (!strcmp(name, SENSORS_HARDWARE_POLL)) {
        struct sensors_poll_device_t *dev =
            malloc(sizeof(*dev));
        memset(dev, 0, sizeof(*dev));

        dev->common.tag = HARDWARE_DEVICE_TAG;
        dev->common.version = 0;
        dev->common.module = (struct hw_module_t*)module;
        dev->common.close = sensors_close_idroid;
        dev->activate = sensors_activate_idroid;
        dev->setDelay = sensors_set_delay_idroid;
        dev->poll = sensors_poll_idroid;
		
        *device = &dev->common;
        status = 0;
    }
    return status;
}

static struct hw_module_methods_t sensors_module_methods =
{
    .open =  open_sensors,
};

/*
 * The Sensors Hardware Module
 */
struct sensors_module_t HAL_MODULE_INFO_SYM =
{
    .common = {
        .tag           = HARDWARE_MODULE_TAG,
        .version_major = 1,
        .version_minor = 0,
        .id            = SENSORS_HARDWARE_MODULE_ID,
        .name          = "iDroid Sensors Module",
        .author        = "Nick Pack <nick@nickpack.com>",
        .methods       = &sensors_module_methods,
    },
    .get_sensors_list = sensors_get_list
};