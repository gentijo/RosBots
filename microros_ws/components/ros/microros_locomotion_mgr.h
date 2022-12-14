#ifndef  __ROS_LOCOMOTION_MGR__
#define  __ROS_LOCOMOTION_MGR__


#include <string.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include "interfaces/if_ros_subscription.h"
#include "interfaces/if_ros_publisher.h"

#include "interfaces/if_locomotion_drive.h"
#include "interfaces/if_rtos.h"
#include "interfaces/if_microros_app.h"
#include "interfaces/if_ros_app.h"


#include "geometry_msgs/msg/twist.h"

enum direction_t {
	forward = 1,
	backward = 2,
	right = 3,
	left =4
};

struct LocomotionCmd
 {
    uint8_t direction;
    uint8_t speed;
	uint8_t duration;

 };

typedef struct LocomotionCmd locomotion_cmd_t;

class microros_locomotion_mgr : public if_ros_subscription {
    public:
        microros_locomotion_mgr() {
            printf("Locomotion mgr create");
        };

        void attach();
        void release();

        microros_locomotion_mgr     *setDriveController( if_locomotion_drive *driveCtrl) {
		    this->m_driveCtrl = driveCtrl;
            printf("\r\nSetting Drive Control %p for LocMgr %p\r\n", this->m_driveCtrl, this);
		    return this; 
        };

        if_locomotion_drive         *getDriveController() { 
            printf("\r\nGetting Drive Control %p for LocMgr %p\r\n", this->m_driveCtrl, this);
            return m_driveCtrl; 
        }

    private:
        
        geometry_msgs__msg__Twist   m_velocity_msg;
        rcl_subscription_t          m_velocity_subscription;

        if_locomotion_drive*        m_driveCtrl;

    private:
        rtos_queue_handle_t             m_locomotionCmdQueue;
        static microros_locomotion_mgr  *s_loc_mgr;

        static void                 locomotion_drive_task(void * arg);
	    static void                 sub_velocity_callback(const void *msgin);

};

#endif